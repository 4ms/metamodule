# Set the plugin name
PLUGINNAME := NLC

# Point to the SDK
ADAPTORDIR := ../VCV-metamodule-adaptor

# Helper variable to point to original source files
SOURCEDIR := ../../vcv_ports/nonlinearcircuits

SOURCES :=\
    $(SOURCEDIR)/src/NLCShared.cpp \
    $(SOURCEDIR)/src/4Seq.cpp \
    $(SOURCEDIR)/src/8BitCipher.cpp \
    $(SOURCEDIR)/src/BOOLs.cpp \
    $(SOURCEDIR)/src/DivideConquer.cpp \
    $(SOURCEDIR)/src/DivineCMOS.cpp \
    $(SOURCEDIR)/src/DoubleNeuron.cpp \
    $(SOURCEDIR)/src/Genie.cpp \
    $(SOURCEDIR)/src/LetsSplosh.cpp \
    $(SOURCEDIR)/src/Neuron.cpp \
    $(SOURCEDIR)/src/Numberwang.cpp \
    $(SOURCEDIR)/src/Router.cpp \
    $(SOURCEDIR)/src/Segue.cpp \
    $(SOURCEDIR)/src/SlothApathy.cpp \
    $(SOURCEDIR)/src/SlothInertia.cpp \
    $(SOURCEDIR)/src/SlothTorpor.cpp \
    $(SOURCEDIR)/src/SquidAxon.cpp \
    $(SOURCEDIR)/src/Statues.cpp \
    $(SOURCEDIR)/src/TripleSloth.cpp \

# If you can't build all the modules, then copy the plugin.cpp file from the source repo, 
# remove the call to plugin->addModel() for the modules you don't want to build
SOURCES += $(SOURCEDIR)/src/NLC.cpp
		
		
INCLUDES := -I. \
			-I$(SOURCEDIR)/src \

# Any extra flags needed can go here:
EXTRA_CLAGS := 
EXTRA_CPPFLAGS := \
		  -Wno-deprecated-enum-float-conversion \
          -Wno-misleading-indentation \
          -Wno-unused-but-set-variable \
          -Wno-unused-function \

include $(ADAPTORDIR)/plugin.mk
