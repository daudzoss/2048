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


#ifndef _PIC24_PORTS_H_
#define _PIC24_PORTS_H_
// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  To do.
 */
//Your device may not have all of these peripherals!
//start RP input mapping
#ifdef _INT1R
#define CONFIG_INT1_TO_RP(pin) _INT1R = pin
#else
#define CONFIG_INT1_TO_RP(pin)
#endif
#ifdef _INT2R
#define CONFIG_INT2_TO_RP(pin) _INT2R = pin
#else
#define CONFIG_INT2_TO_RP(pin)
#endif
#ifdef _T2CKR
#define CONFIG_T2CK_TO_RP(pin) _T2CKR = pin
#else
#define CONFIG_T2CK_TO_RP(pin)
#endif
#ifdef _T3CKR
#define CONFIG_T3CK_TO_RP(pin) _T3CKR = pin
#else
#define CONFIG_T3CK_TO_RP(pin)
#endif
#ifdef _T4CKR
#define CONFIG_T4CK_TO_RP(pin) _T4CKR = pin
#else
#define CONFIG_T4CK_TO_RP(pin)
#endif
#ifdef _T5CKR
#define CONFIG_T5CK_TO_RP(pin) _T5CKR = pin
#else
#define CONFIG_T5CK_TO_RP(pin)
#endif
#ifdef _IC1R
#define CONFIG_IC1_TO_RP(pin) _IC1R = pin
#else
#define CONFIG_IC1_TO_RP(pin)
#endif
#ifdef _IC2R
#define CONFIG_IC2_TO_RP(pin) _IC2R = pin
#else
#define CONFIG_IC2_TO_RP(pin)
#endif
#ifdef _IC3R
#define CONFIG_IC3_TO_RP(pin) _IC3R = pin
#else
#define CONFIG_IC3_TO_RP(pin)
#endif
#ifdef _IC4R
#define CONFIG_IC4_TO_RP(pin) _IC4R = pin
#else
#define CONFIG_IC4_TO_RP(pin)
#endif
#ifdef _IC5R
#define CONFIG_IC5_TO_RP(pin) _IC5R = pin
#else
#define CONFIG_IC5_TO_RP(pin)
#endif
#ifdef _IC6R
#define CONFIG_IC6_TO_RP(pin) _IC6R = pin
#else
#define CONFIG_IC6_TO_RP(pin)
#endif
#ifdef _IC7R
#define CONFIG_IC7_TO_RP(pin) _IC7R = pin
#else
#define CONFIG_IC7_TO_RP(pin)
#endif
#ifdef _IC8R
#define CONFIG_IC8_TO_RP(pin) _IC8R = pin
#else
#define CONFIG_IC8_TO_RP(pin)
#endif
#ifdef _OCFAR
#define CONFIG_OCFA_TO_RP(pin) _OCFAR = pin
#else
#define CONFIG_OCFA_TO_RP(pin)
#endif
#ifdef _OCFBR
#define CONFIG_OCFB_TO_RP(pin) _OCFBR = pin
#else
#define CONFIG_OCFB_TO_RP(pin)
#endif
#ifdef _U1RXR
#define CONFIG_U1RX_TO_RP(pin) _U1RXR = pin
#else
#define CONFIG_U1RX_TO_RP(pin)
#endif
#ifdef _U1CTSR
#define CONFIG_U1CTS_TO_RP(pin) _U1CTSR = pin
#else
#define CONFIG_U1CTS_TO_RP(pin)
#endif
#ifdef _U2RXR
#define CONFIG_U2RX_TO_RP(pin) _U2RXR = pin
#else
#define CONFIG_U2RX_TO_RP(pin)
#endif
#ifdef _U2CTSR
#define CONFIG_U2CTS_TO_RP(pin) _U2CTSR = pin
#else
#define CONFIG_U2CTS_TO_RP(pin)
#endif
#ifdef _SDI1R
#define CONFIG_SDI1_TO_RP(pin) _SDI1R = pin
#else
#define CONFIG_SDI1_TO_RP(pin)
#endif
#ifdef _SCK1R
#define CONFIG_SCK1IN_TO_RP(pin) _SCK1R = pin
#else
#define CONFIG_SCK1IN_TO_RP(pin)
#endif
#ifdef _SS1R
#define CONFIG_SS1IN_TO_RP(pin) _SS1R = pin
#else
#define CONFIG_SS1IN_TO_RP(pin)
#endif
#ifdef _SDI2R
#define CONFIG_SDI2_TO_RP(pin) _SDI2R = pin
#else
#define CONFIG_SDI2_TO_RP(pin)
#endif
#ifdef _SCK2R
#define CONFIG_SCK2IN_TO_RP(pin) _SCK2R = pin
#else
#define CONFIG_SCK2IN_TO_RP(pin)
#endif
#ifdef _SS2R
#define CONFIG_SS2IN_TO_RP(pin) _SS2R = pin
#else
#define CONFIG_SS2IN_TO_RP(pin)
#endif
#ifdef _C1RXR
#define CONFIG_C1RXR_TO_RP(pin) _C1RXR = pin
#else
#define CONFIG_C1RXR_TO_RP(pin)
#endif
#ifdef _C2RXR
#define CONFIG_C2RXR_TO_RP(pin) _C2RXR = pin
#else
#define CONFIG_C2RXR_TO_RP(pin)
#endif



