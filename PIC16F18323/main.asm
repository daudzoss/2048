	processor 16f18323
#include p16f18323.inc
	org 0x000
	pagesel	main
	goto	main
	org 0x004
	;; interrupt vector
	
#include game.asm

;;; main() must finish under 0x800
main
	pagesel	newgame
	call	newgame
LASTMOV	equ	0x70
	movlw	NEIGHUP
	movwf	LASTMOV

loop
	movf	LASTMOV,w
	xorlw	NEIGHUP|NEIGHLF
	movwf	LASTMOV
	call	turn
	bra	loop

	org 0x7ff
	end
