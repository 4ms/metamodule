#pragma once
#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace DemoBuiltIns
{

struct SimpleVCOInfo : MetaModule::ModuleInfoBase {
	static constexpr std::string_view slug{"SimpleVCO"};
	static constexpr std::string_view description{""};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::string_view png_filename{""};

	using enum MetaModule::Coords;

	static constexpr std::array<MetaModule::Element, 3> Elements{{
		MetaModule::Knob{},
		MetaModule::JackInput{},
		MetaModule::JackOutput{},
	}};

	enum class Elem {
		PitchKnob,
		PitchCV,
		RampOut,
	};
};

class SimpleVCO : public MetaModule::SmartCoreProcessor<SimpleVCOInfo> {
	using Info = SimpleVCOInfo;
	using enum Info::Elem;

public:
	SimpleVCO();
	void update() override;
	void set_samplerate(float sr) override;

private:
	void update_freq();

	float sample_rate;
	float phase;
};

} // namespace DemoBuiltIns
