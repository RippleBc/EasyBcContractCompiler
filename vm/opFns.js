const Buffer = require('safe-buffer').Buffer
const async = require('async')
const util = require('../../util')
const BN = util.BN
const exceptions = require('./exceptions.js')
const logTable = require('./logTable.js')
const ERROR = exceptions.ERROR
const VmError = exceptions.VmError
const MASK_160 = new BN(1).shln(160).subn(1) // 1111....111(160个1，20个字节)

// bn.js

// Prefixes

// There are several prefixes to instructions that affect the way the work. 
// Here is the list of them in the order of appearance in the function name:

//     i - perform operation in-place, storing the result in the host object (on which the method was invoked). 
//          Might be used to avoid number allocation costs
//     u - unsigned, ignore the sign of operands when performing operation, or always return positive value. 
//         Second case applies to reduction operations like mod(). In such cases if the result will be negative - 
//          modulo will be added to the result to make it positive

// Postfixes

//     n - the argument of the function must be a plain JavaScript Number. Decimals are not supported.
//     rn - both argument and return value of the function are plain JavaScript Numbers. Decimals are not supported.

// 所谓梅森数，是指形如2^p－1的一类数，其中指数p是素数，常记为Mp 。如果梅森数是素数，就称为梅森素数。
// 用因式分解法可以证明，若2^p－1是素数，则指数p也是素数；反之，当p是素数时，2^p－1（即Mp）却未必是素数。
// 前几个较小的梅森数大都是素数，然而梅森数越大，梅森素数也就越难出现。

// 蒙哥马利算法并不是一个独立的算法，而是三个相互独立又相互联系的算法集合，其中包括
// 蒙哥马利乘模，是用来计算x⋅y (mod N)
// 蒙哥马利约减，是用来计算t⋅ρ−1 (mod N)
// 蒙哥马利幂模，是用来计算xy (mod N) 

BN.prototype.divCeil = function divCeil (num) {
  // 分别进行除法以及取模操作
  var dm = this.divmod(num)

  // 没有余数
  if (dm.mod.isZero()) return dm.div

  // 负数向负无穷取整，正数向正无穷取整
  return dm.div.negative !== 0 ? dm.div.isubn(1) : dm.div.iaddn(1)
}

// 将address转化为一个20字节的大端Buffer数组
function addressToBuffer (address) {
  return address.and(MASK_160).toArrayLike(Buffer, 'be', 20)
}

