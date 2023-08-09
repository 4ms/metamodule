#include "generic_module.hh"
#include "CoreModules/4ms/info/Mixer_info.hh"
using namespace MetaModule;

rack::Model* modelMixer = GenericModule<MixerInfo>::create();
