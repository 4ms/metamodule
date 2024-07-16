#include "plugin/Plugin.hpp"

#ifndef BUILD_DYN_PLUGIN_Rack
namespace Fundamental
{
void init(rack::plugin::Plugin *p);
}
#endif

extern rack::plugin::Model *modelVCO;
extern rack::plugin::Model *modelVCO2;
extern rack::plugin::Model *modelVCF;
extern rack::plugin::Model *modelVCA_1;
extern rack::plugin::Model *modelVCA;
extern rack::plugin::Model *modelLFO;
extern rack::plugin::Model *modelLFO2;
extern rack::plugin::Model *modelDelay;
extern rack::plugin::Model *modelADSR;
extern rack::plugin::Model *modelMixer;
extern rack::plugin::Model *modelVCMixer;
extern rack::plugin::Model *model_8vert;
extern rack::plugin::Model *modelUnity;
extern rack::plugin::Model *modelMutes;
extern rack::plugin::Model *modelPulses;
extern rack::plugin::Model *modelScope;
extern rack::plugin::Model *modelSEQ3;
extern rack::plugin::Model *modelSequentialSwitch1;
extern rack::plugin::Model *modelSequentialSwitch2;
extern rack::plugin::Model *modelOctave;
extern rack::plugin::Model *modelQuantizer;
extern rack::plugin::Model *modelSplit;
extern rack::plugin::Model *modelMerge;
extern rack::plugin::Model *modelSum;
extern rack::plugin::Model *modelViz;
extern rack::plugin::Model *modelMidSide;
extern rack::plugin::Model *modelNoise;
extern rack::plugin::Model *modelRandom;
extern rack::plugin::Model *modelCVMix;
extern rack::plugin::Model *modelFade;
extern rack::plugin::Model *modelLogic;
extern rack::plugin::Model *modelCompare;
extern rack::plugin::Model *modelGates;
extern rack::plugin::Model *modelProcess;
extern rack::plugin::Model *modelMult;
extern rack::plugin::Model *modelRescale;
extern rack::plugin::Model *modelRandomValues;
extern rack::plugin::Model *modelPush;
extern rack::plugin::Model *modelSHASR;
