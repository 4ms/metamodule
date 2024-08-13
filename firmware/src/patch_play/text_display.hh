#pragma once
#include "util/lockfree_fifo_spsc.hh"
#include "util/static_string.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{

struct WatchedTextDisplay {
	uint16_t module_id{};
	uint16_t light_id{};
	StaticString<255> text;
	std::atomic<bool> active{false};

	void activate(uint16_t m_id, uint16_t l_id) {
		module_id = m_id;
		light_id = l_id;
		active.store(true, std::memory_order_release); //all stores before this will not get moved after this
	}

	void deactivate() {
		active.store(false, std::memory_order_release);
	}

	bool is_active() {
		return active.load();
	}
};

struct TextDisplayWatcher {
	static constexpr size_t MaxDisplaysToWatch = 4;

	std::array<WatchedTextDisplay, MaxDisplaysToWatch> watch_displays;

	void start_watching_display(uint16_t module_id, uint16_t light_id) {
		// First search for existing display:
		for (auto &w : watch_displays) {
			if (w.module_id == module_id && w.light_id == light_id) {
				w.activate(module_id, light_id);
				return;
			}
		}
		// If not found, add it into an empty slot:
		for (auto &w : watch_displays) {
			if (!w.is_active()) {
				w.activate(module_id, light_id);
				return;
			}
		}
	}

	void stop_watching_display(uint16_t module_id, uint16_t light_id) {
		for (auto &w : watch_displays) {
			if (w.module_id == module_id && w.light_id == light_id) {
				w.deactivate();
				return;
			}
		}
	}

	void stop_watching_module(uint16_t module_id) {
		for (auto &w : watch_displays) {
			if (w.module_id == module_id) {
				w.deactivate();
			}
		}
	}

	void stop_watching_all() {
		for (auto &w : watch_displays)
			w.deactivate();
	}
};

} // namespace MetaModule
