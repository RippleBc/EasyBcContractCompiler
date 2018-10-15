;0218/09/11
;09:43:19
;
;SPL Compiler Ver 0.1.5


.MODEL SMALL
 
_DATA		segment	public

;global variables
cz_028		db	'achar ='
		db	'$'
cz_027		db	'i = '
		db	'$'
cz_026		db	'age='
		db	'$'
cz_025		db	'not sun'
		db	'$'
cz_024		db	'sun'
		db	'$'
cz_023		db	'dt.month='
		db	'$'
cz_022		db	'dt.year='
		db	'$'
cz_021		db	'b ='
		db	'$'
cz_020		db	'b ='
		db	'$'
cz_019		db	'i = '
		db	'$'
cz_018		db	'List of all perfect numbers:'
		db	'$'
cz_017		db	'you input b ='
		db	'$'
cz_016		db	'you input a ='
		db	'$'
cz_015		db	'please input a and b'
		db	'$'
cz_014		db	'a = '
		db	'$'
cz_013		db	'a = '
		db	'$'
cz_012		db	'a = '
		db	'$'
cz_011		db	'b = '
		db	'$'
cz_010		db	'a = '
		db	'$'
cz_009		db	'i = '
		db	'$'
cz_008		db	'i = '
		db	'$'
cz_007		db	't = '
		db	'$'
cz_006		db	'i < 0'
		db	'$'
cz_005		db	'i = 0'
		db	'$'
cz_004		db	'i > 0'
		db	'$'
cz_003		db	'i = '
		db	'$'
cz_002		db	'i = '
		db	'$'
cz_001		db	'x='
		db	'$'
va_024		db	?
va_023		dw	?
vw_022		dw	?
vc_021		dw	?
vd_020		db	0ch dup (?)
va_019		dw	032h dup (?)
vt_018		dw	?
vi_017		dw	?
vi_016		dw	?
vi_015		dw	?
vi_014		dw	?
vb_013		dw	?
va_012		dw	?
vi_011		dw	?
 
;alloc stack space
 		db	0800h dup(?)

_DATA		ends

;---program ex7_1 ---

_TEXT		segment	public

		include	x86rtl.inc

static_link	equ	word ptr [bp+04h]
retval_addr	equ	word ptr [bp-04h]
retval_addr_hi	equ	word ptr [bp-02h]


; routine : testfunc 
;local variables in testfunc
	vs_027		equ	word  ptr	[bp-0010h]
	vk_026		equ	word  ptr	[bp-000ch]
; arguments in testfunc
ax_009		equ	word  ptr	[bp+0010h]
ay_010		equ	word  ptr	[bp+000ch]
;routine code
rtn001		proc
		assume	cs:_TEXT,ds:_DATA
		mov	ax,_DATA
		mov	ds,ax
		push	bp
		mov	bp,sp
		sub	sp, 4
		sub	sp,0008h
		mov	ax,01h
		push	ax
		lea	ax,word ptr vs_027
		push	ax
		pop	bx
		pop	ax
		mov	word  ptr [bx],ax
		mov	ax,02h
		mov	word ptr vk_026,ax
for_tst0001h:
		mov	ax,word ptr ax_009
		push	ax
		mov	ax,02h
		mov	cx,ax
		pop	ax
		sub	dx,dx
		idiv	cx
		cmp	word ptr vk_026,ax
		jle	for0001h
		jmp	for_x0001h
for0001h:
		mov	ax,word ptr ax_009
		push	ax
		mov	ax,word ptr vk_026
		mov	cx,ax
		pop	ax
		sub	dx,dx
		idiv	cx
		mov	ax,dx
		push	ax
		mov	ax,00h
		pop	dx
		cmp	dx,ax
		mov	ax,1
		je	j_001
		sub	ax,ax
j_001:
		cmp	ax,1
		je	if_t0002h
		jmp	if_f0002h
if_t0002h:
		mov	ax,word ptr vs_027
		push	ax
		mov	ax,word ptr vk_026
		pop	dx
		add	ax,dx
		push	ax
		lea	ax,word ptr vs_027
		push	ax
		pop	bx
		pop	ax
		mov	word  ptr [bx],ax
		jmp	if_x0002h
if_f0002h:
if_x0002h:
		inc	word ptr vk_026
		jmp	for_tst0001h
for_x0001h:
		dec	word ptr vk_026
		mov	ax,word ptr ax_009
		push	ax
		mov	ax,word ptr ay_010
		pop	dx
		add	ax,dx
		mov	word ptr retval_addr,ax

		mov	ax, word ptr retval_addr
		mov	sp,bp
		pop	bp
		ret	000ah

