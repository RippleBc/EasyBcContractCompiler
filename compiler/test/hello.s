#
#SPL Compiler Ver 0.1.5
#
.file "test/hello.s"

sys_call_id = 0x80
exit_syscall = 0x1

.data


#---program helloworld ---

# --- main routine ----
		.text
.globl _main
		.type _main, @function
_main:
		pushl	%ebp
		movl	%esp, %ebp
		movl	$30, %eax
		movl	%eax, vi_012
		movl	$20, %eax
		movl	%eax, vi_013
		movl	vi_012, %eax
		pushl	%eax
		movl	vi_013, %eax
		popl	%edx
		addl	%edx, %eax
		pushl	%eax
		movl	$3, %eax
		pushl	%eax
		movl	vi_012, %eax
		pushl	%eax
		movl	vi_013, %eax
		popl	%edx
		addl	%edx, %eax
		popl	%edx
		imul	%edx
		popl	%edx
		addl	%edx, %eax
		movl	%eax, vi_011
		movl	vi_011, %eax
		pushl	%eax
		pushl	%ebp
		call	_writeln_int
		addl	$8, %esp
		leave
		ret
.size _main, .-main


.globl _start
_start:
		call _main
		movl $0, %ebx
		movl $exit_syscall, %eax
		int  $sys_call_id
.ident	"SPL: 0.1.5"

#.bss variables
		.comm vi_013,4,4
		.comm vi_012,4,4
		.comm vi_011,4,4
