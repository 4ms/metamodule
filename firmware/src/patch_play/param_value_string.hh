#pragma once
#include "util/static_string.hh"
#include <atomic>
#include <cstdint>
#include <optional>
#include <string_view>

namespace MetaModule
{

// The module's own text for a param's value (for VCV modules: ParamQuantity::getDisplayValueString()
// and getUnit()), for the param the GUI is showing. The GUI asks for a param with start_watching(),
// and the player fills in the text when it reads the watched text displays.
struct ParamValueStringWatcher {
	uint16_t module_id{};
	uint16_t param_id{};
	StaticString<63> text;

	void start_watching(uint16_t m_id, uint16_t p_id) {
		active.store(false, std::memory_order_release);
		module_id = m_id;
		param_id = p_id;
		request.fetch_add(1, std::memory_order_release);
		active.store(true, std::memory_order_release); //all stores before this will not get moved after this
	}

	void stop_watching() {
		active.store(false, std::memory_order_release);
	}

	bool is_active() const {
		return active.load(std::memory_order_acquire);
	}

	// Player: returns the request being filled, call finish_fill() with it after writing text
	uint32_t start_fill() const {
		return request.load(std::memory_order_acquire);
	}

	void finish_fill(uint32_t req, bool has_text) {
		filled_has_text = has_text;
		filled.store(req, std::memory_order_release);
	}

	// GUI: the text for the current request, or nullopt if it's not filled yet.
	// An empty string means the module doesn't provide text for this param.
	std::optional<std::string_view> get_text() const {
		if (!is_active() || filled.load(std::memory_order_acquire) != request.load(std::memory_order_relaxed))
			return std::nullopt;
		return filled_has_text ? std::string_view{text.c_str()} : std::string_view{};
	}

private:
	std::atomic<bool> active{false};
	std::atomic<uint32_t> request{0};
	std::atomic<uint32_t> filled{0};
	bool filled_has_text = false;
};

} // namespace MetaModule
