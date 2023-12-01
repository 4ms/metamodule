#pragma once
#include "gui/elements/module_param.hh"
#include "page_args.hh"
#include "patch_file/patch_location.hh"
#include "util/circular_stack.hh"
#include <array>
#include <cstdint>
#include <optional>

namespace MetaModule
{

//forward declare
struct PageBase;

enum class PageId { PatchSel, PatchView, ModuleView, Settings, KnobSetView, KnobMap, CableEdit };

struct PageWithArgs {
	PageBase *page;
	PageArguments *args;
};

class PageList {
	static constexpr uint32_t MaxPages = 8;

	// static inline PageBase *_requested_page = nullptr;
	static inline bool _new_page_requested = false;

	static inline std::array<PageBase *, MaxPages> _pages;

	static inline uint32_t patch_revision = 0;

	///////////// new history

	struct PageHistory {
		PageId page;
		PageArguments args;
	};

	static inline CircularStack<PageHistory, 64> _page_history;
	static inline PageHistory _request{};

	///////////////////////// old history:
	static inline PatchLocation selected_patch_loc{};
	static inline uint32_t selected_module_id = 0;
	static inline uint32_t selected_mappedknob_id = 0;
	static inline uint32_t selected_knob_id = 0;
	static inline uint32_t active_knobset_id = 0;
	static inline uint32_t view_knobset_id = 0;
	static inline ElementCount::Counts selected_element_counts{};
	static inline ElementCount::Indices selected_element_indices{};

public:
	static inline CircularStack<PageBase *, 16> _history;

	static void set_selected_patch_loc(PatchLocation loc) {
		selected_patch_loc = loc;
	}

	static PatchLocation get_selected_patch_location() {
		return selected_patch_loc;
	}

	static ElementCount::Counts get_selected_element_counts() {
		return selected_element_counts;
	}

	static ElementCount::Indices get_selected_element_indices() {
		return selected_element_indices;
	}

	static void set_selected_element_counts(ElementCount::Counts counts) {
		selected_element_counts = counts;
	}

	static void set_selected_element_indices(ElementCount::Indices indices) {
		selected_element_indices = indices;
	}

	static void set_active_knobset(uint32_t id) {
		active_knobset_id = id;
	}

	static uint32_t get_active_knobset() {
		return active_knobset_id;
	}

	static void set_viewing_knobset(uint32_t id) {
		view_knobset_id = id;
	}

	static uint32_t get_viewing_knobset() {
		return view_knobset_id;
	}

	static void set_selected_module_id(uint32_t id) {
		selected_module_id = id;
	}

	static uint32_t get_selected_module_id() {
		return selected_module_id;
	}

	static void set_selected_mappedknob_id(uint32_t id) {
		selected_mappedknob_id = id;
	}

	static uint32_t get_selected_mappedknob_id() {
		return selected_mappedknob_id;
	}

	static void set_selected_knob_id(uint32_t id) {
		selected_knob_id = id;
	}

	static uint32_t get_selected_knob_id() {
		return selected_knob_id;
	}
	//////////////////////////

public:
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
	}

	//////////////////////////

	static void request_initial_page(PageId id, PageArguments args) {
		_request = {id, args};
		_new_page_requested = true;
	}

	static void request_new_page(PageId id, PageArguments args) {
		// Requesting the same page that's most recent page in history
		// is just like going back, so pop -- don't push
		// if (auto last = _page_history.back()) {
		// 	if (last->page == id && last->args == args) {
		// 		_page_history.pop_back();
		// 	}
		// } else
		_page_history.push_back(_request);

		_request = {id, args};
		_new_page_requested = true;
	}

	// Requests to jump to the previous page in history
	// Returns false if history is empty
	static bool request_last_page() {
		auto last = _page_history.pop_back();
		if (!last) {
			return false;
		}
		// if (last.value().page == PageId::None) { // marks end of history
		// 	printf("Last page is start of history\n");
		// 	return false;
		// }

		_request = last.value();
		_new_page_requested = true;
		return true;
	}

	// Returns the requested page, or else nullopt if no new page is requested
	static std::optional<PageWithArgs> get_requested_page() {
		if (_new_page_requested) {
			_new_page_requested = false;
			return PageWithArgs{page(_request.page), &_request.args};

		} else
			return std::nullopt;
	}

	// Clears history and resets internal state
	static void clear_history() {
		_page_history.clear();
		// _request = {};
		// _new_page_requested = false;
	}

private:
	static PageBase *page(PageId id) {
		return _pages[static_cast<std::underlying_type_t<PageId>>(id)];
	}
};

} // namespace MetaModule
