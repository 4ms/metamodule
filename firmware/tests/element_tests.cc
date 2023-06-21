#include "doctest.h"

#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"

struct TestInfo : MetaModule::ElementInfoBase {

	static constexpr std::array<MetaModule::Element, 5> Elements{
		MetaModule::Slider25mmHoriz{{{{1, 2, "Slider1", ""}}}},
		MetaModule::GateJackInput4ms{{{{5, 6, "Gate In 1", ""}}}},
		MetaModule::RedLight{{{{5, 6, "Gate In 1", ""}}}},
		MetaModule::EncoderRGB{{{{3, 4, "Encoder RGB 1", ""}}}},
		MetaModule::RedBlueLight{{{{5, 6, "Gate In 1", ""}}}},
	};
};

TEST_CASE("Can count elements") {
	constexpr auto c = ElementCount<TestInfo>::count();
	CHECK(c.num_params == 2);
	CHECK(c.num_inputs == 1);
	CHECK(c.num_outputs == 0);
	CHECK(c.num_lights == 6); //RGB=3 + Red=1 + RedBlue=2 ==> 6

	// Make sure it can be done at compile-time
	static_assert(c.num_params == 2);
}

TEST_CASE("Can get element index") {
	constexpr auto Slider1 = get<MetaModule::Slider25mmHoriz>(TestInfo::Elements[0]);
	constexpr auto Encoder1 = get<MetaModule::EncoderRGB>(TestInfo::Elements[3]);

	CHECK(ElementId<TestInfo>::get_element_id(Slider1) == 0);
	CHECK(ElementId<TestInfo>::get_element_id(Encoder1) == 3);

	// Make sure it can be done at compile-time
	static_assert(ElementId<TestInfo>::get_element_id(Slider1) == 0);
	static_assert(ElementId<TestInfo>::get_element_id(Encoder1) == 3);
}
