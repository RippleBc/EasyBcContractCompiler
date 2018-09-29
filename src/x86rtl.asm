.MODEL small

_DATA   segment public
		db      512 dup(?)
_DATA ends
		
_TEXT   segment public

char_cr   equ  0dh
char_lf   equ  0ah

_write_int  proc  near

		assume  cs:_TEXT,ds:_DATA
		mov     ax,_DATA
		mov     ds,ax
		push     bp
		mov      bp,sp
		mov      ax,word ptr [bp + 6]
		cmp		ax, 0
		jge		k_positive
		neg		ax
		push	ax
		mov		ah,2
		mov		dl,'-'
		int		21h
		pop		ax
k_positive:		
		mov      bx,0
		mov       cx,10000
		xor        dx,dx
		idiv        cx
		push        dx
		cmp        ax,0
		je          k_d1000
		mov         bx,1
		xor          dh,dh
		mov         dl, '0'
		add          dl, al
		mov          ah,2
		int            21h

k_d1000:       pop          ax
		mov          cx,1000
		xor           dx,dx
		idiv          cx
		push          dx
		cmp          ax,0
		je            mst_1000
		mov        bx,1

mst_1000:   cmp         bx,0
		je          k_d100
		xor         dh,dh
		mov        dl, '0'
		add         dl, al
		mov         ah,2
		int           21h

k_d100:   pop         ax
		mov         cx,100
		xor          dx,dx
		idiv          cx
		push         dx
		cmp          ax,0
		je           mst_100
		mov          bx,1

mst_100:    cmp          bx,0
		je            k_d10
		xor           dh,dh
		mov          dl, '0'
		add           dl,al
		mov          ah,2
		int            21h

k_d10:      pop          ax
		mov 		cx, 10
		xor			dx,dx
		idiv		cx
		push		dx
		cmp			ax, 0
		je			mst_10
		mov 		bx, 1

mst_10:    cmp          bx,0
		je            k_d1
		xor           dh,dh
		mov          dl, '0'
		add           dl,al
		mov          ah,2
		int            21h

k_d1:      pop          ax
		mov          dl, '0'
		add           dl,al
		mov          ah,2
		int            21h
		mov           sp,bp
		pop            bp
		ret             4
_write_int   endp

_write_string   proc   near
		assume   cs:_TEXT,ds:_DATA
		mov     ax,_DATA
		mov     ds,ax
		push     bp
		mov      bp,sp
		mov      dx,word ptr [bp+6]
		mov      ah,9
		int      21h
		mov      sp,bp
		pop       bp
		ret        4
_write_string    endp

_writeln_int     proc  near
		assume  cs:_TEXT,ds:_DATA
		mov     ax,_DATA
		mov     ds,ax
		push     bp
		mov      bp,sp
		mov      ax,word ptr [bp + 6]
		cmp		ax, 0
		jge		w_positive
		neg		ax
		push	ax
		mov		ah,2
		mov		dl,'-'
		int		21h
		pop		ax
w_positive:		
		mov      bx,0
		mov       cx,10000
		xor        dx,dx
		idiv        cx
		push        dx
		cmp        ax,0
		je          w_d1000
		mov         bx,1
		xor          dh,dh
		mov         dl, '0'
		add          dl, al
		mov          ah,2
		int            21h

w_d1000:       pop          ax
		mov          cx,1000
		xor           dx,dx
		idiv          cx
		push          dx
		cmp          ax,0
		je            tst_1000
		mov        bx,1

tst_1000:   cmp         bx,0
		je          w_d100
		xor         dh,dh
		mov        dl, '0'
		add         dl, al
		mov         ah,2
		int           21h

w_d100:   pop         ax
		mov         cx,100
		xor          dx,dx
		idiv          cx
		push         dx
		cmp          ax,0
		je           tst_100
		mov          bx,1

tst_100:    cmp          bx,0
		je            w_d10
		xor           dh,dh
		mov          dl, '0'
		add           dl,al
		mov          ah,2
		int            21h

w_d10:      pop          ax
		mov 		cx, 10
		xor			dx,dx
		idiv		cx
		push		dx
		cmp			ax, 0
		je			tst_10
		mov 		bx, 1

tst_10:    cmp          bx,0
		je            w_d1
		xor           dh,dh
		mov          dl, '0'
		add           dl,al
		mov          ah,2
		int            21h

w_d1:      pop          ax
		mov          dl, '0'
		add           dl,al
		mov          ah,2
		int            21h
		mov           ah,2
		mov           dl,char_cr
		int             21h
		mov            dl,char_lf
		int             21h
		mov            sp,bp
		pop             bp
		ret              4
