#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "params/midi_params.hh"
#include "patch/midi_def.hh"
#include "patch/patch.hh"
#include "util/oscs.hh"
#include <array>
#include <cstdint>
#include <vector>

namespace MetaModule
{

// The lookup tables that route incoming MIDI to module jacks and params.
struct MidiConnections {
	struct JackMidi : Jack {
		uint32_t midi_chan = 0; //0: Omni
	};

	struct PolyJackMidi : JackMidi {
		CoreProcessor::PolyPortBuffer buf{};
		// First poly channel this cable carries: 0 for the 1-4 cable, 4 for the 5-8 cable.
		uint8_t poly_base = 0;
	};

	struct Pulse {
		OneShot pulse{};
		std::vector<JackMidi> conns;
	};

	struct PulseDivider {
		OneShot pulse{};
		std::vector<Jack> conns;
		uint32_t divclk_ctr = 0;
	};

	struct PolyPulse {
		std::array<OneShot, MaxMidiPolyphony> pulses{};
		std::vector<PolyJackMidi> conns;
	};

	// Mono cables, indexed by poly channel
	std::array<std::vector<JackMidi>, MaxMidiPolyphony> note_pitch_conns;
	std::array<std::vector<JackMidi>, MaxMidiPolyphony> note_gate_conns;
	std::array<std::vector<JackMidi>, MaxMidiPolyphony> note_vel_conns;
	std::array<std::vector<JackMidi>, MaxMidiPolyphony> note_aft_conns;
	std::array<Pulse, MaxMidiPolyphony> note_retrig;

	std::array<std::vector<JackMidi>, NumMidiCCsPW> cc_conns;
	std::array<std::vector<JackMidi>, NumMidiNotes> gate_conns;

	// Poly cables (one vector per signal type, not per poly channel)
	std::vector<PolyJackMidi> poly_pitch_conns;
	std::vector<PolyJackMidi> poly_gate_conns;
	std::vector<PolyJackMidi> poly_vel_conns;
	std::vector<PolyJackMidi> poly_aft_conns;
	PolyPulse poly_retrig;

	// Timing events
	std::array<Pulse, TimingEvents::NumTimingEvents> pulses;
	std::array<PulseDivider, Midi::NumDivClocks> divclk_pulses;

	// MIDI -> module param maps
	std::array<std::vector<MappedKnob>, NumMidiCCs> cc_knob_maps;
	std::array<std::vector<MappedKnob>, NumMidiNotes> note_knob_maps;

	bool connected = false;

	//
	// Building and editing the tables (midi_connections.cc)
	//

	void clear();

	// Caches panel_jack_id -> input_jack, if panel_jack_id is a MIDI jack.
	// Returns false (and does nothing) if panel_jack_id is not a MIDI jack.
	bool add_jack_conn(uint32_t panel_jack_id, Jack input_jack, CoreProcessor::PolyPortBuffer polybuf);

	// Removes every connection to the given module input jack
	void erase_jack(Jack jack);

	// Removes every connection and param map referring to the module
	void erase_module(unsigned module_idx);

	// Removes every connection and param map referring to the module, then
	// renumbers the remaining module ids with squash_module_id(module_id&)
	void erase_module(unsigned module_idx, auto &&squash_module_id) {
		erase_module(module_idx);
		for_each_jack_vector([&](auto &v) {
			for (auto &jack : v)
				squash_module_id(jack.module_id);
		});
		for_each_knob_map_vector([&](auto &v) {
			for (auto &map : v)
				squash_module_id(map.module_id);
		});
	}

	void cache_knob_map(MappedKnob const &k);
	void uncache_knob_map(MappedKnob const &k);

	// Finds the cached map for the same MIDI CC/note and module param, or nullptr
	MappedKnob *find_knob_map(MappedKnob const &k);

	bool any_pulse_conns() const;

	void set_samplerate(float hz);

	void reset_divclocks();