// the opcode functions
module.exports = {
  /***********************************************************************************************/
  // 数学计算
  /***********************************************************************************************/
  STOP: function (runState) {
    runState.stopped = true 
  },
  // 最大值为util.TWO_POW256 - 1（2^256 - 1，111...111（256个1））
  ADD: function (a, b, runState) {
    return a.add(b).mod(util.TWO_POW256) 
  },
  MUL: function (a, b, runState) {
    return a.mul(b).mod(util.TWO_POW256)
  },
  // 返回一个二进制补码（tow's complement），补码的设计使符号位能与有效值部分一起参加运算，从而简化运算规则。
  // 负数的补码就是对反码（原码符号位（最高位）保持不变，其他位置按位取反（1取0，0取1））加1，正数的原码反码补码相同。
  SUB: function (a, b, runState) {
    return a.sub(b).toTwos(256)
  },
  // CPU不支持直接做二进制除法，除法运算通过减法运算来实现（减法通过补码操作实现）。
  // 寄存器A中存放被除数，寄存器B中存在除法元算的结果（初始化为0）。
  // 用被除数减除数，减一次，寄存器A += 除数的补码，寄存器B加1，直到被除数小于除数了。寄存器A中的数就是余数，此时寄存器B中的数就是商。
  DIV: function (a, b, runState) {
    if (b.isZero()) {
      trap(ERROR.ARITHMETIC_ERROR)
    } else {
      return a.div(b)
    }
  },
  // 参数和返回值均为补码（two's complement）
  SDIV: function (a, b, runState) {
    if (b.isZero()) {
      trap(ERROR.ARITHMETIC_ERROR)
    } else {
      // 将补码转化为原码
      a = a.fromTwos(256)
      b = b.fromTwos(256)
      // 结果转化为二进制补码
      return a.div(b).toTwos(256)
    }
  },
  MOD: function (a, b, runState) {
    if (b.isZero()) {
      trap(ERROR.ARITHMETIC_ERROR)
    } else {
      return a.mod(b)
    }
  },
  // 参数和返回值均为补码（two's complement）
  SMOD: function (a, b, runState) {
    if (b.isZero()) {
      trap(ERROR.ARITHMETIC_ERROR)
    } else {
      // 补码转源码
      a = a.fromTwos(256)
      b = b.fromTwos(256)
      // 绝对值mod操作
      var r = a.abs().mod(b.abs())
      if (a.isNeg()) {
        r = r.ineg() // a为负数，模值取反（同样为负数）
      }
      // 结果转化为补码
      return r.toTwos(256)
    }
  },
  ADDMOD: function (a, b, c, runState) {
    if (c.isZero()) {
      trap(ERROR.ARITHMETIC_ERROR)
    } else {
      return a.add(b).mod(c)
    }
  },
  MULMOD: function (a, b, c, runState) {
    if (c.isZero()) {
      trap(ERROR.ARITHMETIC_ERROR)
    } else {
      return a.mul(b).mod(c)
    }
  },
  // 采用蒙哥马利幂模算法（返回值 < util.TWO_POW256）
  EXP: function (base, exponent, runState) {
    // 创建一个简约上下文（reduction context）
    var m = BN.red(util.TWO_POW256) 

    // 转换底数（converting number）
    base = base.toRed(m)

    if (!exponent.isZero()) {
      // 计算gas（exponent有效位所占的字节数，不足一个字节按一个字节计算）
      var bytes = 1 + logTable(exponent)
      subGas(runState, new BN(bytes).muln(runState._common.param('gasPrices', 'expByte')))
      // 蒙哥马利幂模运算
      return base.redPow(exponent)
    } else {
      return new BN(1)
    }
  },
  // 符号位拓展（针对有符号Interger），k表示符号位所在的字节的位置，val是补码
  SIGNEXTEND: function (k, val, runState) {
    // val转化为32字节的Buffer（1 word = 32字节）
    val = val.toArrayLike(Buffer, 'be', 32)
    var extendOnes = false

    if (k.lten(31)) {
      k = k.toNumber()

      // 检查符号位是否为1（big endian模式中，Interger的高位位于内存的低位）
      if (val[31 - k] & 0x80) {
        extendOnes = true
      }

      // 符号位扩展（符号位以上的字节全部为0xff）
      if (extendOnes) {
        for (var i = 30 - k; i >= 0; i--) {
          val[i] = 0xff
        }
      }
    }

    return new BN(val)
  },
  // 0x10 range - bit ops
  LT: function (a, b, runState) {
    return new BN(a.lt(b) ? 1 : 0)
  },
  GT: function (a, b, runState) {
    return new BN(a.gt(b) ? 1 : 0)
  },
  // 参数为补码
  SLT: function (a, b, runState) {
    return new BN(a.fromTwos(256).lt(b.fromTwos(256)) ? 1 : 0)
  },
  // 参数为补码
  SGT: function (a, b, runState) {
    return new BN(a.fromTwos(256).gt(b.fromTwos(256)) ? 1 : 0)
  },
  EQ: function (a, b, runState) {
    return new BN(a.eq(b) ? 1 : 0)
  },
  ISZERO: function (a, runState) {
    return new BN(a.isZero() ? 1 : 0)
  },
  AND: function (a, b, runState) {
    return a.and(b)
  },
  OR: function (a, b, runState) {
    return a.or(b)
  },
  // 按位异或（不同为1，相同为0）
  XOR: function (a, b, runState) {
    return a.xor(b)
  },
  // 按位取反
  NOT: function (a, runState) {
    return a.notn(256)
  },
  // 从word（32个字节组成）中提取一个字节。pos表示word（可以简单理解成一个字节数组）的索引
  BYTE: function (pos, word, runState) {
    if (pos.gten(32)) {
      return new BN(0)
    }
    return new BN(word.shrn((31 - pos.toNumber()) * 8).andln(0xff))
  },
  SHL: function (a, b, runState) {
    if(a.ltn(0)) {
      trap(ERROR.ARITHMETIC_ERROR)
    }
    if (a.gten(256)) {
      return new BN(0)
    }
    return b.shln(a.toNumber()).iand(util.MAX_INTEGER)
  },
  SHR: function (a, b, runState) {
    if(a.ltn(0)) {
      trap(ERROR.ARITHMETIC_ERROR)
    }
    if (a.gten(256)) {
      return new BN(0)
    }
    return b.shrn(a.toNumber())
  },
  // b是补码
  SAR: function (a, b, runState) {
    if(a.ltn(0)) {
      trap(ERROR.ARITHMETIC_ERROR)
    }
    // 检查是否是负数
    const isSigned = b.testn(255)
    if (a.gten(256)) {
      if (isSigned) {
        // b为负数，按位平移超过界限（全部移出）
        return new BN(util.MAX_INTEGER)
      } else {
        return new BN(0)
      }
    }
    const c = b.shrn(a.toNumber())
    if (isSigned) {
      // b为负数的情况下，计算平移后仍位于界限内的bitsWidth（不包括符号位）
      const shiftedOutWidth = 255 - a.toNumber()
      const mask = util.MAX_INTEGER.shrn(shiftedOutWidth).shln(shiftedOutWidth)
      // 符号位拓展（高于符号位的bit全部为1）
      return c.ior(mask)
    } else {
      return c
    }
  },
  /***********************************************************************************************/
  // 账号相关操作
  /***********************************************************************************************/
  // SHA3参数从memory中获取（索引offset开始，提取length字节）
  SHA3: function (offset, length, runState) {
    var data = memLoad(runState, offset, length)
    // 计算gas
    subGas(runState, new BN(runState._common.param('gasPrices', 'sha3Word')).imul(length.divCeil(new BN(32))))
    return new BN(util.keccak256(data))
  },
  // 合约地址
  ADDRESS: function (runState) {
    return new BN(runState.address)
  },
  // address对应的合约余额
  BALANCE: function (address, runState, cb) {
    var stateManager = runState.stateManager
    // stack to address
    address = addressToBuffer(address)

    // shortcut if current account
    if (address.toString('hex') === runState.address.toString('hex')) {
      cb(null, new BN(runState.contract.balance))
      return
    }

    // otherwise load account then return balance
    stateManager.getAccountBalance(address, function (err, value) {
      if (err) {
        return cb(err)
      }
      cb(null, new BN(value))
    })
  },
  // 最原始的调用者
  ORIGIN: function (runState) {
    return new BN(runState.origin)
  },
  // 当前合约代码的调用者
  CALLER: function (runState) {
    return new BN(runState.caller)
  },
  // 发送的数字货币数量
  CALLVALUE: function (runState) {
    return new BN(runState.callValue)
  },
  // 获取合约调用指令
  CALLDATALOAD: function (pos, runState) {
    if (pos.gtn(runState.callData.length)) {
      return new BN(0)
    } else {
      pos = pos.toNumber()
      var loaded = runState.callData.slice(pos, pos + 32)
      loaded = loaded.length ? loaded : Buffer.from([0])
      return new BN(util.setLengthRight(loaded, 32))
    }
  },
  // 获取合约调用指令长度
  CALLDATASIZE: function (runState) {
    if (runState.callData.length === 1 && runState.callData[0] === 0) {
      return new BN(0)
    } else {
      return new BN(runState.callData.length)
    }
  },
  // 存储合约调用指令
  CALLDATACOPY: function (memOffset, dataOffset, dataLength, runState) {
    memStore(runState, memOffset, runState.callData, dataOffset, dataLength)
    // 计算gas
    subGas(runState, new BN(runState._common.param('gasPrices', 'copy')).imul(dataLength.divCeil(new BN(32))))
  },
  // 获取合约代码长度
  CODESIZE: function (runState) {
    return new BN(runState.code.length)
  },
  // 存储合约代码
  CODECOPY: function (memOffset, codeOffset, codeLength, runState) {
    memStore(runState, memOffset, runState.code, codeOffset, codeLength)
    // 计算gas
    subGas(runState, new BN(runState._common.param('gasPrices', 'copy')).imul(length.divCeil(new BN(32))))
  },
  // 获取address对应的合约代码的长度
  EXTCODESIZE: function (address, runState, cb) {
    var stateManager = runState.stateManager
    address = addressToBuffer(address)
    stateManager.getContractCode(address, function (err, code) {
      if (err) return cb(err)
      cb(null, new BN(code.length))
    })
  },
  // 存储address对应的合约代码
  EXTCODECOPY: function (address, memOffset, codeOffset, codeLength, runState, cb) {
    var stateManager = runState.stateManager
    address = addressToBuffer(address)

    // 计算gas
    subMemUsage(runState, memOffset, codeLength)
    subGas(runState, new BN(runState._common.param('gasPrices', 'copy')).imul(codeLength.divCeil(new BN(32))))

    stateManager.getContractCode(address, function (err, code) {
      if (err) return cb(err)
      // false表示不计算gas
      memStore(runState, memOffset, code, codeOffset, length, false)
      cb(null)
    })
  },
  // 获取返回数据的长度
  RETURNDATASIZE: function (runState) {
    return new BN(runState.lastReturned.length)
  },
  // 存储返回数据
  RETURNDATACOPY: function (memOffset, returnDataOffset, returnDataLength, runState) {
    if ((returnDataOffset.add(returnDataLength)).gtn(runState.lastReturned.returnDataLength)) {
      trap(ERROR.OUT_OF_GAS)
    }
    // 计算gas
    subGas(runState, new BN(runState._common.param('gasPrices', 'copy')).mul(returnDataLength.divCeil(new BN(32))))
    // false表示不计算gas
    memStore(runState, memOffset, util.toBuffer(runState.lastReturned), returnDataOffset, returnDataLength, false)
  },
  GASPRICE: function (runState) {
    return new BN(runState.gasPrice)
  },
  /***********************************************************************************************/
  // 区块相关操作
  /***********************************************************************************************/
  // 获取区块HASH
  BLOCKHASH: function (number, runState, cb) {
    var stateManager = runState.stateManager
    var diff = new BN(runState.block.header.number).sub(number)

    // block lookups must be within the past 256 blocks
    if (diff.gtn(256) || diff.lten(0)) {
      cb(null, new BN(0))
      return
    }

    stateManager.getBlockHash(number.toArrayLike(Buffer, 'be', 32), function (err, blockHash) {
      if (err) return cb(err)
      cb(null, new BN(blockHash))
    })
  },
  COINBASE: function (runState) {
    return new BN(runState.block.header.coinbase)
  },
  TIMESTAMP: function (runState) {
    return new BN(runState.block.header.timestamp)
  },
  NUMBER: function (runState) {
    return new BN(runState.block.header.number)
  },
  DIFFICULTY: function (runState) {
    return new BN(runState.block.header.difficulty)
  },
  GASLIMIT: function (runState) {
    return new BN(runState.block.header.gasLimit)
  },
  /***********************************************************************************************/
  // 合约state存储空间相关操作
  /***********************************************************************************************/
  // 获取一个word（1 word = 32 bytes）
  MLOAD: function (pos, runState) {
    return new BN(memLoad(runState, pos, new BN(32)))
  },
  // 存储一个word
  MSTORE: function (offset, word, runState) {
    word = word.toArrayLike(Buffer, 'be', 32)
    memStore(runState, offset, word, new BN(0), new BN(32))
  },
  // 存储一个字节
  MSTORE8: function (offset, byte, runState) {
    byte = Buffer.from([ byte.andln(0xff) ])
    memStore(runState, offset, byte, new BN(0), new BN(1))
  },
  SLOAD: function (key, runState, cb) {
    var stateManager = runState.stateManager
    key = key.toArrayLike(Buffer, 'be', 32)

    stateManager.getContractStorage(runState.address, key, function (err, value) {
      if (err) return cb(err)
      value = value.length ? new BN(value) : new BN(0)
      cb(null, value)
    })
  },
  // key -> val存储到合约state
  SSTORE: function (key, val, runState, cb) {
    // 静态调用无法对合约state进行修改
    if (runState.static) {
      trap(ERROR.STATIC_STATE_CHANGE)
    }
    var stateManager = runState.stateManager
    var address = runState.address
    // key转化成word类型（32字节）
    key = key.toArrayLike(Buffer, 'be', 32)

    var value
    if (val.isZero()) {
      value = Buffer.from([])
    } else {
      value = val.toArrayLike(Buffer, 'be')
    }

    stateManager.getContractStorage(address, key, function (err, found) {
      if (err) return cb(err)
      try {
        if ((value.length === 0 && !found.length) || (value.length !== 0 && found.length)) {
          // 合约state占用空间发生变化
          subGas(runState, new BN(runState._common.param('gasPrices', 'sstoreReset')))
        } else if (value.length === 0 && found.length) {
          subGas(runState, new BN(runState._common.param('gasPrices', 'sstoreReset')))
          // 合约state占用空间变小，退还gas
          runState.gasRefund.iaddn(runState._common.param('gasPrices', 'sstoreRefund'))
        } else if (value.length !== 0 && !found.length) {
          // 合约state占用空间变大
          subGas(runState, new BN(runState._common.param('gasPrices', 'sstoreSet')))
        }
      } catch (e) {
        cb(e.error)
        return
      }

      // key -> val写入address对应的state中（写入缓存）
      stateManager.putContractStorage(address, key, value, function (err) {
        if (err) return cb(err)
        runState.contract = stateManager.cache.get(address)
        cb(null)
      })
    })
  },
  /***********************************************************************************************/
  // VM相关（流程，存储操作）
  /***********************************************************************************************/
  PC: function (runState) {
    return new BN(runState.programCounter - 1)
  },
  JUMP: function (dest, runState) {
    if (dest.gtn(runState.code.length)) {
      trap(ERROR.INVALID_JUMP + ' at ' + describeLocation(runState))
    }

    dest = dest.toNumber()

    if (!jumpIsValid(runState, dest)) {
      trap(ERROR.INVALID_JUMP + ' at ' + describeLocation(runState))
    }

    runState.programCounter = dest
  },
  JUMPI: function (dest, cond, runState) {
    if (!cond.isZero()) {
      if (dest.gtn(runState.code.length)) {
        trap(ERROR.INVALID_JUMP + ' at ' + describeLocation(runState))
      }

      dest = dest.toNumber()

      if (!jumpIsValid(runState, dest)) {
        trap(ERROR.INVALID_JUMP + ' at ' + describeLocation(runState))
      }

      runState.programCounter = dest
    }
  },
  JUMPDEST: function (runState) {},
  MSIZE: function (runState) {
    return runState.memoryWordCount.muln(32)
  },
  // 将contract code中指定数量的byte放入stack中
  PUSH: function (runState) {
    const numToPush = runState.opCode - 0x5f
    const loaded = new BN(runState.code.slice(runState.programCounter, runState.programCounter + numToPush).toString('hex'), 16)
    runState.programCounter += numToPush
    return loaded
  },
  POP: function () {},
  DUP: function (runState) {
    const stackPos = runState.opCode - 0x7f
    if (stackPos > runState.stack.length) {
      trap(ERROR.STACK_UNDERFLOW)
    }
    return new BN(runState.stack[runState.stack.length - stackPos])
  },
  // 指定索引位置上的内容与栈顶内容进行互换
  SWAP: function (runState) {
    var stackPos = runState.opCode - 0x8f

    // check the stack to make sure we have enough items on the stack
    var swapIndex = runState.stack.length - stackPos - 1
    if (swapIndex < 0) {
      trap(ERROR.STACK_UNDERFLOW)
    }

    // preform the swap
    var topIndex = runState.stack.length - 1
    var tmp = runState.stack[topIndex]
    runState.stack[topIndex] = runState.stack[swapIndex]
    runState.stack[swapIndex] = tmp
  },
  /***********************************************************************************************/
  // transactioin相关
  /***********************************************************************************************/
  LOG: function (memOffset, memLength) {
    var args = Array.prototype.slice.call(arguments, 0)
    var runState = args.pop()
    if (runState.static) {
      trap(ERROR.STATIC_STATE_CHANGE)
    }

    var topics = args.slice(2)
    topics = topics.map(function (a) {
      return a.toArrayLike(Buffer, 'be', 32)
    })

    const numOfTopics = runState.opCode - 0xa0
    // 获取logData
    const mem = memLoad(runState, memOffset, memLength)
    // 计算gas消耗（topics，logData）
    subGas(runState, new BN(runState._common.param('gasPrices', 'logTopic')).imuln(numOfTopics).iadd(memLength.muln(runState._common.param('gasPrices', 'logData'))))

    // add address
    var log = [runState.address]
    // add topics
    log.push(topics)
    // add log data
    log.push(mem)
    runState.logs.push(log)
  },
  // 获取剩余gas
  GAS: function (runState) {
    return new BN(runState.gasLeft)
  },
  // 指定value值，往新创建的address中发送value个数字货币
  CREATE: function (value, offset, length, runState, done) {
    if (runState.static) {
      trap(ERROR.STATIC_STATE_CHANGE)
    }

    // 获取callData，被创建合约的code必须提前被知道
    var data = memLoad(runState, offset, length)

    // 设置调用参数（gasLimit为默认值0xffffff）
    var options = {
      value: value,
      data: data
    }

    // CREATE操作的返回值不需要保存到memory中
    var localOpts = {
      inOffset: offset, // reading position
      inLength: length, // reading length
      outOffset: new BN(0), // writing position
      outLength: new BN(0) // writing length
    }

    // 计算GAS消耗
    checkCallMemCost(runState, options, localOpts)
    checkOutOfGas(runState, options)
    // 调用
    makeCall(runState, options, localOpts, done)
  },
  CALL: function (gasLimit, toAddress, value, inOffset, inLength, outOffset, outLength, runState, done) {
    var stateManager = runState.stateManager
    toAddress = addressToBuffer(toAddress)

    if (runState.static && !value.isZero()) {
      trap(ERROR.STATIC_STATE_CHANGE)
    }

    // 获取callData
    var data = memLoad(runState, inOffset, inLength)

    var options = {
      gasLimit: gasLimit,
      value: value,
      to: toAddress, // 运行环境是toAddress对应的contract（memory，storage，balance，nonce等全部采用toAddress对应的contract）
      data: data,
      static: runState.static
    }

    var localOpts = {
      inOffset: inOffset,
      inLength: inLength,
      outOffset: outOffset, // call操作的返回值保存到memory的位置
      outLength: outLength // call操作的返回值保存到memory的大小
    }

    if (!value.isZero()) {
      subGas(runState, new BN(runState._common.param('gasPrices', 'callValueTransfer')))
    }

    // 检查toAddress对应的account是否存在
    stateManager.exists(toAddress, function (err, exists) {
      if (err) {
        done(err)
        return
      }

      // 检查toAddress对应的account是否为空
      stateManager.accountIsEmpty(toAddress, function (err, empty) {
        if (err) {
          done(err)
          return
        }

        // toAddress对应的account不存在或者为空
        if (!exists || empty) {
          if (!value.isZero()) {
            try {
              // 计算调用newAccount消耗的gas
              subGas(runState, new BN(runState._common.param('gasPrices', 'callNewAccount')))
            } catch (e) {
              done(e.error)
              return
            }
          }
        }

        try {
          checkCallMemCost(runState, options, localOpts)
          checkOutOfGas(runState, options)
        } catch (e) {
          done(e.error)
          return
        }

        if (!value.isZero()) {
          // 计算往account发送value消耗的gas
          runState.gasLeft.iaddn(runState._common.param('gasPrices', 'callStipend'))
          // 提前加上toAddress账号发送数字货币到其他合约需要消耗的gas数量（防止无法进行发送数字货币的调用，相当于是baseGasLimit）
          options.gasLimit.iaddn(runState._common.param('gasPrices', 'callStipend'))
        }

        makeCall(runState, options, localOpts, done)
      })
    })
  },
  // 与call函数相同，但是只使用toAddress对应的code，其他操作还是在当前address的环境下进行（identical to call but only use the code from toAddress and stay in the context of the current contract otherwise）
  CALLCODE: function (gas, toAddress, value, inOffset, inLength, outOffset, outLength, runState, done) {
    var stateManager = runState.stateManager
    toAddress = addressToBuffer(toAddress)

    var data = memLoad(runState, inOffset, inLength)

    // caller为合约自己（合约通过其他合约的代码改变自身状态，用来实现Library）
    const options = {
      gasLimit: gas,
      value: value,
      data: data,
      to: runState.address, // 运行环境是当前address对应的contract（使用current contract的memory，storage，nonce，balance)
      static: runState.static
    }

    const localOpts = {
      inOffset: inOffset,
      inLength: inLength,
      outOffset: outOffset, 
      outLength: outLength
    }

    if (!value.isZero()) {
      subGas(runState, new BN(runState._common.param('gasPrices', 'callValueTransfer')))
    }

    checkCallMemCost(runState, options, localOpts)
    checkOutOfGas(runState, options)

    if (!value.isZero()) {
      runState.gasLeft.iaddn(runState._common.param('gasPrices', 'callStipend'))
      options.gasLimit.iaddn(runState._common.param('gasPrices', 'callStipend'))
    }

    if (runState._precompiled[toAddress.toString('hex')]) {
      options.compiled = true
      options.code = runState._precompiled[toAddress.toString('hex')]
      // 调用预编译函数
      return makeCall(runState, options, localOpts, done)
    }

    stateManager.getContractCode(toAddress, function (err, code, compiled) {
      if (err) return done(err)
      options.compiled = compiled || false
      options.code = code // 采用toAddress对应的code
      makeCall(runState, options, localOpts, done)
    })
  },
  // 与callcode相同，但是保留caller和value。（identical to callcode but also keep caller and callvalue）
  DELEGATECALL: function (gas, toAddress, inOffset, inLength, outOffset, outLength, runState, done) {
    // If storage variables are accessed via a low-level delegatecall, 
    // the storage layout of the two contracts must align in order for the called contract to correctly access the storage variables of the calling contract by name. 
    // This is of course not the case if storage pointers are passed as function arguments as in the case for the high-level libraries.
    // 被调用合约必须和调用合约的storage结构保持一致，这样被调用合约才能正确访问storage变量。如果storage变量通过函数参数传递给被调用合约去使用，那就不需要对其。
    var stateManager = runState.stateManager
    var value = runState.callValue
    toAddress = addressToBuffer(toAddress)

    var data = memLoad(runState, inOffset, inLength)

    // caller和value保持不变，通过当前合约调用其他合约的代码
    const options = {
      gasLimit: gas,
      value: value,
      data: data,
      to: runState.address,
      caller: runState.caller,
      delegatecall: true, // 运行环境是当前address对应的contract（使用current contract的memory，storage，nonce，balance)
      static: runState.static
    }

    const localOpts = {
      inOffset: inOffset,
      inLength: inLength,
      outOffset: outOffset,
      outLength: outLength
    }

    checkCallMemCost(runState, options, localOpts)
    checkOutOfGas(runState, options)

    // 调用预编译函数
    if (runState._precompiled[toAddress.toString('hex')]) {
      options.compiled = true
      options.code = runState._precompiled[toAddress.toString('hex')]
      return makeCall(runState, options, localOpts, done)
    } 

    // 加载toAddress对应的code
    stateManager.getContractCode(toAddress, function (err, code, compiled) {
      if (err) return done(err)
      options.compiled = compiled || false
      options.code = code
      makeCall(runState, options, localOpts, done)
    })
  },
  // 与call函数相同，但是不允许对state（余额，storage，nonce等等）的修改。（identical to call but do not allow state modifications）
  STATICCALL: function (gasLimit, toAddress, inOffset, inLength, outOffset, outLength, runState, done) {
    var stateManager = runState.stateManager
    var value = new BN(0)
    toAddress = addressToBuffer(toAddress)

    var data = memLoad(runState, inOffset, inLength)

    var options = {
      gasLimit: gasLimit,
      value: value,
      to: toAddress,
      data: data,
      static: true
    }

    var localOpts = {
      inOffset: inOffset,
      inLength: inLength,
      outOffset: outOffset,
      outLength: outLength
    }

    stateManager.exists(toAddress, function (err, exists) {
      if (err) {
        done(err)
        return
      }

      stateManager.accountIsEmpty(toAddress, function (err, empty) {
        if (err) {
          done(err)
          return
        }

        try {
          checkCallMemCost(runState, options, localOpts)
          checkOutOfGas(runState, options)
        } catch (e) {
          done(e.error)
          return
        }

        makeCall(runState, options, localOpts, done)
      })
    })
  },
  RETURN: function (offset, length, runState) {
    runState.returnValue = memLoad(runState, offset, length)
  },
  REVERT: function (offset, length, runState) {
    runState.stopped = true
    runState.returnValue = memLoad(runState, offset, length)
    trap(ERROR.REVERT)
  },
  // '0x70', range - other
  SELFDESTRUCT: function (selfdestructToAddress, runState, cb) {
    if (runState.static) {
      trap(ERROR.STATIC_STATE_CHANGE)
    }
    var stateManager = runState.stateManager
    var contract = runState.contract
    var contractAddress = runState.address
    selfdestructToAddress = addressToBuffer(selfdestructToAddress)

    stateManager.getAccount(selfdestructToAddress, function (err, toAccount) {
      // update balances
      if (err) {
        cb(err)
        return
      }

      stateManager.accountIsEmpty(selfdestructToAddress, function (error, empty) {
        if (error) {
          cb(error)
          return
        }

        if ((new BN(contract.balance)).gtn(0)) {
          if (!toAccount.exists || empty) {
            try {
              subGas(runState, new BN(runState._common.param('gasPrices', 'callNewAccount')))
            } catch (e) {
              cb(e.error)
              return
            }
          }
        }

        // only add to refund if this is the first selfdestruct for the address
        if (!runState.selfdestruct[contractAddress.toString('hex')]) {
          runState.gasRefund = runState.gasRefund.addn(runState._common.param('gasPrices', 'selfdestructRefund'))
        }
        runState.selfdestruct[contractAddress.toString('hex')] = selfdestructToAddress
        runState.stopped = true

        var newBalance = new BN(contract.balance).add(new BN(toAccount.balance))
        async.series([
          stateManager.putAccountBalance.bind(stateManager, selfdestructToAddress, newBalance),
          stateManager.putAccountBalance.bind(stateManager, contractAddress, new BN(0))
        ], function (err) {
          // The reason for this is to avoid sending an array of results
          cb(err)
        })
      })
    })
  }
}