rtn001		endp


; routine : t1 
;local variables in t1
; arguments in t1
ax_011		equ	word  ptr	[bp+000ch]
;routine code
rtn002		proc
		assume	cs:_TEXT,ds:_DATA
		mov	ax,_DATA
		mov	ds,ax
		push	bp
		mov	bp,sp
		sub	sp, 4
		sub	sp,0000h
		lea	ax,cz_001
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr ax_011
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,word ptr ax_011
		push	ax
		mov	ax,00h
		pop	dx
		cmp	dx,ax
		mov	ax,1
		jg	j_002
		sub	ax,ax
j_002:
		mov	word ptr retval_addr,ax

		mov	ax, word ptr retval_addr
		mov	sp,bp
		pop	bp
		ret	0006h

rtn002		endp


; routine : perfect 
;local variables in perfect
	vs_031		equ	word  ptr	[bp-0010h]
	vk_030		equ	word  ptr	[bp-000ch]
; arguments in perfect
ax_012		equ	word  ptr	[bp+000ch]
;routine code
rtn003		proc
		assume	cs:_TEXT,ds:_DATA
		mov	ax,_DATA
		mov	ds,ax
		push	bp
		mov	bp,sp
		sub	sp, 4
		sub	sp,0008h
		mov	ax,01h
		push	ax
		lea	ax,word ptr vs_031
		push	ax
		pop	bx
		pop	ax
		mov	word  ptr [bx],ax
		mov	ax,02h
		mov	word ptr vk_030,ax
for_tst0003h:
		mov	ax,word ptr ax_012
		push	ax
		mov	ax,02h
		mov	cx,ax
		pop	ax
		sub	dx,dx
		idiv	cx
		cmp	word ptr vk_030,ax
		jle	for0003h
		jmp	for_x0003h
for0003h:
		mov	ax,word ptr ax_012
		push	ax
		mov	ax,word ptr vk_030
		mov	cx,ax
		pop	ax
		sub	dx,dx
		idiv	cx
		mov	ax,dx
		push	ax
		mov	ax,00h
		pop	dx
		cmp	dx,ax
		mov	ax,1
		je	j_003
		sub	ax,ax
j_003:
		cmp	ax,1
		je	if_t0004h
		jmp	if_f0004h
if_t0004h:
		mov	ax,word ptr vs_031
		push	ax
		mov	ax,word ptr vk_030
		pop	dx
		add	ax,dx
		push	ax
		lea	ax,word ptr vs_031
		push	ax
		pop	bx
		pop	ax
		mov	word  ptr [bx],ax
		jmp	if_x0004h
if_f0004h:
if_x0004h:
		inc	word ptr vk_030
		jmp	for_tst0003h
for_x0003h:
		dec	word ptr vk_030
		mov	ax,word ptr ax_012
		push	ax
		mov	ax,word ptr vs_031
		pop	dx
		cmp	dx,ax
		mov	ax,1
		je	j_004
		sub	ax,ax
j_004:
		mov	word ptr retval_addr,ax

		mov	ax, word ptr retval_addr
		mov	sp,bp
		pop	bp
		ret	0006h

rtn003		endp


; --- main routine ----
_main		proc	far
		assume	cs:_TEXT,ds:_DATA
start:
		push	ds
		sub	ax,ax
		push	ax
		mov	ax,_DATA
		mov	ds,ax
		mov	ax,014h
		push	ax
		mov	ax,08h
		pop	dx
		add	ax,dx
		mov	word  ptr va_012, ax
		mov	ax,01eh
		push	ax
		mov	ax,02bch
		pop	dx
		add	ax,dx
		mov	word  ptr vb_013, ax
		mov	ax,word ptr va_012
		push	ax
		mov	ax,word ptr vb_013
		pop	dx
		add	ax,dx
		push	ax
		mov	ax,02h
		push	ax
		mov	ax,word ptr va_012
		push	ax
		mov	ax,word ptr vb_013
		pop	dx
		add	ax,dx
		pop	dx
		imul	dx
		pop	dx
		add	ax,dx
		mov	word  ptr vi_011, ax
		mov	ax,word ptr vi_011
		push	ax
		mov	ax,03h
		pop	dx
		sub	dx,ax
		mov	ax,dx
		mov	word  ptr vi_011, ax
		lea	ax,cz_002
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vi_011
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,word ptr vb_013
		push	ax
		mov	ax,02h
		mov	cx,ax
		pop	ax
		sub	dx,dx
		idiv	cx
		mov	word  ptr vi_011, ax
		lea	ax,cz_003
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vi_011
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,03h
		mov	word  ptr va_012, ax
		mov	ax,word ptr va_012
		push	ax
		mov	ax,word ptr vb_013
		pop	dx
		add	ax,dx
		mov	word  ptr vi_011, ax
		mov	ax,word ptr vi_015
		push	ax
		mov	ax,word ptr vi_016
		pop	dx
		add	ax,dx
		mov	word  ptr vi_014, ax
		mov	ax,02h
		mov	word  ptr vi_015, ax
		mov	ax,word ptr vi_015
		push	ax
		mov	ax,word ptr vi_016
		pop	dx
		add	ax,dx
		mov	word  ptr vi_017, ax
		mov	ax,03h
		neg	ax
		mov	word  ptr vi_011, ax
		mov	ax,word ptr vi_011
		push	ax
		mov	ax,00h
		pop	dx
		cmp	dx,ax
		mov	ax,1
		jg	j_005
		sub	ax,ax
