#pragma once
#include "centralData.h"
#include <rack.hpp>

using namespace rack;

// extern CentralData *centralData;
extern std::unique_ptr<CentralData> centralData;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
extern Model *modelHubMedium;
extern Model *modelInfosc01;
extern Model *modelDjembe;
extern Model *modelBipolarsource;
extern Model *modelMultilfo;
extern Model *modelEnvelopefollower;
extern Model *modelVoltagesource;
extern Model *modelNoise;
extern Model *modelSampleplayer;
extern Model *modelSlewlimiter;
extern Model *modelBandpassfilter;
extern Model *modelHighpassfilter;
extern Model *modelReverb;
extern Model *modelKarplus;
extern Model *modelGateseq16;
extern Model *modelGateseq8;
extern Model *modelOctave;
extern Model *modelMinmax;
extern Model *modelDrum;
extern Model *modelComplexenvelope;
extern Model *modelFmosc;
extern Model *modelStereomixer;
extern Model *modelPanner;
extern Model *modelGateconverter;
extern Model *modelDetune;
extern Model *modelPitchshift;
extern Model *modelSwitch4to1;
extern Model *modelSwitch1to4;
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
extern Model *modelHubMini;
extern Model *modelInfosc64bphas;
extern Model *modelEnOsc;
