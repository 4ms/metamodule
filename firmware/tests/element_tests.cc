#include "doctest.h"

#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"

struct TestInfo : MetaModule::ModuleInfoBase {

	using enum MetaModule::Coords;
	static constexpr std::array<MetaModule::Element, 9> Elements{
		MetaModule::Slider{{{{{1, 2, Center, "Slider1", ""}}}}},			//Param 0
		MetaModule::GateJackInput4ms{{5, 6, Center, "Gate In 1", ""}},		//Input 0
		MetaModule::RedLight{{5, 6, Center, "Gate In 1", ""}},				//Light 0
		MetaModule::EncoderRGB{{{{{3, 4, Center, "Encoder RGB 1", ""}}}}},	//Param 1, Lights 1,2,3
		MetaModule::AnalogJackOutput4ms{{5, 6, Center, "Audio Out 1", ""}}, //Output 0
		MetaModule::AnalogJackOutput4ms{{5, 7, Center, "Audio Out 2", ""}}, //Output 1
		MetaModule::AnalogJackInput4ms{{4, 6, Center, "Audio In 1", ""}},	//Input 1
		MetaModule::RedBlueLight{{5, 6, Center, "", ""}},					//Lights 4,5
		MetaModule::Slider25mmVertLED{{5, 6, Center, "Slider2", ""}},		//Param 2, Lights 6
	};
};

TEST_CASE("Can count elements") {
	constexpr auto c = ElementCount::count<TestInfo>();
	CHECK(c.num_params == 3);
	CHECK(c.num_inputs == 2);
	CHECK(c.num_outputs == 2);
	CHECK(c.num_lights == 7);

	// Make sure it can be done at compile-time
	static_assert(c.num_params == 3);
}

TEST_CASE("Can get element index") {
	constexpr auto Slider1 = get<MetaModule::Slider>(TestInfo::Elements[0]);
	constexpr auto Encoder1 = get<MetaModule::EncoderRGB>(TestInfo::Elements[3]);

	CHECK(ElementCount::get_element_id<TestInfo>(Slider1) == 0);
	CHECK(ElementCount::get_element_id<TestInfo>(Encoder1) == 3);

	// Make sure it can be done at compile-time
	static_assert(ElementCount::get_element_id<TestInfo>(Slider1) == 0);
	static_assert(ElementCount::get_element_id<TestInfo>(Encoder1) == 3);
}

TEST_CASE("Can get param index") {
	constexpr auto Slider1 = get<MetaModule::Slider>(TestInfo::Elements[0]);
	constexpr auto InJack1 = get<MetaModule::JackInput>(TestInfo::Elements[1]);
	constexpr auto Light1 = get<MetaModule::MonoLight>(TestInfo::Elements[2]);
	constexpr auto Encoder1 = get<MetaModule::EncoderRGB>(TestInfo::Elements[3]);
	constexpr auto Out1 = get<MetaModule::JackOutput>(TestInfo::Elements[4]);
	constexpr auto Out2 = get<MetaModule::JackOutput>(TestInfo::Elements[5]);
	constexpr auto InJack2 = get<MetaModule::JackInput>(TestInfo::Elements[6]);
	constexpr auto Light2 = get<MetaModule::DualLight>(TestInfo::Elements[7]);
	constexpr auto SliderLED = get<MetaModule::SliderLight>(TestInfo::Elements[8]);

	constexpr auto NonExistingKnob = MetaModule::EncoderRGB{{{{{1, 2, MetaModule::Coords::Center, "DNE", ""}}}}};

	CHECK(ElementCount::get_indices<TestInfo>(Slider1).value().param_idx == 0);
	CHECK(ElementCount::get_indices<TestInfo>(Encoder1).value().param_idx == 1);
	CHECK(ElementCount::get_indices<TestInfo>(SliderLED).value().param_idx == 2);

	CHECK(ElementCount::get_indices<TestInfo>(InJack1).value().input_idx == 0);
	CHECK(ElementCount::get_indices<TestInfo>(InJack2).value().input_idx == 1);

	CHECK(ElementCount::get_indices<TestInfo>(Out1).value().output_idx == 0);
	CHECK(ElementCount::get_indices<TestInfo>(Out2).value().output_idx == 1);

	CHECK(ElementCount::get_indices<TestInfo>(Light1).value().light_idx == 0);
	CHECK(ElementCount::get_indices<TestInfo>(Encoder1).value().light_idx == 1);
	CHECK(ElementCount::get_indices<TestInfo>(Light2).value().light_idx == 4);
	CHECK(ElementCount::get_indices<TestInfo>(SliderLED).value().light_idx == 6);

	// This is weird... TODO; change how this works?
	// get_indices<>(BaseElement) is not called except in tests, so doesn't matter really
	SUBCASE("Some indices are invalid if the type does not match") {
		CHECK(ElementCount::get_indices<TestInfo>(SliderLED).value().output_idx == 2);
	}

	CHECK(ElementCount::get_indices<TestInfo>(NonExistingKnob) == std::nullopt);

	// Make sure it can be done at compile-time
	static_assert(ElementCount::get_indices<TestInfo>(Slider1).value().param_idx == 0);
	static_assert(ElementCount::get_indices<TestInfo>(Encoder1).value().param_idx == 1);
	static_assert(ElementCount::get_indices<TestInfo>(SliderLED).value().param_idx == 2);

	static_assert(ElementCount::get_indices<TestInfo>(InJack1).value().input_idx == 0);
	static_assert(ElementCount::get_indices<TestInfo>(InJack2).value().input_idx == 1);

	static_assert(ElementCount::get_indices<TestInfo>(Out1).value().output_idx == 0);
	static_assert(ElementCount::get_indices<TestInfo>(Out2).value().output_idx == 1);

	static_assert(ElementCount::get_indices<TestInfo>(Light1).value().light_idx == 0);
	static_assert(ElementCount::get_indices<TestInfo>(Encoder1).value().light_idx == 1);
	static_assert(ElementCount::get_indices<TestInfo>(Light2).value().light_idx == 4);
	static_assert(ElementCount::get_indices<TestInfo>(SliderLED).value().light_idx == 6);

	static_assert(ElementCount::get_indices<TestInfo>(NonExistingKnob) == std::nullopt);
}

