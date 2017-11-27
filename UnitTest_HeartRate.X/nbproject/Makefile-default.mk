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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/UnitTest_HeartRate.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/UnitTest_HeartRate.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=LCD/busyxlcd.c LCD/openxlcd.c LCD/putrxlcd.c LCD/putsxlcd.c LCD/readaddr.c LCD/readdata.c LCD/setcgram.c LCD/setddram.c LCD/wcmdxlcd.c LCD/writdata.c Source_HeartRate.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/LCD/busyxlcd.o ${OBJECTDIR}/LCD/openxlcd.o ${OBJECTDIR}/LCD/putrxlcd.o ${OBJECTDIR}/LCD/putsxlcd.o ${OBJECTDIR}/LCD/readaddr.o ${OBJECTDIR}/LCD/readdata.o ${OBJECTDIR}/LCD/setcgram.o ${OBJECTDIR}/LCD/setddram.o ${OBJECTDIR}/LCD/wcmdxlcd.o ${OBJECTDIR}/LCD/writdata.o ${OBJECTDIR}/Source_HeartRate.o
POSSIBLE_DEPFILES=${OBJECTDIR}/LCD/busyxlcd.o.d ${OBJECTDIR}/LCD/openxlcd.o.d ${OBJECTDIR}/LCD/putrxlcd.o.d ${OBJECTDIR}/LCD/putsxlcd.o.d ${OBJECTDIR}/LCD/readaddr.o.d ${OBJECTDIR}/LCD/readdata.o.d ${OBJECTDIR}/LCD/setcgram.o.d ${OBJECTDIR}/LCD/setddram.o.d ${OBJECTDIR}/LCD/wcmdxlcd.o.d ${OBJECTDIR}/LCD/writdata.o.d ${OBJECTDIR}/Source_HeartRate.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/LCD/busyxlcd.o ${OBJECTDIR}/LCD/openxlcd.o ${OBJECTDIR}/LCD/putrxlcd.o ${OBJECTDIR}/LCD/putsxlcd.o ${OBJECTDIR}/LCD/readaddr.o ${OBJECTDIR}/LCD/readdata.o ${OBJECTDIR}/LCD/setcgram.o ${OBJECTDIR}/LCD/setddram.o ${OBJECTDIR}/LCD/wcmdxlcd.o ${OBJECTDIR}/LCD/writdata.o ${OBJECTDIR}/Source_HeartRate.o

# Source Files
SOURCEFILES=LCD/busyxlcd.c LCD/openxlcd.c LCD/putrxlcd.c LCD/putsxlcd.c LCD/readaddr.c LCD/readdata.c LCD/setcgram.c LCD/setddram.c LCD/wcmdxlcd.c LCD/writdata.c Source_HeartRate.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/UnitTest_HeartRate.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F452
MP_PROCESSOR_OPTION_LD=18f452
MP_LINKER_DEBUG_OPTION=-r=ROM@0x7DC0:0x7FFF -r=RAM@GPR:0x5F4:0x5FF -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/LCD/busyxlcd.o: LCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/busyxlcd.o   LCD/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/busyxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/busyxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/openxlcd.o: LCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/openxlcd.o   LCD/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/openxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/openxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/putrxlcd.o: LCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/putrxlcd.o   LCD/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/putrxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/putrxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/putsxlcd.o: LCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/putsxlcd.o   LCD/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/putsxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/putsxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/readaddr.o: LCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readaddr.o.d 
	@${RM} ${OBJECTDIR}/LCD/readaddr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/readaddr.o   LCD/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/readaddr.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/readaddr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/readdata.o: LCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readdata.o.d 
	@${RM} ${OBJECTDIR}/LCD/readdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/readdata.o   LCD/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/readdata.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/readdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/setcgram.o: LCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setcgram.o.d 
	@${RM} ${OBJECTDIR}/LCD/setcgram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/setcgram.o   LCD/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/setcgram.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/setcgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/setddram.o: LCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setddram.o.d 
	@${RM} ${OBJECTDIR}/LCD/setddram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/setddram.o   LCD/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/setddram.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/setddram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/wcmdxlcd.o: LCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/wcmdxlcd.o   LCD/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/wcmdxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/wcmdxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/writdata.o: LCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/writdata.o.d 
	@${RM} ${OBJECTDIR}/LCD/writdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/writdata.o   LCD/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/writdata.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/writdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source_HeartRate.o: Source_HeartRate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Source_HeartRate.o.d 
	@${RM} ${OBJECTDIR}/Source_HeartRate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source_HeartRate.o   Source_HeartRate.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source_HeartRate.o 
	@${FIXDEPS} "${OBJECTDIR}/Source_HeartRate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/LCD/busyxlcd.o: LCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/busyxlcd.o   LCD/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/busyxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/busyxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/openxlcd.o: LCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/openxlcd.o   LCD/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/openxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/openxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/putrxlcd.o: LCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/putrxlcd.o   LCD/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/putrxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/putrxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/putsxlcd.o: LCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/putsxlcd.o   LCD/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/putsxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/putsxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/readaddr.o: LCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readaddr.o.d 
	@${RM} ${OBJECTDIR}/LCD/readaddr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/readaddr.o   LCD/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/readaddr.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/readaddr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/readdata.o: LCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readdata.o.d 
	@${RM} ${OBJECTDIR}/LCD/readdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/readdata.o   LCD/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/readdata.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/readdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/setcgram.o: LCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setcgram.o.d 
	@${RM} ${OBJECTDIR}/LCD/setcgram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/setcgram.o   LCD/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/setcgram.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/setcgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/setddram.o: LCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setddram.o.d 
	@${RM} ${OBJECTDIR}/LCD/setddram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/setddram.o   LCD/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/setddram.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/setddram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/wcmdxlcd.o: LCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.o.d 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/wcmdxlcd.o   LCD/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/wcmdxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/wcmdxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCD/writdata.o: LCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/writdata.o.d 
	@${RM} ${OBJECTDIR}/LCD/writdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCD/writdata.o   LCD/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCD/writdata.o 
	@${FIXDEPS} "${OBJECTDIR}/LCD/writdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source_HeartRate.o: Source_HeartRate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Source_HeartRate.o.d 
	@${RM} ${OBJECTDIR}/Source_HeartRate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source_HeartRate.o   Source_HeartRate.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source_HeartRate.o 
	@${FIXDEPS} "${OBJECTDIR}/Source_HeartRate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/UnitTest_HeartRate.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    lab1_i.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "lab1_i.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/UnitTest_HeartRate.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/UnitTest_HeartRate.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   lab1_i.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "lab1_i.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/UnitTest_HeartRate.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
