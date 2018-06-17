	processor 16f1719
	include	p16f1719.inc

#ifdef __DEBUG

#else

#endif

;;; uncomment to reduce zOS footprint by 100 words (at cost of zOS_FRK/EXE/FND):
;zOS_MIN	equ	1
	
	org	0
	include zos.inc
	include zosmacro.inc
	
;; software interrupt lines used: SI3 to print chars to console
STDOUT1	equ	zOS_SI3	; SWI for job 1
STDOUT2	equ	zOS_SI4	; SWI for job 2
STDOUT3	equ	zOS_SI5	; SWI for job 3
STDOUT4	equ	zOS_SI6	; SWI for job 4
STDOUT5	equ	zOS_SI7	; SWI for job 5

	pagesel	main
	goto	main


;;; 
	include	game.inc	;// defines newgame() and turn()
	include	io.inc		;// defines in_isr() and outgrid()

	clrw			;void main(void) {
main

	banksel ANSELC
	bcf 	ANSELC,RC7
	bcf 	ANSELC,RC6

	banksel TRISC
	bsf 	TRISC,RC7	;host TX
	bcf 	TRISC,RC6	;host RX

        banksel PPSLOCK
        bcf     INTCON,GIE      ;
        movlw   0x55            ;    GIE = 0;
        movwf   PPSLOCK         ;    PPSLOCK = 0x55;
        movlw   0xaa            ;    PPSLOCK = 0xAA;
        movwf   PPSLOCK         ;    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
        bcf     PPSLOCK,PPSLOCKED
	banksel	RXPPS
        movlw   0x17            ;
        movwf   RXPPS           ;    RXPPSbits.RXPPS = 027;   //RC7->EUSART:RX;

        banksel RC2PPS
        movlw   0x24
        movwf   RC6PPS          ;    RC6PPSbits.RC6PPS = 0x24;   //RC6->EUSART:TX;

        banksel PPSLOCK
        movlw   0x55
        movwf   PPSLOCK         ;    PPSLOCK = 0x55;
        movlw   0xaa
        movwf   PPSLOCK         ;    PPSLOCK = 0xAA;
                                ;    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
        bsf     PPSLOCK,PPSLOCKED


HBPORT1	equ	LATA
HBPIN1	equ	RA4
RTSFLG1	equ	PIR1
	
CLKRAT1	equ	.032000000/.000009600
	
	variable i,p,anselec,tristat
i = 0
	while	i < 2
i += 1

#ifdef TX1IF
#ifdef RC1IF
p = i
#else
p = 0	 
#endif
#endif

	if RTSFLG#v(i)
#if HBPORT#v(i)
poffset = HBPORT#v(i) - LATA
anselec	= ANSELA + poffset
tristat = TRISA + poffset
	banksel	anselec
	bcf	anselec,HBPIN#v(i)
	banksel	tristat
	bcf	tristat,HBPIN#v(i)
	movlb	0
	
	gamejob	p,CLKRAT#v(i),RTSFLG#v(i),HBPORT#v(i),HBPIN#v(i)
#else; // no LED to manage, assign pin-toggler to RE3 MCLR (never an output!)
	gamejob	p,CLKRAT#v(i),RTSFLG#v(i),LATE,RE3
#endif
	endif
	endw

	zOS_RUN	INTCON,INTCON	; zOS_RUN(/*T0IE in*/INTCON, /*T0IF in*/INTCON);
	end			;}
