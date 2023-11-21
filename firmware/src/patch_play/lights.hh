#pragma once
#include "util/lockfree_fifo_spsc.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{

struct WatchedLight {
	uint16_t module_id{};
	uint16_t light_id{};
	float value = 0.f;
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

struct LightWatcher {
	static constexpr size_t MaxLightsToWatch = 256;

	std::array<WatchedLight, MaxLightsToWatch> watch_lights;

	void start_watching_light(uint16_t module_id, uint16_t light_id) {
		// First search for existing light:
		for (auto &w : watch_lights) {
			if (w.module_id == module_id && w.light_id == light_id) {
				w.activate(module_id, light_id);
				return;
			}
		}
		// If not found, add it into an empty slot:
		for (auto &w : watch_lights) {
			if (!w.is_active()) {
				w.activate(module_id, light_id);
				return;
			}
		}
		//TODO: handle case of no empty slots?
		//TODO: more optimal function for adding a span of {module_id, light_id} -- don't start over each time
		//--- could save best guess start spot for next add: (last added value, or last removed value)
	}

	void stop_watching_light(uint16_t module_id, uint16_t light_id) {
		for (auto &w : watch_lights) {
			if (w.module_id == module_id && w.light_id == light_id) {
				w.deactivate();
				return;
			}
		}
	}

	void stop_watching_module(uint16_t module_id) {
		for (auto &w : watch_lights) {
			if (w.module_id == module_id) {
				w.deactivate();
			}
		}
	}

	void stop_watching_all() {
		for (auto &w : watch_lights)
			w.deactivate();
	}
};

} // namespace MetaModule
