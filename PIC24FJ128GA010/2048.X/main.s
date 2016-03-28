.include "p24FJ128GA010.inc"

	.section psv psv
HELLO_MSG:
	.asciz	"2048-style game using vi keys HJKL to move, Esc to exit\n"
	
	.text
exp16inp:
	;; read tact switches here
	return
	
vi_input:	
	call	_inChar		;int16_t vi_input (void) {
	and	W0,#0x1f,W0	; do switch (0x1f & getchar()) {
	cp	W0,#0x01	; case 'a' - '`':
	bra	NZ,Lleft	;
.ifdef AUTOMOVE
	mov	#0x8000,W0	;
	return			;  return 0x8000;
.endif
Lleft:
	cp	W0,#0x08	; case 'h' - '`':
	bra	NZ,Ldown	;
	mov	#0x0002,W0	;
	return			;  return +2; // left
Ldown:
	cp	W0,#0x0a	; case 'j' - '`':
	bra	NZ,Lup		;
	mov	#0xfff8,W0	;
	return			;  return -8; // down
Lup:
	cp	W0,#0x0b	; case 'k' - '`':
	bra	NZ,Lright	;
	mov	#0x0008,W0	;
	return			;  return +8; // up 
Lright:
	cp	W0,#0x0c	; case 'l' - '`':
	bra	NZ,Lesc		;
	mov	#0xfffe,W0	;
	return			;  return -2; // right
Lesc:
	cp	W0,#0x1b	; case '\033':
	bra	NZ,vi_input	;  return 0; // quit
	clr	W0		; } while (1);
	return			;}

.global	_main
_main:
	mov	#HELLO_MSG,W0	;
	call	_configBasic	;
	call	_ssetup		;
Lgamelp:	
	.equ TWOROWLCD,2
.ifdef TWOROWLCD
	call	_LCD_Initialize	;
	mov	#TWOROWLCD,W0	;
	mov	#256,W1		;
.else
	mov	#4,W0		;
	mov	#2048,W1	;
.endif

.if 0
 mov #handle(vi_input),W2
 mov #handle(nullfunc),W3
 call autogame
.else
	mov #handle(vi_input),W2;
	mov #handle(_osimple),W3;
	call	game		;
	call	_summary	;
.endif
	goto	$
nullfunc:
	return
	.end

