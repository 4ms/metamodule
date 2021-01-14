#pragma once
#include <rack.hpp>

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
extern Model *modelEightstepprob;
extern Model *modelQuantizer;
extern Model *modelFourstep;
extern Model *modelEightstep;
extern Model *modelBitcrush;
extern Model *modelPhaser;
extern Model *modelFreqshift;
extern Model *modelLowpassfilter;
extern Model *modelLowpassgate;
extern Model *modelClkmultiplier;
extern Model *modelClkdivider;
extern Model *modelLFO;
extern Model *modelAD;
extern Model *modelCrossfade;
extern Model *modelMixer4;
extern Model *modelLogic;
extern Model *modelSampleHold;
extern Model *modelAtt;
extern Model *modelFadeDelay;
extern Model *modelVCA;
extern Model *modelComparator;
extern Model *modelSend;

extern Model *modelExpander;
