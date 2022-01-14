#pragma once
#include "central_data.hpp"
#include <rack.hpp>

using namespace rack;

// extern CentralData *centralData;
extern std::unique_ptr<CentralData> centralData;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
//////////////// Auto generated ///////////////////////
// Add models below here
extern Model *modelVerb;
extern Model *modelSwitch41;
extern Model *modelSwitch14;
extern Model *modelSeq8;
extern Model *modelSeq4;
extern Model *modelQuant;
extern Model *modelProb8;
extern Model *modelMNMX;
extern Model *modelLPF;
extern Model *modelAtvert2;
extern Model *modelBPF;
extern Model *modelBuffMult;
extern Model *modelComplexEG;
extern Model *modelDetune;
extern Model *modelDjembe;
extern Model *modelDrum;
extern Model *modelEnOsc;
extern Model *modelFM;
extern Model *modelFollow;
extern Model *modelGate;
extern Model *modelHPF;
extern Model *modelHubMedium;
extern Model *modelInfOsc;
extern Model *modelKPLS;
extern Model *modelMultiLFO;
extern Model *modelPan;
extern Model *modelPitchShift;
extern Model *modelSMR;
extern Model *modelSlew;
extern Model *modelSource;
extern Model *modelStMix;
//////////////////////////////////////////////////
