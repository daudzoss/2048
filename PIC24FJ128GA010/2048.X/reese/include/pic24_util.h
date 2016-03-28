/*
 * "Copyright (c) 2008 Robert B. Reese, Bryan A. Jones, J. W. Bruce ("AUTHORS")"
 * All rights reserved.
 * (R. Reese, reese_AT_ece.msstate.edu, Mississippi State University)
 * (B. A. Jones, bjones_AT_ece.msstate.edu, Mississippi State University)
 * (J. W. Bruce, jwbruce_AT_ece.msstate.edu, Mississippi State University)
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 *
 *
 */

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  This file contains miscellaneous functions that
 *  that do not fall under any particular category.
 *
 *  See also pic24_util.c for details on how
 *  these functions were implemented.
 */

#ifndef  _PIC24_UTIL_H_
#define _PIC24_UTIL_H_

#define DEV_ID_LOCATION 0xFF0000
#define REVISION_LOCATION 0xFF0002

/*
Revision information is found in the Silicon Errata
sheet for the device. The Device ID is contained
in the datasheet for the target device.
*/


#ifdef __PIC24HJ12GP201__
#define DEV_ID 0x00080a
#define DEV_ID_STR "PIC24HJ12GP201"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A2"
//#define EXPECTED_REVISION2 0x003002
//#define EXPECTED_REVISION2_STR "A3"
#endif

#ifdef __PIC24HJ12GP202__
#define DEV_ID 0x00080B
#define DEV_ID_STR "PIC24HJ12GP202"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A2"
//#define EXPECTED_REVISION2 0x003002
//#define EXPECTED_REVISION2_STR "A3"
#endif

#ifdef __PIC24HJ16GP304__
#define DEV_ID 0x000F17
#define DEV_ID_STR "PIC24HJ16GP304"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A2"
//#define EXPECTED_REVISION2 0x003002
//#define EXPECTED_REVISION2_STR "A3"
#endif

#ifdef __PIC24HJ32GP202__
#define DEV_ID 0x000F1D
#define DEV_ID_STR "PIC24HJ32GP202"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION2 0x003002
#define EXPECTED_REVISION2_STR "A3"
#endif

#ifdef __PIC24HJ32GP204__
#define DEV_ID 0x000F1F
#define DEV_ID_STR "PIC24HJ32GP204"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A2"
//#define EXPECTED_REVISION2 0x003002
//#define EXPECTED_REVISION2_STR "A3"
#endif

#ifdef __PIC24HJ32GP302__
#define DEV_ID 0x000645
#define DEV_ID_STR "PIC24HJ32GP302"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif

#ifdef __PIC24HJ32GP304__
#define DEV_ID 0x000647
#define DEV_ID_STR "PIC24HJ32GP304"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif


#ifdef __PIC24HJ64GP206__
#define DEV_ID 0x000041
#define DEV_ID_STR "PIC24HJ64GP206"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24HJ64GP210__
#define DEV_ID 0x000047
#define DEV_ID_STR "PIC24HJ64GP210"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24HJ64GP202__
#define DEV_ID 0x000655
#define DEV_ID_STR "PIC24HJ64GP202"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif

#ifdef __PIC24HJ64GP204__
#define DEV_ID 0x000657
#define DEV_ID_STR "PIC24HJ64GP204"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif

#ifdef __PIC24HJ64GP502__
#define DEV_ID 0x000675
#define DEV_ID_STR "PIC24HJ64GP502"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif

#ifdef __PIC24HJ64GP504__
#define DEV_ID 0x000677
#define DEV_ID_STR "PIC24HJ64GP504"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif

#ifdef __PIC24HJ64GP510__
#define DEV_ID 0x00004B
#define DEV_ID_STR "PIC24HJ64GP510"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24HJ128GP202__
#define DEV_ID 0x000665
#define DEV_ID_STR "PIC24HJ128GP202"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif

#ifdef __PIC24HJ128GP204__
#define DEV_ID 0x000667
#define DEV_ID_STR "PIC24HJ128GP204"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif

#ifdef __PIC24HJ128GP206__
#define DEV_ID 0x00005D
#define DEV_ID_STR "PIC24HJ128GP206"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24HJ128GP210__
#define DEV_ID 0x00005F
#define DEV_ID_STR "PIC24HJ128GP210"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24HJ128GP502__
#define DEV_ID 0x00067d
#define DEV_ID_STR "PIC24HJ128GP502"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif

#ifdef __PIC24HJ128GP504__
#define DEV_ID 0x00067f
#define DEV_ID_STR "PIC24HJ128GP504"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#endif

#ifdef __PIC24HJ256GP206__
#define DEV_ID 0x000071
#define DEV_ID_STR "PIC24HJ256GP206"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24HJ256GP210__
#define DEV_ID 0x000073
#define DEV_ID_STR "PIC24HJ256GP210"
#define EXPECTED_REVISION1 0x003002
#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION2 0x003004
#define EXPECTED_REVISION2_STR "A3"
#endif

#ifdef __PIC24HJ256GP610__
#define DEV_ID 0x00007B
#define DEV_ID_STR "PIC24HJ256GP610"
#define EXPECTED_REVISION1 0x003002
#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION2 0x003004
#define EXPECTED_REVISION2_STR "A3"
#endif

#ifdef __PIC24HJ128GP306__
#define DEV_ID 0x000065
#define DEV_ID_STR "PIC24HJ128GP306"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24HJ128GP310__
#define DEV_ID 0x000067
#define DEV_ID_STR "PIC24HJ128GP310"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24HJ64GP506__
#define DEV_ID 0x000049
#define DEV_ID_STR "PIC24HJ64GP506"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif



#ifdef __PIC24HJ128GP506__
#define DEV_ID 0x000061
#define DEV_ID_STR "PIC24HJ128GP506"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24HJ128GP510__
#define DEV_ID 0x000063
#define DEV_ID_STR "PIC24HJ128GP510"
//#define EXPECTED_REVISION1 0x003002
///#define EXPECTED_REVISION1_STR "A2"
#define EXPECTED_REVISION1 0x003004
#define EXPECTED_REVISION1_STR "A3"
#endif

//24F Family
//PIC24FJXXGA002 (28 pin),PIC24FJXXGA004 (44 pin)
#ifdef __PIC24FJ16GA002__
#define DEV_ID 0x000444
#define DEV_ID_STR "PIC24FJ16GA002"
#define EXPECTED_REVISION1 0x003003
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ32GA002__
#define DEV_ID 0x000445
#define DEV_ID_STR "PIC24FJ32GA002"
#define EXPECTED_REVISION1 0x003003
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ48GA002__
#define DEV_ID 0x000446
#define DEV_ID_STR "PIC24FJ48GA002"
#define EXPECTED_REVISION1 0x003003
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ64GA002__
#define DEV_ID 0x000447
#define DEV_ID_STR "PIC24FJ64GA002"
#define EXPECTED_REVISION1 0x003003
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ16GA004__
#define DEV_ID 0x00044C
#define DEV_ID_STR "PIC24FJ16GA004"
#define EXPECTED_REVISION1 0x003003
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ32GA004__
#define DEV_ID 0x00044D
#define DEV_ID_STR "PIC24FJ32GA004"
#define EXPECTED_REVISION1 0x003003
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ48GA004__
#define DEV_ID 0x00044E
#define DEV_ID_STR "PIC24FJ48GA004"
#define EXPECTED_REVISION1 0x003003
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ64GA004__
#define DEV_ID 0x00044F
#define DEV_ID_STR "PIC24FJ64GA004"
#define EXPECTED_REVISION1 0x003003
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ128GA010__
#define DEV_ID 0x00040D
#define DEV_ID_STR "PIC24FJ128GA010"
#define EXPECTED_REVISION1 0x003003
#define EXPECTED_REVISION1_STR "A3"
#define EXPECTED_REVISION2 0x003004
#define EXPECTED_REVISION2_STR "A4"
#define EXPECTED_REVISION3 0x003044//0x003007  //RBR: I can't find docs on this revision code.
#define EXPECTED_REVISION3_STR "A?"
#endif

