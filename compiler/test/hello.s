#
#SPL Compiler Ver 0.1.5
#
.file "test/hello.s"

sys_call_id = 0x80
exit_syscall = 0x1



#---program helloworld ---

# --- main routine ----
		.text
.globl _main
		.type _main, @function
_main:
		pushl	%ebp
		movl	%esp, %ebp
