#include "info/Tapo_info.hh"
#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"

namespace MetaModule
{

class TapoCore : public SmartCoreProcessor<TapoInfo> {
	using Info = TapoInfo;
	using ThisCore = TapoCore;
	using enum Info::Elem;

public:
	TapoCore() = default;

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