_writeln_int         endp

_writeln_string proc       near
		assume        cs:_TEXT,	ds:_DATA
		mov          ax,_DATA
		mov     ds,ax
		push     bp
		mov     bp,sp
		mov     dx,word ptr [bp+6]
		mov      ah,9
		int       21h
		mov      ah,2
		mov      dl,char_cr
		int 	21h
		mov		dl, char_lf
		int		21h
		mov      sp,bp
		pop       bp
		ret        4
_writeln_string  endp

_read_char   proc    near
		assume    cs:_TEXT,ds:_DATA
		mov      ax,_DATA
		mov      ds,ax
		push      bp
		mov      bp,sp
		mov		ah, 1
		int		21h
		xor		ah, ah
		mov      bx, word ptr [bp+6]
		mov		[bx], ax
		mov		sp, bp
		pop		bp
		ret 4
_read_char endp

_read_string	proc	near
		assume	cs:_TEXT, ds:_DATA
		mov		ax, _DATA
		mov		ds, ax
		push	bp
		mov		bp, sp
		mov		bx, word ptr [bp + 6]
		mov      cx,0
		mov      ah,1
_rd_start:
		int        21h
		inc        cx
		cmp       al,char_cr
		je         _rd_out
		cmp       al,char_lf
		je         _rd_out
		mov       [bx],ax
		inc        bx
		jmp        _rd_start
_rd_out:
		mov       ax, '$'
		mov       [bx],ax
		mov       ah,2
		mov       dl,char_cr
		int         21h
		mov        dl,char_lf
		int          21h
		mov         sp,bp
		pop          bp
		ret           4
_read_string        endp

_read_int    proc        near
		assume      cs:_TEXT,ds:_DATA
		mov        ax,_DATA
		mov        ds,ax
		push        bp
		mov       bp,sp
		mov       bx,10
		mov       dx,0
		mov       cx,0
_ri_start:
		mov       ah,1
		int         21h
		cmp        al,char_cr
		je          _ri_out
		cmp        al,char_lf
		je          _ri_out
		cmp        al, '0'
		jl          _ri_out
		cmp        al, '9'
		jg         _ri_out
		sub        al, '0'
		xor         ah,ah
		push        ax
		mov        ax,cx
		imul        bx
		mov        cx,ax
		pop         ax
		add         cx,ax
		jmp         _ri_start
_ri_out:
		mov        bx,word ptr [bp+6]
		mov        [bx],cx
		mov        ah,2
		mov        dl,char_cr
		int          21h
		mov			dl, char_lf
		int			21h
		mov         sp,bp
		pop          bp
		ret           4
_read_int	endp

_abs_int   proc       near
		assume     cs:_TEXT,ds:_DATA
		mov        ds,ax
		push        bp
		mov          bp,sp
		mov         ax,word ptr [bp+6]
		cmp         ax,0
		jg           abs_out
		neg          ax 
abs_out:
		;mov      word ptr [bp+6],ax
		mov      sp,bp
		pop       bp
		ret        4
_abs_int        endp

_sqr_int        proc       near
		assume     cs:_TEXT,ds:_DATA
		mov        ax, _DATA
		mov        ds,ax
		push        bp
		mov        bp,sp
		mov        ax,word ptr [bp+6]
		mov        cx,ax
		imul        cx
		;mov        word ptr [bp+6],ax
		mov        sp,bp
		pop         bp
		ret          4
_sqr_int         endp

_odd_int        proc       near
		assume     cs:_TEXT,ds:_DATA
		mov        ax,_DATA
		mov        ds,ax
		push        bp
		mov        bp,sp
		mov        ax, word ptr [bp + 6]
		and         ax,1
		;mov        word ptr [bp + 6],ax
		mov         sp,bp
		pop          bp
		ret           4
_odd_int     endp
		
_sqrt_int     proc            near
		assume          cs:_TEXT,ds:_DATA
		mov				ax, _DATA
		mov             ds,ax
		push             bp
		mov				bp,sp
		mov             ax,word ptr [bp+6]
		mov             cx,0
		mov             dx,1
sssb:
		sub             ax,dx
		cmp             ax,0
		jl               srt_out
		inc             cx
		add            dx,2
		jmp            sssb

srt_out:
		mov            ax, cx
		mov            sp, bp
		pop             bp
		ret              4
_sqrt_int     endp
		
_TEXT      ends
		public _write_int
		public _writeln_int
		public _write_string
		public _writeln_string
		public _read_char
		public _read_string
		public _read_int
		public _abs_int
		public _sqr_int
		public _odd_int
		public _sqrt_int
		end

