#include "doctest.h"

#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/moduleFactory.hh"
#include "console/concurrent_buffer.hh"
#include "midi/rotocontrol/serializer.hh"
#include "patch/patch_data.hh"
#include <array>
#include <cstring>
#include <memory>
#include <vector>

using namespace MetaModule;

// Minimal CoreProcessor stub for the modules span
struct StubProcessor : public CoreProcessor {
	void update() override {
	}
	void set_samplerate(float) override {
	}
	void set_param(int, float) override {
	}
	void set_input(int, float) override {
	}
	float get_output(int) const override {
		return 0.f;
	}
};

// Helper: extract bytes written to ConcurrentBuffer
static std::vector<uint8_t> get_buffer_data(ConcurrentBuffer &buf) {
	std::vector<uint8_t> result(buf.current_write_pos);
	for (int i = 0; i < buf.current_write_pos; ++i) {
		result[i] = buf.buffer.data[i];
	}
	return result;
}

// Helper: find a byte sequence in a buffer
static int find_sequence(std::span<const uint8_t> haystack, std::span<const uint8_t> needle) {
	if (needle.size() > haystack.size())
		return -1;
	for (size_t i = 0; i <= haystack.size() - needle.size(); ++i) {
		if (std::memcmp(&haystack[i], needle.data(), needle.size()) == 0)
			return (int)i;
	}
	return -1;
}

// Count occurrences of a byte sequence
static int count_sequence(std::span<const uint8_t> haystack, std::span<const uint8_t> needle) {
	int count = 0;
	if (needle.size() > haystack.size())
		return 0;
	for (size_t i = 0; i <= haystack.size() - needle.size(); ++i) {
		if (std::memcmp(&haystack[i], needle.data(), needle.size()) == 0)
			count++;
	}
	return count;
}

// Protocol constants
// start_config_update: 5A 01 04 00 00 F0 F1
static constexpr uint8_t START_CONFIG[] = {0x5A, 0x01, 0x04, 0x00, 0x00, 0xF0, 0xF1};
// end_config_update:   5A 01 05 00 00 F0 F1
static constexpr uint8_t END_CONFIG[] = {0x5A, 0x01, 0x05, 0x00, 0x00, 0xF0, 0xF1};
// clear_midi_setup(0): 5A 02 0A 00 01 00 F0 F1
static constexpr uint8_t CLEAR_SETUP[] = {0x5A, 0x02, 0x0A, 0x00, 0x01, 0x00, 0xF0, 0xF1};
// set_setup(0):        5A 02 03 00 01 00 F0 F1
static constexpr uint8_t SET_SETUP[] = {0x5A, 0x02, 0x03, 0x00, 0x01, 0x00, 0xF0, 0xF1};

// Register test modules with known element layouts

// A module with a single Knob element (param_idx=0)
struct KnobModInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"TestKnobMod"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::array<Element, 1> Elements{{
		Knob{{{{{0, 0, Coords::Center, "Freq", "Frequency"}}}}},
	}};
};

// A module with a KnobSnapped element (3 positions)
struct SnappedKnobModInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"TestSnappedKnobMod"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::array<Element, 1> Elements{{
		KnobSnapped{{{{{{0, 0, Coords::Center, "Mode", "Mode"}}}}}, 3, {"Low", "Mid", "High"}},
	}};
};

// A module with a MomentaryButton element
struct ButtonModInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"TestButtonMod"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::array<Element, 1> Elements{{
		MomentaryButton{{{{{0, 0, Coords::Center, "Trig", "Trigger"}}}}},
	}};
};

// A module with a LatchingButton element
struct LatchButtonModInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"TestLatchBtnMod"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::array<Element, 1> Elements{{
		LatchingButton{{{{{0, 0, Coords::Center, "Toggle", "Toggle"}}}}},
	}};
};

// A module with a FlipSwitch (3-pos)
struct FlipSwitchModInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"TestFlipSwitchMod"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::array<Element, 1> Elements{{
		FlipSwitch{{{{{0, 0, Coords::Center, "Sw", "Switch"}}}, 3}, {}, {"Off", "Mid", "On"}},
	}};
};

// A module with a long control name
struct LongNameModInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"TestLongNameMod"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::array<Element, 1> Elements{{
		Knob{{{{{0, 0, Coords::Center, "VeryLongKnobName", "VeryLongKnobNameThatShouldBeTruncated"}}}}},
	}};
};

