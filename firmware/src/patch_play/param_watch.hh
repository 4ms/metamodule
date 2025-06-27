#pragma once
#include "patch/patch.hh"
#include <array>
#include <atomic>
#include <cstdint>
#include <span>

namespace MetaModule
{

struct WatchedParam {
	uint16_t module_id{};
	uint16_t param_id{};
	float value;
	std::atomic<bool> active{false};

	// MIDI mapping info
	uint8_t midi_chan{0};
	uint16_t panel_knob_id{};

	void activate(uint16_t module_id, uint16_t param_id) {
		this->module_id = module_id;
		this->param_id = param_id;
		active.store(true, std::memory_order_release); //all stores before this will not get moved after this
	}

	void set_midi_mapping(const MappedKnob &mapped_knob) {
		midi_chan = mapped_knob.midi_chan > 0 ? mapped_knob.midi_chan - 1 : 0;
		panel_knob_id = mapped_knob.panel_knob_id;
	}

	void deactivate() {
		active.store(false, std::memory_order_release);
	}

	bool is_active() const {
		return active.load();
	}
};

struct ParamWatcher {
	static constexpr size_t MaxParamsToWatch = 257; // 128 cc + 128 notegate + 1 pitchwheel

	std::span<WatchedParam> active_watched_params() {
		return std::span<WatchedParam>{&watched_params[lowest_active_idx], &watched_params[highest_active_idx + 1]};
	}

	void start_watching_param(const MappedKnob &mapped_knob) {
		for (auto idx = 0u; auto &w : watched_params) {
			if (!w.is_active()) {
				w.activate(mapped_knob.module_id, mapped_knob.param_id);
				w.set_midi_mapping(mapped_knob);
				add(idx);
				return;
			}
			idx++;
		}
	}

	void update_watched_param(const MappedKnob &mapped_knob) {
		for (auto &w : watched_params) {
			if (w.is_active() && w.module_id == mapped_knob.module_id && w.param_id == mapped_knob.param_id) {
				w.set_midi_mapping(mapped_knob);
				return;
			}
		}
	}

	void stop_watching_param(const MappedKnob &mapped_knob) {
		for (auto idx = 0u; auto &w : watched_params) {
			if (w.is_active() && w.module_id == mapped_knob.module_id && w.param_id == mapped_knob.param_id) {
				w.deactivate();
				remove(idx);
				return;
			}
			idx++;
		}
	}

	void stop_watching_all() {
		for (auto &w : watched_params) {
			if (w.is_active()) {
				w.deactivate();
			}
		}
		lowest_active_idx = 0;
		highest_active_idx = 0;
	}

private:
	std::array<WatchedParam, MaxParamsToWatch> watched_params;

	unsigned lowest_active_idx = 0;
	unsigned highest_active_idx = 0;

	void add(unsigned idx) {
		highest_active_idx = std::max(idx, highest_active_idx);
		lowest_active_idx = std::min(idx, lowest_active_idx);
	}

	void remove(unsigned idx) {
		if (lowest_active_idx == highest_active_idx)
			return;

		if (lowest_active_idx > highest_active_idx) {
			lowest_active_idx = 0;
			highest_active_idx = 0;
			return;
		}

		if (idx == highest_active_idx) {
			if (highest_active_idx == 0)
				return;
			// find previous active
			for (auto i = highest_active_idx - 1; i >= lowest_active_idx; i--) {
				if (watched_params[i].is_active()) {
					highest_active_idx = i;
					break;
				}
			}
		}

		if (idx == lowest_active_idx) {
			if (lowest_active_idx >= watched_params.size() - 1) {
				lowest_active_idx = watched_params.size() - 1;
				return;
			}
			// find next active
			for (auto i = lowest_active_idx + 1; i < highest_active_idx; i++) {
				if (watched_params[i].is_active()) {
					lowest_active_idx = i;
					break;
				}
			}
		}
	}
};

} // namespace MetaModule
