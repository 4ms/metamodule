#include "CoreModules/coreProcessor.h"
#include "CoreModules/elements/element_info_view.hh"
#include "info/SMR_info.hh"
#include "CoreModules/moduleFactory.hh"

namespace MetaModule
{

class SMRCore : public CoreProcessor {
	using Info = SMRInfo;
	using ThisCore = SMRCore;

public:
	SMRCore() = default;

	void update() override {
	}

	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
	}

	float get_output(int output_id) const override {
		return 0.f;
	}

	void set_samplerate(float sr) override {
	}

	float get_led_brightness(int led_id) const override {
		return 0.f;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
};

} // namespace MetaModule
