#include "moduleFactory.hh"

namespace MetaModule
{

SeqMap<ModuleTypeSlug, ModuleFactory::CreateModuleFunc, ModuleFactory::MAX_MODULE_TYPES> ModuleFactory::creation_funcs;

SeqMap<ModuleTypeSlug, ModuleInfoView, ModuleFactory::MAX_MODULE_TYPES> ModuleFactory::infos;

SeqMap<ModuleTypeSlug, ModuleFactory::FaceplatePtr, ModuleFactory::MAX_MODULE_TYPES> ModuleFactory::faceplates;

} // namespace MetaModule
