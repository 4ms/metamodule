#include "doctest.h"
#include "patch/patch.hh"

TEST_CASE("MappedParam get_mapped_val")
{

	MappedKnob knob;
	float mapped_low;
	float mapped_high;
	SUBCASE("Normal mappings (partial range)")
	{
		mapped_low = 0.3f;
		mapped_high = 0.8f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.3));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.55));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.8));

		mapped_low = 0.9f;
		mapped_high = 1.0f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.9));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.95));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(1.0));
	}

	SUBCASE("Mapped to full range (trivial mapping)")
	{
		mapped_low = 0.0f;
		mapped_high = 1.0f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.0));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.5));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(1.0));
	}

	SUBCASE("Zero mapping")
	{
		mapped_low = 0.0f;
		mapped_high = 0.0f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.0));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.0));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.0));
	}

	SUBCASE("Reverse direction mapping (0..1 => 1..0)")
	{
		mapped_low = 1.0f;
		mapped_high = 0.0f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(1.0));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.5));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.0));
	}
	SUBCASE("Partial range, reverse direction(0..1 => 1.0..0.5)")
	{
		mapped_low = 0.5f;
		mapped_high = 0.1f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.5));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.3));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.1));
	}
}
