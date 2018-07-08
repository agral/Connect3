###########################  CONFIGURATION SECTION  ###########################
CXX=g++
RM=rm -f
RM_RECURSIVE=rm -rf
CXXFLAGS=-g -c -Wall -Wextra -Wpedantic -D_REENTRANT --std=c++1z
LDFLAGS=
LDLIBS=-lSDL2 -lSDL2_image -lSDL2_ttf
EXE_NAME_APP = Connect3
EXE_NAME_TEST = test_${EXE_NAME_APP}

# Directory structure:
DIR_SRC = src
DIR_BIN = bin
DIR_OBJ = ${DIR_BIN}/obj

DIR_SRC_TEST = test
DIR_OBJ_TEST = ${DIR_OBJ}/test

# Auto-deduced variables:
SOURCES_COMMON := $(shell find ${DIR_SRC} ! -name "main.cpp" -name "*.cpp")
SOURCES_APP := $(shell find ${DIR_SRC} -name "*.cpp")
OBJECTS_APP := $(patsubst ${DIR_SRC}/%.cpp,${DIR_OBJ}/%.o,${SOURCES_APP})
SOURCES_TEST := ${SOURCES_COMMON} $(shell find ${DIR_SRC_TEST} -name "*.cpp")
OBJECTS_TEST := $(patsubst ${DIR_SRC_TEST}/%.cpp,${DIR_OBJ_TEST}/%.o,${SOURCES_TEST})
SOURCES_TESTSUITES_ONLY := $(shell find ${DIR_SRC_TEST} ! -name "Catch_MAIN.cpp" -name "*.cpp")
OBJECTS_TESTSUITES_ONLY := $(patsubst ${DIR_SRC_TEST}/%.cpp,${DIR_OBJ_TEST}/%.o,${SOURCES_TESTSUITES_ONLY})

# Helper methods:
dir_guard=@mkdir -p $(@D)

.PHONY: _default all clean cleantest run test
#######################  END OF CONFIGURATION SECTION  ########################

###############################  RULES FOLLOW  ################################
_default: ${DIR_BIN}/${EXE_NAME_APP}

all : ${DIR_BIN}/${EXE_NAME_APP} ${DIR_BIN}/${EXE_NAME_TEST}

clean:
	@${RM} ${DIR_OBJ}/*.o
	@${RM} ${DIR_OBJ_TEST}/*.o
	@${RM} ${DIR_BIN}/${EXE_NAME_APP}
	@${RM} ${DIR_BIN}/${EXE_NAME_TEST}
	@rm -rf ${DIR_OBJ}
	@rm -rf ${DIR_BIN}
	@echo "Cleaned."

cleantest:
	@${RM} ${OBJECTS_TESTSUITES_ONLY}

run: ${DIR_BIN}/${EXE_NAME_APP}
	@${DIR_BIN}/${EXE_NAME_APP}

test: ${DIR_BIN}/${EXE_NAME_TEST}
	@${DIR_BIN}/${EXE_NAME_TEST}

# Links all the app's object files into a binary, creating an executable:
${DIR_BIN}/${EXE_NAME_APP} : ${OBJECTS_APP}
	${dir_guard}
	@${CXX} ${LDFLAGS} -o $@ ${OBJECTS_APP} ${LDLIBS}

# Links all the test's object files into a binary, creating an executable:
${DIR_BIN}/${EXE_NAME_TEST} : ${OBJECTS_TEST}
	${dir_guard}
	${CXX} ${LDFLAGS} -o $@ ${OBJECTS_TEST} ${LDLIBS}

# Compiles a single file of application's source code to an object file:
${DIR_OBJ}/%.o : ${DIR_SRC}/%.cpp
	${dir_guard}
	${CXX} ${CXXFLAGS} $< -o $@

# Compiles a single file of test suite's source code to an object file:
${DIR_OBJ_TEST}/%.o : ${DIR_SRC_TEST}/%.cpp
	${dir_guard}
	${CXX} ${CXXFLAGS} $< -o $@

print-%:
	@echo $* = $($*)

