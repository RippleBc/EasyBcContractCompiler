;header of asm

;_write_int		PROTO PASCAL intvalue:WORD
;_writeln_int	PROTO PASCAL intvalue:WORD
;_write_string	PROTO PASCAL stringptr:WORD
;_writeln_string	PROTO PASCAL stringptr:WORD
;_read_char		PROTO PASCAL charptr:WORD
;_read_string	PROTO PASCAL stringptr:WORD
;_read_int		PROTO PASCAL intptr:WORD
;_abs_int		PROTO PASCAL intvalue:WORD
;_sqr_int		PROTO PASCAL intvalue:WORD
;_odd_int		PROTO PASCAL intvalue:WORD
;_sqrt_int		PROTO PASCAL intvalue:WORD

EXTRN _write_int:NEAR
EXTRN _writeln_int:NEAR
EXTRN _write_string:NEAR
EXTRN _writeln_string:NEAR
EXTRN _read_char:NEAR
EXTRN _read_string:NEAR
EXTRN _read_int:NEAR
EXTRN _abs_int:NEAR
EXTRN _sqr_int:NEAR
EXTRN _odd_int:NEAR
EXTRN _sqrt_int:NEAR