#ifdef __PIC24FJ96GA010__
#define DEV_ID 0x00040C
#define DEV_ID_STR "PIC24FJ96GA010"
//#define EXPECTED_REVISION1 0x000003
//#define EXPECTED_REVISION1_STR "A3"
#define EXPECTED_REVISION1 0x000004
#define EXPECTED_REVISION1_STR "A4"
#endif

#ifdef __PIC24FJ64GA010__
#define DEV_ID 0x00040B
#define DEV_ID_STR "PIC24FJ64GA010"
//#define EXPECTED_REVISION1 0x000003
//#define EXPECTED_REVISION1_STR "A3"
#define EXPECTED_REVISION1 0x000004
#define EXPECTED_REVISION1_STR "A4"
#endif

#ifdef __PIC24FJ128GA008__
#define DEV_ID 0x00040A
#define DEV_ID_STR "PIC24FJ128GA008"
//#define EXPECTED_REVISION1 0x000003
//#define EXPECTED_REVISION1_STR "A3"
#define EXPECTED_REVISION1 0x000004
#define EXPECTED_REVISION1_STR "A4"
#endif

#ifdef __PIC24FJ96GA008__
#define DEV_ID 0x000409
#define DEV_ID_STR "PIC24FJ96GA008"
//#define EXPECTED_REVISION1 0x000003
//#define EXPECTED_REVISION1_STR "A3"
#define EXPECTED_REVISION1 0x000004
#define EXPECTED_REVISION1_STR "A4"
#endif

#ifdef __PIC24FJ64GA008__
#define DEV_ID 0x000408
#define DEV_ID_STR "PIC24FJ64GA008"
//#define EXPECTED_REVISION1 0x000003
//#define EXPECTED_REVISION1_STR "A3"
#define EXPECTED_REVISION1 0x000004
#define EXPECTED_REVISION1_STR "A4"
#endif

#ifdef __PIC24FJ128GA006__
#define DEV_ID 0x00040A
#define DEV_ID_STR "PIC24FJ128GA006"
//#define EXPECTED_REVISION1 0x000003
//#define EXPECTED_REVISION1_STR "A3"
#define EXPECTED_REVISION1 0x000004
#define EXPECTED_REVISION1_STR "A4"
#endif

#ifdef __PIC24FJ96GA006__
#define DEV_ID 0x000409
#define DEV_ID_STR "PIC24FJ96GA006"
//#define EXPECTED_REVISION1 0x000003
//#define EXPECTED_REVISION1_STR "A3"
#define EXPECTED_REVISION1 0x000004
#define EXPECTED_REVISION1_STR "A4"
#endif

#ifdef __PIC24FJ64GA006__
#define DEV_ID 0x000408
#define DEV_ID_STR "PIC24FJ64GA006"
//#define EXPECTED_REVISION1 0x000003
//#define EXPECTED_REVISION1_STR "A3"
#define EXPECTED_REVISION1 0x000004
#define EXPECTED_REVISION1_STR "A4"
#endif

