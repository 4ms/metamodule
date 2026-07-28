#include "doctest.h"
#include "patch/midi_def.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"

using namespace MetaModule;

TEST_CASE("MappedParam get_mapped_val") {

	MappedKnob knob;
	float mapped_low;
	float mapped_high;
	SUBCASE("Normal mappings (partial range)") {
		mapped_low = 0.3f;
		mapped_high = 0.8f;
		knob.max = mapped_high;
		knob.min = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.3));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.55));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.8));

		mapped_low = 0.9f;
		mapped_high = 1.0f;
		knob.max = mapped_high;
		knob.min = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.9));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.95));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(1.0));
	}

	SUBCASE("Mapped to full range (trivial mapping)") {
		mapped_low = 0.0f;
		mapped_high = 1.0f;
		knob.max = mapped_high;
		knob.min = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.0));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.5));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(1.0));
	}

	SUBCASE("Zero mapping") {
		mapped_low = 0.0f;
		mapped_high = 0.0f;
		knob.max = mapped_high;
		knob.min = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.0));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.0));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.0));
	}

	SUBCASE("Reverse direction mapping (0..1 => 1..0)") {
		mapped_low = 1.0f;
		mapped_high = 0.0f;
		knob.max = mapped_high;
		knob.min = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(1.0));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.5));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.0));
	}
	SUBCASE("Partial range, reverse direction(0..1 => 1.0..0.5)") {
		mapped_low = 0.5f;
		mapped_high = 0.1f;
		knob.max = mapped_high;
		knob.min = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.5));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.3));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.1));
	}
}

TEST_CASE("update_midi_poly_num: Auto computes from cables, setting overrides") {
	PatchData pd;

	SUBCASE("Auto (setting == 0) computes max poly chans used by cables") {
		CHECK(pd.midi_poly_num_setting == 0); // default is Auto

		pd.add_mapped_injack(MidiNote2Jack, {.module_id = 1, .jack_id = 0});
		CHECK(pd.midi_poly_num == 2);

		pd.add_mapped_injack(MidiNote8Jack, {.module_id = 2, .jack_id = 0});
		CHECK(pd.midi_poly_num == 8);

		pd.update_midi_poly_num(); // full recompute also yields 8
		CHECK(pd.midi_poly_num == 8);
	}

	SUBCASE("A poly cable in Auto mode uses MaxMidiPolyChannels") {
		pd.add_mapped_injack(MidiNotePolyJack, {.module_id = 1, .jack_id = 0});
		CHECK(pd.midi_poly_num == MaxMidiPolyChannels);
	}

	SUBCASE("Setting (1-8) hard-sets midi_poly_num regardless of cables") {
		pd.add_mapped_injack(MidiNote8Jack, {.module_id = 1, .jack_id = 0});
		CHECK(pd.midi_poly_num == 8);

		pd.midi_poly_num_setting = 3;
		pd.update_midi_poly_num();
		CHECK(pd.midi_poly_num == 3);

		// Adding a higher-channel cable must not bump the hard-set count up
		pd.add_mapped_injack(MidiNotePolyJack, {.module_id = 2, .jack_id = 0});
		CHECK(pd.midi_poly_num == 3);

		// Returning to Auto recomputes from the cables present
		pd.midi_poly_num_setting = 0;
		pd.update_midi_poly_num();
		CHECK(pd.midi_poly_num == 8);
	}
}
