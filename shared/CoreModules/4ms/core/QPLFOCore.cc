#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/QPLFO_info.hh"

namespace MetaModule
{

class QPLFOCore : public SmartCoreProcessor<QPLFOInfo> {
	using Info = QPLFOInfo;
	using ThisCore = QPLFOCore;
	using enum Info::Elem;

public:
	QPLFOCore() = default;

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
