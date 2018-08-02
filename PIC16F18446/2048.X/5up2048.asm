	processor 16f18446
	include	p16f18446.inc

#ifdef __DEBUG
	__CONFIG _CONFIG1,_RSTOSC_HFINT32 & _CLKOUTEN_ON & _CSWEN_ON & _FCMEN_OFF
	__CONFIG _CONFIG2,_MCLRE_ON & _PWRTS_OFF & _LPBOREN_OFF & _BOREN_ON & _BORV_LO & _ZCDDIS_OFF & _PPS1WAY_OFF & _STVREN_ON
	__CONFIG _CONFIG3,_WDTCPS_WDTCPS_0 & _WDTE_OFF & _WDTCWS_WDTCWS_7 & _WDTCCS_SC
	__CONFIG _CONFIG4,_BBEN_OFF & _SAFEN_OFF & _WRTAPP_OFF & _WRTB_OFF & _WRTC_OFF & _WRTD_OFF & _WRTSAF_OFF & _LVP_OFF
	__CONFIG _CONFIG5,_CP_OFF
#else
	__CONFIG _CONFIG1,_RSTOSC_HFINT32 & _CLKOUTEN_OFF & _CSWEN_ON & _FCMEN_OFF
	__CONFIG _CONFIG2,_MCLRE_ON & _PWRTS_OFF & _LPBOREN_OFF & _BOREN_ON & _BORV_LO & _ZCDDIS_OFF & _PPS1WAY_OFF & _STVREN_ON	
	__CONFIG _CONFIG3,_WDTCPS_WDTCPS_0 & _WDTE_ON & _WDTCWS_WDTCWS_7 & _WDTCCS_SC
	__CONFIG _CONFIG4,_BBEN_OFF & _SAFEN_OFF & _WRTAPP_OFF & _WRTB_OFF & _WRTC_OFF & _WRTD_OFF & _WRTSAF_OFF & _LVP_OFF
	__CONFIG _CONFIG5,_CP_OFF
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
#if 0
#ifdef __DEBUG
	banksel	OSCCON
	bsf	OSCCON,IRCF3	; // change from 0.5MHz default to 16MHz
	movlb	0		;
#endif

	banksel	TRISA
	bsf	TRISA,RA7	; TRISA = 0xb0;
	bcf	TRISA,RA6	; // xtal <--------startup error? race cond'n?
	bsf	TRISA,RA5	; // MCLR
	bsf	TRISA,OPTO1	; // RA4 is I1
	bcf	TRISA,RELAY1	; // RA3 is O1
	bcf	TRISA,RELAY2	; // RA2 is O2
	bcf	TRISA,RELAY3	; // RA1 is O3
	bcf	TRISA,RELAY4	; // RA0 is O4
	bsf	TRISB,RB7	; TRISB = 0xdb;
	bsf	TRISB,RB6	; // ICSP
	bcf	TRISB,HBEAT	; // RB5 is HBEAT
	bsf	TRISB,OPTO4	; // RB4 is I4
	bsf	TRISB,OPTO3	; // RB3 is I3
	bcf	TRISB,RB2	; // RB2 is TXD
	bsf	TRISB,RB1	; // RB1 is RXD
	bsf	TRISB,OPTO2	; // RB0 is I2

	banksel	ANSELA
	clrf	ANSELA		; ANSELA = 0x00; // no analog
	clrf	ANSELB		; ANSELB = 0x00; // no analog

	banksel	OPTION_REG
	bcf	OPTION_REG,T0CS	; OPTION_REG &= ~(1<<TMR0CS);// off Fosc not pin
	bcf	OPTION_REG,PSA	; OPTION_REG &= ~(1<<PSA);// using max prescaler

	banksel	IOCBP
	movf	ALL_IOC,w	;
	movwf	IOCBP		; IOCBP = all_ioc; // IOCIF senses rising optos
	movwf	IOCBN		; IOCBN = all_ioc; // IOCIF senses falling optos
	
	movlb	0		; // this has to happen at end after all zOS_LAU
	bsf	INTCON,IOCIE	; INTCON |= 1<<IOCIE; // enable edge sensing HWI
	clrf	ALL_IOC		; ALL_IOC = 0; // will go nonzero once zOS_CON()
#endif
	

HBPORT1	equ	LATA
HBPIN1	equ	2		; Free PIC16F18446 evaluation board (April 2018)
RTSFLG1	equ	PIR3		; has the user LED on pin RA2
#ifdef TX2IF
RTSFLG2	equ	PIR3
#else
HBPORT2	equ	0
HBPIN2	equ	0
RTSFLG2	equ	0		; only on PIC16F18455/56 et al
#endif
#ifdef TX3IF
RTSFLG	equ	?
#else
HBPORT3	equ	0
HBPIN3	equ	0
RTSFLG3	equ	0		; only on PIC18 for now :'(
#endif
#ifdef TX4IF
RTSFLG	equ	?
#else
HBPORT4	equ	0
HBPIN4	equ	0
RTSFLG4	equ	0		; only on PIC18 for now :'(
#endif
#ifdef TX5IF
RTSFLG	equ	?
#else
HBPORT5	equ	0
HBPIN5	equ	0
RTSFLG5	equ	0		; only on PIC18 for now :'(
#endif

CLKRAT1	equ	.032000000/.000009600
CLKRAT2	equ	.032000000/.000009600
CLKRAT3	equ	.032000000/.000009600
CLKRAT4	equ	.032000000/.000009600
CLKRAT5	equ	.032000000/.000009600
	
	variable i,anselec,tristat
i = 0
	while	i < 5
i += 1
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
	gamejob	i,CLKRAT#v(i),RTSFLG#v(i),HBPORT#v(i),HBPIN#v(i)
#else; // no LED to manage, assign pin-toggler to RA3 MCLR (never an output!)
	gamejob	i,CLKRAT#v(i),RTSFLG#v(i),LATA,3
#endif
	endif
	endw

	zOS_RUN	INTCON,INTCON	; zOS_RUN(/*T0IE in*/INTCON, /*T0IF in*/INTCON);
	end			;}
