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
 *  This file consolidates all the user-configurable \#defines
 *  scattered throughout the \ref PIC24_support
 *  "PIC24 support library". These may be changed by either
 *  editing the files in which these \#defines occur,
 *  copying then editing the \#defines below to a position below this comment
 *  (which overrides values
 *  set by the previous method), or by defining them via passing
 *  a <code>-Dname=value</code> flag to the compiler.
 */

// No relevant defines in pic24_adc.h

/** @{
 *  \name Defines from pic24_clockfreq.h
 */

// Doxygen 1.5.6 warns that the \copydoc below produces a
// recursive call chain. This warning also appears if
// the referenced file doesn't exist, so it seems like
// Doxygen can find the referenced file. Workaround: this
// file needs to come before all of its references
// alphabetically (i.e. pic24_alibconfig.h puts it before
// pic24_clockfreq.h, which makes the line below work).
/// \copysee{pic24_clockfreq.h::CLOCK_CONFIG}
// Uncomment one of the #defines below to make
// a clock choice. If all the #defines below
// are commentend, code in pic24_clockfreq.h
// will pick a default clock choice.
#ifndef CLOCK_CONFIG
//#define CLOCK_CONFIG SIM_CLOCK
//#define CLOCK_CONFIG FRCPLL_FCY16MHz
//#define CLOCK_CONFIG FRC_FCY4MHz
//#define CLOCK_CONFIG PRIPLL_8MHzCrystal_16MHzFCY
//#define CLOCK_CONFIG PRI_NO_PLL_7372KHzCrystal
//#define CLOCK_CONFIG FRC_FCY3685KHz
//#define CLOCK_CONFIG FRCPLL_FCY40MHz
//#define CLOCK_CONFIG PRIPLL_7372KHzCrystal_40MHzFCY
//#define CLOCK_CONFIG PRIPLL_8MHzCrystal_40MHzFCY
#endif

// For convenience, choose the fastest
// possible clock depending on which
// processor we're using. If simulation mode is
// selected, then use the simulation clock.
#ifndef CLOCK_CONFIG
#if defined(SIM)
#define CLOCK_CONFIG SIM_CLOCK
#elif defined(EXPLORER16_100P) && defined(__PIC24H__)
#define CLOCK_CONFIG PRIPLL_8MHzCrystal_40MHzFCY
#elif defined(EXPLORER16_100P) && defined(__PIC24F__)
#define CLOCK_CONFIG PRIPLL_8MHzCrystal_16MHzFCY
#elif defined(__PIC24H__) || defined(__DOXYGEN__)
#define CLOCK_CONFIG FRCPLL_FCY40MHz
#elif defined(__PIC24F__)
#define CLOCK_CONFIG FRCPLL_FCY16MHz
#else
#error Unknown processor
#endif
#endif

/// @}

/** \name Defines from pic24_delay.h
 *  @{
 */

// Renaming this from pic24_defaults.h to pic24_libconfig.h
// causes this to be reported by Doxygen as a recursive call
// chain. Doxygen 1.5.6. See comments on CLOCK_CONFIG in this
// file for a workaround.
/// \copysee{pic24_delay.h::DEBOUNCE_DLY}
#ifndef DEBOUNCE_DLY
#define DEBOUNCE_DLY  15   //in milliseconds
#endif

/// @}


// No relevant defines in pic24_dma.h
// No relevant defines in pic24_ecan.h
// No relevant defines in pic24_flash.h
// No relevant defines in pic24_generic.h
// No relevant defines in pic24_i2c.h
// No relevant defines in pic24_ports.h

/** \name Defines from pic24_serial.h
 *  @{
 */

/// \copysee{pic24_serial.h::SERIAL_EOL_DEFAULT}
#ifndef SERIAL_EOL_DEFAULT   //can be overridden in project file
#define SERIAL_EOL_DEFAULT SERIAL_EOL_LF
#endif

/// \copysee{pic24_serial.h::DEFAULT_UART}
#ifndef DEFAULT_UART
#if defined(EXPLORER16_100P)
#define DEFAULT_UART 2
#else
#define DEFAULT_UART 1
#endif
#endif

/// @}

// No relevant defines in pic24_spi.h
// No relevant defines in pic24_timer.h

/** \name Defines from pic24_uart.h
 *  @{
 */

/// \copysee{pic24_uart.h::DEFAULT_BAUDRATE}
#ifndef DEFAULT_BAUDRATE
// For convenience, common baud rates (uncomment one):
//#define DEFAULT_BAUDRATE  230400
//#define DEFAULT_BAUDRATE  115200
#define DEFAULT_BAUDRATE   57600
//#define DEFAULT_BAUDRATE   38400
//#define DEFAULT_BAUDRATE   19200
//#define DEFAULT_BAUDRATE    9600
#endif

/// \copysee{pic24_uart.h::DEFAULT_BRGH}
#ifndef DEFAULT_BRGH
#define DEFAULT_BRGH  0
#endif

/// \copysee{pic24_uart.h::DEFAULT_BAUDRATE1}
#ifndef DEFAULT_BAUDRATE1
#define DEFAULT_BAUDRATE1  DEFAULT_BAUDRATE   //defined in pic24_serial.h
#endif

/// \copysee{pic24_uart.h::DEFAULT_BRGH1}
#ifndef DEFAULT_BRGH1
#define DEFAULT_BRGH1  0
#endif


/// @}

// No relevant defines in pic24_timer.h

/** \name Defines from pic24_util.h
 *  @{
 */

#ifndef USE_HEARTBEAT
/// \copysee{pic24_uart.h::USE_HEARTBEAT}
#define USE_HEARTBEAT 1
#endif

#ifndef HB_LED
#if defined(EXPLORER16_100P)
#define HB_LED _LATA7
#define CONFIG_HB_LED() CONFIG_RA7_AS_DIG_OUTPUT()
#else
/// \copysee{pic24_uart.h::HB_LED}
#define HB_LED _LATB15
/// \copysee{pic24_uart.h::CONFIG_HB_LED}
#define CONFIG_HB_LED() CONFIG_RB15_AS_DIG_OD_OUTPUT()
#endif
#endif // #ifndef HB_LED

/// @}

