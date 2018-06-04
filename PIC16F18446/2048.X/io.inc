;;; interrupt service routine is re-entrant, shared by all consoles
in_isr
	movf	zOS_JOB,w	;void in_isr(void) {
	movwf	BSR		; bsr = rtosjob;// to access char_io var et al
	btfsc	zOS_AR0,6	; if (zOS_AR0 & 0x40) // from zOS_INP, zOS_AR0>0
	bcf	zOS_AR0,5	;  zOS_AR0 &= 0xdf; // zOS_AR0=tolower(zOS_AR0)
	movf	zOS_AR0,w	; switch (char_io = zOS_AR0) {
	xorlw	'H'		;  case 'H':
	movlw	NEIGHLF		;   COMMAND = 1<<1;
	btfsc	STATUS,Z	;   break;
	bra	newchar		;
	movf	zOS_AR0,w	;
	xorlw	'J'		;  case 'J':
	movlw	NEIGHDN		;   COMMAND = 1<<0;
	btfsc	STATUS,Z	;   break;
	bra	newchar		;
	movf	zOS_AR0,w	;
	xorlw	'K'		;  case 'K':
	movlw	NEIGHUP		;   COMMAND = 1<<3;
	btfsc	STATUS,Z	;   break;
	bra	newchar		;
	movf	zOS_AR0,w	;
	xorlw	'L'		;  case 'L':
	movlw	NEIGHDN		;   COMMAND = 1<<2; break;
	btfsc	STATUS,Z	;
	bra	newchar		;
	xorlw	'R'		;  case 'R':
	movlw	-1		;   COMMAND = -1; break;
	btfsc	STATUS,Z	;  default:
	bra	newchar		;   COMMAND = 0; return;
	clrf	COMMAND		; }
	zOS_RFI
newchar
	movwf	COMMAND		;} // in_isr()
monlast
	zOS_RFI
	
;;; re-entrant code to print grid outside of interrupt context here...
outdig
	
	return
	da	"   1"		;never exists
	da	"   2"
	da	"   4"
	da	"   8"
	da	"  16"
	da	"  32"
	da	"  64"
	da	" 128"
	da	" 256"
	da	" 512"
	da	"1024"
	da	"2048"
	da	"4096"
	da	"8192"
	da	"16Ki"
	da	"32Ki"
	
outval

	

outgrid	

	zOS_SWI	-1		;


	
gamejob	macro	p,rat,rts,hb,pin
	local	gameadr,gamead2,gamead3,endgame,vars,optlo,opthi
	pagesel	endgame
	goto	endgame
vars	set	0x20
optlo	set	optadrl-vars
opthi	set	optadrh-vars
	
gameadr
	incfsz	COMMAND,w	;inline void gamejob(p,rat,rts,hb,pin) {
	bra	gamead2		; if (COMMAND == -1) {
	pagesel	newgame
	call	newgame		;  newgame();
	bra	gamead3		; } else {
gamead2
	movf	COMMAND,w	;  if (COMMAND == 0)
	btfsc	STATUS,Z	;   return; // back to zOS_CON task
	return			;  else
	andlw	0x0f		;   turn(COMMAND & 0x0f);
	pagesel	turn
	call	turn		; }
gamead3
	pagesel	outgrid
	call	outgrid		; outgrid();
	clrf	COMMAND		; COMMAND = 0;
	return			;}

endgame
	zOS_INP	p,rat,rts,hb,pin,in_isr
	movlw	low gameadr
	movwi	optlo[FSR1]
	movlw	high gameadr
	movwi	opthi[FSR1]
	
	endm
