#include "doctest.h"
#include "params/metaparams.hh"

using MetaModule::MetaParams;

TEST_CASE("patch_playing starts false") {
	MetaParams m;
	CHECK(m.patch_playing == false);
}

TEST_CASE("clear() resets patch_playing") {
	MetaParams m;
	m.patch_playing = true;
	m.clear();
	CHECK(m.patch_playing == false);
}
