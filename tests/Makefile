#Set this to @ to keep the makefile quiet
# SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = localtests
CPPUTEST_OBJS_DIR = tests/build/objs
CPPUTEST_LIB_DIR = tests/build/lib

#--- Inputs ----#
CPPUTEST_HOME = tests/cpputest
CPP_PLATFORM = Gcc
CC = gcc
PROJECT_HOME_DIR = .

# CPPUTEST_USE_STD_C_LIB = N
# CPPUTEST_USE_STD_CPP_LIB = N

SRC_FILES = src/drivers/rotary.cc \
			# src/debug.cc \
			#src/drivers/pin.cc

# SRC_DIRS = \
# 	src \

TEST_SRC_DIRS = \
	tests \
	tests/stubs \
	tests/stubs/driver \
	tests/stubs/stm32 \


INCLUDE_DIRS =\
	$(CPPUTEST_HOME)/include\
	tests/fff \
	tests/ \
	tests/stubs \
	tests/stubs/stm32 \
	tests/stubs/driver \
	stm32/periph/include \
	stm32/device/include \
	stm32/core/include \
	src \
	src/util \
	src/drivers \


MOCKS_SRC_DIRS = \
	mocks \
	mocks/drivers \

CPPUTEST_WARNINGFLAGS += -Wall 
CPPUTEST_WARNINGFLAGS += -Werror
CPPUTEST_WARNINGFLAGS += -Wswitch-default
CPPUTEST_WARNINGFLAGS += -Wno-format-nonliteral
CPPUTEST_WARNINGFLAGS += -Wno-sign-conversion 
CPPUTEST_WARNINGFLAGS += -Wno-pedantic 
CPPUTEST_WARNINGFLAGS += -Wno-shadow
CPPUTEST_WARNINGFLAGS += -Wno-missing-field-initializers
CPPUTEST_WARNINGFLAGS += -Wno-unused-parameter
CPPUTEST_WARNINGFLAGS += -Wno-register
CPPUTEST_WARNINGFLAGS += -Wno-missing-noreturn
CPPUTEST_WARNINGFLAGS += -Wno-unused-template \
						-Wno-poison-system-directories \

CPPUTEST_CFLAGS += -Wall
CPPUTEST_CFLAGS += -Wstrict-prototypes
CPPUTEST_CFLAGS += -pedantic
CPPUTEST_CFLAGS += -Wno-missing-prototypes
CPPUTEST_CFLAGS += -Wno-documentation\
					-Wno-documentation-unknown-command \
					-DTESTPROJECT \
					-DSTM32F746xx \
					-DSTM32F7 \
					-DUSE_HAL_DRIVER \
					-DUSE_FULL_LL_DRIVER \
					-D'F_CPU=216000000' \
					-Wno-poison-system-directories \


CPPUTEST_CXXFLAGS += --std=c++17
CPPUTEST_CXXFLAGS += -Wno-c++98-compat-pedantic
CPPUTEST_CXXFLAGS += -Wno-c++98-compat
CPPUTEST_CXXFLAGS += -Wno-inconsistent-missing-destructor-override
CPPUTEST_CXXFLAGS += -Wno-documentation \
					-Wno-documentation-unknown-command\
					-Wno-missing-noreturn \
					-DTESTPROJECT \
					-DSTM32F746xx \
					-DSTM32F7 \
					-DUSE_HAL_DRIVER \
					-DUSE_FULL_LL_DRIVER \
					-D'F_CPU=216000000' \

#LD_LIBRARIES = -lpthread
-include tests/cpputest/build/MakefileWorker.mk

.PHONY: cpputest
cpputest: tests/cpputest/lib/libCppUTest.a

ifeq ("$(wildcard tests/cpputest/build/MakefileWorker.mk)","")
	@echo "Building MakefileWorker.mk"
	cd tests/cpputest; autoreconf . -i && ./configure --enable-std-cpp14 && make tdd
endif


tests/cpputest/lib/libCppUTest.a:
	cd ./tests/cpputest; autoreconf . -i && ./configure --enable-std-cpp14 && make tdd
