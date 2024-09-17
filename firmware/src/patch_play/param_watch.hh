#pragma once
#include "util/static_string.hh"
#include <array>
#include <atomic>
#include <cstdint>

namespace MetaModule
{

struct WatchedParam {
	uint16_t module_id{};
	uint16_t param_id{};
	float value;
	std::atomic<bool> active{false};

	void activate(uint16_t module_id, uint16_t param_id) {
		this->module_id = module_id;
		this->param_id = param_id;
		active.store(true, std::memory_order_release); //all stores before this will not get moved after this
	}

	void deactivate() {
		active.store(false, std::memory_order_release);
	}

	bool is_active() const {
		return active.load();
	}
};

struct ParamWatcher {
	static constexpr size_t MaxParamsToWatch = 256;

	std::array<WatchedParam, MaxParamsToWatch> watched_params;

	void start_watching_param(uint16_t module_id, uint16_t param_id) {
		// First search for existing param:
		for (auto &w : watched_params) {
			if (w.module_id == module_id && w.param_id == param_id) {
				w.activate(module_id, param_id);
				return;
			}
		}
		// If not found, add it into an empty slot:
		for (auto &w : watched_params) {
			if (!w.is_active()) {
				w.activate(module_id, param_id);
				return;
			}
		}
	}

	void stop_watching_param(uint16_t module_id, uint16_t param_id) {
		for (auto &w : watched_params) {
			if (w.module_id == module_id && w.param_id == param_id) {
				w.deactivate();
				return;
			}
		}
	}

	void stop_watching_module(uint16_t module_id) {
		for (auto &w : watched_params) {
			if (w.module_id == module_id) {
				w.deactivate();
			}
		}
	}

	void stop_watching_all() {
		for (auto &w : watched_params) {
			if (w.is_active()) {
				w.deactivate();
			}
		}
	}
};

} // namespace MetaModule
