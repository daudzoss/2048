#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/2048.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/2048.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=game.s main.s reese/common/pic24_serial.c reese/common/pic24_util.c reese/common/pic24_clockfreq.c reese/common/pic24_uart.c output.c reese/common/pic24_configbits.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/game.o ${OBJECTDIR}/main.o ${OBJECTDIR}/reese/common/pic24_serial.o ${OBJECTDIR}/reese/common/pic24_util.o ${OBJECTDIR}/reese/common/pic24_clockfreq.o ${OBJECTDIR}/reese/common/pic24_uart.o ${OBJECTDIR}/output.o ${OBJECTDIR}/reese/common/pic24_configbits.o
POSSIBLE_DEPFILES=${OBJECTDIR}/game.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/reese/common/pic24_serial.o.d ${OBJECTDIR}/reese/common/pic24_util.o.d ${OBJECTDIR}/reese/common/pic24_clockfreq.o.d ${OBJECTDIR}/reese/common/pic24_uart.o.d ${OBJECTDIR}/output.o.d ${OBJECTDIR}/reese/common/pic24_configbits.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/game.o ${OBJECTDIR}/main.o ${OBJECTDIR}/reese/common/pic24_serial.o ${OBJECTDIR}/reese/common/pic24_util.o ${OBJECTDIR}/reese/common/pic24_clockfreq.o ${OBJECTDIR}/reese/common/pic24_uart.o ${OBJECTDIR}/output.o ${OBJECTDIR}/reese/common/pic24_configbits.o

# Source Files
SOURCEFILES=game.s main.s reese/common/pic24_serial.c reese/common/pic24_util.c reese/common/pic24_clockfreq.c reese/common/pic24_uart.c output.c reese/common/pic24_configbits.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/2048.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ128GA010
MP_LINKER_FILE_OPTION=,--script=p24FJ128GA010.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/reese/common/pic24_serial.o: reese/common/pic24_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_serial.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_serial.c  -o ${OBJECTDIR}/reese/common/pic24_serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_serial.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_serial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/reese/common/pic24_util.o: reese/common/pic24_util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_util.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_util.c  -o ${OBJECTDIR}/reese/common/pic24_util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_util.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_util.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/reese/common/pic24_clockfreq.o: reese/common/pic24_clockfreq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_clockfreq.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_clockfreq.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_clockfreq.c  -o ${OBJECTDIR}/reese/common/pic24_clockfreq.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_clockfreq.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_clockfreq.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/reese/common/pic24_uart.o: reese/common/pic24_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_uart.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_uart.c  -o ${OBJECTDIR}/reese/common/pic24_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/output.o: output.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/output.o.d 
	@${RM} ${OBJECTDIR}/output.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  output.c  -o ${OBJECTDIR}/output.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/output.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/output.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/reese/common/pic24_configbits.o: reese/common/pic24_configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_configbits.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_configbits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_configbits.c  -o ${OBJECTDIR}/reese/common/pic24_configbits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_configbits.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_configbits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/reese/common/pic24_serial.o: reese/common/pic24_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_serial.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_serial.c  -o ${OBJECTDIR}/reese/common/pic24_serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_serial.o.d"        -g -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_serial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/reese/common/pic24_util.o: reese/common/pic24_util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_util.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_util.c  -o ${OBJECTDIR}/reese/common/pic24_util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_util.o.d"        -g -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_util.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/reese/common/pic24_clockfreq.o: reese/common/pic24_clockfreq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_clockfreq.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_clockfreq.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_clockfreq.c  -o ${OBJECTDIR}/reese/common/pic24_clockfreq.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_clockfreq.o.d"        -g -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_clockfreq.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/reese/common/pic24_uart.o: reese/common/pic24_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_uart.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_uart.c  -o ${OBJECTDIR}/reese/common/pic24_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_uart.o.d"        -g -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/output.o: output.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/output.o.d 
	@${RM} ${OBJECTDIR}/output.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  output.c  -o ${OBJECTDIR}/output.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/output.o.d"        -g -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/output.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/reese/common/pic24_configbits.o: reese/common/pic24_configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/reese/common" 
	@${RM} ${OBJECTDIR}/reese/common/pic24_configbits.o.d 
	@${RM} ${OBJECTDIR}/reese/common/pic24_configbits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  reese/common/pic24_configbits.c  -o ${OBJECTDIR}/reese/common/pic24_configbits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/reese/common/pic24_configbits.o.d"        -g -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/reese/common/pic24_configbits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/game.o: game.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/game.o.d 
	@${RM} ${OBJECTDIR}/game.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  game.s  -o ${OBJECTDIR}/game.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -Wa,-MD,"${OBJECTDIR}/game.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax,-ahl=${OBJECTDIR}/game.lst,--defsym=AUTOMOVE=1 --defsym=TWOROWLCD=1$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/game.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.o: main.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  main.s  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -Wa,-MD,"${OBJECTDIR}/main.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax,-ahl=${OBJECTDIR}/main.lst,--defsym=AUTOMOVE=1 --defsym=TWOROWLCD=1$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/main.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/game.o: game.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/game.o.d 
	@${RM} ${OBJECTDIR}/game.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  game.s  -o ${OBJECTDIR}/game.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -Wa,-MD,"${OBJECTDIR}/game.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-ahl=${OBJECTDIR}/game.lst,--defsym=AUTOMOVE=1 --defsym=TWOROWLCD=1$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/game.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.o: main.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  main.s  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -Wa,-MD,"${OBJECTDIR}/main.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-ahl=${OBJECTDIR}/main.lst,--defsym=AUTOMOVE=1 --defsym=TWOROWLCD=1$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/main.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/2048.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/2048.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include"  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/2048.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/2048.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DEXPLORER16_100P -DSERIAL_EOL_DEFAULT=SERIAL_EOL_CR_LF -legacy-libc  -I"/opt/microchip/xc16/v1.25/include" -I"/opt/microchip/xc16/v1.25/support/PIC24F/h" -I"/opt/microchip/xc16/v1.25/support/PIC24F/inc" -I"reese/include" -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/2048.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
