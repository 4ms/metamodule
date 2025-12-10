#pragma once
#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{

struct BlankInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Blank"};
	static constexpr std::string_view description{""};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::string_view png_filename{""};

	using enum Coords;

	static constexpr std::array<Element, 3> Elements{{
		Knob{},
		JackInput{},
		JackOutput{},
	}};

	enum class Elem {
		DummyKnob,
		DummyIn,
		DummyOut,
	};
};

class Blank : public SmartCoreProcessor<BlankInfo> {
	using Info = BlankInfo;
	using enum Info::Elem;

public:
	Blank() = default;

	void update() override {
	}

	void set_samplerate(float sr) override {
	}
};

} // namespace MetaModule
