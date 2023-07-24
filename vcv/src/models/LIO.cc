#include "generic_module.hh"
#include "CoreModules/4ms/info/LIO_info.hh"
using namespace MetaModule;

rack::Model* modelLIO = GenericModule<LIOInfo>::create();
