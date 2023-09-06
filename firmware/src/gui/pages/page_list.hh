#pragma once
#include "gui/elements/module_param.hh"
#include "util/circular_stack.hh"
#include <array>
#include <cstdint>
#include <optional>

namespace MetaModule
{

//forward declare
struct PageBase;

enum PageId : uint32_t { PatchSel, PatchView, ModuleView, ControlView, Settings, KnobEdit };

class PageList {
	static constexpr uint32_t MaxPages = 8;

	static inline PageBase *_requested_page = nullptr;
	static inline bool _new_page_requested = false;
	static inline CircularStack<PageBase *, 16> _history;
	static inline std::array<PageBase *, MaxPages> _pages;

	//TODO: these need to be in PageManager or somewhere else...
	static inline uint32_t selected_patch_id = 0;
	static inline uint32_t selected_module_id = 0;
	static inline uint32_t active_knobset_id = 0;
	// static inline ModuleParam selected_control_id{};
	static inline uint32_t patch_revision = 0;

public:
	static void set_selected_patch_id(uint32_t id) {
		selected_patch_id = id;
	}

	static uint32_t get_selected_patch_id() {
		return selected_patch_id;
	}

	static void set_active_knobset(uint32_t id) {
		active_knobset_id = id;
	}

	static uint32_t get_active_knobset() {
		return active_knobset_id;
	}

	static void set_selected_module_id(uint32_t id) {
		selected_module_id = id;
	}

	static uint32_t get_selected_module_id() {
		return selected_module_id;
	}

	static void increment_patch_revision() {
		patch_revision++;
	}

	static uint32_t get_patch_revision() {
		return patch_revision;
	}

	// Associates a pointer to a Page with an id
	// Used only by request_new_page(PageId)
	static bool register_page(PageBase *page, PageId id) {
		auto idx = static_cast<uint32_t>(id);
		if (idx >= MaxPages)
			return false;
		if (!page)
			return false;
		_pages[idx] = page;
		return true;
	}

	static void request_new_page(PageId id) {
		auto idx = static_cast<uint32_t>(id);
		request_new_page(*_pages[idx]);
	}

	// Requests that we jump to the given page
	// Another client should use get_new_page() to get this page and jump to it
	static void request_new_page(PageBase &page) {
		_history.push_back(_requested_page);
		_requested_page = &page;
		_new_page_requested = true;
	}

	// Requests to jump to the last page in history
	// Returns false if history is empty, otherwise true
	// Another client should use get_requested_page() to get this page and jump to it
	static bool request_last_page() {
		auto lastpage = PageList::_get_last_page().value_or(nullptr);
		if (!lastpage)
			return false;

		_requested_page = lastpage;
		_new_page_requested = true;
		return true;
	}

	// Returns the requested page, or else nullopt if no new page is requested
	static std::optional<PageBase *> get_requested_page() {
		if (_new_page_requested) {
			_new_page_requested = false;
			return _requested_page;
		} else
			return std::nullopt;
	}

	// Clears history and resets internal state
	static void clear_history() {
		_history.clear();
		_requested_page = nullptr;
		_new_page_requested = false;
	}

private:
	// Returns the last page in the history, or else nullopt if history is empty
	static std::optional<PageBase *> _get_last_page() {
		return _history.pop_back();
	}
};
} // namespace MetaModule
