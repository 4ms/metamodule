# Set the plugin name
PLUGINNAME := HetrickCV

# Point to the SDK
ADAPTORDIR := ../VCV-metamodule-adaptor

# Helper variable to point to original source files
SOURCEREPO := ../../vcv_ports/hetrickcv

SOURCES :=\
    $(SOURCEREPO)/src/ASR.cpp \
    $(SOURCEREPO)/src/AnalogToDigital.cpp \
    $(SOURCEREPO)/src/BinaryGate.cpp \
    $(SOURCEREPO)/src/BinaryNoise.cpp \
    $(SOURCEREPO)/src/Bitshift.cpp \
    $(SOURCEREPO)/src/Boolean3.cpp \
    $(SOURCEREPO)/src/Chaos1Op.cpp \
    $(SOURCEREPO)/src/Chaos2Op.cpp \
    $(SOURCEREPO)/src/Chaos3Op.cpp \
    $(SOURCEREPO)/src/ChaoticAttractors.cpp \
    $(SOURCEREPO)/src/ClockedNoise.cpp \
    $(SOURCEREPO)/src/Contrast.cpp \
    $(SOURCEREPO)/src/Crackle.cpp \
    $(SOURCEREPO)/src/DigitalToAnalog.cpp \
    $(SOURCEREPO)/src/Dust.cpp \
    $(SOURCEREPO)/src/Exponent.cpp \
    $(SOURCEREPO)/src/FBSineChaos.cpp \
    $(SOURCEREPO)/src/FlipFlop.cpp \
    $(SOURCEREPO)/src/FlipPan.cpp \
    $(SOURCEREPO)/src/GateDelay.cpp \
    $(SOURCEREPO)/src/GateJunction.cpp \
    $(SOURCEREPO)/src/GateJunctionExp.cpp \
    $(SOURCEREPO)/src/Gingerbread.cpp \
    $(SOURCEREPO)/src/LogicCombine.cpp \
    $(SOURCEREPO)/src/MidSide.cpp \
    $(SOURCEREPO)/src/MinMax.cpp \
    $(SOURCEREPO)/src/PhaseDrivenSequencer.cpp \
    $(SOURCEREPO)/src/PhaseDrivenSequencer32.cpp \
    $(SOURCEREPO)/src/PhasorAnalyzer.cpp \
    $(SOURCEREPO)/src/PhasorBurstGen.cpp \
    $(SOURCEREPO)/src/PhasorDivMult.cpp \
    $(SOURCEREPO)/src/PhasorEuclidean.cpp \
    $(SOURCEREPO)/src/PhasorGates.cpp \
    $(SOURCEREPO)/src/PhasorGates32.cpp \
    $(SOURCEREPO)/src/PhasorGates64.cpp \
    $(SOURCEREPO)/src/PhasorGen.cpp \
    $(SOURCEREPO)/src/PhasorGeometry.cpp \
    $(SOURCEREPO)/src/PhasorHumanizer.cpp \
    $(SOURCEREPO)/src/PhasorOctature.cpp \
    $(SOURCEREPO)/src/PhasorQuadrature.cpp \
    $(SOURCEREPO)/src/PhasorRandom.cpp \
    $(SOURCEREPO)/src/PhasorRanger.cpp \
    $(SOURCEREPO)/src/PhasorReset.cpp \
    $(SOURCEREPO)/src/PhasorRhythmGroup.cpp \
    $(SOURCEREPO)/src/PhasorShape.cpp \
    $(SOURCEREPO)/src/PhasorShift.cpp \
    $(SOURCEREPO)/src/PhasorStutter.cpp \
    $(SOURCEREPO)/src/PhasorSubstepShape.cpp \
    $(SOURCEREPO)/src/PhasorSwing.cpp \
    $(SOURCEREPO)/src/PhasorTimetable.cpp \
    $(SOURCEREPO)/src/PhasorToClock.cpp \
    $(SOURCEREPO)/src/PhasorToLFO.cpp \
    $(SOURCEREPO)/src/PhasorToWaveforms.cpp \
    $(SOURCEREPO)/src/XYToPolar.cpp \
    $(SOURCEREPO)/src/Probability.cpp \
    $(SOURCEREPO)/src/Scanner.cpp \
    $(SOURCEREPO)/src/2To4.cpp \
    $(SOURCEREPO)/src/VectorMix.cpp \
    $(SOURCEREPO)/src/Waveshaper.cpp \
    $(SOURCEREPO)/src/HetrickUtilities.cpp \

#DSP
SOURCES += $(wildcard $(SOURCEREPO)/src/DSP/*.cpp)
SOURCES += $(wildcard $(SOURCEREPO)/src/DSP/Phasors/*.cpp)

#Gamma
SOURCES += \
    $(SOURCEREPO)/Gamma/src/arr.cpp \
    $(SOURCEREPO)/Gamma/src/DFT.cpp \
    $(SOURCEREPO)/Gamma/src/Domain.cpp \
    $(SOURCEREPO)/Gamma/src/FFT_fftpack.cpp \
    $(SOURCEREPO)/Gamma/src/fftpack++1.cpp \
    $(SOURCEREPO)/Gamma/src/fftpack++2.cpp \
    $(SOURCEREPO)/Gamma/src/scl.cpp \


# If you can't build all the modules, then copy the plugin.cpp file from the source repo, 
# and remove the calls to plugin->addModel() for the modules you don't want to build.
SOURCES += ./HetrickCV.cpp
		
INCLUDES := -I. \
			-I$(SOURCEREPO)/src \
			-I$(SOURCEREPO)/Gamma \
			-I$(SOURCEREPO) \

# Any extra flags needed can go here:
EXTRA_CLAGS := -fvisibility=hidden \
			   -Wno-misleading-indentation \
			   -Wno-unused-but-set-variable \
			   -Wno-unused-function \
			   -Wno-unused-variable \

EXTRA_CPPFLAGS := -Wno-deprecated-enum-float-conversion \
				  -fvisibility-inlines-hidden \

include $(ADAPTORDIR)/plugin.mk
