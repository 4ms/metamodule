#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/SISM_info.hh"

namespace MetaModule
{

class SISMCore : public SmartCoreProcessor<SISMInfo> {
	using Info = SISMInfo;
	using ThisCore = SISMCore;
	using enum Info::Elem;

public:
	SISMCore()
		: outputValue{0.f,0.f,0.f,0.f}, inputValue{0.f,0.f,0.f,0.f} {
	}

	void update() override {
		if(auto channel1InputValue = getInput<In1In>(); channel1InputValue) {
			inputValue[0] = *channel1InputValue;
		} else {
			inputValue[0] = 0.f;
		}

		if(auto channel2InputValue = getInput<In2In>(); channel2InputValue) {
			inputValue[1] = *channel2InputValue;
		} else {
			inputValue[1] = inputValue[0];
		}

		if(auto channel3InputValue = getInput<In3In>(); channel3InputValue) {
			inputValue[2] = *channel3InputValue;
		} else {
			inputValue[2] = 0.f;
		}

		if(auto channel4InputValue = getInput<In4In>(); channel4InputValue) {
			inputValue[3] = *channel4InputValue;
		} else {
			inputValue[3] = inputValue[2];
		}

		outputValue[0] = process(inputValue[0], getState<Scale1Knob>(), getState<Shift1Knob>());
		outputValue[1] = process(inputValue[1], getState<Scale2Knob>(), getState<Shift2Knob>());
		outputValue[2] = process(inputValue[2], getState<Scale3Knob>(), getState<Shift3Knob>());
		outputValue[3] = process(inputValue[3], getState<Scale4Knob>(), getState<Shift4Knob>());

		setOutput<Out1Out>(outputValue[0]);
		setOutput<Out2Out>(outputValue[1]);
		setOutput<Out3Out>(outputValue[2]);
		setOutput<Out4Out>(outputValue[3]);
	}

	void set_samplerate(float sr) override {
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	static constexpr float maximumShiftInV = 9.5f;
	std::array<float, 4> outputValue;
	std::array<float, 4> inputValue;

private:
	float process(float input, float scaleAmount, float shiftAmount) {
		return input * attenueverte(scaleAmount) + attenueverte(shiftAmount) * maximumShiftInV;
	}

	float attenueverte(float input) {
		return 2.0f * input - 1.0f;
	}
};

} // namespace MetaModule
