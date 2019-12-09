#include "../src/touch.hh"

 void testbf()
 {
  	auto sense16 = bitfield(CAP1203Sensitivity::_16x);
  	auto sense1 = bitfield(CAP1203Sensitivity::_1x);
  	auto senseauto_16_1 = bitfield<uint16_t>(CAP1203Sensitivity::_1x);
  	auto bit5 = setbit(4);
  	auto bit15 = setbit(15);
  	auto bitauto_15 = setbit<uint16_t>(15);
  	uint16_t bit16_15 = setbit<uint16_t>(15);
		auto chan123_16 = channels(kCAP1203Chan3, kCAP1203Chan1, kCAP1203Chan1);
 }
 