//end RP input mapping
//Your device may not have all of these peripherals!
//start RP output mapping
#ifdef _RP0R
#define CONFIG_C1OUT_TO_RP(pin) _RP##pin##R = 1
#else
#define CONFIG_C1OUT_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_C2OUT_TO_RP(pin) _RP##pin##R = 2
#else
#define CONFIG_C2OUT_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_U1TX_TO_RP(pin) _RP##pin##R = 3
#else
#define CONFIG_U1TX_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_U1RTS_TO_RP(pin) _RP##pin##R = 4
#else
#define CONFIG_U1RTS_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_U2TX_TO_RP(pin) _RP##pin##R = 5
#else
#define CONFIG_U2TX_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_U2RTS_TO_RP(pin) _RP##pin##R = 6
#else
#define CONFIG_U2RTS_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_SDO1_TO_RP(pin) _RP##pin##R = 7
#else
#define CONFIG_SDO1_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_SCK1OUT_TO_RP(pin) _RP##pin##R = 8
#else
#define CONFIG_SCK1OUT_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_SS1OUT_TO_RP(pin) _RP##pin##R = 9
#else
#define CONFIG_SS1OUT_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_SDO2_TO_RP(pin) _RP##pin##R = 10
#else
#define CONFIG_SDO2_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_SCK2OUT_TO_RP(pin) _RP##pin##R = 11
#else
#define CONFIG_SCK2OUT_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_SS2OUT_TO_RP(pin) _RP##pin##R = 12
#else
#define CONFIG_SS2OUT_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_C1TX_TO_RP(pin) _RP##pin##R = 16
#else
#define CONFIG_C1TX_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_OC1_TO_RP(pin) _RP##pin##R = 18
#else
#define CONFIG_OC1_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_OC2_TO_RP(pin) _RP##pin##R = 19
#else
#define CONFIG_OC2_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_OC3_TO_RP(pin) _RP##pin##R = 20
#else
#define CONFIG_OC3_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_OC4_TO_RP(pin) _RP##pin##R = 21
#else
#define CONFIG_OC4_TO_RP(pin)
#endif
#ifdef _RP0R
#define CONFIG_OC5_TO_RP(pin) _RP##pin##R = 22
#else
#define CONFIG_OC5_TO_RP(pin)
#endif



//end RP output mapping
#if defined(__PIC24HJ128GP202__)

#include "devices/pic24hj128gp202_ports.h"

#elif defined(__PIC24HJ128GP204__)

#include "devices/pic24hj128gp204_ports.h"

#elif defined(__PIC24HJ128GP206__)

#include "devices/pic24hj128gp206_ports.h"

#elif defined(__PIC24HJ128GP210__)

#include "devices/pic24hj128gp210_ports.h"