namespace MetaModule
{
struct DEVInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"DEV"};
	static constexpr std::string_view description{"Dual EnvVCA"};
	static constexpr uint32_t width_hp = 16;
	static constexpr std::string_view svg_filename{"res/modules/DEV_artwork.svg"};

	using enum Coords;

	static constexpr std::array<Element, 45> Elements{{
		Slider25mmVertLED{{to_mm<72>(22.415), to_mm<72>(108.25), Center, "Rise A Slider", ""}},
		Slider25mmVertLED{{to_mm<72>(56.265), to_mm<72>(108.25), Center, "Fall A Slider", ""}},
		Slider25mmVertLED{{to_mm<72>(174.115), to_mm<72>(108.25), Center, "Rise B Slider", ""}},
		Slider25mmVertLED{{to_mm<72>(207.965), to_mm<72>(108.25), Center, "Fall B Slider", ""}},
		Knob9mm{{to_mm<72>(93.13), to_mm<72>(95.86), Center, "Level A", ""}},
		Knob9mm{{to_mm<72>(137.25), to_mm<72>(95.86), Center, "Level B", ""}},
		Knob9mm{{to_mm<72>(93.13), to_mm<72>(138.65), Center, "Offset A", ""}},
		Knob9mm{{to_mm<72>(137.25), to_mm<72>(138.65), Center, "Offset B", ""}},
		Knob9mm{{to_mm<72>(23.5), to_mm<72>(184.03), Center, "Rise A", ""}},
		Knob9mm{{to_mm<72>(94.11), to_mm<72>(183.67), Center, "Fall A", ""}},
		Knob9mm{{to_mm<72>(136.27), to_mm<72>(184.03), Center, "Rise B", ""}},
		Knob9mm{{to_mm<72>(206.87), to_mm<72>(184.03), Center, "Fall B", ""}},
		GateJackInput4ms{{to_mm<72>(115.19), to_mm<72>(60.85), Center, "Cycle Gate", ""}},
		AnalogJackInput4ms{{to_mm<72>(58.56), to_mm<72>(208.68), Center, "Time CV A", ""}},
		AnalogJackInput4ms{{to_mm<72>(171.86), to_mm<72>(208.68), Center, "Time CV B", ""}},
		GateJackInput4ms{{to_mm<72>(23.09), to_mm<72>(232.82), Center, "Trig A", ""}},
		AnalogJackInput4ms{{to_mm<72>(58.52), to_mm<72>(252.75), Center, "Follow A", ""}},
		AnalogJackInput4ms{{to_mm<72>(171.85), to_mm<72>(252.75), Center, "Follow B", ""}},
		GateJackInput4ms{{to_mm<72>(207.29), to_mm<72>(232.82), Center, "Trig B", ""}},
		AnalogJackInput4ms{{to_mm<72>(23.06), to_mm<72>(274.73), Center, "Audio A In", ""}},
		AnalogJackInput4ms{{to_mm<72>(58.48), to_mm<72>(300.48), Center, "VCA CV A", ""}},
		AnalogJackInput4ms{{to_mm<72>(171.9), to_mm<72>(300.41), Center, "VCA CV B", ""}},
		AnalogJackInput4ms{{to_mm<72>(207.29), to_mm<72>(274.76), Center, "Audio B In", ""}},
		GateJackOutput4ms{{to_mm<72>(95.04), to_mm<72>(233.88), Center, "EOR A", ""}},
		GateJackOutput4ms{{to_mm<72>(135.28), to_mm<72>(233.99), Center, "EOF B", ""}},
		AnalogJackOutput4ms{{to_mm<72>(115.22), to_mm<72>(288.78), Center, "OR", ""}},
		AnalogJackOutput4ms{{to_mm<72>(23.06), to_mm<72>(324.82), Center, "Audio A Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(90.49), to_mm<72>(324.82), Center, "Env A Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(139.91), to_mm<72>(324.88), Center, "Env B Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(207.32), to_mm<72>(324.82), Center, "Audio B Out", ""}},
		RedBlueLight{{to_mm<72>(45.84), to_mm<72>(176.26), Center, "Rise A Light", ""}},
		RedBlueLight{{to_mm<72>(70.54), to_mm<72>(176.26), Center, "Fall A Light", ""}},
		RedBlueLight{{to_mm<72>(159.84), to_mm<72>(176.26), Center, "Rise B Light", ""}},
		RedBlueLight{{to_mm<72>(184.53), to_mm<72>(176.26), Center, "Fall B Light", ""}},
		OrangeLight{{to_mm<72>(99.58), to_mm<72>(260.79), Center, "EOR Light", ""}},
		OrangeLight{{to_mm<72>(130.68), to_mm<72>(261.07), Center, "EOF Light", ""}},
		RedBlueLight{{to_mm<72>(65.92), to_mm<72>(327.45), Center, "Env A Light", ""}},
		RedBlueLight{{to_mm<72>(164.39), to_mm<72>(327.52), Center, "Env B Light", ""}},
		Toggle3pos{{to_mm<72>(17.6), to_mm<72>(41.905), Center, "Rise A Switch", ""}},
		Toggle3pos{{to_mm<72>(50.49), to_mm<72>(41.905), Center, "Fall A Switch", ""}},
		Toggle3pos{{to_mm<72>(179.89), to_mm<72>(41.905), Center, "Rise B Switch", ""}},
		Toggle3pos{{to_mm<72>(212.77), to_mm<72>(41.905), Center, "Fall B Switch", ""}},
		LatchingButtonMonoLight{{{{to_mm<72>(82.8), to_mm<72>(41.64), Center, "Cycle A", ""}}}},
		LatchingButtonMonoLight{{{{to_mm<72>(147.61), to_mm<72>(41.68), Center, "Cycle B", ""}}}},

		OrangeLight{{to_mm<72>(130.68), to_mm<72>(261.07), Center, "extra", ""}},
	}};
};
} // namespace MetaModule