	// Each poly cable carries the channels above its poly_base, clamped to MaxPolyChannels.
	// e.g. poly_num=6: the 1-4 cable reports 4 channels, the 5-8 cable reports 2.
	void set_poly_channel_count(uint32_t poly_num);

	void zero_poly_buffers();

	//
	// Walking the tables
	//

	// Calls f(Jack const&) for every module jack in every table
	void for_each_jack(auto &&f) {
		for_each_jack_vector([&](auto &v) {
			for (auto const &jack : v)
				f(static_cast<Jack const &>(jack));
		});
	}

	//
	// Audio context
	//

	// Ends any pulses whose duration has elapsed, setting their jacks to 0
	// via set_input(Jack, float)
	void update_pulses(auto &&set_input) {
		for (auto &mp : pulses) {
			if (mp.conns.empty())
				continue;
			if (!mp.pulse.update()) {
				for (auto const &jack : mp.conns)
					set_input(jack, 0.f);
			}
		}

		for (auto &mp : divclk_pulses) {
			if (mp.conns.empty())
				continue;
			if (!mp.pulse.update()) {
				for (auto const &jack : mp.conns)
					set_input(jack, 0.f);
			}
		}

		for (auto &ret : note_retrig) {
			if (ret.conns.empty())
				continue;
			if (!ret.pulse.update()) {
				for (auto const &jack : ret.conns)
					set_input(jack, 0.f);
			}
		}

		if (!poly_retrig.conns.empty()) {
			for (unsigned ch = 0; ch < MaxMidiPolyphony; ch++) {
				if (!poly_retrig.pulses[ch].update()) {
					for (auto &jack : poly_retrig.conns) {
						if (ch < jack.poly_base)
							continue;
						unsigned idx = ch - jack.poly_base;
						if (idx < CoreProcessor::MaxPolyChannels && jack.buf.voltages)
							jack.buf.voltages[idx] = 0.f;
					}
				}
			}
		}
	}

private:
	// Calls f(std::vector<T>&) for every vector of jacks (mono, poly, and pulse conns)
	void for_each_jack_vector(auto &&f) {
		for (auto &v : note_pitch_conns)
			f(v);
		for (auto &v : note_gate_conns)
			f(v);
		for (auto &v : note_vel_conns)
			f(v);
		for (auto &v : note_aft_conns)
			f(v);
		for (auto &p : note_retrig)
			f(p.conns);
		for (auto &v : cc_conns)
			f(v);
		for (auto &v : gate_conns)
			f(v);
		f(poly_pitch_conns);
		f(poly_gate_conns);
		f(poly_vel_conns);
		f(poly_aft_conns);
		f(poly_retrig.conns);
		for (auto &p : pulses)
			f(p.conns);
		for (auto &p : divclk_pulses)
			f(p.conns);
	}

	// Calls f(std::vector<PolyJackMidi>&) for every vector of poly jacks
	void for_each_poly_vector(auto &&f) {
		f(poly_pitch_conns);
		f(poly_gate_conns);
		f(poly_vel_conns);
		f(poly_aft_conns);
		f(poly_retrig.conns);
	}

	// Calls f(std::vector<MappedKnob>&) for every vector of param maps
	void for_each_knob_map_vector(auto &&f) {
		for (auto &v : cc_knob_maps)
			f(v);
		for (auto &v : note_knob_maps)
			f(v);
	}

	template<typename T>
	static void update_or_add(std::vector<T> &v, const Jack &d, uint32_t midi_chan = 0)
		requires std::derived_from<T, JackMidi>;

	static void update_or_add(std::vector<Jack> &v, const Jack &d);
	static void update_or_add(std::vector<MappedKnob> &v, const MappedKnob &d);

	static void update_or_add_poly(std::vector<PolyJackMidi> &v,
								   const Jack &d,
								   uint32_t midi_chan,
								   CoreProcessor::PolyPortBuffer buf,
								   uint8_t poly_base = 0);
};

} // namespace MetaModule
