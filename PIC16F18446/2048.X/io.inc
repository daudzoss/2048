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
celltab
	da	"    "		;static char* celltab[] = {"    ", // empty cell
	da	"   2"		;                          "   2",
	da	"   4"		;                          "   4",
	da	"   8"		;                          "   8",
	da	"  16"		;                          "  16",
	da	"  32"		;                          "  32",
	da	"  64"		;                          "  64",
	da	" 128"		;                          " 128",
	da	" 256"		;                          " 256",
	da	" 512"		;                          " 512",
	da	"1024"		;                          "1024",
	da	"2048"		;                          "2048",
	da	"4096"		;                          "4096",
	da	"8192"		;                          "8192",
	da	"16Ki"		;                          "16Ki", // 16384
	da	"32Ki"		;                          "32Ki"};// 32768
outcell
	andlw	0x0f		;void outcell(uint4_t w) {
	lslf	WREG		;
	lslf	WREG		;
	addlw	low outtab	;
	movwf	FSR0L		;
	movlw	high outtab	;
	clrf	FSR0H		;
	addwfc	FSR0H,f		; fsr0 = celltab[0x0f & w];
	movlw	5		; uint5_t i = 5;
	movwf	PCLATH		; char w = ' '; // first print a leading space
	movlw	' '		; do {
cellchr
	zOS_ARG	0		;  zOS_ARG(0, w); // print the character in WREG
	zOS_SWI	-1		;  zOS_SWI(-1); // calls its own char output SWI
	moviw	FSR0++		;  w = *fsr0++;
	decfsz	PCLATH,f	;
	bra	cellchr		; } while (--i > 0); // always loop 5x
	return			;}
	
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
