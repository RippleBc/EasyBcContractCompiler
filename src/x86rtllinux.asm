
.comm  _print_buf, 320, 4

write_syscall = 4
read_syscall = 3
max_int	= 1000000000
max_int1 = 100000000
fd_out = 1
fd_in = 0
char_size = 1
sys_call_id = 0x80
read_buf_len = 319

.text

.globl _write_char
	.type	_write_char, @function
_write_char:
	pushl	%ebp
	movl	%esp, %ebp

	pushl	%eax
	movl	$write_syscall, %eax
	movl	$fd_out, %ebx
	leal	_print_buf, %ecx
	popl	%edx
	movb	%dl, (%ecx)

	movl	$char_size, %edx
	int		$sys_call_id

	leave
	ret

	.size	_write_char, .-_write_char

.globl _writeln_char
	.type	_writeln_char, @function
_writeln_char:
	pushl	%ebp
	movl	%esp, %ebp

	pushl 	%eax
	movl	$write_syscall, %eax
	movl	$fd_out, %ebx
	leal	_print_buf, %ecx
	popl	%edx
	movb	%dl, (%ecx)
	movl	$char_size, %edx
	int		$sys_call_id

	movl	$write_syscall, %eax
	movl	$fd_out, %ebx
	leal	_print_buf, %ecx
	movb	$'\n', (%ecx)
	movl	$char_size, %edx
	int		$sys_call_id

	leave
	ret

	.size	_writeln_char, .-_write_char

.globl _write_digit
	.type	_write_digit, @function
_write_digit:
	pushl	%ebp
	movl	%esp, %ebp

	xorl	%ebx, %ebx
	movb	$'0', %bl
	addb	%bl, %dl
	movb	%dl, %al
	call	_write_char
	
	leave
	ret

	.size	_write_char, .-_write_char
.globl _write_int
	.type	_write_int, @function
_write_int:

	pushl	%ebp
	movl	%esp,%ebp

	leal	_print_buf, %ebx
	movl	$0, %esi
	movl	12(%ebp), %eax
	cmpl	$0, %eax
	jge		k_positive

	negl	%eax
	pushl	%eax
	movl	$'-', %eax
	call	_write_char
	popl	%eax

k_positive:

	movl	$0, %ebx
	movl	$max_int,  %ecx
	pushl	%eax

loop_again:
	popl	%eax
	xorl	%edx, %edx
	idiv	%ecx
	pushl	%edx
	cmpl	$0, %eax
	jg		k_d1000
	cmpl	$0, %esi
	jg		k_d1000
	jmp		k_cont
k_d1000:
	incl	%esi
	pushl	%ecx
	movl	%eax, %edx
	call	_write_digit
	popl	%ecx
k_cont:	
	movl	%ecx, %eax
	movl	$10, %ecx
	xorl	%edx, %edx
	idiv	%ecx
	movl	%eax, %ecx
	cmp		$0, %ecx
	jle		write_loop_exit
	jmp		loop_again

write_loop_exit:

	cmpl	$0, %esi
	jg		real_leave

	movl	$'0', %eax
	call	_write_char

real_leave:
	leave
	ret

	.size	_write_int,	.-_write_int

.globl _writeln_int
	.type	_writeln_int, @function
_writeln_int:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %esi
	pushl	%esi
	movl	16(%ebp), %esi
	pushl	%esi
	call	_write_int
	addl	$8, %esp
	movl	$'\n',	%eax
	call	_write_char

	leave
	ret
	.size	_writeln_int, .-_writeln_int

.globl _writeln_string
	.type	_writeln_strint, @function
_writeln_string:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %esi
	pushl	%esi
	movl	16(%ebp), %esi
	pushl	%esi
	call	_write_string
	addl	$8, %esp

	movl	$'\n',	%eax
	call	_write_char

	leave
	ret
	.size	_writeln_string, .-_writeln_string

.globl _write_string
	.type	_write_string, @function

_write_string:

	pushl	%ebp
	movl	%esp, %ebp

	movl	$fd_out, %ebx
	movl	$0, %edx
	movl	12(%ebp), %esi
	movl	%esi, %ecx

