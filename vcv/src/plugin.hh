#pragma once
#include "central_data.hh"
#include <rack.hpp>

using namespace rack;

extern std::unique_ptr<CentralData> centralData;
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
//////////////// Auto generated ///////////////////////
// Add models below here
extern Model *modelOctave;
extern Model *modelNoise;
extern Model *modelSHEV;
extern Model *modelENVVCA;
extern Model *modelDEV;
extern Model *modelFreeverb;
extern Model *modelSTS;
extern Model *modelVCAM;
extern Model *modelTapo;
extern Model *modelShift;
extern Model *modelSISM;
extern Model *modelSH;
extern Model *modelSCM;
extern Model *modelRCD;
extern Model *modelQPLFO;
extern Model *modelQCD;
extern Model *modelPI;
extern Model *modelPEG;
extern Model *modelMixer;
extern Model *modelLPG;
extern Model *modelLIO;
extern Model *modelL4;
extern Model *modelGate8;
extern Model *modelGate32;
extern Model *modelGRev;
extern Model *modelFade;
extern Model *modelDLD;
extern Model *modelComp;
extern Model *modelCLKM;
extern Model *modelCLKD;
extern Model *modelADEnv;
extern Model *modelSequant;
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
