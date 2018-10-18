/*

This is the core of the Ethereum Virtual Machine (EVM or just VM).

NOTES:

stack items are lazly dupilicated.
So you must never directly change a buffer from the stack,
instead you should `copy` it first

not all stack items are 32 bytes, so if the operation realies on the stack
item length then you must use util.pad(<item>, 32) first.
*/
const Buffer = require('safe-buffer').Buffer
const async = require('async')
const util = require('../../util')
const Block = require('../../block')
const lookupOpInfo = require('./opcodes.js')
const opFns = require('./opFns.js')
const exceptions = require('./exceptions.js')
const setImmediate = require('timers').setImmediate
const BN = util.BN

const ERROR = exceptions.ERROR
const VmError = exceptions.VmError

/**
 * Runs EVM code
 * @param opts
 * @param opts.account {Account} the account that the exucuting code belongs to
 * @param opts.address {Buffer}  the address of the account that is exucuting this code
 * @param opts.block {Block} the block that the transaction is part of
 * @param opts.caller {Buffer} the address that ran this code
 * @param opts.code {Buffer} the code to be run
 * @param opts.data {Buffer}  the input data
 * @param opts.gasLimit {Buffer}
 * @param opts.origin {Buffer} the address where the call originated from
 * @param opts.value {Buffer} the amount the being transfered
 * @param cb {Function}
 */
