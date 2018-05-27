	processor 16f18446
	include	p16f18446.inc
/*
#ifdef __DEBUG
	__CONFIG _CONFIG1,_FOSC_INTOSC & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _CLKOUTEN_ON & _IESO_ON & _FCMEN_ON
#else
	__CONFIG _CONFIG1,_FOSC_HS & _WDTE_ON & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _CLKOUTEN_OFF & _IESO_ON & _FCMEN_ON
#endif
	__CONFIG _CONFIG2,_WRT_ALL & _PLLEN_OFF & _STVREN_ON & _BORV_LO & _LVP_ON
*/

;;; uncomment to reduce zOS footprint by 100 words (at cost of zOS_FRK/EXE/FND):
;zOS_MIN	equ	1
	
	include zos.inc
	include zosmacro.inc
	
;; software interrupt lines used: SI3 to print chars to console
STDOUT	equ	zOS_SI3	; SWI for job 1
STDOUT2	equ	zOS_SI4	; SWI for job 2
STDOUT3	equ	zOS_SI5	; SWI for job 3
STDOUT4	equ	zOS_SI6	; SWI for job 4
UNUSEDI	equ	zOS_SI7	; SWI for job 5

	pagesel	main
	goto	main

instanc	macro	port,hb,pin,isr
	local	clkrat
#ifdef __DEBUG
clkrat	equ	.016000000/.000009600
#else
clkrat	equ	.020000000/.000009600
#endif
	
	zOS_INP	port,clkrat,PIR1,hb,pin,isr
#if 1
	movlw	OUTCHAR		; zOS_MAN(/*UART*/1,20MHz/9600bps,PIR1,PORTB,5);
	movwi	0[FSR0]		; zOS_ARG(3, OUTCHAR/*only 1 SWI*/);
#endif

;;;
	
#ifdef	TWO_HEAD
#endif
	
;;; 

main
#ifdef __DEBUG
	banksel	OSCCON
	bsf	OSCCON,IRCF3	; // change from 0.5MHz default to 16MHz
	movlb	0		;
#endif
	
	include	game.inc
	
	clrw			;void main(void) {
main
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
	
	zOS_RUN	INTCON,INTCON	; zOS_RUN(/*T0IE in*/INTCON, /*T0IF in*/INTCON);
	end			;}
