#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/L4_info.hh"
#include "l4/Tables.h"

namespace MetaModule
{

class L4Core : public SmartCoreProcessor<L4Info> {
	using Info = L4Info;
	using ThisCore = L4Core;
	using enum Info::Elem;

public:
	L4Core() = default;

	void update() override {
		if(auto input = getInput<In1In>(); input) {
			setOutput<OutLeftOut>(*input * PanningTable.lookup(1.f - getState<Pan1Knob>()));
		}
		
	}

	void set_samplerate(float sr) override {
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
};

} // namespace MetaModule
