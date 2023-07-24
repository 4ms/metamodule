#include "generic_module.hh"
#include "CoreModules/4ms/info/SMR_info.hh"
using namespace MetaModule;

rack::Model* modelSMR = GenericModule<SMRInfo>::create();