#ifdef __PIC24FJ256GA110__
#define DEV_ID 0x00101E
#define DEV_ID_STR "PIC24FJ256GA110"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ192GA110__
#define DEV_ID 0x001016
#define DEV_ID_STR "PIC24FJ192GA110"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ128GA110__
#define DEV_ID 0x00100E
#define DEV_ID_STR "PIC24FJ128GA110"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ256GA108__
#define DEV_ID 0x00101A
#define DEV_ID_STR "PIC24FJ256GA108"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ192GA108__
#define DEV_ID 0x001012
#define DEV_ID_STR "PIC24FJ192GA108"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ128GA108__
#define DEV_ID 0x00100A
#define DEV_ID_STR "PIC24FJ128GA108"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ256GA106__
#define DEV_ID 0x001018
#define DEV_ID_STR "PIC24FJ256GA106"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ192GA106__
#define DEV_ID 0x001010
#define DEV_ID_STR "PIC24FJ192GA106"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ128GA106__
#define DEV_ID 0x001008
#define DEV_ID_STR "PIC24FJ128GA106"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

/***** PIC24F GB ****/

#ifdef __PIC24FJ256GB110__
#define DEV_ID 0x00101F
#define DEV_ID_STR "PIC24FJ256GB110"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ192GB110__
#define DEV_ID 0x001017
#define DEV_ID_STR "PIC24FJ192GB110"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ128GB110__
#define DEV_ID 0x00100F
#define DEV_ID_STR "PIC24FJ128GB110"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ64GB110__
#define DEV_ID 0x001007
#define DEV_ID_STR "PIC24FJ64GB110"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ256GB108__
#define DEV_ID 0x00101B
#define DEV_ID_STR "PIC24FJ256GB108"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ192GB108__
#define DEV_ID 0x001013
#define DEV_ID_STR "PIC24FJ192GB108"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ128GB108__
#define DEV_ID 0x00100B
#define DEV_ID_STR "PIC24FJ128GB108"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ64GB108__
#define DEV_ID 0x001003
#define DEV_ID_STR "PIC24FJ64GB108"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ256GB106__
#define DEV_ID 0x001018
#define DEV_ID_STR "PIC24FJ256GB106"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ192GB106__
#define DEV_ID 0x001010
#define DEV_ID_STR "PIC24FJ192GB106"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ128GB106__
#define DEV_ID 0x001008
#define DEV_ID_STR "PIC24FJ128GB106"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif

#ifdef __PIC24FJ64GB106__
#define DEV_ID 0x001001
#define DEV_ID_STR "PIC24FJ64GB106"
#define EXPECTED_REVISION1 0x000001
#define EXPECTED_REVISION1_STR "A3"
#endif


/* Use these default device ID and revision values
if you are trying to discover the ID/Revision by
executing code on your target device and watching
was is printed by the printResetCause() function
*/
#ifndef DEV_ID
#define DEV_ID 0
#define DEV_ID_STR "unknown"
#define EXPECTED_REVISION1 0
#define EXPECTED_REVISION1_STR "unknown"
#warning *********************************************
#warning * Unknown chip type! Define a device ID and *
#warning * revision ID in the lines above for this   *
#warning * chip to remove this warning message.      *
#warning * These values can be found by              *
#warning * executing the checkDeviceAndRevision()    *
#warning * function, which is typically called after *
#warning * reset via calling printResetCause().      *
#warning * This check allows you to ensure that the  *
#warning * programmed hex file is running on the     *
#warning * same device type it was compiled for.     *
#warning * This is only a warning.                   *
#warning *********************************************
#endif


//may need variations for auto_psv, no_auto_psv
//auto_psv is default, generates extra code for
//accessing constants in program memory or through
//24 bit points. Just go safe route for now.

//explicitly use  'auto_psv' since that is default and to
//get rid of warning message
#ifdef _ISR
#undef _ISR
//make our own definition that gets rid of warning
#define _ISR __attribute__((interrupt)) __attribute__ ((auto_psv))
#endif

#ifdef _ISRFAST
#undef _ISRFAST
//make our own definition that gets rid of warning
#define _ISRFAST __attribute__((interrupt)) __attribute__ ((no_auto_psv))
#endif


#define SLEEP()  Sleep()
#define IDLE()   Idle()
#define CLRWDT() ClrWdt()
#define NOP() Nop()
#define ENABLEWDT() _SWDTEN = 1
#define DISABLEWDT() _SWDTEN = 0

