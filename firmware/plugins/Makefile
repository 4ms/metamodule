BINARYNAME := Befaco
BUILDDIR := build
ADAPTORDIR := VCV-metamodule-adaptor
OBJDIR := $(BUILDDIR)/obj/obj

SOURCES = $(ADAPTORDIR)/libc_stub.c \
		Befaco/src/DualAtenuverter.cpp \
		Befaco/src/ABC.cpp \
		Befaco/src/ADSR.cpp \
		Befaco/src/ChoppingKinky.cpp \
		Befaco/src/HexmixVCA.cpp \
		Befaco/src/Kickall.cpp \
		Befaco/src/Mixer.cpp \
		Befaco/src/Morphader.cpp \
		Befaco/src/MotionMTR.cpp \
		Befaco/src/Percall.cpp \
		Befaco/src/Rampage.cpp \
		Befaco/src/STMix.cpp \
		Befaco/src/SamplingModulator.cpp \
		Befaco/src/SlewLimiter.cpp \
		Befaco/src/StereoStrip.cpp \
		Befaco/src/EvenVCO.cpp \
		Befaco/src/PonyVCO.cpp \
		Befaco/src/SpringReverb.cpp \
		Befaco-plugin.cpp \
		
INCLUDES := -I. \
			-IBefaco/src \
			-I$(ADAPTORDIR)/include \
			-I$(ADAPTORDIR)/dep/include \
			-I$(ADAPTORDIR)/dep/include/cpputil

EXTRA_CPPFLAGS := -Wno-deprecated-enum-float-conversion

include $(ADAPTORDIR)/plugin.mk
