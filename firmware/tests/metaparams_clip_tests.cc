#include "doctest.h"
#include "params/metaparams.hh"

using MetaModule::MetaParams;

TEST_CASE("clipped_outs accumulates through update_with and transfer") {
	MetaParams audio, sync, gui;

	audio.clipped_outs = 0b0010;
	sync.update_with(audio);
	CHECK(sync.clipped_outs == 0b0010);
	CHECK(audio.clipped_outs == 0);

	// A second block before the GUI reads: OR, don't overwrite
	audio.clipped_outs = 0b1000'0000'0000;
	sync.update_with(audio);
	CHECK(sync.clipped_outs == 0b1000'0000'0010);

	gui.clipped_outs = 0b0100; // GUI hasn't consumed yet
	gui.transfer(sync);
	CHECK(gui.clipped_outs == 0b1000'0000'0110);
	CHECK(sync.clipped_outs == 0);
}

TEST_CASE("clear() zeroes clipped_outs") {
	MetaParams m;
	m.clipped_outs = 0xFFFF;
	m.clear();
	CHECK(m.clipped_outs == 0);
}