module.exports = function (opts, cb) {
  var self = this
  var stateManager = self.stateManager

  var block = opts.block || new Block()

  // VM internal state
  var runState = {
    stateManager: stateManager, // 
    returnValue: false, // 代码执行之后的返回至
    stopped: false, // 是否停止
    vmError: false, // 是否出现VM错误
    programCounter: 0, //  程序当前执行的opCode的index索引
    opCode: undefined, // 程序当前执行的操作码
    opName: undefined, // 程序当前执行的操作码对应的操作名称
    gasLeft: new BN(opts.gasLimit), // 当前还剩下的gas
    gasLimit: new BN(opts.gasLimit), // 交易设置的gasLimit
    gasRefund: new BN(0), // 回退的gas
    gasPrice: opts.gasPrice, 
    memory: [],
    highestMemCost: new BN(0), // 最高内存使用量
    memoryWordCount: new BN(0), // 32bytes为一个work
    stack: [],
    lastReturned: [], // 最后返回的内容
    logs: [], // 执行代码产生的log
    validJumps: [], // 记录代码中需要进行跳转的opCode的index（索引）
    
    depth: opts.depth || 0, // 合约调用深度
    // opts.suicides is kept for backward compatiblity with pre-EIP6 syntax
    selfdestruct: opts.selfdestruct || opts.suicides || {}, // 是否是自杀合约
    block: block, // 交易所在的block
    callValue: opts.value || new BN(0),
    address: opts.address || util.zeros(32), // 合约地址
    caller: opts.caller || util.zeros(32), // 调用合约的账号的地址
    origin: opts.origin || opts.caller || util.zeros(32), // 合约调用的源地址
    callData: opts.data || Buffer.from([0]), // 里面记录了调用合约的ABI信息
    code: opts.code, // 合约对应的合约代码
    populateCache: opts.populateCache === undefined ? true : opts.populateCache, // 合约代码执行完毕后是否将缓存中的记录flush到数据库
    static: opts.static || false // false表示不能在合约中调用其他合约，true表示可以
  }

  // temporary - to be factored out
  runState._common = self._common
  runState._precompiled = self._precompiled
  runState._vm = self

  // prepare to run vm
  preprocessValidJumps(runState)
  // load contract then start vm run
  loadContract(runVm)

  // iterate through the given ops until something breaks or we hit STOP
  function runVm () {
    async.whilst(vmIsActive, iterateVm, parseVmResults)
  }

  // ensure contract is loaded; only used if runCode is called directly
  function loadContract (cb) {
    stateManager.getAccount(runState.address, function (err, account) {
      if (err) return cb(err)
      runState.contract = account
      cb()
    })
  }

  function vmIsActive () {
    var notAtEnd = runState.programCounter < runState.code.length

    return !runState.stopped && notAtEnd && !runState.vmError && !runState.returnValue
  }

  function iterateVm (done) {
    var opCode = runState.code[runState.programCounter]
    var opInfo = lookupOpInfo(opCode)
    var opName = opInfo.name
    var opFn = opFns[opName]

    runState.opName = opName
    runState.opCode = opCode

    async.series([
      runStepHook,
      runOp
    ], function (err) {
      setImmediate(done.bind(null, err))
    })

    function runStepHook (cb) {
      var eventObj = {
        pc: runState.programCounter,
        gasLeft: runState.gasLeft,
        opcode: lookupOpInfo(opCode, true),
        stack: runState.stack,
        depth: runState.depth,
        address: runState.address,
        account: runState.contract,
        cache: runState.stateManager.cache,
        memory: runState.memory
      }
      self.emit('step', eventObj, cb)
    }

    function runOp (cb) {
      // check for invalid opcode
      if (opName === 'INVALID') {
        return cb(new VmError(ERROR.INVALID_OPCODE))
      }

      // check for stack underflows
      if (runState.stack.length < opInfo.in) {
        return cb(new VmError(ERROR.STACK_UNDERFLOW))
      }

      if ((runState.stack.length - opInfo.in + opInfo.out) > 1024) {
        return cb(new VmError(ERROR.STACK_OVERFLOW))
      }

      // calculate gas
      var fee = new BN(opInfo.fee)
      // TODO: move to a shared funtion; subGas in opFuns
      runState.gasLeft = runState.gasLeft.sub(fee)
      if (runState.gasLeft.ltn(0)) {
        runState.gasLeft = new BN(0)
        cb(new VmError(ERROR.OUT_OF_GAS))
        return
      }

      // advance program counter
      runState.programCounter++
      var argsNum = opInfo.in
      var retNum = opInfo.out
      // pop the stack
      var args = argsNum ? runState.stack.splice(-argsNum) : []

      args.reverse()
      args.push(runState)
      // create a callback for async opFunc
      if (opInfo.async) {
        args.push(function (err, result) {
          if (err) return cb(err)

          // save result to the stack
          if (result !== undefined) {
            if (retNum !== 1) {
              // opcode post-stack mismatch
              return cb(new VmError(ERROR.INTERNAL_ERROR))
            }

            runState.stack.push(result)
          } else {
            if (retNum !== 0) {
              // opcode post-stack mismatch
              return cb(new VmError(ERROR.INTERNAL_ERROR))
            }
          }

          cb()
        })
      }

      try {
        // run the opcode
        var result = opFn.apply(null, args)
      } catch (e) {
        if (e.errorType && e.errorType === 'VmError') {
          cb(e)
          return
        } else {
          throw e
        }
      }

      // save result to the stack
      if (result !== undefined) {
        if (retNum !== 1) {
          // opcode post-stack mismatch
          return cb(new VmError(ERROR.INTERNAL_ERROR))
        }

        runState.stack.push(result)
      } else {
        if (!opInfo.async && retNum !== 0) {
          // opcode post-stack mismatch
          return cb(new VmError(ERROR.INTERNAL_ERROR))
        }
      }

      // call the callback if opFn was sync
      if (!opInfo.async) {
        cb()
      }
    }
  }

  function parseVmResults (err) {
    // remove any logs on error
    if (err) {
      runState.logs = []
      stateManager.revertContracts()
      runState.vmError = true
    }

    var results = {
      runState: runState, // 当前合约代码执行上下文
      selfdestruct: runState.selfdestruct,
      gasRefund: runState.gasRefund, // 回退的gas
      exception: err ? 0 : 1, // 1表示正常，0表示vm错误
      exceptionError: err,
      logs: runState.logs, // 合约代码执行时产生的log
      gas: runState.gasLeft, // 合约代码执行完毕后剩余的gas
      'return': runState.returnValue ? runState.returnValue : Buffer.alloc(0) // 合约代码执行完毕后的返回值
    }

    if (results.exceptionError) {
      delete results.gasRefund
      delete results.selfdestruct
    }

    if (err && err.error !== ERROR.REVERT) {
      results.gasUsed = runState.gasLimit
    } else {
      results.gasUsed = runState.gasLimit.sub(runState.gasLeft)
    }

    if (runState.populateCache) {
      self.stateManager.cache.flush(function () {
        self.stateManager.cache.clear()
        cb(err, results)
      })
    } else {
      cb(err, results)
    }
  }
}

// find all the valid jumps and puts them in the `validJumps` array
function preprocessValidJumps (runState) {
  for (var i = 0; i < runState.code.length; i++) {
    var curOpCode = lookupOpInfo(runState.code[i]).name

    // no destinations into the middle of PUSH
    if (curOpCode === 'PUSH') {
      i += runState.code[i] - 0x5f
    }

    if (curOpCode === 'JUMPDEST') {
      runState.validJumps.push(i)
    }
  }
}
