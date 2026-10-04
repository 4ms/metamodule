#include "doctest.h"
#include "audio/clip_detect.hh"
#include <set>

using namespace MetaModule;

TEST_CASE("exceeds_24bit") {
	CHECK_FALSE(ClipDetect::exceeds_24bit(0));
	CHECK_FALSE(ClipDetect::exceeds_24bit(0x7F'FFFF));
	CHECK_FALSE(ClipDetect::exceeds_24bit(-0x80'0000));
	CHECK(ClipDetect::exceeds_24bit(0x80'0000));
	CHECK(ClipDetect::exceeds_24bit(-0x80'0001));
}

TEST_CASE("Expander codec channels map to distinct panel-output bits 8..15") {
	std::set<unsigned> bits;
	for (unsigned ch = 0; ch < AudioExpander::NumOutJacks; ch++) {
		auto b = ClipDetect::ext_output_bit(ch);
		CHECK(b >= PanelDef::NumAudioOut);
		CHECK(b < PanelDef::NumAudioOut + AudioExpander::NumOutJacks);
		bits.insert(b);
	}
	CHECK(bits.size() == AudioExpander::NumOutJacks);
	// codec chan 0 drives panel output index out_order[0]
	CHECK(ClipDetect::ext_output_bit(0) == PanelDef::NumAudioOut + AudioExpander::out_order[0]);
}