function describeLocation (runState) {
  var hash = util.keccak256(runState.code).toString('hex')
  var address = runState.address.toString('hex')
  var pc = runState.programCounter - 1
  return hash + '/' + address + ':' + pc
}

function subGas (runState, amount) {
  runState.gasLeft.isub(amount)
  if (runState.gasLeft.ltn(0)) {
    runState.gasLeft = new BN(0)
    trap(ERROR.OUT_OF_GAS)
  }
}

function trap (err) {
  throw new VmError(err)
}

/**
 * Subtracts the amount needed for memory usage from `runState.gasLeft`
 * @method subMemUsage
 * @param {BN} offset
 * @param {BN} length
 * @return {String}
 */
function subMemUsage (runState, offset, length) {
  // YP (225): access with zero length will not extend the memory
  if (length.isZero()) return

  const newMemoryWordCount = offset.add(length).divCeil(new BN(32))
  if (newMemoryWordCount.lte(runState.memoryWordCount)) return

  const words = newMemoryWordCount
  const fee = new BN(runState._common.param('gasPrices', 'memory'))
  const quadCoeff = new BN(runState._common.param('gasPrices', 'quadCoeffDiv'))
  // words * 3 + words ^2 / 512
  const cost = words.mul(fee).add(words.mul(words).div(quadCoeff))

  if (cost.gt(runState.highestMemCost)) {
    subGas(runState, cost.sub(runState.highestMemCost))
    runState.highestMemCost = cost
  }

  runState.memoryWordCount = newMemoryWordCount
}

