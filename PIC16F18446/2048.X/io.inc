;;; shared by all 
in_isr
	
#if 0
	movf	RTOSJOB,w	;void monisr(void) {
	movwf	BSR		;  bsr = rtosjob;// to access char_io var et al
	pagesel	monbufd
	movlw	0xe0		; // from RTOSINP isr with char RTOSAR0>0
	addwf	RTOSAR0,w	;
	btfss	WREG,7		; // refuse to echo unprintable characters
	call	monbufd		; if (RTOSAR0 > 31 && monbuf(rtosjob,p0) > 0) {
	andlw	0x1		;  // successful echo into circular buffer
	pagesel	monlast
	btfsc	STATUS,Z	;
	goto	monlast		;
	
	movf	RTOSAR0,w	;  // handle '~' before the tolower() conversion
	xorlw	'~'		;
	btfss	STATUS,Z	;
	bra	monchr1		;  if (RTOSAR0 == '~') {
	pagesel	mon0
	call	mon0		;
	pagesel	monx
	call	monx		;
	comf	accumul,f	;   accumul = ~accumul;
	comf	accumuh,w	;
	movwf	accumuh		;
	movwf	char_io		;   char_io = accumuh = ~accumuh; // preserve
	pagesel	monhex
	call	monhex		;   monhex(rtosjob, p0);
	movf	accumul,w	;   accumuh = accumul; // accumuh overwritten
	movwf	accumuh		;   monlsb(rtosjob, p0);
	pagesel	monlsb
	call	monlsb		;   accumuh = char_io; // accumuh now restored
	movf	char_io,w	;   char_io = 0; // completely handled in ISR
	movwf	accumuh		;   RTOSRFI();
	clrf	char_io		;  }
	RTOSRFI

monchr1
	btfsc	RTOSAR0,6	;  if (RTOSAR0 & 0x40)
	bcf	RTOSAR0,5	;   RTOSAR0 &= 0xdf; // RTOSAR0=tolower(RTOSAR0)
	movf	RTOSAR0,w	;//FIXME: ` { | } ~ DEL mapped onto @ [ \ ] ^ _
	movwf	char_io		;
	xorlw	0x08		;  switch (char_io = RTOSAR0) {
	movlw	0x7f		;
	btfss	STATUS,Z	;  case '\b':
	movf	char_io,w	;
	xorlw	0x7f		;
	btfss	STATUS,Z	;  case '\0177':
	bra	monchr2		;
	movlw	'\r'		;
	pagesel	monbufs
	call	monbufs		;   monbuf(rtosjob, p0, '\r');
	pagesel	monprmp
	goto	monprmp		;   goto monprmp;
	
monchr2
	movf	char_io,w	;
#if 0
	xorlw	0x0a		;
	movlw	0x0d		;
	btfss	STATUS,Z	;  case '\n':
	movf	char_io,w	;
#endif	
	xorlw	0x0d		;
	btfss	STATUS,Z	;  case '\r':
	bra	monchr3		;   monbuf(rtosjob, p0, '\n');// follows the \r
	movlw	'\r'		;
	pagesel	monbufs		;
	call	monbufs		;
	pagesel	monlf		;
	call	monlf		;
	
	movf	destreg,w	;   // repeat \r's can set a whole range of
	movwf	FSR0L		;   // addresses to zero???
	movf	1+destreg,w	;
	movwf	FSR0H		;   fsr0 = destreg;
	iorwf	FSR0L,w		;
	pagesel	monprmp
	btfsc	STATUS,Z	;
	goto	monprmp		;   if (fsr0) { // destreg was set by ' ' or =
	movf	accumul,w	;    if (fsr0 & 0x8000 == 0)
	btfss	FSR0H,7		;
	movwi	FSR0++		;     *fsr0 = accumul & 0x00ff; // not in flash
	movf	FSR0L,w		;
	movwf	destreg		;
	movf	FSR0H,w		;    destreg++; // advances for next access
	movwf	1+destreg	;   }
	pagesel	monprmp
	goto	monprmp		;   goto monprmp;

monchr3
	movf	char_io,w	;
	xorlw	','		;
	movlw	' '		;
	btfsc	STATUS,Z	;
	movwf	char_io		;  case ',': // synonym for ' '
	movf	char_io,w	;
	xorlw	' '		;
	btfsc	STATUS,Z	;  case ' ':
	bra	mondump		;
	movf	char_io,w	;
	xorlw	'.'		;
	btfsc	STATUS,Z	;  case '.':
	bra	mondump		;
	movf	char_io,w	;
	xorlw	'='		;
	btfss	STATUS,Z	;  case '=':
	bra	monchr4		;

mondump
	movf	accumul,w	;   // pressing ' ' or '.' or '=' should apply
	iorwf	accumuh,w	;   // to the recently incremented address from
	btfsc	STATUS,Z	;   // a previous operation (if any) or to an
	bra	mondest		;   // an address typed immediately before it
	movf	accumul,w	;
	movwf	destreg		;
	movf	accumuh,w	;   if (accumul) // typed a value before ' '/=
	movwf	1+destreg	;    destreg = accumul; // otherwise no clobber
	movf	char_io,w	;   if (char_io == ' ') {
	xorlw	' '		;    char_io = 0; // all we do is a destreg xfer
	pagesel	monzero
	btfsc	STATUS,Z	;    break;
	goto	monzero		;   }
mondest
	btfss	1+destreg,7	;   if (destreg & 0x8000) { // flash, not RAM
	bra	monram		;
	pagesel	mon0
	call	mon0		;    putchar('0');
	pagesel	monx
	call	monx		;    putchar('x');
	movf	destreg,w	;
	movwf	FSR0L		;
	movf	1+destreg,w	;
	movwf	FSR0H		;    fsr0 = destreg;
	RTOSPSH	BSR
	banksel	RTOSADL
	movf	FSR0L,w		;    RTOSPSH(&bsr);
	movwf	RTOSADL		;
	movf	FSR0H,w		;
	movwf	RTOSADH		;    RTOSAD = fsr0;
	RTOSRDF
	movf	RTOSRDH,w	;    RTOSRDF();
	movwf	RTOSAR0		;    RTOSARG(0,RTOSRDH); // only way to access
	RTOSPOP	BSR
	movf	RTOSAR0,w	;    RTOSPOP(&bsr);
	movwf	accumuh		;
	pagesel	monhex
	call	monhex		;    monhex(rtosjob, p0, accumuh=0);// high byte
	movf	destreg,w	;
	movwf	FSR0L		;
	movf	1+destreg,w	;
	movwf	FSR0H		;    fsr0 = destreg; // monhex() clobbered fsr0
	moviw	FSR0++		;
	movwf	accumul		;
	movf	FSR0L,w		;
	movwf	destreg		;    accumuh = *fsr0++;
	movf	FSR0H,w		;    destreg = fsr0;
	movwf	1+destreg	;    monlsb(rtosjob, p0, accumuh);  //      LSB
	movf	accumul,w	;
	pagesel	monlsb	
	call	monlsb		;    moncrlf(rtosjob, p0);          //     \r\n
#ifdef RTOSMIN
#else
	local	disasmb,disasmr
	pagesel	disasmb
	goto	disasmb		;    goto disasmb; disasmr:
disasmr
#endif	
	movlw	'\r'
	pagesel	monbufs
	call	monbufs
	pagesel	monlf
	call	monlf		;    goto monprmp;
	pagesel	monprmp
	goto	monprmp		;   }
	
monram
	pagesel	mon0
	call	mon0		;
	pagesel	monx
	call	monx		;
	movf	destreg,w	;
	movwf	FSR0L		;
	movf	1+destreg,w	;
	movwf	FSR0H		;   fsr0 = destreg;
	moviw	FSR0++		;
	movwf	accumuh		;   accumuh = *fsr0++;
	pagesel	monhex
	call	monhex		;   monhex(p0, accumuh);

	movf	char_io,w	;
	xorlw	'.'		;   // then exits in the '.' case to just print
	btfss	STATUS,Z	;   if (char_io == '.') {
	bra	monramd		;
	movf	FSR0L,w		;
	movwf	destreg		;
	movf	FSR0H,w		;
	movwf	1+destreg	;    destreg = fsr0;
	movlw	'\r'		;    monbufs('\r');
	pagesel	monbufs
	call	monbufs		;    monbufs('\n');
	pagesel	monlf
	call	monlf		;    goto monprmp;
	pagesel	monprmp
	goto	monprmp		;   }
monramd
	movf	char_io,w	;   // or follow by 3 backspaces in the '=' case
	xorlw	'.'		;   // to show that \r will result in a 0 write
	btfss	STATUS,Z	;
	movlw	3		;
	pagesel	monback
	call	monback		;   monback(rtosjob, p0, (char_io == '.')?0:3);
	clrf	char_io		;   char_io = 0;
	RTOSRFI			;  break;

monchr4
	movf	char_io,w	;
	xorlw	'X'		;
	btfss	STATUS,Z	;  case 'X':
	bra	monchr5		;
	movlw	0x10		;   numbase = 16;
	movwf	numbase		;   char_io = 0;
	clrf	char_io		;  break;
	RTOSRFI

monchr5
	movf	char_io,w	;
	xorlw	'%'		;
	btfss	STATUS,Z	;  case '%':
	bra	monchr6		;
	movlw	0x9b		;
	addwf	accumul,w	;
	btfsc	WREG,7		;
	bra	monpctg		;   if (accumul > 102)
	movlw	0x66		;
	movwf	accumul		;    accumul = 102;
monpctg
	movf	accumul,w	;   accumul = RTOSPCT(accumul);
	RTOSPCT	accumul
	movf	accumul,w	;  monecho:
	movwf	accumuh		;   accumuh = accumul;
	pagesel	monhex		;   monhex(rtosjob, p0); print as e.g. 50%0x7d
	call	monhex		;   accumuh = 0;
	clrf	accumuh		;   char_io = 0;
	clrf	char_io		;  break;
	RTOSRFI
	
monchr6
	movf	char_io,w	;
	xorlw	'?'		;
	btfss	STATUS,Z	; case '?':
	bra	monwrit		;
	movlw	0-1		;
	movwf	destreg		;  destreg = -1;
	movlw	0x3b		;
	movwf	char_io		;  // fall through with "-1,accumul" to readback
monwrit
	movf	char_io,w	;
	xorlw	0x3b		;
	btfss	STATUS,Z	;  case ';': // store highest priv job's globals
	bra	mondflt		;
	movlw	RTOSNUM+1	;
	movwf	RTOSJOB		; rtosjob = RTOSNUM+1;// search from high to low
	RTOSMEM	FSR0,RTOSJOB,0	; fsr0 = 0x10 * (1 + RTOSJOB);
monrtry
	RTOSLIV	FSR0,RTOSJOB,0,mondflt
	moviw	RTOSHDH[FSR0]	; do {
	btfss	WREG,RTOSPRB	;  RTOSLIV(fsr0, rtosjob, 0, clcchr8); // found!
	bra	monrtry		; } while (RTOSHDH[fsr0] & (1<<RTOSPRB) == 0);
	RTOSGLO	FSR0,RTOSJOB
	movf	accumul,w	; fsr0 = 0x70 + 2*rtosjob; // found! privileged!
	movwi	1[FSR0]		; 1[fsr0] = accumul & 0x00ff;
	movf	destreg,w	;
	movwi	0[FSR0]		; 0[fsr0] = destreg & 0x00ff;
	movwf	1+destreg	; destreg <<= 8;
	moviw	1[FSR0]		;
	movwf	destreg		; destreg |= accumul & 0x00ff;
	pagesel	monempty
	goto	monempty	; clcchr8:
	
mondflt
	movlw	0-0x30		;  default:
	addwf	char_io,f	;
	btfsc	char_io,7	;
	bra	monchr9 	;   if ((char_io -= ('0'&0xdf /*0x10*/)) >= 0) {
	movlw	0-0x10		;
	addwf	char_io,w	;
	btfsc	WREG,7		;    if (char_io > 0x10)
	bra	$+3		;
	movlw	0xf9		;
	addwf	char_io,f	;     char_io -= 0x07;// 0x41->0x11->0x0a... so
	btfss	STATUS,Z	;                     // or :=0x0a,...,?=0x0f,
	bra	monchr7		;                     // or A=0x2a,B=0x2b,...
	movf	accumul,w	;                     // G=0x30,...,Z=0x43
	iorwf	accumuh,w	;    if ((char_io == 0) &&
	btfss	STATUS,Z	;        (accumul == 0) && (accumuh == 0)) {
	bra	monchr7		;     numbase &= ~2; // digit(s) leading 0(s),
	bcf	numbase,1	;     char_io = 0;
	clrf	char_io		;     break;         // just go into octal mode
	RTOSRFI
	
monchr7
	movlw	0xf0		;
	andwf	char_io,w	;
	btfss	STATUS,Z	;    } else if ((char_io & 0xf0 == 0) // 0-9,a-f
	bra	monsave		;              && (numbase & 0x10)) { // base 16
	btfss	numbase,4	;
	bra	monchr8		;
	swapf	accumuh,f	;
	movlw	0xf0		;
	andwf	accumuh,f	;     accumuh <<= 4;
	swapf	accumul,w	;
	andlw	0x0f		;
	iorwf	accumuh,f	;     accumuh |= accumul >> 4;
	movlw	0x0f		;
	andwf	char_io,f	;     char_io &= 0x0f;
	andwf	accumul,f	;     accumul &= 0x0f;
	swapf	accumul,w	;
	iorwf	char_io,w	;     accumul = (accumul << 4) | char_io;
	movwf	accumul		;     char_io = 0;
	clrf	char_io		;     break;
	RTOSRFI
	
monchr8
	movf	char_io,w	;    } else /*if (char_io <= 9)*/ {
	andlw	0xf0		;     uint16_t sum;
	btfss	STATUS,Z	;     accumuh <<= 1;
	bra	monsave		;     accumuh |= (accumul & 0x80) ? 1 : 0;
				;     accumul <<= 1;
	lslf	accumul,f	;     w = accumul;//w keeps original accumul<<1
	rlf	accumuh,f	;     accumuh <<= 1;
	movf	accumul,w	;     accumuh |= (accumul & 0x80) ? 1 : 0;
				;     accumul <<= 1;
	lslf	accumul,f	;     accumuh |= (accumul & 0x80) ? 1 : 0;
	rlf	accumuh,f	;     accumul <<= 1; // accumuh:accumul <<= 3;
				;     if (numbase & 2) { // base 10 presumed
	lslf	accumul,f	;      sum = (accumuh<<8)+accumul + w;
	rlf	accumuh,f	;      accumul = sum & 0x00ff;
	btfss	numbase,1	;      accumuh = sum >> 8;
	bra	$+4		;     }
	addwf	accumul,f	;     sum = (accumuh<<8)+accumul + char_io&0x0f;
	movlw	0		;     accumul = sum & 0x00ff;
	addwfc	accumuh,f	;     accumuh = sum >> 8;
	movf	char_io,w	;     break;
	andlw	0x0f		;    }
	addwf	accumul,f	;   } // if we get here, restore input character
	movlw	0		;   char_io += 0x37; // 0x10->'G',0x11->'H' etc.
	addwfc	accumuh,f	;   RTOSAR1 = accumul;
	RTOSRFI
monchr9
	movlw	0-0x37		;   if (isr) goto isr; // with RTOSAR1=accumul
monsave
	movlw	0x37		;  } // switch ()
	addwf	char_io,f	;  char_io = 0;
	movf	accumul,w	; } // if () // was less than 32 so aborts
	movwf	RTOSAR1		;
	if (isr)
	pagesel	isr
	 goto	isr		; RTOSRFI(); // reached only if isr == 0
	else
	 RTOSRFI
	endif

;;; 
monprmp
	movf	1+destreg,w	;monprmp:
	movwf	accumuh		; accumuh = destreg>>8;
	iorwf	destreg,w	; if (destreg) { // prompt with destreg if non-0
	pagesel	mon0
	btfsc	STATUS,Z	;  monhex(rtosjob, p0);
	bra	monzero		;  accumuh = destreg & 0xff;
	call	mon0		;
	pagesel	monx
	call	monx		;
	pagesel	monhex
	call	monhex		;  monlsb(rtosjob, p0);
	movf	destreg,w	; }
	movwf	accumuh		;monlast: RTOSACC(&accumul,&numbase); RTOSRFI();
	pagesel	monlsb
	call	monlsb		;         char_io = 0;
monempty
	pagesel	monspc
	call	monspc		;    putchar(' ');
monzero
	RTOSACC	accumul,numbase
monlast
	clrf	char_io		;} // RTOSMON()
	RTOSRFI
