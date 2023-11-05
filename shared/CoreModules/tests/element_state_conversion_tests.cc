#include "doctest.h"
#include "elements/element_state_conversion.hh"

TEST_CASE("Convert State SlideSwitch 7 pos") {

	unsigned num_pos = 7;
	auto sw = MetaModule::SlideSwitchNPos{MetaModule::BaseElement{}, num_pos};

	//Positions:
	//  1/7     2/7    3/7     4/7     5/7     6/7     7/7

	//|.....|.......|......|.......|.......|.......|.......|
	//0...0.5/6   1.5/6   2.5/6  3.5/6   4.5/6   5.5/6     1

	CHECK(MetaModule::StateConversion::convertState(sw, 0.0) == 1);

	// Slightly under/over each breakpoint:
	CHECK(MetaModule::StateConversion::convertState(sw, 0.5 / 6. - 0.001) == 1);
	CHECK(MetaModule::StateConversion::convertState(sw, 0.5 / 6. + 0.001) == 2);

	CHECK(MetaModule::StateConversion::convertState(sw, 1.5 / 6. - 0.001) == 2);
	CHECK(MetaModule::StateConversion::convertState(sw, 1.5 / 6. + 0.001) == 3);

	CHECK(MetaModule::StateConversion::convertState(sw, 2.5 / 6. - 0.001) == 3);
	CHECK(MetaModule::StateConversion::convertState(sw, 2.5 / 6. + 0.001) == 4);

	CHECK(MetaModule::StateConversion::convertState(sw, 3.5 / 6. - 0.001) == 4);
	CHECK(MetaModule::StateConversion::convertState(sw, 3.5 / 6. + 0.001) == 5);

	CHECK(MetaModule::StateConversion::convertState(sw, 4.5 / 6. - 0.001) == 5);
	CHECK(MetaModule::StateConversion::convertState(sw, 4.5 / 6. + 0.001) == 6);

	CHECK(MetaModule::StateConversion::convertState(sw, 5.5 / 6. - 0.001) == 6);
	CHECK(MetaModule::StateConversion::convertState(sw, 5.5 / 6. + 0.001) == 7);

	CHECK(MetaModule::StateConversion::convertState(sw, 1.0) == 7);
}

TEST_CASE("Convert State SlideSwitch 2 pos") {

	unsigned num_pos = 2;
	auto sw = MetaModule::SlideSwitchNPos{MetaModule::BaseElement{}, num_pos};

	//Positions:
	//  1/2    2/2

	//|......|......|
	//0    0.5/1    1

	CHECK(MetaModule::StateConversion::convertState(sw, 0.0) == 1);

	// Slightly under/over each breakpoint:
	CHECK(MetaModule::StateConversion::convertState(sw, 0.5 / 1. - 0.001) == 1);
	CHECK(MetaModule::StateConversion::convertState(sw, 0.5 / 1. + 0.001) == 2);

	CHECK(MetaModule::StateConversion::convertState(sw, 1.0) == 2);
}