/** Defined the number of UART modules supported by this chip.
 *  NOTE: this only works when testing \#defines, not
 *  testing variable. So, don't test UxSTA; instead,
 *  test _UxRXIF which is uniquely defined for each
 *  UART. (Idea taken from the C30 peripheral library,
 *  in uart.h.)
 */
#if   defined(_U4RXIF)
#define NUM_UART_MODS 4
#elif defined(_U3RXIF)
#define NUM_UART_MODS 3
#elif defined(_U2RXIF)
#define NUM_UART_MODS 2
#elif defined(_U1RXIF) || defined(__DOXYGEN__)
#define NUM_UART_MODS 1
#else
#error UxRXIF flag not defined!
#endif

#if   defined(_SI2C2IF)
#define NUM_I2C_MODS 2
#elif defined(_SI2C1IF) || defined(__DOXYGEN__)
#define NUM_I2C_MODS 1
#else
#error SI2CxIF flag not defined!
#endif

#if   defined(_SPI2IF)
#define NUM_SPI_MODS 2
#elif defined(_SPI1IF) || defined(__DOXYGEN__)
#define NUM_SPI_MODS 1
#else
#error SPIxIF flag not defined!
#endif

#if   defined(_C2IF)
#define NUM_ECAN_MODS 2
#elif defined(_C1IF) || defined(__DOXYGEN__)
#define NUM_ECAN_MODS 1
#endif


extern uint32 u32_heartbeatCount;

extern _PERSISTENT char* sz_lastTimeoutError;

/** @{ \name Bitfield to struct conversion
 *  Given a bitfield struct representing an SFR,
 *  convert this to a word (uint16) or to the
 *  high and low bytes (uint8) of that word.
 *  Note: though this looks ugly, it introduces
 *  no unexpected compiler overhead at -O1. See
 *  \ref u16_INTTREGlast for an example.
 */
#define BITS2WORD(sfrBitfield)  ( *((uint16*) &sfrBitfield) )
#define BITS2BYTEL(sfrBitfield) ( ((uint8*)  &sfrBitfield)[0] )
#define BITS2BYTEH(sfrBitfield) ( ((uint8*)  &sfrBitfield)[1] )
///@}

/** Report an error on reset via \ref reportError,
 *  also printing the file and
 *  line number where this macro was called via
 *  a call to \ref ERROR_FILE_LINE.
 *  \param msg Error message to report
 */
#define REPORT_ERROR(msg) reportError(ERROR_FILE_LINE(msg))

#ifdef SIM
#define HELLO_MSG "****************************************************\n" \
                  "*    SIMULATION MODE - DO NOT RUN ON A REAL PIC!   *\n" \
                  "****************************************************\n" \
                  "\n" __FILE__ ", built on " __DATE__ " at " __TIME__ "\n"
// Output a warning during compilation also
#warning ***********************************************
#warning * SIMULATION MODE - DO NOT RUN ON A REAL PIC! *
#warning ***********************************************
#else
#define HELLO_MSG "\n" __FILE__ ", built on " __DATE__ " at " __TIME__ "\n"
#endif



void configHeartbeat(void);
void doHeartbeat(void);
void toggleHeartbeat(void);
void reportError(const char* szErrorMessage);
void printResetCause(void);
void configPinsForLowPower(void);
void configBasic(const char* psz_helloMsg);

#ifndef USE_HEARTBEAT
/** If this macro is true, heartbeat functionality is enabled.
 *  If false, heartbeat is disabled.
 */
#define USE_HEARTBEAT 1
#endif

/** Choose a pin for the heartbeat.
 *  If \ref USE_HEARTBEAT is false, the heartbeat is disabled.
 */
#ifndef HB_LED
#define HB_LED _LATB15
/** Define a config function for the heartbeat pin. */
#define CONFIG_HB_LED() CONFIG_RB15_AS_DIG_OD_OUTPUT()
#endif


#endif