#endif ;pasted from zOS_MON

outgrid	
;;; re-entrant code to print grid here...

gamejob	macro	p,rat,rts,hb,pin
	pagesel	endgame
	goto	endgame
	local	gameadr,endgame,vars,optlo,opthi
vars	set	0x20
optlo	set	optadrl-vars
opthi	set	optadrh-vars

gameadr
#if 0;copied from zOS_MAN()
	movf	char_io,w	; if (char_io == 0)
	btfsc	STATUS,Z	;  return 0; // back to RTOSCON task
	return			; switch (char_io) {

	xorlw	'G'		;
	btfss	STATUS,Z	; caseG:
	bra	manchr		; case 'G': // Generate a fork/duplicate of job
	clrf	char_io		;  char_io = 0; // presume failure, so no retry
	
	movf	accumul,w	;  if (accumul == 0)
	btfsc	STATUS,Z	;   return 0;
	return			;  RTOSARG(0, accumul);
	RTOSARG	0
	RTOSACC	accumul,numbase
	movlw	'J'		;  RTOSACC(&accumul, &numbase); // reset
	movwf	char_io		;  if (RTOSSWI(RTOSFRK))
	RTOSSWI	RTOSFRK
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
	return			;  RTOSARG(0, accumul);
	movf	accumul,w	;
	RTOSARG	0
	movf	accumuh,w	;
	RTOSARG	1
	RTOSACC	accumul,numbase
	movlw	'J'		;  RTOSACC(&accumul, &numbase);
	movwf	char_io		;  if (RTOSSWI(RTOSFND))
	RTOSSWI	RTOSFND
	andlw	0x07		;   goto caseJ; // FIXME: table, from match down
	movwf	accumul		;
	btfsc	STATUS,Z	;  else
	clrf	char_io		;   break;
	
manchr0
	movf	char_io,w	;
	xorlw	'I'		;
	btfss	STATUS,Z	; caseI:
	bra	manchr1		; case 'I': // send a software Interrupt > 7
	clrf	char_io		;  char_io = 0; // with destreg RTOSAR1:RTOSAR0
	
	movf	destreg,w	;  RTOSARG(0, destreg);
	clrf	destreg		;
	RTOSARG	0
	movf	1+destreg,w	;  RTOSARG(1, destreh);
	clrf	1+destreg	;
	RTOSARG	1
	movf	accumul,w	;  w = accumul;
	RTOSACC	accumul,numbase
	andlw	0xf8		;  RTOSACC(&accumul, &numbase); // reset
	btfsc	STATUS,Z	;  if (w & 0xf8) {
	bra	reenabl		;   int w = RTOSSWI(accumul); // disable again
	movlp	0		;   INTCON &= ~(1<<GIE);// for RTOSAR and _BUF()
	call	0x02		;   RTOSARG(1, w);
	RTOSARG	0		;   RTOSARG(0, 0);
#if 0
	clrf	RTOSAR1		;   RTOSBUF(rtosjob, p0); //print hex SWI result
	xorwf	RTOSAR1,f	;   RTOSENA();
	xorwf	RTOSAR0,f	;   goto caseJ;
	RTOSBUF	FSR0,max,p0
#else
	RTOSARG	1		;
	xorwf	RTOSAR0,f	;
	RTOSSWI	0xff
	movlw	'\r'		;
	RTOSARG	0		;
	RTOSSWI	0xff		;
	movlw	'\n'		;
	RTOSARG	0		;
	RTOSSWI	0xff		;
#endif
	
reenabl
	RTOSENA

manchr1
	movf	char_io,w	; }
	xorlw	'J'		;
	btfss	STATUS,Z	; caseJ:
	bra	manchr2		; case 'J': // List struct for all running jobs

	decf	accumul,w	; // keep char_io='J' until last job line prints
	andlw	0x07		;
	btfsc	WREG,2		;  if ((accumul < 1) || (accumul > 5))
	movlw	RTOSNUM-1	;
	addlw	0x01		;
	movwf	accumul		;   accumul = RTOSNUM;
	bcf	INTCON,GIE	;  INTCON &= ~(1<<GIE); // to keep p0==p1 atomic
	pagesel	jobinfo
	movf	p0,w		;
	xorwf	p1,w		;  if (p0 == p1)
	btfsc	STATUS,Z	;   return jobinfo(); // will decrement accumul
	goto	jobinfo		;  RTOSENA(); // re-enable interrupts if p0!=p1
	RTOSENA
	retlw	0		;  return 0;//try again after caller advances p0

manchr2
	movf	char_io,w	;
	xorlw	'K'		;
	btfss	STATUS,Z	; caseK:
	bra	manchr3		; case 'K': // Kill a single job (# mandatory)
	clrf	char_io		;  char_io = 0;

	movf	accumul,w	;  if (accumul == 0)
	btfsc	STATUS,Z	;   return 0;
	return			;  RTOSARG(0, accumul);
	RTOSARG	0
	RTOSACC	accumul,numbase
	movlw	'J'		;  RTOSACC(&accumul, &numbase);
	movwf	char_io		;  RTOSSWI(RTOSEND); // listed indicates failure
	RTOSSWI	RTOSEND
;;; FIXME: put J at bottom so K onward don't pay a performance penalty awaiting
	
manchr3
	movf	char_io,w	;
	xorlw	'L'		;
	btfss	STATUS,Z	; caseL:
	bra	manchr4		; case 'L': // Launch a fresh instance of a job
	clrf	char_io		;  char_io = 0;

	movf	accumul,w	;  if (accumul == 0)
	btfsc	STATUS,Z	;   return 0;
	return			;  RTOSARG(0, accumul);
	RTOSARG	0
	RTOSACC	accumul,numbase
	movlw	'J'		;  RTOSACC(&accumul, &numbase); // reset
	movwf	char_io		;  if ((w = RTOSSWI(RTOSFRK)) != 0) {
	RTOSSWI	RTOSFRK
	andlw	0x07		;   RTOSARG(0,w); RTOSSWI(RTOSRST);
	btfsc	STATUS,Z	;   goto caseJ; // success, prints in job list
	clrf	char_io		;  } else
	RTOSARG	0
	RTOSSWI	RTOSRST		;   break; // failure, drop to end of switch()

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
	RTOSARG	0
	RTOSARG	1
	RTOSARG	2
	RTOSARG	3
	RTOSSWI	RTOSNEW
	RTOSARG	0
;	RTOSBUF	FSR0,max,p0
;	movlw	'J'		;
;	movwf	char_io		;

;	movf	accumul,w	;  if (accumul == 0)
;	btfsc	STATUS,Z	;   return 0;
;	return			;  RTOSARG(0, accumul);
	clrw			;
	RTOSARG	0
	RTOSACC	accumul,numbase
	movlw	'J'		;  RTOSACC(&accumul, &numbase);
	movwf	char_io		;  if ((w = RTOSSWI(RTOSSLP)) != 0) {
;	RTOSSWI	RTOSSLP
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
	return			;  fsr1 = 0x10 * (1 + accumul) + RTOSPCH;
	movlw	'J'		;
	movwf	char_io		;
	RTOSMEM	FSR1,accumul,RTOSPCH
	movf	INDF1,w		;  if (*fsr1) { // is a valid (PCH not 0x00) job
	btfsc	STATUS,Z	;   *fsr |= 0x80;
	clrf	char_io		;   goto caseJ;
	iorlw	0x80		;  } else {
	movf	INDF1,f		;
	btfss	STATUS,Z	;
	movwf	INDF1		;   RTOSACC(&accumul, &numbase);
	btfsc	STATUS,Z	;   break; // only clear accumul if not caseJ
	bra	manchr6		;  }
	RTOSACC	accumul,numbase
	
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
	return			;  fsr1 = 0x10 * (1 + accumul) + RTOSPCH;
	movlw	'J'		;
	movwf	char_io		;  if (*fsr1 &= ~(1<<RTOSWAI)) {
	RTOSMEM	FSR1,accumul,RTOSPCH
	movlw	0x7f		;   goto caseJ; // valid job won't be 0 or 0x80
	andwf	INDF1,f		;  } else {
	btfss	STATUS,Z	;   RTOSACC(&accumul, &numbase);
	bra	manchr8		;
	RTOSACC	accumul,numbase
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
	movlw	RTOSNUM-1	;
	addlw	0x01		;
	movwf	accumul		;   accumul = RTOSNUM;
	bcf	INTCON,GIE	;  INTCON &= ~(1<<GIE); // to keep p0==p1 atomic
	pagesel	stkinfo
	movf	p0,w		;
	xorwf	p1,w		;  if (p0 == p1)
	btfsc	STATUS,Z	;   return jobinfo(); // will decrement accumul
	goto	stkinfo		;  RTOSENA(); // re-enable interrupts if p0!=p1
	RTOSENA
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
	movlw	low RTOSSTK	;
	movwf	FSR0L		;
	movlw	high RTOSSTK	;
	movwf	FSR0H		;
	decf	accumul,w	;
	brw			;
	addfsr	FSR0,6		;
	addfsr	FSR0,6		;
	addfsr	FSR0,6		;
	addfsr	FSR0,6		; fsr0 = RTOSSTK + 6 * (5 - accumul);
	RTOSLOC	FSR1,RTOSJOB,buf
	movlw	'\r'		; fsr1 = (RTOSJOB << 7) + buf;
	movwi	FSR1++		;
	movlw	'\n'		;
	movwi	FSR1++		;
	movlw	'-'		;
	movwi	FSR1++		;
	movf	accumul,w	;
	addlw	-12		; // print this stack offset as -0/-1/-2/-3/-4
	RTOSHEX
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
	btfsc	STATUS,Z	; RTOSENA(); // interrupts back ON!
	clrf	char_io		; return w;
	RTOSENA
	return			;} // stkinfo()
#endif
	;guaranteed to arrive with p0=p1, interrupts off and in the correct bank
jobinfo
	movf	wrap,w		;int8_t jobinfo(void) {
	movwf	p0		; p0 = p1 = wrap;
	movwf	p1		; fsr0 = 0x10 * (1 + accumul); //FIXME: 2+
	RTOSMEM	FSR0,accumul,0
	RTOSLOC	FSR1,RTOSJOB,buf
	movlw	'\r'		; fsr1 = (RTOSJOB << 7) + buf;
	movwi	FSR1++		;
	movlw	'\n'		;
	movwi	FSR1++		;
	movf	accumul,w	; // print this job number 5/4/3/2/1
	RTOSHEX
	movwi	FSR1++		; p1 += sprintf(p1, "\r\n%1X", accumul);
	
	moviw	RTOSHDH[FSR0]	;
	andlw	1<<RTOSPRB	;
	movlw	':'		; // print '*' if the job is privileged else ':'
	btfss	STATUS,Z	;
	movlw	'*'		; p1 += sprintf(p1, "%c", (RTOSHDH[fsr0] &
	movwi	FSR1++		;                    (1<<RTOSPRB)) ? '*' : ':');
	
	RTOSIHF	RTOSHDH,FSR0,FSR1
	RTOSIHF	RTOSHDL,FSR0,FSR1
	movlw	' '		; 
	movwi	FSR1++		;
	movlw	'P'		; // print the 4-hex-digit header then PC
	movwi	FSR1++		;
	movlw	'C'		; p1 += sprintf(p1, "%04X PC",
	movwi	FSR1++		;         (RTOSHDH[fsr0] << 8) + RTOSHDL[fsr0]);
	
	moviw	RTOSPCH[FSR0]	;
	andlw	1<<RTOSWAI	;
	movlw	'='		; // print '=' if the job is sleeping else 'z'
	btfss	STATUS,Z	;
	movlw	'z'		; p1 += sprintf(p1, "%c", (RTOSPCH[fsr0] &
	movwi	FSR1++		;                    (1<<RTOSWAI)) ? 'z' : ':');
	
	RTOSIHF	RTOSPCH,FSR0,FSR1
	moviw	RTOSPCH[FSR0]	; // drop out after PCH if 0 (job is deleted)
	btfsc	STATUS,Z	; p1 += sprintf(p1, "%02X", RTOSPCH[fsr0]);
	bra	manname		; if (RTOSPCH[fsr0] & 0xff00) {
	RTOSIHF	RTOSPCL,FSR0,FSR1
	movlw	' '		;  // print the low byte of program counter
	movwi	FSR1++		;  p1 += sprintf(p1, "%02X", RTOSPCL[fsr0]); 
	moviw	RTOSISH[FSR0]	;
	btfsc	STATUS,Z	;  // drop out after PCL if no interrupt routine
	bra	manname		;  if (RTOSISH[fsr0] & 0xff00) {
	movlw	'I'		;
	movwi	FSR1++		;
	movlw	'S'		;
	movwi	FSR1++		;
	movlw	'R'		;
	movwi	FSR1++		;
	movlw	'@'		;
	movwi	FSR1++		;   // print ISR@ then 4-hex-digit routine addr
	RTOSIHF	RTOSISH,FSR0,FSR1
	RTOSIHF	RTOSISR,FSR0,FSR1
	movlw	'('		;   p1 += sprintf(p1, " ISR@%04X",
	movwi	FSR1++		;         (RTOSISH[fsr0] << 8) + RTOSISR[fsr0]);
	movlw	'h'		;
	movwi	FSR1++		;
	RTOSIHF	RTOSHIM,FSR0,FSR1
	movlw	's'		;
	movwi	FSR1++		;  // print (hw HwIMask sw SwIMask) scrunched up
	RTOSIHF	RTOSSIM,FSR0,FSR1
	movlw	')'		;   p1 += sprintf(p1, "(h%02Xs%02X) ",
	movwi	FSR1++		;                 RTOSHIM[fsr0], RTOSSIM[fsr0]);
manname
	movlw	' '		;
	movwi	FSR1++		;
	movlw	0x22 ;'"'	;
	movwi	FSR1++		;
	moviw	RTOSPCH[FSR0]	;
	btfss	STATUS,Z	;
	bra	manlive		;   if (RTOSPCH[fsr0] == 0) {
	movlw 	low mandead	;    static char mandead = "<not running>";
	movwf	FSR0L		;
	movlw	high mandead	;
	movwf	FSR0H		;    fsr0 = mandead;
	movlw	mandead-manlive	;
	movwf	char_io		;    char_io = strlen(mandead);
	bra	manloop		;
mandead
	RTOSNAM	"<not running>"
manlive
	moviw	RTOSHDL[FSR0]	;   } else {
	movwf	char_io		;
	moviw	RTOSHDH[FSR0]	;
	iorlw	0x80		;
	movwf	FSR0H		;    fsr0 = 0x8000 | (RTOSHDH[fsr0] << 8) ;
	movf	char_io,w	;
	movwf	FSR0L		;    fsr0 |= RTOSHDL[fsr0];
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
	btfsc	STATUS,Z	; RTOSENA(); // interrupts back ON!
	clrf	char_io		; return w;
	RTOSENA
	return			;
#endif;copy from zOS_MAN()
	
endgame
	zOS_INP	p,rat,rts,hb,pin,in_isr
	movlw	low gameadr
	movwi	optlo[FSR1]
	movlw	high gameadr
	movwi	opthi[FSR1]
	endm
