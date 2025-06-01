#include "doctest.h"
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <utility>

std::pair<uint16_t, uint16_t> scale_aspect(float width, float height, float screen_w, float screen_h) {
	const float ratio = width / height;		  //1.5
	const float screen_ratio = 320.f / 240.f; //1.3333
	uint16_t w = (ratio >= screen_ratio) ? 320 : std::round(240 * ratio);
	uint16_t h = (ratio <= screen_ratio) ? 240 : std::round(320 / ratio);
	return {w, h};
}

TEST_CASE("ratio") {
	{
		auto [w, h] = scale_aspect(60, 60, 320, 240);
		CHECK(w == 240);
		CHECK(h == 240);
	}

	{
		auto [w, h] = scale_aspect(40, 60, 320, 240);
		CHECK(w == 160);
		CHECK(h == 240);
	}

	{
		auto [w, h] = scale_aspect(80, 60, 320, 240);
		CHECK(w == 320);
		CHECK(h == 240);
	}

	{
		auto [w, h] = scale_aspect(90, 60, 320, 240);
		CHECK(w == 320);
		CHECK(h == 213);
	}
}