/**
 * Loads bytes from memory and returns them as a buffer. If an error occurs
 * a string is instead returned. The function also subtracts the amount of
 * gas need for memory expansion.
 * @method memLoad
 * @param {BN} offset where to start reading from
 * @param {BN} length how far to read
 * @return {Buffer|String}
 */
function memLoad (runState, offset, length) {
  // check to see if we have enougth gas for the mem read
  subMemUsage(runState, offset, length)

  // 读取长度为0，则返回一个长度为0的Buffer对象
  if (length.isZero()) {
    return Buffer.alloc(0)
  }

  offset = offset.toNumber()
  length = length.toNumber()

  // memory数组中，从索引为offset开始，获取length长度的数据
  var loaded = runState.memory.slice(offset, offset + length)
  // 将剩余的内容填充为0
  for (var i = loaded.length; i < length; i++) {
    loaded[i] = 0
  }
  // 返回Buffer对象
  return Buffer.from(loaded)
}

/**
 * Stores bytes to memory. If an error occurs a string is instead returned.
 * The function also subtracts the amount of gas need for memory expansion.
 * @method memStore
 * @param {BN} offset where to start writing from
 * @param {Buffer} val
 * @param {BN} valOffset
 * @param {BN} length how far to read
 * @param {Boolean} skipSubMem
 * @return {Buffer|String}
 */
