#include "CoreModules/Befaco/info/DualAtenuverter_info.hh"
#include "CoreModules/Befaco/info/EvenVCO_info.hh"
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include <memory>

class DualAtenuverter;

namespace MetaModule
{

namespace Befaco
{

bool registered_DualAtenuverter =
	ModuleFactory::registerModuleType(DualAtenuverterInfo::slug, ModuleInfoView::makeView<DualAtenuverterInfo>());
bool registered_EvenVCO = ModuleFactory::registerModuleType(EvenVCOInfo::slug, ModuleInfoView::makeView<EvenVCOInfo>());

} // namespace Befaco

namespace AudibleInstruments
{
//
}
} // namespace MetaModule