j_005:
		cmp	ax,1
		je	if_t0005h
		jmp	if_f0005h
if_t0005h:
		lea	ax,cz_004
		push	ax
		push	bp
		call	_writeln_string
		jmp	if_x0005h
if_f0005h:
		mov	ax,word ptr vi_011
		push	ax
		mov	ax,00h
		pop	dx
		cmp	dx,ax
		mov	ax,1
		je	j_006
		sub	ax,ax
j_006:
		cmp	ax,1
		je	if_t0006h
		jmp	if_f0006h
if_t0006h:
		lea	ax,cz_005
		push	ax
		push	bp
		call	_writeln_string
		jmp	if_x0006h
if_f0006h:
		lea	ax,cz_006
		push	ax
		push	bp
		call	_writeln_string
if_x0006h:
if_x0005h:
		mov	ax,0ch
		push	ax
		push	bp
		call rtn003
		mov	word  ptr vt_018, ax
		lea	ax,cz_007
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vt_018
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,03h
		mov	word  ptr vi_011, ax
		lea	ax,cz_008
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vi_011
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,word ptr va_012
		push	ax
		mov	ax,word ptr vb_013
		push	ax
		push	bp
		call rtn001
		mov	word  ptr vi_011, ax
		lea	ax,cz_009
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vi_011
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,01eh
		mov	word  ptr va_012, ax
		mov	ax,028h
		mov	word  ptr vb_013, ax
rep_0007h:
		lea	ax,cz_010
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr va_012
		push	ax
		push	bp
		call	_writeln_int
		lea	ax,cz_011
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vb_013
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,word ptr va_012
		push	ax
		mov	ax,01h
		pop	dx
		add	ax,dx
		mov	word  ptr va_012, ax
		mov	ax,word ptr va_012
		push	ax
		mov	ax,word ptr vb_013
		pop	dx
		cmp	dx,ax
		mov	ax,1
		jg	j_007
		sub	ax,ax
j_007:
		cmp	ax,1
		je	rep_x0007h
		jmp	rep_0007h
		rep_x0007h:
		mov	ax,01eh
		mov	word ptr va_012,ax
for_tst0008h:
		mov	ax,028h
		cmp	word ptr va_012,ax
		jle	for0008h
		jmp	for_x0008h
for0008h:
		lea	ax,cz_012
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr va_012
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,word ptr va_012
		push	ax
		mov	ax,01h
		pop	dx
		add	ax,dx
		mov	word  ptr va_012, ax
		inc	word ptr va_012
		jmp	for_tst0008h
for_x0008h:
		dec	word ptr va_012
		lea	ax,cz_013
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr va_012
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,028h
		mov	word ptr va_012,ax
for_tst0009h:
		mov	ax,01eh
		cmp	word ptr va_012,ax
		jge	for0009h
		jmp	for_x0009h
for0009h:
		lea	ax,cz_014
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr va_012
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,word ptr va_012
		push	ax
		mov	ax,01h
		pop	dx
		add	ax,dx
		mov	word  ptr vb_013, ax
		dec	word ptr va_012
		jmp	for_tst0009h
for_x0009h:
		inc	word ptr va_012
		lea	ax,cz_015
		push	ax
		push	bp
		call	_writeln_string