// 记录有效数据以及清零
function memStore (runState, offset, val, valOffset, outLength, skipSubMem) {
  if (skipSubMem !== false) {
    subMemUsage(runState, offset, length)
  }

  // shortcut
  if (length.isZero()) {
    return
  }

  offset = offset.toNumber()
  length = length.toNumber()

  var safeLen = 0
  // 从val索引为valOffst开始读取length个字节已经越界（无法从索引为valOffset开始从val中获取length个字节的数据）
  if (valOffset.addn(length).gtn(val.length)) {
    // valOffset已经越界（超过val的最大索引）
    if (valOffset.gten(val.length)) {
      safeLen = 0
    } else {
      // valOffset没有越界，但是读取length个字节后越界了
      // safeLen表示可以读取的有效的字节数量（valOffset到val末尾之间的字节数）
      safeLen = val.length - valOffset.toNumber()
    }
  } else {
    // safeLen表示可以读取的有效的字节数量（val的长度支持从valOffset读取length个字节，这里的可读取有效字节为length)
    safeLen = val.length      
  }

  // 有部分数据可供读取，将有效数据放入memory中
  let i = 0
  if (safeLen > 0) {
    safeLen = safeLen > length ? length : safeLen
    for (; i < safeLen; i++) {
      runState.memory[offset + i] = val[valOffset.toNumber() + i]
    }
  }

  // 写入数据不够，剩余数据使用0进行填充，可以用于清零操作
  // 使得val的长度大于0，safeLen <=0 ，实现将memory中offset开始，长度为length的内容置为0
  if (val.length > 0 && i < length) {
    for (; i < length; i++) {
      runState.memory[offset + i] = 0
    }
  }
}

