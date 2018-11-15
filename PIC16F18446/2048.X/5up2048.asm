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

	org	0
	include zos.inc
	include zosmacro.inc
;;; we need zOS_EXE in order to have the option to launch a program from console

;; software interrupt lines used: SI3 to print chars to console
STDOUT1	equ	zOS_SI3	; SWI for job 1
STDOUT2	equ	zOS_SI4	; SWI for job 2
STDOUT3	equ	zOS_SI5	; SWI for job 3
STDOUT4	equ	zOS_SI6	; SWI for job 4
STDOUT5	equ	zOS_SI7	; SWI for job 5

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

	pagesel	main
	goto	main

;;; 
	include	game.inc	;// defines newgame() and turn()
	include	io.inc		;// defines in_isr() and outgrid()

	clrw			;void main(void) {
main
#ifdef __DEBUG
#else
	banksel	OSCCON1
	movlw	0x60		; // change from 0.5MHz default to 16MHz w/o PLL
;	movlw	0x10		; // change from 0.5MHz default to 32MHz w/2xPLL
	movwf	OSCCON1		; OSCCON1 = 6<<NOSC0;
	btfss	OSCCON3,ORDY	; while (OSCCON3 & (1<<ORDY))
	bra	$-1		;  ;
	movlb	0		;
#endif
	banksel	TRISA
#ifdef CURIOSITY_NANO
	bsf	TRISA,RA7	; TRISA = 0xfb;
	bsf	TRISA,RA6	; // RA7 and RA6 not bonded out in 20-pin QFN
	bsf	TRISA,RA5	; // RA5 SOSCI 32.768kHz crystal
	bsf	TRISA,RA4	; // RA4 SOSCO 32.768kHz crystal
	bsf	TRISA,RA3	; // RA3 MCLR
	bcf	TRISA,RA2	; // RA2 LED heartbeat indicator on TMR0
	bsf	TRISA,RA1	; // RA1 ICSPCLK
	bcf	TRISA,RA0	; // RA0 ICSPDAT
	bcf	TRISB,RB7	; TRISB = 0x1f;
	bcf	TRISB,RB5	; // RB7 and RB5 are open-drain I2C SCL and SCK
	bcf	TRISB,RB6	; // RB6 is microcontroller TX (output), host RX
	bsf	TRISB,RB4	; // RB4 is microcontroller RX (input), host TX
	bcf	TRISB,RB3	; // RB3 not bonded out in 20-pin QFN
	bcf	TRISB,RB2	; // RB2 not bonded out in 20-pin QFN
	bcf	TRISB,RB1	; // RB1 not bonded out in 20-pin QFN
	bcf	TRISB,RB0	; // RB0 not bonded out in 20-pin QFN
	bcf	TRISC,RC7	; TRISC = 0x17;
	bcf	TRISC,RC6	; // RC7 and RC6 SPI SS and SCK respectively
	bcf	TRISC,RC5	; // RC5 is SPI MOSI (microcontroller as host)
	bsf	TRISC,RC4	; // RC4 is SPI MISO (microcontroller as host)
	bcf	TRISC,RC3	; // RC3 is PWM output
	bsf	TRISC,RC2	; // RC2 is SW
	bsf	TRISC,RC1	; // RC1 is ADC1
	bsf	TRISC,RC0	; // RC0 is ADC0

	banksel	ANSELA
	clrf	ANSELA		; ANSELA = 0x00; // no analog
	clrf	ANSELB		; ANSELB = 0x00; // no analog
	movlw	0x03		;
	movwf	ANSELC		; ANSELC = 0x03; // only two ADC inputs

	banksel T0CON0
	movlw	1<T0EN		;
	movwf	T0CON0		; T0CON0 = 0x80; // TMR0 enabled, 8-bit, no post
	movlw	0x5f		;
	movwf	T0CON1		; T0CON1 = 0x5f; // TMR0 Fosc/4, async, max pre

	movlb	0		; // this has to happen at end after all zOS_LAU
	bsf	INTCON,IOCIE	; INTCON |= 1<<IOCIE; // enable edge sensing HWI
	clrf	ALL_IOC		; ALL_IOC = 0; // will go nonzero once zOS_CON()
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
