#pragma once
#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>

namespace MetaModule
{

// Tabulates and smooths live CPU load measurements from both cores and makes it available to the GUI
class LiveLoadMeter {
public:
	static constexpr unsigned MaxCores = 2;

	// All loads are percent of the audio block period, in tenths of a percent
	// (e.g. 123 => 12.3%)
	struct Loads {
		uint16_t overhead;
		uint16_t mappings;
		uint16_t sync;
		uint16_t cables;
		std::array<uint16_t, MaxCores> core_modules;
		uint16_t midi;
		bool valid;
	};

	// -- Audio context (Core 1) --

	// Time to process one audio frame in AudioStream::process()
	void tally_frame(uint32_t loop_ticks) {
		frame_loop_ticks += loop_ticks;
	}

	// Time AudioStream::process() spends handling the MIDI stream (counted as
	// MIDI, not Mappings, even though it happens inside the frame loop)
	void tally_midi_stream(uint32_t midi_ticks) {
		midi_stream_ticks += midi_ticks;
	}

	// Times from PatchPlayer::update_patch(): total time, time running this core's modules,
	// and time spent waiting for the other core to finish its modules
	void tally_update_patch(
		uint32_t total_ticks, uint32_t module_ticks, uint32_t wait_ticks, uint32_t cable_ticks, uint32_t midi_ticks) {
		update_patch_ticks += total_ticks;
		core1_module_ticks += module_ticks;
		sync_ticks += wait_ticks;
		midi_pulse_ticks += midi_ticks;
		core1_cable_ticks += cable_ticks;
	}

	void finish_block(uint32_t block_ticks, uint32_t period_ticks) {
		if (period_ticks == 0)
			return;

		auto core2_total = core2_module_ticks.load(std::memory_order_relaxed);

		std::array<uint32_t, NumCategories> ticks{
			sat_sub(update_patch_ticks, core1_module_ticks + sync_ticks + core1_cable_ticks + midi_pulse_ticks) +
				sat_sub(block_ticks, frame_loop_ticks),							  // Overhead
			sat_sub(frame_loop_ticks, update_patch_ticks + midi_stream_ticks),	  // Mappings
			sync_ticks,															  // Sync
			core1_cable_ticks,													  // Cables
			core1_module_ticks,
			core2_total - last_core2_total,
			midi_pulse_ticks + midi_stream_ticks, // MIDI
		};
		last_core2_total = core2_total;

		frame_loop_ticks = 0;
		update_patch_ticks = 0;
		core1_module_ticks = 0;
		sync_ticks = 0;
		core1_cable_ticks = 0;
		midi_pulse_ticks = 0;
		midi_stream_ticks = 0;

		for (auto i = 0u; i < NumCategories; i++) {
			float frac = (float)ticks[i] / (float)period_ticks;
			lpf[i] = published.valid ? lpf[i] + (frac - lpf[i]) * Alpha : frac;
		}

		published = Loads{
			.overhead = to_tenths(lpf[0]),
			.mappings = to_tenths(lpf[1]),
			.sync = to_tenths(lpf[2]),
			.cables = to_tenths(lpf[3]),
			.core_modules = {to_tenths(lpf[4]), to_tenths(lpf[5])},
			.midi = to_tenths(lpf[6]),
			.valid = true,
		};
	}

	void reset() {
		frame_loop_ticks = 0;
		update_patch_ticks = 0;
		core1_module_ticks = 0;
		sync_ticks = 0;
		core1_cable_ticks = 0;
		midi_pulse_ticks = 0;
		midi_stream_ticks = 0;
		last_core2_total = core2_module_ticks.load(std::memory_order_relaxed);
		lpf.fill(0.f);
		published = Loads{};
	}

	// -- AuxPlayer (Core 2) --

	void tally_core2_modules(uint32_t module_ticks) {
		core2_module_ticks.fetch_add(module_ticks, std::memory_order_relaxed);
	}

	// -- GUI --

	Loads get() const {
		return published;
	}

private:
	static constexpr unsigned NumCategories = 7;
	static constexpr float Alpha = 0.05f;

	static uint32_t sat_sub(uint32_t a, uint32_t b) {
		return a > b ? a - b : 0;
	}

	static uint16_t to_tenths(float frac) {
		return (uint16_t)std::min(frac * 1000.f, 65535.f);
	}

	uint32_t frame_loop_ticks = 0;
	uint32_t update_patch_ticks = 0;
	uint32_t core1_module_ticks = 0;
	uint32_t sync_ticks = 0;
	uint32_t core1_cable_ticks = 0;
	uint32_t midi_pulse_ticks = 0;
	uint32_t midi_stream_ticks = 0;

	std::atomic<uint32_t> core2_module_ticks{0};
	uint32_t last_core2_total = 0;

	std::array<float, NumCategories> lpf{};

	Loads published{};
};

} // namespace MetaModule
