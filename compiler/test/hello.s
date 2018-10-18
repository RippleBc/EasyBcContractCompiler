#
#SPL Compiler Ver 0.1.5
#
.file "test/hello.s"

sys_call_id = 0x80
exit_syscall = 0x1

.data
.globl cz_001
		.section .rodata
		.align 4
.LCcz_001:
		.string "inta = "
		.data
		.align 4
		.type cz_001 @object
		.size cz_001, 4
cz_001:
		.long .LCcz_001


#---program helloworld ---

# --- main routine ----
		.text
.globl _main
		.type _main, @function
_main:
		pushl	%ebp
		movl	%esp, %ebp
		movl	$30, %eax
		movl	%eax, vi_002
		movl	$20, %eax
		movl	%eax, vi_003
		movl	vi_002, %eax
		pushl	%eax
		movl	vi_003, %eax
		popl	%edx
		addl	%edx, %eax
		pushl	%eax
		movl	$3, %eax
		pushl	%eax
		movl	vi_002, %eax
		pushl	%eax
		movl	vi_003, %eax
		popl	%edx
		addl	%edx, %eax
		popl	%edx
		imul	%edx
		popl	%edx
		addl	%edx, %eax
		movl	%eax, vi_001
		movl	cz_001, %eax
		pushl	%eax
		pushl	%ebp
		call	_writeln_string
		addl	$8, %esp
		movl	vi_001, %eax
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
		.comm vi_003,4,4
		.comm vi_002,4,4
		.comm vi_001,4,4