TEST_CASE("get_indices()") {
	auto indices = ElementCount::get_indices<MetaModule::DEVInfo>();

	CHECK(indices[11].param_idx == 11);										//Fall B
	CHECK(indices[12].param_idx == ElementCount::Indices::NoElementMarker); //Cycle Gate, not a param
	CHECK(indices[13].param_idx == ElementCount::Indices::NoElementMarker);

	CHECK(indices[38].param_idx == 12); //Rise A Switch = 12
	CHECK(indices[39].param_idx == 13); //Fall A Switch = 13

	CHECK(indices[42].param_idx == 16);										//Cycle A = 16
	CHECK(indices[43].param_idx == 17);										//Cycle B = 17
	CHECK(indices[44].param_idx == ElementCount::Indices::NoElementMarker); //extra light, not a param
	CHECK(indices[44].light_idx == 20);

	// Check only one element has the matching index
	for (auto i = 0; auto ind : indices) {
		if (i == 42)
			CHECK(ind.param_idx == 16);
		else
			CHECK_FALSE(ind.param_idx == 16);

		if (i == 11)
			CHECK(ind.param_idx == 11);
		else
			CHECK_FALSE(ind.param_idx == 11);

		if (i == 0)
			CHECK(ind.param_idx == 0);
		else
			CHECK_FALSE(ind.param_idx == 0);

		i++;
	}

	constexpr auto CycleA = get<MetaModule::LatchingButtonMonoLight>(MetaModule::DEVInfo::Elements[42]);
	constexpr auto CycleB = get<MetaModule::LatchingButtonMonoLight>(MetaModule::DEVInfo::Elements[43]);

	static_assert(ElementCount::get_indices<MetaModule::DEVInfo>(CycleA).value().param_idx == 16);
	static_assert(ElementCount::get_indices<MetaModule::DEVInfo>(CycleB).value().param_idx == 17);
}
