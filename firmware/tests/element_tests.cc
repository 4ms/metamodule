#include "doctest.h"

#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"

struct TestInfo : MetaModule::ModuleInfoBase {

	static constexpr std::array<MetaModule::Element, 9> Elements{
		MetaModule::Slider25mmHoriz{{{{1, 2, "Slider1", ""}}}},			//Param 0
		MetaModule::GateJackInput4ms{{{{5, 6, "Gate In 1", ""}}}},		//Input 0
		MetaModule::RedLight{{{{5, 6, "Gate In 1", ""}}}},				//Light 0
		MetaModule::EncoderRGB{{{{3, 4, "Encoder RGB 1", ""}}}},		//Param 1, Lights 1,2,3
		MetaModule::AnalogJackOutput4ms{{{{5, 6, "Audio Out 1", ""}}}}, //Output 0
		MetaModule::AnalogJackOutput4ms{{{{5, 7, "Audio Out 2", ""}}}}, //Output 1
		MetaModule::AnalogJackInput4ms{{{{4, 6, "Audio In 1", ""}}}},	//Input 1
		MetaModule::RedBlueLight{{{{5, 6, "", ""}}}},					//Lights 4,5
		MetaModule::Slider25mmVertLED{{{{{5, 6, "Slider2", ""}}}}},		//Param 2, Lights 6
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
	constexpr auto Slider1 = get<MetaModule::Slider25mmHoriz>(TestInfo::Elements[0]);
	constexpr auto Encoder1 = get<MetaModule::EncoderRGB>(TestInfo::Elements[3]);

	CHECK(ElementCount::get_element_id<TestInfo>(Slider1) == 0);
	CHECK(ElementCount::get_element_id<TestInfo>(Encoder1) == 3);

	// Make sure it can be done at compile-time
	static_assert(ElementCount::get_element_id<TestInfo>(Slider1) == 0);
	static_assert(ElementCount::get_element_id<TestInfo>(Encoder1) == 3);
}

TEST_CASE("Can get param index") {
	constexpr auto Slider1 = get<MetaModule::Slider25mmHoriz>(TestInfo::Elements[0]);
	constexpr auto InJack1 = get<MetaModule::GateJackInput4ms>(TestInfo::Elements[1]);
	constexpr auto Light1 = get<MetaModule::RedLight>(TestInfo::Elements[2]);
	constexpr auto Encoder1 = get<MetaModule::EncoderRGB>(TestInfo::Elements[3]);
	constexpr auto Out1 = get<MetaModule::AnalogJackOutput4ms>(TestInfo::Elements[4]);
	constexpr auto Out2 = get<MetaModule::AnalogJackOutput4ms>(TestInfo::Elements[5]);
	constexpr auto InJack2 = get<MetaModule::AnalogJackInput4ms>(TestInfo::Elements[6]);
	constexpr auto Light2 = get<MetaModule::RedBlueLight>(TestInfo::Elements[7]);
	constexpr auto SliderLED = get<MetaModule::Slider25mmVertLED>(TestInfo::Elements[8]);

	constexpr auto NonExistingKnob = MetaModule::EncoderRGB{{{{1, 2, "DNE", ""}}}};

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
