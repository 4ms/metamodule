#pragma once
#include <rack.hpp>

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
extern Model *modelLowpassfilter;
extern Model *modelLowpassgate;
extern Model *modelClkmultiplier;
extern Model *modelClkdivider;
// extern Model *modelDual_opener;
// extern Model *modelDspTemplate;
// extern Model *modelAdjTest;

extern Model *modelExpander;
extern Model *modelPatchPlayer;

//Layout Templates:
extern Model *modelTemplate4;
extern Model *modelTemplate8;
extern Model *modelTemplate12;
extern Model *modelTemplate16;

//CoreModules:
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
