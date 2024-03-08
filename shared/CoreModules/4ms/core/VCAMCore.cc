#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/VCAM_info.hh"
#include "vcam/vcam_channel.h"

namespace MetaModule
{

class VCAMCore : public SmartCoreProcessor<VCAMInfo> {
	using Info = VCAMInfo;
	using ThisCore = VCAMCore;
	using enum Info::Elem;

public:
	VCAMCore() = default;

	void update() override {
		channelA1.pot(getState<A1LevelKnob>());

		if (auto control = getInput<A1JackIn>(); control) {
			channelA1.control(*control);
		} else {
			channelA1.control(5.f);
		}

		bool isMuted = (getState<A1Button>() == LatchingButton::State_t::DOWN);
		channelA1.mute(isMuted);

		if (auto input = getInput<InAIn>(); input) {
			channelA1.input(*input);
			setOutput<Out1Out>(channelA1.output());
		} else {
			setOutput<Out1Out>(0.f);
		}

		setLED<A1Button>(channelA1.getLEDbrightness());
	}

	void set_samplerate(float sr) override {
		timeStepInS = 1.0f / sr;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	float timeStepInS = 1.f / 48000.f;

private:
	Channel channelA1;
};

} // namespace MetaModule