#elif defined(__PIC24HJ128GP306__)

#include "devices/pic24hj128gp306_ports.h"

#elif defined(__PIC24HJ128GP310__)

#include "devices/pic24hj128gp310_ports.h"

#elif defined(__PIC24HJ128GP502__)

#include "devices/pic24hj128gp502_ports.h"

#elif defined(__PIC24HJ128GP504__)

#include "devices/pic24hj128gp504_ports.h"

#elif defined(__PIC24HJ128GP506__)

#include "devices/pic24hj128gp506_ports.h"

#elif defined(__PIC24HJ128GP510__)

#include "devices/pic24hj128gp510_ports.h"

#elif defined(__PIC24HJ12GP201__)

#include "devices/pic24hj12gp201_ports.h"

#elif defined(__PIC24HJ12GP202__)

#include "devices/pic24hj12gp202_ports.h"

#elif defined(__PIC24HJ16GP304__)

#include "devices/pic24hj16gp304_ports.h"

#elif defined(__PIC24HJ256GP206__)

#include "devices/pic24hj256gp206_ports.h"

#elif defined(__PIC24HJ256GP210__)

#include "devices/pic24hj256gp210_ports.h"

#elif defined(__PIC24HJ256GP610__)

#include "devices/pic24hj256gp610_ports.h"

#elif defined(__PIC24HJ32GP202__)

#include "devices/pic24hj32gp202_ports.h"

#elif defined(__PIC24HJ32GP204__)

#include "devices/pic24hj32gp204_ports.h"

#elif defined(__PIC24HJ32GP302__)

#include "devices/pic24hj32gp302_ports.h"

#elif defined(__PIC24HJ32GP304__)

#include "devices/pic24hj32gp304_ports.h"

#elif defined(__PIC24HJ64GP202__)

#include "devices/pic24hj64gp202_ports.h"

#elif defined(__PIC24HJ64GP204__)

#include "devices/pic24hj64gp204_ports.h"

#elif defined(__PIC24HJ64GP206__)

#include "devices/pic24hj64gp206_ports.h"

#elif defined(__PIC24HJ64GP210__)

#include "devices/pic24hj64gp210_ports.h"

#elif defined(__PIC24HJ64GP502__)

#include "devices/pic24hj64gp502_ports.h"

#elif defined(__PIC24HJ64GP504__)

#include "devices/pic24hj64gp504_ports.h"

#elif defined(__PIC24HJ64GP506__)

#include "devices/pic24hj64gp506_ports.h"

#elif defined(__PIC24HJ64GP510__)

#include "devices/pic24hj64gp510_ports.h"

#elif defined(__PIC24F04KA200__)

#include "devices/pic24f04ka200_ports.h"

#elif defined(__PIC24F04KA201__)

#include "devices/pic24f04ka201_ports.h"

#elif defined(__PIC24F08KA101__)

#include "devices/pic24f08ka101_ports.h"

#elif defined(__PIC24F08KA102__)

#include "devices/pic24f08ka102_ports.h"

#elif defined(__PIC24F16KA101__)

#include "devices/pic24f16ka101_ports.h"

#elif defined(__PIC24F16KA102__)

#include "devices/pic24f16ka102_ports.h"

#elif defined(__PIC24F32KA101__)

#include "devices/pic24f32ka101_ports.h"

#elif defined(__PIC24F32KA102__)

#include "devices/pic24f32ka102_ports.h"

#elif defined(__PIC24FJ128GA006__)

#include "devices/pic24fj128ga006_ports.h"

#elif defined(__PIC24FJ128GA008__)

#include "devices/pic24fj128ga008_ports.h"

#elif defined(__PIC24FJ128GA010__)

#include "devices/pic24fj128ga010_ports.h"

#elif defined(__PIC24FJ128GA106__)

#include "devices/pic24fj128ga106_ports.h"

#elif defined(__PIC24FJ128GA108__)

#include "devices/pic24fj128ga108_ports.h"

#elif defined(__PIC24FJ128GA110__)

#include "devices/pic24fj128ga110_ports.h"