_cmp_zero:

	movb	(%esi), %al
	cmpb	$0, %al
	je		_get_zero
	incl	%edx
	incl	%esi
	jmp		_cmp_zero

_get_zero:

	movl	$write_syscall, %eax
	int		$sys_call_id

	leave
	ret
	.size	_write_string, .-_write_string

.globl _read_char
	.type	_read_char, @function
_read_char:
	pushl	%ebp
	movl	%esp, %ebp

	movl	$read_syscall, %eax
	movl	$fd_in, %ebx
	leal	_print_buf, %ecx
	movl	$read_buf_len, %edx
	int		$sys_call_id

	movl	12(%ebp), %ebx
	movl	_print_buf, %eax
	movb	%al, (%ebx)

	leave
	ret

	.size	_read_char, .-_read_char

.globl _read_int
	.type	_read_int, @function
_read_int:

	pushl	%ebp
	movl	%esp, %ebp

	movl	$read_syscall, %eax
	movl	$fd_in, %ebx
	leal	_print_buf, %ecx
	movl	$read_buf_len, %edx
	int		$sys_call_id

	leal	_print_buf, %esi
	xorl	%ecx, %ecx
	xorl	%edi, %edi

	movb	(%esi), %al
	cmpb	$'-', %al
	jne		r_positive
	
	incl	%edi
	incl	%esi

r_positive:
	xorl	%eax, %eax
	movb	(%esi), %al
	cmpb	$'0', %al
	jb		r_exit
	cmpb	$'9', %al
	jg		r_exit
	subb	$'0', %al
	cmpl	$max_int1, %ecx
	jg		r_exit
	pushl	%eax
	movl	%ecx, %eax
	xorl	%edx, %edx
	movl	$10, %ecx
	imull	%ecx
	movl	%eax, %ecx
	popl	%eax
	addl	%eax, %ecx
	incl	%esi
	jmp		r_positive

r_exit:
	cmpl	$0, %edi
	jbe		r_ret
	negl	%ecx
r_ret:
	movl	12(%ebp), %eax
	movl	%ecx, (%eax)

	leave
	ret

	.size	_read_int,	.-_read_int

.globl _readln_int
	.type	_readln_int, @function
_readln_int:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %esi
	pushl	%esi
	movl	16(%ebp), %esi
	pushl	%esi
	call	_read_int
	addl	$8, %esp
	movl	$'\n',	%eax
	call	_write_char

	leave
	ret
	.size	_readln_int, .-_readln_int

.globl _read_string
	.type	_read_string, @function
_read_string:
	pushl	%ebp
	movl	%esp, %ebp

	movl	$read_syscall, %eax
	movl	$fd_in, %ebx
	leal	_print_buf, %ecx
	movl	$read_buf_len, %edx
	int		$sys_call_id

	movl	12(%ebp), %edi
	leal	_print_buf, %esi
	movl	$read_buf_len, %ecx
	xorl	%edx, %edx
	movb	$'\n', %dl

read_next_char:
	movb	(%esi), %al
	movb	%al, (%edi)
	cmpb	'\n', %al
	jz		read_over
	incl	%esi
	incl	%edi
	jmp		read_next_char

read_over:

	leave
	ret

	.size	_read_string, .-_read_string

.globl _abs_int
	.type	_abs_int, @function
_abs_int:

	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	cmpl	$0, %eax
	jg		abs_out
	negl	%eax
abs_out:
	leave
	ret

	.size _abs_int, .-_abs_int

.globl _sqt_int
	.type	_sqt_int, @function
_sqt_int:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	%eax, %ecx
	xorl	%edx, %edx
	imull	%ecx
	leave
	ret

	.size _sqt_int, .-_sqt_int

.globl _odd_int
	.type	_odd_int, @function
_odd_int:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	andl	$1, %eax
	leave
	ret

	.size _odd_int, .-_odd_int

.globl _sqrt_int
	.type	_sqrt_int, @function
_sqrt_int:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	$0, %ecx
	movl	$1, %edx
sssb:
	subl	%edx, %eax
	cmpl	$0, %eax
	jl		sqrt_out
	incl	%ecx
	addl	$2, %edx
	jmp		sssb
sqrt_out:
	movl	%ecx, %eax

	leave
	ret

	.size _sqrt_int, .-_sqrt_int

