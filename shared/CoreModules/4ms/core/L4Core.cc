#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/L4_info.hh"
#include "l4/Tables.h"

#include "processors/tools/expDecay.h"
#include "processors/tools/dcBlock.h"

namespace MetaModule
{

class L4Core : public SmartCoreProcessor<L4Info> {
	using Info = L4Info;
	using ThisCore = L4Core;
	using enum Info::Elem;

public:
	L4Core() {
		channel1EnvelopeLeft.attackTime = envelopeTimeConstant;
		channel1EnvelopeLeft.decayTime = envelopeTimeConstant;

		channel1EnvelopeRight.attackTime = envelopeTimeConstant;
		channel1EnvelopeRight.decayTime = envelopeTimeConstant;

		channel2EnvelopeLeft.attackTime = envelopeTimeConstant;
		channel2EnvelopeLeft.decayTime = envelopeTimeConstant;

		channel2EnvelopeRight.attackTime = envelopeTimeConstant;
		channel2EnvelopeRight.decayTime = envelopeTimeConstant;

		channel3EnvelopeLeft.attackTime = envelopeTimeConstant;
		channel3EnvelopeLeft.decayTime = envelopeTimeConstant;

		channel3EnvelopeRight.attackTime = envelopeTimeConstant;
		channel3EnvelopeRight.decayTime = envelopeTimeConstant;

		channel4EnvelopeLeft.attackTime = envelopeTimeConstant;
		channel4EnvelopeLeft.decayTime = envelopeTimeConstant;

		channel4EnvelopeRight.attackTime = envelopeTimeConstant;
		channel4EnvelopeRight.decayTime = envelopeTimeConstant;
	};

	void update() override {
		float outputLeft = 0.f;
		float outputRight = 0.f;

		auto channelLeft = 0.f;
		auto channelRight = channelLeft;

		if(auto input = getInput<In1In>(); input) {
			channelLeft = *input * PanningTable.lookup(1.f - getState<Pan1Knob>()) * LevelTable.lookup(getState<Level1Knob>());
			channelRight = *input * PanningTable.lookup(getState<Pan1Knob>()) * LevelTable.lookup(getState<Level1Knob>());

			outputLeft += channelLeft;
			outputRight += channelRight;
		}

		setLED<Level1LedLight>(std::array<float,3>{0.f, channel1EnvelopeRight.update(gcem::abs(channelRight)) / LEDScaling , channel1EnvelopeLeft.update(gcem::abs(channelLeft)) / LEDScaling});

		channelLeft = 0.f;
		channelRight = channelLeft;

		if(auto input = getInput<In2In>(); input) {
			channelLeft = *input * PanningTable.lookup(1.f - getState<Pan2Knob>()) * LevelTable.lookup(getState<Level2Knob>());
			channelRight = *input * PanningTable.lookup(getState<Pan2Knob>()) * LevelTable.lookup(getState<Level2Knob>());

			outputLeft += channelLeft;
			outputRight += channelRight;
		}

		setLED<Level2LedLight>(std::array<float,3>{0.f, channel2EnvelopeRight.update(gcem::abs(channelRight)) / LEDScaling , channel2EnvelopeLeft.update(gcem::abs(channelLeft)) / LEDScaling});

		channelLeft = 0.f;
		channelRight = channelLeft;

		if(auto inputL = getInput<In3LIn>(); inputL) {
			channelLeft = *inputL * LevelTable.lookup(getState<Level3Knob>());
			channelRight =  channelLeft;
		}

		if(auto inputR = getInput<In3RIn>(); inputR) {
			channelRight = *inputR * LevelTable.lookup(getState<Level3Knob>());
		}

		outputLeft += channelLeft;
		outputRight += channelRight;

		setLED<Level3LedLight>(std::array<float,3>{0.f, channel3EnvelopeRight.update(gcem::abs(channelRight)) / LEDScaling , channel3EnvelopeLeft.update(gcem::abs(channelLeft)) / LEDScaling});

		channelLeft = 0.f;
		channelRight = channelLeft;

		if(auto inputL = getInput<In4LIn>(); inputL) {
			channelLeft = *inputL * LevelTable.lookup(getState<Level4Knob>());
			channelRight = channelLeft;
		}

		if(auto inputR = getInput<In4RIn>(); inputR) {
				channelRight = *inputR * LevelTable.lookup(getState<Level4Knob>());
		}

		outputLeft += channelLeft;
		outputRight += channelRight;

		setLED<Level4LedLight>(std::array<float,3>{0.f, channel4EnvelopeRight.update(gcem::abs(channelRight)) / LEDScaling , channel4EnvelopeLeft.update(gcem::abs(channelLeft)) / LEDScaling});

		setOutput<OutLeftOut>(outputLeft);
		setOutput<OutRightOut>(outputRight);
		
	}

	void set_samplerate(float sr) override {
		channel1EnvelopeLeft.set_samplerate(sr);
		channel1EnvelopeRight.set_samplerate(sr);
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	static constexpr float LEDScaling = 5.f;
	static constexpr float envelopeTimeConstant = 200.f;

	ExpDecay channel1EnvelopeLeft;
	ExpDecay channel1EnvelopeRight;

	ExpDecay channel2EnvelopeLeft;
	ExpDecay channel2EnvelopeRight;

	ExpDecay channel3EnvelopeLeft;
	ExpDecay channel3EnvelopeRight;

	ExpDecay channel4EnvelopeLeft;
	ExpDecay channel4EnvelopeRight;
};

} // namespace MetaModule
