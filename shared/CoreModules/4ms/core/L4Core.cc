#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/L4_info.hh"

namespace MetaModule
{

class L4Core : public SmartCoreProcessor<L4Info> {
	using Info = L4Info;
	using ThisCore = L4Core;
	using enum Info::Elem;

public:
	L4Core() = default;

	void update() override {
		
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