// A module with two knobs (to test param_id matching)
struct TwoKnobModInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"TestTwoKnobMod"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::array<Element, 2> Elements{{
		Knob{{{{{0, 0, Coords::Center, "Freq", "Frequency"}}}}},
		Knob{{{{{10, 0, Coords::Center, "Res", "Resonance"}}}}},
	}};
};

// Auto-register test modules
static bool reg_knob =
	ModuleFactory::registerModuleType("TestKnobMod", nullptr, ModuleInfoView::makeView<KnobModInfo>(), "");
static bool reg_snapped = ModuleFactory::registerModuleType(
	"TestSnappedKnobMod", nullptr, ModuleInfoView::makeView<SnappedKnobModInfo>(), "");
static bool reg_button =
	ModuleFactory::registerModuleType("TestButtonMod", nullptr, ModuleInfoView::makeView<ButtonModInfo>(), "");
static bool reg_latch =
	ModuleFactory::registerModuleType("TestLatchBtnMod", nullptr, ModuleInfoView::makeView<LatchButtonModInfo>(), "");
static bool reg_flip =
	ModuleFactory::registerModuleType("TestFlipSwitchMod", nullptr, ModuleInfoView::makeView<FlipSwitchModInfo>(), "");
static bool reg_longname =
	ModuleFactory::registerModuleType("TestLongNameMod", nullptr, ModuleInfoView::makeView<LongNameModInfo>(), "");
static bool reg_two =
	ModuleFactory::registerModuleType("TestTwoKnobMod", nullptr, ModuleInfoView::makeView<TwoKnobModInfo>(), "");

// Helper: create a MappedKnob for MIDI CC
static MappedKnob make_midi_cc_knob(uint8_t cc_num, uint16_t module_id, uint16_t param_id, uint8_t midi_chan = 1) {
	MappedKnob k{};
	k.panel_knob_id = MidiCC0 + cc_num;
	k.module_id = module_id;
	k.param_id = param_id;
	k.midi_chan = midi_chan;
	k.min = 0.f;
	k.max = 1.f;
	return k;
}

TEST_CASE("RotoControlSerializer: empty patch produces framing only") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Empty");

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>()); // HubMedium at index 0

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);
	CHECK(data.size() > 0);

	// Should contain: start_config_update, clear_midi_setup, end_config_update, set_setup
	CHECK(find_sequence(data, START_CONFIG) >= 0);
	CHECK(find_sequence(data, CLEAR_SETUP) >= 0);
	CHECK(find_sequence(data, END_CONFIG) >= 0);
	CHECK(find_sequence(data, SET_SETUP) >= 0);

	// No control config commands (0x5A 0x02 0x07 for knob, 0x5A 0x02 0x08 for switch)
	uint8_t knob_cmd[] = {0x5A, 0x02, 0x07};
	uint8_t switch_cmd[] = {0x5A, 0x02, 0x08};
	CHECK(find_sequence(data, knob_cmd) == -1);
	CHECK(find_sequence(data, switch_cmd) == -1);
}