rep_000ah:
		mov	ax,word ptr va_012
		lea	ax,word ptr va_012
		push	ax
		push	bp
		call	_read_int
		lea	ax,cz_016
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr va_012
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,word ptr vb_013
		lea	ax,word ptr vb_013
		push	ax
		push	bp
		call	_read_int
		lea	ax,cz_017
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vb_013
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,word ptr va_012
		push	ax
		mov	ax,00h
		pop	dx
		cmp	dx,ax
		mov	ax,1
		jg	j_008
		sub	ax,ax
j_008:
		push	ax
		mov	ax,word ptr vb_013
		push	ax
		mov	ax,00h
		pop	dx
		cmp	dx,ax
		mov	ax,1
		jg	j_009
		sub	ax,ax
j_009:
		pop	dx
		and	ax,dx
		push	ax
		mov	ax,word ptr va_012
		push	ax
		mov	ax,word ptr vb_013
		pop	dx
		cmp	dx,ax
		mov	ax,1
		jl	j_010
		sub	ax,ax
j_010:
		pop	dx
		and	ax,dx
		cmp	ax,1
		je	rep_x000ah
		jmp	rep_000ah
		rep_x000ah:
		lea	ax,cz_018
		push	ax
		push	bp
		call	_writeln_string
		mov	ax,word ptr va_012
		mov	word ptr vi_011,ax
for_tst000bh:
		mov	ax,word ptr vb_013
		cmp	word ptr vi_011,ax
		jle	for000bh
		jmp	for_x000bh
for000bh:
		mov	ax,word ptr vi_011
		push	ax
		push	bp
		call rtn003
		cmp	ax,1
		je	if_t000ch
		jmp	if_f000ch
if_t000ch:
		mov	ax,word ptr vi_011
		push	ax
		push	bp
		call	_writeln_int
		jmp	if_x000ch
if_f000ch:
if_x000ch:
		inc	word ptr vi_011
		jmp	for_tst000bh
for_x000bh:
		dec	word ptr vi_011
		mov	ax,02h
		mov	word  ptr va_012, ax
		mov	ax,03h
		mov	word  ptr vb_013, ax
		mov	ax,word ptr va_012
		push	cx
		mov	cx,ax
		jmp	cs13_tst
cs13a_0001h:
		mov	ax,03h
		mov	word  ptr vi_011, ax
		jmp	cs13_x
cs13a_0002h:
		mov	ax,04h
		mov	word  ptr vi_011, ax
		jmp	cs13_x
cs13a_0003h:
		mov	ax,word ptr vb_013
		push	cx
		mov	cx,ax
		jmp	cs14_tst
cs14a_0001h:
		mov	ax,06h
		mov	word  ptr vi_011, ax
		jmp	cs14_x
cs14a_0002h:
		mov	ax,07h
		mov	word  ptr vi_011, ax
		jmp	cs14_x
cs14_tst:
		mov	ax,03h
		cmp	cx,ax
		jne	cs14n_01h
		jmp	cs14a_0001h
cs14n_01h:
		mov	ax,04h
		cmp	cx,ax
		jne	cs14n_02h
		jmp	cs14a_0002h
cs14n_02h:
cs14_x:
		pop	cx
		jmp	cs13_x
cs13_tst:
		mov	ax,02h
		cmp	cx,ax
		jne	cs13n_01h
		jmp	cs13a_0001h
cs13n_01h:
		mov	ax,05h
		cmp	cx,ax
		jne	cs13n_02h
		jmp	cs13a_0002h
cs13n_02h:
		mov	ax,06h
		cmp	cx,ax
		jne	cs13n_03h
		jmp	cs13a_0003h
cs13n_03h:
cs13_x:
		pop	cx
		lea	ax,cz_019
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vi_011
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,00h
		mov	word  ptr va_012, ax
		mov	ax,0ah
		mov	word  ptr vb_013, ax
wl_tst000fh:
		mov	ax,word ptr va_012
		push	ax
		mov	ax,0ah
		pop	dx
		cmp	dx,ax
		mov	ax,1
		jle	j_011
		sub	ax,ax
j_011:
		cmp	ax,1
		je	wl000fh
		jmp	wl_x000fh
wl000fh:
		mov	ax,word ptr vb_013
		push	ax
		mov	ax,01h
		pop	dx
		add	ax,dx
		mov	word  ptr vb_013, ax
		lea	ax,cz_020
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vb_013
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,word ptr va_012
		push	ax
		mov	ax,01h
		pop	dx
		add	ax,dx
		mov	word  ptr va_012, ax
		jmp	wl_tst000fh
wl_x000fh:
		lea	ax,cz_021
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vb_013
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,01h
		mov	word ptr vi_011,ax
