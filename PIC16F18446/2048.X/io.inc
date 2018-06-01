;;; service routine is re-entrant shared by all consoles
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
	xorlw	'N'		;  case 'N':
	movlw	-1		;   COMMAND = 255; break;
	btfsc	STATUS,Z	;  default:
	bra	newchar		;   COMMAND = 0; return;
	clrf	COMMAND		; }
	
	zOS_RFI
newchar
	movwf	COMMAND		;} // in_isr()
monlast
	zOS_RFI
	
outgrid	
;;; re-entrant code to print grid outside of interrupt context here...



	
gamejob	macro	p,rat,rts,hb,pin
	pagesel	endgame
	goto	endgame
	local	gameadr,endgame,vars,optlo,opthi
vars	set	0x20
optlo	set	optadrl-vars
opthi	set	optadrh-vars

	
gameadr
	movf	COMMAND,w	; if (COMMAND == 0)
	btfsc	STATUS,Z	;  return 0; // back to zOS_CON task
	return			; else {
	incfsz	COMMAND,

#if 0;copied from zOS_MAN()
	xorlw	'G'		;
	btfss	STATUS,Z	; caseG:
	bra	manchr		; case 'G': // Generate a fork/duplicate of job
	clrf	char_io		;  char_io = 0; // presume failure, so no retry
	
	movf	accumul,w	;  if (accumul == 0)
	btfsc	STATUS,Z	;   return 0;
	return			;  zOS_ARG(0, accumul);
	zOS_ARG	0
	zOS_ACC	accumul,numbase
	movlw	'J'		;  zOS_ACC(&accumul, &numbase); // reset
	movwf	char_io		;  if (zOS_SWI(zOS_FRK))
	zOS_SWI	zOS_FRK
	andlw	0x07		;   goto caseJ; // success, prints in job list
	btfsc	STATUS,Z	;  else
	clrf	char_io		;   break; // failure, drop to end of switch()

manchr
	movf	char_io,w	;
	xorlw	'H'		;
	btfss	STATUS,Z	; caseH:
	bra	manchr0		; case 'H': // find jobs by Handle (start addr)
	clrf	char_io		;  char_io = 0;

	movf	accumul,w	;  if (accumul == 0)
	iorwf	accumuh,w	;
	btfsc	STATUS,Z	;   return 0;
	return			;  zOS_ARG(0, accumul);
	movf	accumul,w	;
	zOS_ARG	0
	movf	accumuh,w	;
	zOS_ARG	1
	zOS_ACC	accumul,numbase
	movlw	'J'		;  zOS_ACC(&accumul, &numbase);
	movwf	char_io		;  if (zOS_SWI(zOS_FND))
	zOS_SWI	zOS_FND
	andlw	0x07		;   goto caseJ; // FIXME: table, from match down
	movwf	accumul		;
	btfsc	STATUS,Z	;  else
	clrf	char_io		;   break;
	
manchr0
	movf	char_io,w	;
	xorlw	'I'		;
	btfss	STATUS,Z	; caseI:
	bra	manchr1		; case 'I': // send a software Interrupt > 7
	clrf	char_io		;  char_io = 0; // with destreg zOS_AR1:zOS_AR0
	
	movf	destreg,w	;  zOS_ARG(0, destreg);
	clrf	destreg		;
	zOS_ARG	0
	movf	1+destreg,w	;  zOS_ARG(1, destreh);
	clrf	1+destreg	;
	zOS_ARG	1
	movf	accumul,w	;  w = accumul;
	zOS_ACC	accumul,numbase
	andlw	0xf8		;  zOS_ACC(&accumul, &numbase); // reset
	btfsc	STATUS,Z	;  if (w & 0xf8) {
	bra	reenabl		;   int w = zOS_SWI(accumul); // disable again
	movlp	0		;   INTCON &= ~(1<<GIE);// for zOS_AR and _BUF()
	call	0x02		;   zOS_ARG(1, w);
	zOS_ARG	0		;   zOS_ARG(0, 0);
#if 0
	clrf	zOS_AR1		;   zOS_BUF(rtosjob, p0); //print hex SWI result
	xorwf	zOS_AR1,f	;   zOS_ENA();
	xorwf	zOS_AR0,f	;   goto caseJ;
	zOS_BUF	FSR0,max,p0
#else
	zOS_ARG	1		;
	xorwf	zOS_AR0,f	;
	zOS_SWI	0xff
	movlw	'\r'		;
	zOS_ARG	0		;
	zOS_SWI	0xff		;
	movlw	'\n'		;
	zOS_ARG	0		;
	zOS_SWI	0xff		;
#endif
	
reenabl
	zOS_ENA

manchr1
	movf	char_io,w	; }
	xorlw	'J'		;
	btfss	STATUS,Z	; caseJ:
	bra	manchr2		; case 'J': // List struct for all running jobs

	decf	accumul,w	; // keep char_io='J' until last job line prints
	andlw	0x07		;
	btfsc	WREG,2		;  if ((accumul < 1) || (accumul > 5))
	movlw	zOS_NUM-1	;
	addlw	0x01		;
	movwf	accumul		;   accumul = zOS_NUM;
	bcf	INTCON,GIE	;  INTCON &= ~(1<<GIE); // to keep p0==p1 atomic
	pagesel	jobinfo
	movf	p0,w		;
	xorwf	p1,w		;  if (p0 == p1)
	btfsc	STATUS,Z	;   return jobinfo(); // will decrement accumul
	goto	jobinfo		;  zOS_ENA(); // re-enable interrupts if p0!=p1
	zOS_ENA
	retlw	0		;  return 0;//try again after caller advances p0

manchr2
	movf	char_io,w	;
	xorlw	'K'		;
	btfss	STATUS,Z	; caseK:
	bra	manchr3		; case 'K': // Kill a single job (# mandatory)
	clrf	char_io		;  char_io = 0;

	movf	accumul,w	;  if (accumul == 0)
	btfsc	STATUS,Z	;   return 0;
	return			;  zOS_ARG(0, accumul);
	zOS_ARG	0
	zOS_ACC	accumul,numbase
	movlw	'J'		;  zOS_ACC(&accumul, &numbase);
	movwf	char_io		;  zOS_SWI(zOS_END); // listed indicates failure
	zOS_SWI	zOS_END
;;; FIXME: put J at bottom so K onward don't pay a performance penalty awaiting
	
manchr3
	movf	char_io,w	;
	xorlw	'L'		;
	btfss	STATUS,Z	; caseL:
	bra	manchr4		; case 'L': // Launch a fresh instance of a job
	clrf	char_io		;  char_io = 0;

	movf	accumul,w	;  if (accumul == 0)
	btfsc	STATUS,Z	;   return 0;
	return			;  zOS_ARG(0, accumul);
	zOS_ARG	0
	zOS_ACC	accumul,numbase
	movlw	'J'		;  zOS_ACC(&accumul, &numbase); // reset
	movwf	char_io		;  if ((w = zOS_SWI(zOS_FRK)) != 0) {
	zOS_SWI	zOS_FRK
	andlw	0x07		;   zOS_ARG(0,w); zOS_SWI(zOS_RST);
	btfsc	STATUS,Z	;   goto caseJ; // success, prints in job list
	clrf	char_io		;  } else
	zOS_ARG	0
	zOS_SWI	zOS_RST		;   break; // failure, drop to end of switch()

manchr4
	movf	char_io,w	;
	xorlw	'N'		;
	btfss	STATUS,Z	; caseN:
	bra	manchr5		; case 'N': // New (parameterless) job at addr

	movf	accumul,w	;
	movwf	FSR0L		;
	movf	accumuh,w	;
	movwf	FSR0H		;
	clrw			;
	zOS_ARG	0
	zOS_ARG	1
	zOS_ARG	2
	zOS_ARG	3
	zOS_SWI	zOS_NEW
	zOS_ARG	0
;	zOS_BUF	FSR0,max,p0
;	movlw	'J'		;
;	movwf	char_io		;

;	movf	accumul,w	;  if (accumul == 0)
;	btfsc	STATUS,Z	;   return 0;
;	return			;  zOS_ARG(0, accumul);
	clrw			;
	zOS_ARG	0
	zOS_ACC	accumul,numbase
	movlw	'J'		;  zOS_ACC(&accumul, &numbase);
	movwf	char_io		;  if ((w = zOS_SWI(zOS_SLP)) != 0) {
;	zOS_SWI	zOS_SLP
;	andlw	0xff		;   accumul = w;
;	movwf	accumul		;   goto caseJ;
;	btfsc	STATUS,Z	;  } else
;	clrf	char_io		;   break;

manchr5
	movf	char_io,w	;
	xorlw	'P'		;
	btfss	STATUS,Z	; caseP:
	bra	manchr6		; case 'P': // Pause job by putting it to Sleep
	clrf	char_io		;  char_io = 0;

	movf	accumul,w	;  if (accumul == 0)
	btfsc	STATUS,Z	;   return 0;
	return			;  fsr1 = 0x10 * (1 + accumul) + zOS_PCH;
	movlw	'J'		;
	movwf	char_io		;
	zOS_MEM	FSR1,accumul,zOS_PCH
	movf	INDF1,w		;  if (*fsr1) { // is a valid (PCH not 0x00) job
	btfsc	STATUS,Z	;   *fsr |= 0x80;
	clrf	char_io		;   goto caseJ;
	iorlw	0x80		;  } else {
	movf	INDF1,f		;
	btfss	STATUS,Z	;
	movwf	INDF1		;   zOS_ACC(&accumul, &numbase);
	btfsc	STATUS,Z	;   break; // only clear accumul if not caseJ
	bra	manchr6		;  }
	zOS_ACC	accumul,numbase
	
manchr6
	movf	char_io,w	;
	xorlw	'Q'		;
	btfss	STATUS,Z	; caseQ:
	bra	manchr7		; case 'Q': // Quit without wake (off)
	clrf	char_io		;  char_io = 0;
	
	bcf	WDTCON,SWDTEN	;  WDTCON &= ~(1<<SWDTEN);
	movf	accumul,f	;
	btfss	STATUS,Z	;  if (accumul)
	sleep			;   sleep(); // never wakes up

manchr7
	movf	char_io,w	;
	xorlw	'R'		;
	btfss	STATUS,Z	; caseR:
	bra	manchr8		; case 'R': // Resume a pause/asleep job 
	clrf	char_io		;  char_io = 0;

	swapf	accumul,w	;  if (accumul == 0x5a /*e.g.*/)
	xorwf	accumul,w	;
	addlw	1		;
	btfsc	STATUS,Z	;
	reset			;   reset();
	
	movf	accumul,w	;  if (accumul == 0)
	btfsc	STATUS,Z	;   return 0;
	return			;  fsr1 = 0x10 * (1 + accumul) + zOS_PCH;
	movlw	'J'		;
	movwf	char_io		;  if (*fsr1 &= ~(1<<zOS_WAI)) {
	zOS_MEM	FSR1,accumul,zOS_PCH
	movlw	0x7f		;   goto caseJ; // valid job won't be 0 or 0x80
	andwf	INDF1,f		;  } else {
	btfss	STATUS,Z	;   zOS_ACC(&accumul, &numbase);
	bra	manchr8		;
	zOS_ACC	accumul,numbase
	clrf	char_io		;   break;
	
manchr8
#if 0;has never worked
	movf	char_io,w	;  }
	xorlw	'S'		;
	btfss	STATUS,Z	;
	bra	manchr9		; case 'S': // Stack dump is actually scratch
	clrf	char_io		;  char_io = 0; // always succeeds, no arg

	decf	accumul,w	; // keep char_io='S' until last job line prints
	andlw	0x07		;
	btfsc	WREG,2		;  if ((accumul < 1) || (accumul > 5))
	movlw	zOS_NUM-1	;
	addlw	0x01		;
	movwf	accumul		;   accumul = zOS_NUM;
	bcf	INTCON,GIE	;  INTCON &= ~(1<<GIE); // to keep p0==p1 atomic
	pagesel	stkinfo
	movf	p0,w		;
	xorwf	p1,w		;  if (p0 == p1)
	btfsc	STATUS,Z	;   return jobinfo(); // will decrement accumul
	goto	stkinfo		;  zOS_ENA(); // re-enable interrupts if p0!=p1
	zOS_ENA
	retlw	0		;  return 0;//try again after caller advances p0
#endif
	
manchr9
	movf	char_io,w	;
	xorlw	'Z'		;
	btfss	STATUS,Z	;
	bra	mannone		; case 'Z': // go to low-power Zz mode for time
	clrf	char_io		;  char_io = 0;
	
	bsf	WDTCON,SWDTEN	;  if (w = accumul<<1) { // WDT prescalre
	lslf	accumul,w	;   w |= 1<<SWDTEN; // enable the wakeup
	btfsc	STATUS,Z	;   
	bra	mannone		; 
	iorlw	1<<SWDTEN	;
	movwf	WDTCON		;
	sleep			;  break;  // wakes up according to prescaler

mannone
	retlw	0		; } return 0; //naught to do }

#if 0;has never worked	
	;guaranteed to arrive with p0=p1, interrupts off and in the correct bank
stkinfo
	movf	wrap,f		;int8_t stkinfo(void) {
	movwf	p0		; p0 = p1 = wrap;
	movwf	p1		;
	movlw	low zOS_STK	;
	movwf	FSR0L		;
	movlw	high zOS_STK	;
	movwf	FSR0H		;
	decf	accumul,w	;
	brw			;
	addfsr	FSR0,6		;
	addfsr	FSR0,6		;
	addfsr	FSR0,6		;
	addfsr	FSR0,6		; fsr0 = zOS_STK + 6 * (5 - accumul);
	zOS_LOC	FSR1,zOS_JOB,buf
	movlw	'\r'		; fsr1 = (zOS_JOB << 7) + buf;
	movwi	FSR1++		;
	movlw	'\n'		;
	movwi	FSR1++		;
	movlw	'-'		;
	movwi	FSR1++		;
	movf	accumul,w	;
	addlw	-12		; // print this stack offset as -0/-1/-2/-3/-4
	zOS_HEX
	movwi	FSR1++		; p1 += sprintf(p1, "\r\n-%1X", accumul & 7);
	movlw	3		;
	movwf	accumuh		; for (accumuh = 3; accumuh; accumuh--) {
stkloop
	movlw	' '		;
	movwi	FSR1++		;  p1 += sprintf(p1, " %04X", *((int*) fsr0));
	moviw	--FSR0		;
	movwi	FSR1++		;
	moviw	--FSR0		;
	movwi	FSR1++		;
	decfsz	accumuh,f	;
	bra	stkloop		; }
	
	movf	FSR1L,w		;
	movwf	p1		; w = accumul--; // return with w as nonzero job
	movf	accumul,w	; if (accumul == 0)
	decf	accumul,f	;  char_io = 0;// final row in table was printed
	btfsc	STATUS,Z	; zOS_ENA(); // interrupts back ON!
	clrf	char_io		; return w;
	zOS_ENA
	return			;} // stkinfo()
#endif
	;guaranteed to arrive with p0=p1, interrupts off and in the correct bank
jobinfo
	movf	wrap,w		;int8_t jobinfo(void) {
	movwf	p0		; p0 = p1 = wrap;
	movwf	p1		; fsr0 = 0x10 * (1 + accumul); //FIXME: 2+
	zOS_MEM	FSR0,accumul,0
	zOS_LOC	FSR1,zOS_JOB,buf
	movlw	'\r'		; fsr1 = (zOS_JOB << 7) + buf;
	movwi	FSR1++		;
	movlw	'\n'		;
	movwi	FSR1++		;
	movf	accumul,w	; // print this job number 5/4/3/2/1
	zOS_HEX
	movwi	FSR1++		; p1 += sprintf(p1, "\r\n%1X", accumul);
	
	moviw	zOS_HDH[FSR0]	;
	andlw	1<<zOS_PRB	;
	movlw	':'		; // print '*' if the job is privileged else ':'
	btfss	STATUS,Z	;
	movlw	'*'		; p1 += sprintf(p1, "%c", (zOS_HDH[fsr0] &
	movwi	FSR1++		;                    (1<<zOS_PRB)) ? '*' : ':');
	
	zOS_IHF	zOS_HDH,FSR0,FSR1
	zOS_IHF	zOS_HDL,FSR0,FSR1
	movlw	' '		; 
	movwi	FSR1++		;
	movlw	'P'		; // print the 4-hex-digit header then PC
	movwi	FSR1++		;
	movlw	'C'		; p1 += sprintf(p1, "%04X PC",
	movwi	FSR1++		;         (zOS_HDH[fsr0] << 8) + zOS_HDL[fsr0]);
	
	moviw	zOS_PCH[FSR0]	;
	andlw	1<<zOS_WAI	;
	movlw	'='		; // print '=' if the job is sleeping else 'z'
	btfss	STATUS,Z	;
	movlw	'z'		; p1 += sprintf(p1, "%c", (zOS_PCH[fsr0] &
	movwi	FSR1++		;                    (1<<zOS_WAI)) ? 'z' : ':');
	
	zOS_IHF	zOS_PCH,FSR0,FSR1
	moviw	zOS_PCH[FSR0]	; // drop out after PCH if 0 (job is deleted)
	btfsc	STATUS,Z	; p1 += sprintf(p1, "%02X", zOS_PCH[fsr0]);
	bra	manname		; if (zOS_PCH[fsr0] & 0xff00) {
	zOS_IHF	zOS_PCL,FSR0,FSR1
	movlw	' '		;  // print the low byte of program counter
	movwi	FSR1++		;  p1 += sprintf(p1, "%02X", zOS_PCL[fsr0]); 
	moviw	zOS_ISH[FSR0]	;
	btfsc	STATUS,Z	;  // drop out after PCL if no interrupt routine
	bra	manname		;  if (zOS_ISH[fsr0] & 0xff00) {
	movlw	'I'		;
	movwi	FSR1++		;
	movlw	'S'		;
	movwi	FSR1++		;
	movlw	'R'		;
	movwi	FSR1++		;
	movlw	'@'		;
	movwi	FSR1++		;   // print ISR@ then 4-hex-digit routine addr
	zOS_IHF	zOS_ISH,FSR0,FSR1
	zOS_IHF	zOS_ISR,FSR0,FSR1
	movlw	'('		;   p1 += sprintf(p1, " ISR@%04X",
	movwi	FSR1++		;         (zOS_ISH[fsr0] << 8) + zOS_ISR[fsr0]);
	movlw	'h'		;
	movwi	FSR1++		;
	zOS_IHF	zOS_HIM,FSR0,FSR1
	movlw	's'		;
	movwi	FSR1++		;  // print (hw HwIMask sw SwIMask) scrunched up
	zOS_IHF	zOS_SIM,FSR0,FSR1
	movlw	')'		;   p1 += sprintf(p1, "(h%02Xs%02X) ",
	movwi	FSR1++		;                 zOS_HIM[fsr0], zOS_SIM[fsr0]);
manname
	movlw	' '		;
	movwi	FSR1++		;
	movlw	0x22 ;'"'	;
	movwi	FSR1++		;
	moviw	zOS_PCH[FSR0]	;
	btfss	STATUS,Z	;
	bra	manlive		;   if (zOS_PCH[fsr0] == 0) {
	movlw 	low mandead	;    static char mandead = "<not running>";
	movwf	FSR0L		;
	movlw	high mandead	;
	movwf	FSR0H		;    fsr0 = mandead;
	movlw	mandead-manlive	;
	movwf	char_io		;    char_io = strlen(mandead);
	bra	manloop		;
mandead
	zOS_NAM	"<not running>"
manlive
	moviw	zOS_HDL[FSR0]	;   } else {
	movwf	char_io		;
	moviw	zOS_HDH[FSR0]	;
	iorlw	0x80		;
	movwf	FSR0H		;    fsr0 = 0x8000 | (zOS_HDH[fsr0] << 8) ;
	movf	char_io,w	;
	movwf	FSR0L		;    fsr0 |= zOS_HDL[fsr0];
	moviw	--FSR0		;
	iorlw	0xe0		;
	movwf	char_io		;    char_io = 0xe0 | *--fsr0; // max 32? chars
#if 1
	addwf	FSR0L,f		;
	btfss	STATUS,C	;
	decf	FSR0H,f		;   for (fsr0 -= char_io; ++char_io; fsr1++) {
#else	
	local	manbit0,manbit1
	movf	FSR0L,w		;
	addwf	char_io,w	;
	btfss	WREG,7		;
	bra	manbit0		;
	btfss	FSR0L,7		;
	decf	FSR0H,f		;
	bra	manbit1		;
manbit0
	btfsc	FSR0L,7		;
	decf	FSR0H,f		;
manbit1
	movwf	FSR0L		;   for (fsr0 -= char_io; ++char_io; fsr1++) {
#endif
manloop
	moviw	FSR0++		;    char w = *fsr0++ ;
	btfsc	WREG,7		;
	bra	crlf		;    if ((w > '\0177') ||
	addlw	0-0x20		;
	btfsc	WREG,7		;
	bra	crlf		;        (w < ' '))
	addlw	0x20		;     break;
	movwi	FSR1++		;    *fsr1 = w; // added to buffer
	incfsz	char_io,f	;
	bra	manloop		;   }
crlf	
	movlw	0x22 ;'"'	;
	movwi	FSR1++		;
	movlw	'\r'		;  }
	movwi	FSR1++		; }
	movlw	'\n'		; // print a second \r\n, double-spacing table  
	movwi	FSR1++		; p1 += sprintf(p1, "\r\n");
	
	movlw	'J'		;
	movwf	char_io		;
	movf	FSR1L,w		;
	movwf	p1		; w = accumul--; // return with w as nonzero job
	movf	accumul,w	; if (accumul == 0)
	decf	accumul,f	;  char_io = 0;// final row in table was printed
	btfsc	STATUS,Z	; zOS_ENA(); // interrupts back ON!
	clrf	char_io		; return w;
	zOS_ENA
	return			;
#endif;copy from zOS_MAN()
	
	







endgame
	zOS_INP	p,rat,rts,hb,pin,in_isr
	movlw	low gameadr
	movwi	optlo[FSR1]
	movlw	high gameadr
	movwi	opthi[FSR1]
	endm