TEST_CASE("RotoControlSerializer: single knob MIDI CC mapping") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestKnobMod");

	pd.midi_maps.set.push_back(make_midi_cc_knob(/*cc*/ 10, /*module_id*/ 1, /*param_id*/ 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>()); // HubMedium
	modules.push_back(std::make_unique<StubProcessor>()); // TestKnobMod

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	// Should have exactly one knob control config command
	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	CHECK(count_sequence(data, knob_header) == 1);

	// Find the knob command and verify its fields
	int pos = find_sequence(data, knob_header);
	CHECK(pos >= 0);

	// Byte layout after header (5A 02 07):
	// [3..4] data_length (MSB, LSB)
	// [5] setup_index = 0
	// [6] control_index = 0 (first knob)
	// [7] control_mode = CC_7BIT = 0x00
	// [8] control_channel = 1
	// [9] control_param = cc_num = 10
	CHECK(data[pos + 5] == 0x00); // setup_index
	CHECK(data[pos + 6] == 0x00); // control_index (first knob)
	CHECK(data[pos + 7] == 0x00); // CC_7BIT
	CHECK(data[pos + 8] == 0x01); // midi channel 1
	CHECK(data[pos + 9] == 10);	  // CC number 10

	// [10..11] NRPN address = 0
	CHECK(data[pos + 10] == 0x00);
	CHECK(data[pos + 11] == 0x00);

	// [12..13] min = 0
	CHECK(data[pos + 12] == 0x00);
	CHECK(data[pos + 13] == 0x00);

	// [14..15] max = 127
	CHECK(data[pos + 14] == 0x00);
	CHECK(data[pos + 15] == 127);

	// [16..28] control name "Freq" padded to 13 bytes
	CHECK(data[pos + 16] == 'F');
	CHECK(data[pos + 17] == 'r');
	CHECK(data[pos + 18] == 'e');
	CHECK(data[pos + 19] == 'q');
	CHECK(data[pos + 20] == 0x00); // null terminator

	// For knob: [29] color_scheme=0, [30] haptic_mode=KNOB_300=0, [31] indent_pos1=0xFF, [32] indent_pos2=0xFF
	CHECK(data[pos + 29] == 0x00);							// color_scheme
	CHECK(data[pos + 30] == (uint8_t)HapticMode::KNOB_300); // haptic_mode
	CHECK(data[pos + 31] == 0xFF);							// indent_pos1
	CHECK(data[pos + 32] == 0xFF);							// indent_pos2

	// [33] haptic_steps = 0 (continuous knob)
	CHECK(data[pos + 33] == 0x00);
}

TEST_CASE("RotoControlSerializer: midi_chan 0 maps to channel 1") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestKnobMod");

	auto knob = make_midi_cc_knob(20, 1, 0);
	knob.midi_chan = 0; // should be sent as 1
	pd.midi_maps.set.push_back(knob);

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);
	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	int pos = find_sequence(data, knob_header);
	CHECK(pos >= 0);
	CHECK(data[pos + 8] == 0x01); // channel forced to 1
}