#elif defined(__PIC24FJ128GB106__)

#include "devices/pic24fj128gb106_ports.h"

#elif defined(__PIC24FJ128GB108__)

#include "devices/pic24fj128gb108_ports.h"

#elif defined(__PIC24FJ128GB110__)

#include "devices/pic24fj128gb110_ports.h"

#elif defined(__PIC24FJ16GA002__)

#include "devices/pic24fj16ga002_ports.h"

#elif defined(__PIC24FJ16GA004__)

#include "devices/pic24fj16ga004_ports.h"

#elif defined(__PIC24FJ192GA106__)

#include "devices/pic24fj192ga106_ports.h"

#elif defined(__PIC24FJ192GA108__)

#include "devices/pic24fj192ga108_ports.h"

#elif defined(__PIC24FJ192GA110__)

#include "devices/pic24fj192ga110_ports.h"

#elif defined(__PIC24FJ192GB106__)

#include "devices/pic24fj192gb106_ports.h"

#elif defined(__PIC24FJ192GB108__)

#include "devices/pic24fj192gb108_ports.h"

#elif defined(__PIC24FJ192GB110__)

#include "devices/pic24fj192gb110_ports.h"

#elif defined(__PIC24FJ256GA106__)

#include "devices/pic24fj256ga106_ports.h"

#elif defined(__PIC24FJ256GA108__)

#include "devices/pic24fj256ga108_ports.h"

#elif defined(__PIC24FJ256GA110__)

#include "devices/pic24fj256ga110_ports.h"

#elif defined(__PIC24FJ256GB106__)

#include "devices/pic24fj256gb106_ports.h"

#elif defined(__PIC24FJ256GB108__)

#include "devices/pic24fj256gb108_ports.h"

#elif defined(__PIC24FJ256GB110__)

#include "devices/pic24fj256gb110_ports.h"

#elif defined(__PIC24FJ32GA002__)

#include "devices/pic24fj32ga002_ports.h"

#elif defined(__PIC24FJ32GA004__)

#include "devices/pic24fj32ga004_ports.h"

#elif defined(__PIC24FJ48GA002__)

#include "devices/pic24fj48ga002_ports.h"

#elif defined(__PIC24FJ48GA004__)

#include "devices/pic24fj48ga004_ports.h"

#elif defined(__PIC24FJ64GA002__)

#include "devices/pic24fj64ga002_ports.h"

#elif defined(__PIC24FJ64GA004__)

#include "devices/pic24fj64ga004_ports.h"

#elif defined(__PIC24FJ64GA006__)

#include "devices/pic24fj64ga006_ports.h"

#elif defined(__PIC24FJ64GA008__)

#include "devices/pic24fj64ga008_ports.h"

#elif defined(__PIC24FJ64GA010__)

#include "devices/pic24fj64ga010_ports.h"

#elif defined(__PIC24FJ64GA106__)

#include "devices/pic24fj64ga106_ports.h"

#elif defined(__PIC24FJ64GA108__)

#include "devices/pic24fj64ga108_ports.h"

#elif defined(__PIC24FJ64GA110__)

#include "devices/pic24fj64ga110_ports.h"

#elif defined(__PIC24FJ64GB106__)

#include "devices/pic24fj64gb106_ports.h"

#elif defined(__PIC24FJ64GB108__)

#include "devices/pic24fj64gb108_ports.h"

#elif defined(__PIC24FJ64GB110__)

#include "devices/pic24fj64gb110_ports.h"

#elif defined(__PIC24FJ96GA006__)

#include "devices/pic24fj96ga006_ports.h"

#elif defined(__PIC24FJ96GA008__)

#include "devices/pic24fj96ga008_ports.h"

#elif defined(__PIC24FJ96GA010__)

#include "devices/pic24fj96ga010_ports.h"

#else

#error -- processor ID not specified in pic24_ports.h

#endif


#ifndef _PIC24_DIGIO_DEFINED
#warning Digital IO macros not defined for this device!
#warning Edit common\pic24_ports.h file!
#endif
#endif
