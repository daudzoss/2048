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

// Documentation placed on the getting started page. This file only
// include comments for Doxygen; it does not contain any
// code.
/**
 * \page gettingStarted Getting started
 * To prepare and test your system for use with the programs
 * in this package:
 * -# \ref softwareInstall - Install the necessary software
 *    on a Windows-based PC.
 * -# \ref hardwareBringup - Build or purchase a PIC24-based
 *    board.
 * -# \ref pic24Test -- Using the bootloader, program the PIC24 micro with the echo program for testing purposes. 
 *     This verifies proper installation of your hardware/software setup. 
 * The sections below provide additional details for following each of these steps.
 *
 *
 * \section softwareInstall Software installation
 * -# Download and install the latest version of the 
 *    <a href="http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1406&dDocName=en019469&part=SW007002">MPLAB IDE</a>
 *    (the Full Release Zipped Installation under the Downloads section near the bottom). 
 *     For v8.10, the buttons to click during installation are: 
 *     next, next, I accept/next, next, next, next, next, yes, finish.
 * -# Download and install the latest version of the 
 *    <a href="http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1406&dDocName=en010065"> MPLAB
 *    C compiler for PIC24 MCUs</a>. Notes:
 *    -# MPLAB <b> must</b> be installed before the compiler
 *    -# Accept all the defaults when installing; in particular, 
 *       click "Yes" to the "Modify Environment?" question (see images below). 
 *        No new program will show up on your start menu; instead, the compiler 
 *        will now be available in MPLAB. That enables the compiler to properly 
 *        register itself with MPLAB. 
 *     -# See the <a href="http://www.bugmenot.com/view/microchip.com"> BugMeNot</a>
 *        for a userid/password if you don't want to create one.
 * -# If you do not have the Microsoft .NET framework installed, download and 
 *     install the .NET runtime by visiting the
 *     <a href="http://www.microsoft.com/downloads"> Microsoft Download Center</a> and 
 *	  searching for '.NET runtime'. Install version 2.0 or later. 
 *	  If you're not sure if the .NET framework is installed, try running the 
 *    bootloader in the following step; if it fails, download the .NET framework.
 * -# Copy the "code/" directory on the book's CD-ROM to a location on your PC (we recommend a directory
 *    without spaces and a short path, such as the top level of your C:\ drive). You can also
 *    get the latest version of the files from 
 *     <a href="http://www.ece.msstate.edu/courses/ece3724/main_pic24/labs/files/pic24_code_examples.zip"> HERE </a>, but
 *    these may deviate slightly from the book examples.
 * -# Test the bootloader, a .NET application, by executing code\bin\winbootldr.exe. 
 *    A GUI should pop up. If that fails, consult the <a href="manuallyCreated/PIC24_bully_bootloader.pdf"> bootloader documentation </a>
 *    for troubleshooting steps.
 *
 * \section hardwareBringup Hardware bring-up
 * There are several options for acquiring the hardware necessary to run a PIC24:
 * - \ref Wireup "Wire up a PIC24 from scratch."
 * - Purchase a \ref SPARKFUN "SparkFun PIC24 breakout board."
 * - Purchase a \ref EXPLORER "Microchip Explorer16 board."
 *
 * \section Wireup Wiring up a PIC24 System
 * -# Begin by following the <a href="manuallyCreated/board_walkthru_pic24.pdf"> prototyping walk-through. </a>. This 
 *    assumes that you have the part kit discussed in Appendix C and breadboard, we buy our parts kit from 
 *    <a href="http://www.elexp.com/"> Electronix Express </a> (contact them and simply ask about the Mississippi 
 *    State University parts kit for the ECE 3724 course).
 * -# Using an \ref ICSP "ICSP programmer", program the bootloader onto your PIC24 micro.
 * -# Install the <a href="http://www.ftdichip.com/Drivers/VCP.htm"> FTDI drivers</a> 
 *    (use the setup executable link) to communicate with your PIC via an \ref FTDICABLE "FTDI cable".
 * 
 * \section SPARKFUN SparkFun PIC24 breakout board
 * -# Purchase a <a href="http://www.sparkfun.com/commerce/product_info.php?products_id=8787"> SparkFun PIC24 breakout board.</a>
 * -# At a minimum, install 0.1" pitch headers in the 6-pin connection for use with an FTDI cable. Installing headers in the
 *    remaining positions allows access to much of the functionality of the chip by allowing the board
 *    to plugged directly into a breadboard. Sparkfun has these headers in breakaway
 *    form in their related links section of the PIC24 breakout board section. 
 * -# Install the <a href="http://www.ftdichip.com/Drivers/VCP.htm"> FTDI drivers</a> 
 *    (use the setup executable link) to communicate with your PIC via an \ref FTDICABLE "FTDI cable".
 * -# The SparkFun PIC24 breakout board already comes with the bootloader programmed on the PIC24 micro, and a
 *     sample application configured for 57600 baud, so you can run the bootloader GUI and see if 
 *     the welcome menu from the application displays in the GUI.  You can also try downloading a new program into the board
 *     as detailed in \ref pic24Test "Testing with echo".
 * -# For advanced users, purchase a <a href="http://www.sparkfun.com/commerce/product_info.php?products_id=194"> SparkFun ICSP connector</a>
 *    for use with an \ref ICSP "ICSP programmer". This allows you to program the board without using the bootloader.
 *
 * \section EXPLORER Explorer16 board
 * The Explorer16 is a development board available from Microchip - it comes in 100 pin and 44 pin versions. 
 * The CPU is set by a plug-in module, of which each board has a few available. The directory /code/explorer16_100p 
 * contains a few examples for the Explorer16/100 pin board. These projects can use the source files 
 * from the other directories, but the macro EXPLORER16_100P either must defined in the include/pic24_libconfig.h file 
 * or it must be added to the MPLAB project (Use Project->Build Options-> Project, click on the MPLAB C30 tab, 
 * and in Macro Definitions click 'Add', and add EXPLORER16_100P). The EXPLORER16_100P macro causes the 
 * default UART to be UART2 since that is what is used on the Explorer16/100 pin board. 
 * It also causes the clock option to use the external 8 MHz oscillator, with the PLL used to produce 
 * a 16 MHz FCY for PIC24F and 40 MHz for PIC24H.
 *
 * \section FTDICABLE FTDI cable
 * A simple solution for connecting your PIC24 to a PC is an <a href="http://www.ftdichip.com/"> FTDI </a> 
 * <a href="http://www.ftdichip.com/Products/EvaluationKits/TTL-232R-3V3.htm"> TTL-232R-3V3 </a> USB to TTL level 
 * serial converter cable. One end plugs into a PC's USB port while the other provides 
 * TTL-compatible serial I/O lines which can be directly connected to your PIC's serial I/O pins. 
 * In addition, the cable provide +5V, which can be used to power your board through a regulator. 
 * For more information, see the FTDI datasheet. Sources:
 *    - <a href="http://search.digikey.com/scripts/DkSearch/dksus.dll?Detail?name=768-1015-ND"> Digi-key </a> 
 *    - <a href="http://www.mouser.com/Search/ProductDetail.aspx?qs=Xb8IjHhkxj627GFcejHp0Q%3d%3d"> Mouser </a>
 *    - SparkFun sells their own <a href="http://www.sparkfun.com/commerce/product_info.php?products_id=8772"> FTDI board </a>, 
 *      which provides the same functionality as the cable.
 *
 *
 * \section ICSP ICSP programmers
 * If you purchase an unprogrammed PIC24 chip, you'll need to program it with the bootloader, 
 * after which the bootloader can be used to program the PIC24 micro with your code. 
 * If the bootloader gets corrupted, it must be reprogrammed. Finally, advanced users may which to 
 * remove the bootloader and program the PIC24 micro via ICSP. Several options exist:
 *   - Microchip sells the <a href="http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1406&dDocName=en023805"> PICkit2 </a>, 
 *     a low-cost programmer; only the PICkit2, not the various starter kits, are required. 
 *     This is the solution used by the authors.
 *   - A second, more expensive option is the Microchip <a href="http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1406&dDocName=en010046&part=DV164005">ICD2</a>.
 *   - <a href="http://www.sparkfun.com/commerce/product_info.php?products_id=9"> Third-party programmers </a> can (possibly) be used.
 *
 * To program your PIC with the bootloader using a PICkit2:
 *   -# Install the <a href="http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1406&dDocName=en023805"> PICkit 2 software </a> from Microchip's website.
 *   -# Connect the PICkit 2 programmer up to your board. 
 *      The arrow on the PICkit corresponds to pin 1.
 *      - The PICkit may need to have an OS downloaded. If the PICkit software complains, 
 *        click Tools -> Download PICkit 2 Operating System.
 *   -# In the PICkit software, select Device Family -> PIC24.
 *      - If the PIC24 micro is not automatically found, press and hold the MCLR button on the board. When you release the MCLR button, 
 *        click the "Read" button in the PICkit software.
 *      - Check to make sure your device is properly recognized.
 *      - Click the Erase button to erase the device.
 *      - Hex files for the bootloader for various devices are in the code/hex direcrtory.
 *         Load the bootloader hex file via File -> Import Hex. Be sure to select 
 *         the appropriate PIC architecture. 
 *         Additionally, take note of the information contained in the bootloader's name (i.e. baudrate).
 *
 * \section pic24Test Testing with echo
 * With the necessary software installed and hardware acquired, test your system by programming 
 * it with a simple echo program. The echo program waits for a UART1 RX character, increments it, 
 * then echos it back. To test:
 *  -# Before programming the PIC24 micro with the echo program, be sure to have 
 *     all the required software installed and the bootloader loaded (see the steps above).
 *  -# Open MPLAB, then open the echo project using Project -> Open. You may have to do this twice if the
 *    files do not display the first time since the CD-ROM does not contain workspace files (the first time
 *    creates an empty workspace).
 *  -# The project should compile as is; build the project with Project -> Make (or press F10). To troubleshoot:
 *     -# Click Configure -> Select Device and make sure the appropriate device  (PIC24HJ32GP202) is selected.
 *     -# Click Project -> Build Options -> Project. Under the Directories tab, "Show directories for:" 
 *        the Include Search Path and make sure the relative paths are meaningful for your setup.
 *  -# Start the <a href="manuallyCreated/PIC24_bully_bootloader.pdf"> PIC24 bootloader </a> application by opening code/bin/winbootloader.exe.
 *  -# Hook the USB cable up to your computer and to your PIC24 micro.
 *  -# In Bully bootloader, select the appropriate COM port and baud rate and check "OpenCOM."
 *     -# The baud rate is determined by the bootloader firmware loaded on the PIC24 CPU, all of our hex files use 57600 baud.
 *     -# If you do not know which COM port to use, in Windows 
 *        select Start -> Control Panel -> System (or Windows Key + Pause|Break). 
 *        Select the Hardware tab and click Device Manager. In the new window, 
 *        expand the "Ports (COM & LPT)" entry and look for "USB Serial Port (COMx)".
 *  -# Click the HexFile button and navigate within the Open dialog box to your MPLAB's project directory.
 *  -# Select the appropriate .hex file, and click Open.
 *  -# Press and hold the MCLR button on your PIC24 system, then press the PROGRAM button within 2 seconds.
 *     You should see the lower output box scrolling with information as the program is download. If you have
 *     a Sparkfun board, or if you have the RTS# line on your FTDI cable connected to the PIC24 MCLR pin, then
 *     you can press the "MCLR# and Prgm" button to download the program without manually pressing the MCLR button.
 *  -# You should see the welcome message for the Echo application appear after the program is downloaded.
 *  -# At the top of Bully bootloader is a white text input field. Type the letter 'a' into the box, and click Send.
 *  -# Check to see that the letter 'b' appeared in the top output box (the Echo program echos the incremented version
 *     of the character back), just below the input text field. 
 *     More bootloader documentation is found at <a href="manuallyCreated/PIC24_bully_bootloader.pdf"> Bully Bootloader GUI documentation.</a>
 *  
 * Your system is now prepared to run any of the examples
 * included in this package. To create your own program,
 * refer to the many \ref textbookExamples "example programs"
 * available or see the \ref PIC24_support
 * "PIC24 support library" page.
 * 
 */