// checks if a jump is valid given a destination
function jumpIsValid (runState, dest) {
  return runState.validJumps.indexOf(dest) !== -1
}

// checks to see if we have enough gas left for the memory reads and writes
// required by the CALLs
function checkCallMemCost (runState, callOptions, localOpts) {
  // calculates the gas need for saving the output in memory
  subMemUsage(runState, localOpts.outOffset, localOpts.outLength)

  if (!callOptions.gasLimit) {
    callOptions.gasLimit = new BN(runState.gasLeft)
  }
}

function checkOutOfGas (runState, callOptions) {
  const gasAllowed = runState.gasLeft.sub(runState.gasLeft.divn(64))
  if (callOptions.gasLimit.gt(gasAllowed)) {
    callOptions.gasLimit = gasAllowed
  }
}

// sets up and calls runCall
function makeCall (runState, callOptions, localOpts, cb) {
  // 默认为当前transaction所操作合约的地址
  callOptions.caller = callOptions.caller || runState.address
  // 继承当前transaction的origin
  callOptions.origin = runState.origin
  // 继承当前transaction的gasPrice
  callOptions.gasPrice = runState.gasPrice
  // 继承当前transaction的block
  callOptions.block = runState.block
  callOptions.populateCache = false
  // transaction的static
  callOptions.static = callOptions.static || false
  // transaction的selfdestruct
  callOptions.selfdestruct = runState.selfdestruct

  // increment the runState.depth
  callOptions.depth = runState.depth + 1

  // empty the return data buffer
  runState.lastReturned = Buffer.alloc(0)

  // 检查vm调用深度，如果不是delegatecall，检查当前合约账号的余额是否满足调用要求
  if (runState.depth >= runState._common.param('vm', 'stackLimit') || (callOptions.delegatecall !== true && new BN(runState.contract.balance).lt(callOptions.value))) {
    cb(null, new BN(0))
  } else {
    // if creating a new contract then increament the nonce
    if (!callOptions.to) {
      runState.contract.nonce = new BN(runState.contract.nonce).addn(1)
    }
    // 保存合约账户信息
    runState.stateManager.cache.put(runState.address, runState.contract)
    runState._vm.runCall(callOptions, parseCallResults)
  }

  function parseCallResults (err, results) {
    if (err) return cb(err)

    // concat the runState.logs，合约A调用合约B，在合约B中所产生的log属于合约A
    if (results.vm.logs) {
      runState.logs = runState.logs.concat(results.vm.logs)
    }

    // 计算gasRefund
    if (results.vm.gasRefund) {
      runState.gasRefund = runState.gasRefund.add(results.vm.gasRefund)
    }

    // 计算gasLeft
    runState.gasLeft.isub(results.gasUsed)

    // makeCall的返回值放入memory中
    if (results.vm.return && (!results.vm.exceptionError || results.vm.exceptionError.error === ERROR.REVERT)) {

      // 将results.vm.return保存到state.memory中
      memStore(runState, localOpts.outOffset, results.vm.return, new BN(0), localOpts.outLength, false)

      // create操作出现异常，则记录lastReturn值
      if (results.vm.exceptionError && results.vm.exceptionError.error === ERROR.REVERT && runState.opName === 'CREATE') {
        runState.lastReturned = results.vm.return
      }

      switch (runState.opName) {
        case 'CALL':
        case 'CALLCODE':
        case 'DELEGATECALL':
        case 'STATICCALL':
          runState.lastReturned = results.vm.return
          break
      }
    }

    // 没有异常出现
    if (!results.vm.exceptionError) {
      // All these functions are low-level functions and should be used with care. 
      // Specifically, any unknown contract might be （带有恶意的） and if you call it, 
      // you hand over control to that contract which could in turn call back into your contract, 
      // so be prepared for changes to your state variables when the call returns.
      runState.stateManager.getAccount(runState.address, function (err, account) {
        if (err) return cb(err)

        runState.contract = account
        // makeCall是一个创建合约的操作，返回新创建的合约的地址
        if (results.createdAddress) {
          cb(null, new BN(results.createdAddress))
        } else {
          cb(null, new BN(results.vm.exception))
        }
      })
    } else {
      // makeCall是一个创建合约的操作，并且已经失败
      if (results.vm.createdAddress) {
        // nonce -= 1
        runState.contract.nonce = new BN(runState.contract.nonce).subn(1)
      }

      cb(null, new BN(results.vm.exception))
    }
  }
}
