#include "CoreModules/Befaco/info/DualAtenuverter_info.hh"
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include <memory>

class DualAtenuverter;

namespace MetaModule
{

namespace Befaco
{

// static std::unique_ptr<CoreProcessor> create() { return std::make_unique<DualAtenuverter>(); }

bool registered_DualAtenuverter =
	ModuleFactory::registerModuleType(DualAtenuverterInfo::slug, ModuleInfoView::makeView<DualAtenuverterInfo>());
} // namespace Befaco

namespace AudibleInstruments
{
//
}
} // namespace MetaModule
