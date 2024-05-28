#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/PI_info.hh"

namespace MetaModule
{

class PICore : public SmartCoreProcessor<PIInfo> {
	using Info = PIInfo;
	using ThisCore = PICore;
	using enum Info::Elem;

public:
	PICore() :
		sampleRate(48000.f) {

	};

	void update() override {
	}

	void set_samplerate(float sr) override {
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>(), Info::png_filename);
	// clang-format on

private:
	float sampleRate;
};

} // namespace MetaModule