TEST_CASE("RotoControlSerializer: momentary button maps as SWITCH with PUSH haptic") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestButtonMod");
	pd.midi_maps.set.push_back(make_midi_cc_knob(15, 1, 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	// Should produce a SWITCH command (0x08), not KNOB (0x07)
	uint8_t switch_header[] = {0x5A, 0x02, 0x08};
	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	CHECK(count_sequence(data, switch_header) == 1);
	CHECK(count_sequence(data, knob_header) == 0);

	int pos = find_sequence(data, switch_header);
	CHECK(pos >= 0);

	// Control name should be "Trig" (short_name)
	CHECK(data[pos + 16] == 'T');
	CHECK(data[pos + 17] == 'r');
	CHECK(data[pos + 18] == 'i');
	CHECK(data[pos + 19] == 'g');

	// For switch: [29] color_scheme=0, [30] led_on_color=0x00, [31] led_off_color=0x01, [32] haptic_mode=PUSH=0x00
	CHECK(data[pos + 29] == 0x00);						// color_scheme
	CHECK(data[pos + 30] == 0x00);						// led_on_color
	CHECK(data[pos + 31] == 0x01);						// led_off_color
	CHECK(data[pos + 32] == (uint8_t)HapticMode::PUSH); // haptic_mode

	// [33] haptic_steps = 0 (serializer passes 0 for SWITCH controls)
	CHECK(data[pos + 33] == 0);
}

TEST_CASE("RotoControlSerializer: latching button maps as SWITCH with KNOB_N_STEP haptic") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestLatchBtnMod");
	pd.midi_maps.set.push_back(make_midi_cc_knob(20, 1, 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	uint8_t switch_header[] = {0x5A, 0x02, 0x08};
	int pos = find_sequence(data, switch_header);
	CHECK(pos >= 0);

	// haptic_mode = KNOB_N_STEP = 0x01 (for switch layout: pos+32)
	CHECK(data[pos + 32] == (uint8_t)HapticMode::KNOB_N_STEP);
	// [33] haptic_steps = 0 (serializer passes 0 for SWITCH controls)
	CHECK(data[pos + 33] == 0);
}

TEST_CASE("RotoControlSerializer: snapped knob with position names") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestSnappedKnobMod");
	pd.midi_maps.set.push_back(make_midi_cc_knob(30, 1, 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	int pos = find_sequence(data, knob_header);
	CHECK(pos >= 0);

	// haptic_mode = KNOB_N_STEP = 0x01
	CHECK(data[pos + 30] == (uint8_t)HapticMode::KNOB_N_STEP);

	// haptic_steps = 3
	CHECK(data[pos + 33] == 3);

	// Step names follow at pos+34, each 13 bytes
	// Step 0: "Low" padded to 13
	CHECK(data[pos + 34] == 'L');
	CHECK(data[pos + 35] == 'o');
	CHECK(data[pos + 36] == 'w');
	CHECK(data[pos + 37] == 0x00);

	// Step 1: "Mid" at pos+47
	CHECK(data[pos + 47] == 'M');
	CHECK(data[pos + 48] == 'i');
	CHECK(data[pos + 49] == 'd');
	CHECK(data[pos + 50] == 0x00);

	// Step 2: "High" at pos+60
	CHECK(data[pos + 60] == 'H');
	CHECK(data[pos + 61] == 'i');
	CHECK(data[pos + 62] == 'g');
	CHECK(data[pos + 63] == 'h');
	CHECK(data[pos + 64] == 0x00);
}

TEST_CASE("RotoControlSerializer: flip switch with position names") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestFlipSwitchMod");
	pd.midi_maps.set.push_back(make_midi_cc_knob(40, 1, 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	// FlipSwitch with 3 pos and haptic_steps == 3 => routed as KNOB (not switch, since haptic_steps != 2)
	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	int pos = find_sequence(data, knob_header);
	CHECK(pos >= 0);

	CHECK(data[pos + 30] == (uint8_t)HapticMode::KNOB_N_STEP);
	CHECK(data[pos + 33] == 3); // haptic_steps

	// Step names: "Off", "Mid", "On"
	CHECK(data[pos + 34] == 'O');
	CHECK(data[pos + 35] == 'f');
	CHECK(data[pos + 36] == 'f');
	CHECK(data[pos + 37] == 0x00);

	CHECK(data[pos + 47] == 'M');
	CHECK(data[pos + 48] == 'i');
	CHECK(data[pos + 49] == 'd');
	CHECK(data[pos + 50] == 0x00);

	CHECK(data[pos + 60] == 'O');
	CHECK(data[pos + 61] == 'n');
	CHECK(data[pos + 62] == 0x00);
}

TEST_CASE("RotoControlSerializer: multiple MIDI maps produce sequential control indices") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestTwoKnobMod");

	pd.midi_maps.set.push_back(make_midi_cc_knob(10, 1, 0)); // Freq
	pd.midi_maps.set.push_back(make_midi_cc_knob(11, 1, 1)); // Res

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	CHECK(count_sequence(data, knob_header) == 2);

	// First knob command
	int pos1 = find_sequence(data, knob_header);
	CHECK(pos1 >= 0);
	CHECK(data[pos1 + 6] == 0x00); // control_index = 0
	CHECK(data[pos1 + 9] == 10);   // CC 10
	CHECK(data[pos1 + 16] == 'F'); // "Freq"

	// Second knob command (search after first)
	int pos2 = find_sequence(std::span<const uint8_t>(data).subspan(pos1 + 5), knob_header);
	CHECK(pos2 >= 0);
	pos2 += pos1 + 5;			   // adjust to absolute position
	CHECK(data[pos2 + 6] == 0x01); // control_index = 1
	CHECK(data[pos2 + 9] == 11);   // CC 11
	CHECK(data[pos2 + 16] == 'R'); // "Res"
}

TEST_CASE("RotoControlSerializer: skips invalid module_id") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestKnobMod");

	// module_id=5 is out of range (only indices 0,1 exist)
	pd.midi_maps.set.push_back(make_midi_cc_knob(10, 5, 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	// No knob or switch commands should be generated
	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	uint8_t switch_header[] = {0x5A, 0x02, 0x08};
	CHECK(count_sequence(data, knob_header) == 0);
	CHECK(count_sequence(data, switch_header) == 0);
}

TEST_CASE("RotoControlSerializer: skips null module in modules span") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestKnobMod");

	pd.midi_maps.set.push_back(make_midi_cc_knob(10, 1, 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(nullptr); // null module

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	CHECK(count_sequence(data, knob_header) == 0);
}

TEST_CASE("RotoControlSerializer: mixed knobs and buttons use separate index counters") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestKnobMod");
	pd.module_slugs.push_back("TestButtonMod");
	pd.module_slugs.push_back("TestKnobMod");

	// Knob CC10 -> module 1 (knob), Button CC20 -> module 2 (button), Knob CC30 -> module 3 (knob)
	pd.midi_maps.set.push_back(make_midi_cc_knob(10, 1, 0));
	pd.midi_maps.set.push_back(make_midi_cc_knob(20, 2, 0));
	pd.midi_maps.set.push_back(make_midi_cc_knob(30, 3, 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>()); // Hub
	modules.push_back(std::make_unique<StubProcessor>()); // TestKnobMod
	modules.push_back(std::make_unique<StubProcessor>()); // TestButtonMod
	modules.push_back(std::make_unique<StubProcessor>()); // TestKnobMod

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	uint8_t switch_header[] = {0x5A, 0x02, 0x08};

	CHECK(count_sequence(data, knob_header) == 2);
	CHECK(count_sequence(data, switch_header) == 1);

	// First knob: control_index = 0
	int kpos1 = find_sequence(data, knob_header);
	CHECK(kpos1 >= 0);
	CHECK(data[kpos1 + 6] == 0x00);

	// Switch: control_index = 0 (separate counter)
	int spos = find_sequence(data, switch_header);
	CHECK(spos >= 0);
	CHECK(data[spos + 6] == 0x00);

	// Second knob: control_index = 1
	int kpos2 = find_sequence(std::span<const uint8_t>(data).subspan(kpos1 + 5), knob_header);
	CHECK(kpos2 >= 0);
	kpos2 += kpos1 + 5;
	CHECK(data[kpos2 + 6] == 0x01);
}

TEST_CASE("RotoControlSerializer: long control name is truncated to 12 chars") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestLongNameMod");
	pd.midi_maps.set.push_back(make_midi_cc_knob(50, 1, 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);
	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	int pos = find_sequence(data, knob_header);
	CHECK(pos >= 0);

	// Name field is 13 bytes at pos+16, should be "VeryLongKnob" + null (12 chars + null)
	std::string name(reinterpret_cast<const char *>(&data[pos + 16]), 12);
	CHECK(name == "VeryLongKnob");
	CHECK(data[pos + 28] == 0x00); // 13th byte is null
}

TEST_CASE("RotoControlSerializer: command ordering") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestKnobMod");
	pd.midi_maps.set.push_back(make_midi_cc_knob(10, 1, 0));

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	// Verify ordering: start_config < clear_setup < knob_config < end_config < set_setup
	int start_pos = find_sequence(data, START_CONFIG);
	int clear_pos = find_sequence(data, CLEAR_SETUP);
	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	int knob_pos = find_sequence(data, knob_header);
	int end_pos = find_sequence(data, END_CONFIG);
	int setup_pos = find_sequence(data, SET_SETUP);

	CHECK(start_pos >= 0);
	CHECK(clear_pos > start_pos);
	CHECK(knob_pos > clear_pos);
	CHECK(end_pos > knob_pos);
	CHECK(setup_pos > end_pos);
}

TEST_CASE("RotoControlSerializer: non-MIDI-CC mapping is skipped") {
	ConcurrentBuffer buf{};
	RotoControlSerializer serializer(&buf);

	PatchData pd;
	pd.blank_patch("Test");
	pd.module_slugs.push_back("TestKnobMod");

	// Panel knob mapping (not MIDI CC)
	MappedKnob k{};
	k.panel_knob_id = 0; // panel knob, not MidiCC
	k.module_id = 1;
	k.param_id = 0;
	k.midi_chan = 1;
	pd.midi_maps.set.push_back(k);

	std::vector<std::unique_ptr<CoreProcessor>> modules;
	modules.push_back(std::make_unique<StubProcessor>());
	modules.push_back(std::make_unique<StubProcessor>());

	serializer.update_from_patch(pd, modules);

	auto data = get_buffer_data(buf);

	uint8_t knob_header[] = {0x5A, 0x02, 0x07};
	uint8_t switch_header[] = {0x5A, 0x02, 0x08};
	CHECK(count_sequence(data, knob_header) == 0);
	CHECK(count_sequence(data, switch_header) == 0);
}