for_tst0010h:
		mov	ax,032h
		cmp	word ptr vi_011,ax
		jle	for0010h
		jmp	for_x0010h
for0010h:
		lea	ax,word ptr va_019
		push	ax
		mov	ax,word ptr vi_011
		sub	ax,01h
		mov	cx,04h
		imul	cx
		pop	dx
		add	dx,ax
		push	dx
		mov	ax,word ptr vi_011
		neg	ax
		push	ax
		pop	ax
		pop	bx
		mov	word ptr [bx],ax
		inc	word ptr vi_011
		jmp	for_tst0010h
for_x0010h:
		dec	word ptr vi_011
		lea	ax,word ptr va_019
		push	ax
		mov	ax,028h
		sub	ax,01h
		mov	cx,04h
		imul	cx
		pop	dx
		add	dx,ax
		push	dx
		pop	bx
		mov	ax,word ptr [bx]
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,032h
		mov	word ptr vi_011,ax
for_tst0011h:
		lea	ax,word ptr va_019
		push	ax
		mov	ax,028h
		sub	ax,01h
		mov	cx,04h
		imul	cx
		pop	dx
		add	dx,ax
		push	dx
		pop	bx
		mov	ax,word ptr [bx]
		cmp	word ptr vi_011,ax
		jge	for0011h
		jmp	for_x0011h
for0011h:
		lea	ax,word ptr va_019
		push	ax
		mov	ax,word ptr vi_011
		sub	ax,01h
		mov	cx,04h
		imul	cx
		pop	dx
		add	dx,ax
		push	dx
		pop	bx
		mov	ax,word ptr [bx]
		push	ax
		push	bp
		call	_write_int
		mov	al,' '
		mov	dl,al
		mov	ah,2
		int	21h
		dec	word ptr vi_011
		jmp	for_tst0011h
for_x0011h:
		inc	word ptr vi_011
		lea	ax,word ptr vd_020
		push	ax
		pop	ax
		mov	dx,00h
		add	ax,dx
		push	ax
		mov	ax,07d7h
		pop	bx
		mov	word ptr [bx],ax
		lea	ax,word ptr vd_020
		push	ax
		pop	ax
		mov	dx,04h
		add	ax,dx
		push	ax
		mov	ax,0bh
		pop	bx
		mov	word ptr [bx],ax
		lea	ax,cz_022
		push	ax
		push	bp
		call	_write_string
		lea	ax,word ptr vd_020
		push	ax
		pop	ax
		mov	dx,00h
		add	ax,dx
		push	ax
		pop	bx
		mov	ax,word ptr [bx]
		push	ax
		push	bp
		call	_writeln_int
		lea	ax,cz_023
		push	ax
		push	bp
		call	_write_string
		lea	ax,word ptr vd_020
		push	ax
		pop	ax
		mov	dx,04h
		add	ax,dx
		push	ax
		pop	bx
		mov	ax,word ptr [bx]
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,01h
		mov	word  ptr vw_022, ax
		mov	ax,word ptr vw_022
		push	ax
		mov	ax,01h
		pop	dx
		cmp	dx,ax
		mov	ax,1
		je	j_012
		sub	ax,ax
j_012:
		cmp	ax,1
		je	if_t0012h
		jmp	if_f0012h
if_t0012h:
		lea	ax,cz_024
		push	ax
		push	bp
		call	_writeln_string
		jmp	if_x0012h
if_f0012h:
		lea	ax,cz_025
		push	ax
		push	bp
		call	_writeln_string
if_x0012h:
		mov	ax,017h
		mov	word  ptr va_023, ax
		mov	ax,01f4h
		mov	word  ptr va_023, ax
		lea	ax,cz_026
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr va_023
		push	ax
		push	bp
		call	_writeln_int
		mov	ax,03h
		neg	ax
		mov	word  ptr vi_011, ax
		lea	ax,cz_027
		push	ax
		push	bp
		call	_write_string
		mov	ax,word ptr vi_011
		push	ax
		push	bp
		call	_writeln_int
		mov	al,'a'
		mov	byte ptr va_024,al
		sub	ax,ax
		mov	al,byte ptr va_024
		push	ax
		mov	ax,01h
		pop	dx
		add	ax,dx
		mov	byte ptr va_024,al
		lea	ax,cz_028
		push	ax
		push	bp
		call	_write_string
		sub	ax,ax
		mov	al,byte ptr va_024
		mov	dl,al
		mov	ah,2
		int	21h
		ret
_main		endp

_TEXT		ends
		end	start

