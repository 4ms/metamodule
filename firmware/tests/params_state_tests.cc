#include "doctest.h"
#include "params/params_state.hh"

TEST_CASE("jack sense bits") {
	MetaModule::ParamsState p;

	using namespace MetaModule;

	// The checked numbers are the TCA9555 port/pin number
	// from the main MM and expander schematics.
	// For the expander, +16 is added to the TCA9555 Port/pin number.
	//
	// Main PCB port 0 bit 0 => 0
	// Main PCB port 0 bit 1 => 1
	// ...
	// Main PCB port 1 bit 7 => 8
	// Main PCB port 1 bit 1 => 9
	// ...
	// Main PCB port 1 bit 7 => 15
	// Expander port 0 bit 0 => 16
	// Expander port 0 bit 1 => 17
	// ...
	// Expander port 1 bit 7 => 24
	// Expander port 1 bit 1 => 25
	// ...
	// Expander port 1 bit 7 => 31

	// Ins 1 - 6:
	CHECK(ParamsState::input_bit(0) == 14);
	CHECK(ParamsState::input_bit(1) == 11);
	CHECK(ParamsState::input_bit(2) == 15);
	CHECK(ParamsState::input_bit(3) == 13);
	CHECK(ParamsState::input_bit(4) == 10);
	CHECK(ParamsState::input_bit(5) == 8);
	// Gate In 1 - 2
	CHECK(ParamsState::input_bit(6) == 12);
	CHECK(ParamsState::input_bit(7) == 9);

	// Expander Ins 1 - 6:
	CHECK(ParamsState::input_bit(8) == 16);
	CHECK(ParamsState::input_bit(9) == 21);
	CHECK(ParamsState::input_bit(10) == 17);
	CHECK(ParamsState::input_bit(11) == 20);
	CHECK(ParamsState::input_bit(12) == 19);
	CHECK(ParamsState::input_bit(13) == 23);

	// Outs 1 - 8: (panel jack ids 0 - 7)
	CHECK(ParamsState::output_bit(0) == 4);
	CHECK(ParamsState::output_bit(1) == 5);
	CHECK(ParamsState::output_bit(2) == 6);
	CHECK(ParamsState::output_bit(3) == 1);
	CHECK(ParamsState::output_bit(4) == 2);
	CHECK(ParamsState::output_bit(5) == 7);
	CHECK(ParamsState::output_bit(6) == 3);
	CHECK(ParamsState::output_bit(7) == 0);

	// Expander Outs 9 - 16 (panel jack ids 8 - 15)
	CHECK(ParamsState::output_bit(8) == 18);
	CHECK(ParamsState::output_bit(9) == 22);
	CHECK(ParamsState::output_bit(10) == 31);
	CHECK(ParamsState::output_bit(11) == 25);
	CHECK(ParamsState::output_bit(12) == 30);
	CHECK(ParamsState::output_bit(13) == 27);
	CHECK(ParamsState::output_bit(14) == 29);
	CHECK(ParamsState::output_bit(15) == 28);
}
