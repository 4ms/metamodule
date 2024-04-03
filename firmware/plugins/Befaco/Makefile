# Set the plugin name
PLUGINNAME := Befaco

# Point to the SDK
ADAPTORDIR := ../VCV-metamodule-adaptor

# Helper variable to point to original source files
BEFACODIR := ../../vcv_ports/Befaco

SOURCES :=\
		$(BEFACODIR)/src/DualAtenuverter.cpp \
		$(BEFACODIR)/src/ABC.cpp \
		$(BEFACODIR)/src/ADSR.cpp \
		$(BEFACODIR)/src/ChoppingKinky.cpp \
		$(BEFACODIR)/src/HexmixVCA.cpp \
		$(BEFACODIR)/src/Kickall.cpp \
		$(BEFACODIR)/src/Mixer.cpp \
		$(BEFACODIR)/src/Morphader.cpp \
		$(BEFACODIR)/src/MotionMTR.cpp \
		$(BEFACODIR)/src/Percall.cpp \
		$(BEFACODIR)/src/Rampage.cpp \
		$(BEFACODIR)/src/STMix.cpp \
		$(BEFACODIR)/src/SamplingModulator.cpp \
		$(BEFACODIR)/src/SlewLimiter.cpp \
		$(BEFACODIR)/src/StereoStrip.cpp \
		$(BEFACODIR)/src/EvenVCO.cpp \
		$(BEFACODIR)/src/PonyVCO.cpp \
		$(BEFACODIR)/src/SpringReverb.cpp \

# If you can't build all the modules, then copy the plugin.cpp file from the source repo, 
# remove the call to plugin->addModel() for the modules you don't want to build
SOURCES += ./plugin.cpp
		
		
INCLUDES := -I. \
			-I$(BEFACODIR)/src \

# Any extra flags needed can go here:
EXTRA_CLAGS := 
EXTRA_CPPFLAGS := -Wno-deprecated-enum-float-conversion

include $(ADAPTORDIR)/plugin.mk
