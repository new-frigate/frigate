#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Compiler/ControlEdge.o \
	${OBJECTDIR}/Compiler/Exchange.o \
	${OBJECTDIR}/Compiler/ExternalEdge.o \
	${OBJECTDIR}/Compiler/Graph.o \
	${OBJECTDIR}/Compiler/InternalEdge.o \
	${OBJECTDIR}/Compiler/StaticHelper.o \
	${OBJECTDIR}/Compiler/Subgraph.o \
	${OBJECTDIR}/Compiler/Vertex.o \
	${OBJECTDIR}/Parser/HexParser.o \
	${OBJECTDIR}/Parser/Lexer.o \
	${OBJECTDIR}/Parser/Parser.o \
	${OBJECTDIR}/Parser/Tag.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/translator

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/translator: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/translator ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Compiler/ControlEdge.o: Compiler/ControlEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Compiler/ControlEdge.o Compiler/ControlEdge.cpp

${OBJECTDIR}/Compiler/Exchange.o: Compiler/Exchange.cpp 
	${MKDIR} -p ${OBJECTDIR}/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Compiler/Exchange.o Compiler/Exchange.cpp

${OBJECTDIR}/Compiler/ExternalEdge.o: Compiler/ExternalEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Compiler/ExternalEdge.o Compiler/ExternalEdge.cpp

${OBJECTDIR}/Compiler/Graph.o: Compiler/Graph.cpp 
	${MKDIR} -p ${OBJECTDIR}/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Compiler/Graph.o Compiler/Graph.cpp

${OBJECTDIR}/Compiler/InternalEdge.o: Compiler/InternalEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Compiler/InternalEdge.o Compiler/InternalEdge.cpp

${OBJECTDIR}/Compiler/StaticHelper.o: Compiler/StaticHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Compiler/StaticHelper.o Compiler/StaticHelper.cpp

${OBJECTDIR}/Compiler/Subgraph.o: Compiler/Subgraph.cpp 
	${MKDIR} -p ${OBJECTDIR}/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Compiler/Subgraph.o Compiler/Subgraph.cpp

${OBJECTDIR}/Compiler/Vertex.o: Compiler/Vertex.cpp 
	${MKDIR} -p ${OBJECTDIR}/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Compiler/Vertex.o Compiler/Vertex.cpp

${OBJECTDIR}/Parser/HexParser.o: Parser/HexParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/Parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Parser/HexParser.o Parser/HexParser.cpp

${OBJECTDIR}/Parser/Lexer.o: Parser/Lexer.cpp 
	${MKDIR} -p ${OBJECTDIR}/Parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Parser/Lexer.o Parser/Lexer.cpp

${OBJECTDIR}/Parser/Parser.o: Parser/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/Parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Parser/Parser.o Parser/Parser.cpp

${OBJECTDIR}/Parser/Tag.o: Parser/Tag.cpp 
	${MKDIR} -p ${OBJECTDIR}/Parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Parser/Tag.o Parser/Tag.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/translator

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
