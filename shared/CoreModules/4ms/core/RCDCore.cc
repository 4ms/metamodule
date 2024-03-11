#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/RCD_info.hh"

#include "CoreModules/4ms/core/helpers/EdgeDetector.h"
#include "CoreModules/4ms/core/helpers/FlipFlop.h"

namespace MetaModule
{

class RCDCore : public SmartCoreProcessor<RCDInfo> {
	using Info = RCDInfo;
	using ThisCore = RCDCore;
	using enum Info::Elem;

public:
	RCDCore()
		: triggerDetector(1.0f, 2.0f) {
	}

	void update() override {
		setLED<LedInLight>(std::array{1.f,1.f,1.f});
	}

	void set_samplerate(float sr) override {
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	FlipFlop triggerDetector;
	EdgeDetector triggerEdgeDetector;

};

} // namespace MetaModule
