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
	bool _new_page_requested = false;

	static constexpr uint32_t MaxPages = 8;
	std::array<PageBase *, MaxPages> _pages;

	uint32_t _active_knobset_id = 0;
	uint32_t _patch_revision = 0;

	struct PageHistory {
		PageId page;
		PageArguments args;
	};
	CircularStack<PageHistory, 64> _page_history;
	PageHistory _request{};

public:
	void set_active_knobset(uint32_t id) {
		_active_knobset_id = id;
	}

	uint32_t get_active_knobset() {
		return _active_knobset_id;
	}

	void increment_patch_revision() {
		_patch_revision++;
	}

	uint32_t get_patch_revision() {
		return _patch_revision;
	}

	// Associates a pointer to a Page with an id
	// Used only by request_new_page(PageId)
	bool register_page(PageBase *page, PageId id) {
		auto idx = static_cast<uint32_t>(id);
		if (idx >= MaxPages)
			return false;
		if (!page)
			return false;
		_pages[idx] = page;
		return true;
	}

	void request_initial_page(PageId pageid, PageArguments args) {
		_request = {pageid, args};
		_new_page_requested = true;
	}

	void stash_state(PageId pageid, PageArguments args) {
		_request = {pageid, args};
	}

	void request_new_page(PageId pageid, PageArguments args) {
		// Requesting the same page that's most recent page in history
		// is just like going back, so pop -- don't push
		// if (auto last = _page_history.back()) {
		// 	if (last->page == id && last->args == args) {
		// 		_page_history.pop_back();
		// 	}
		// } else
		_page_history.push_back(_request);

		_request = {pageid, args};
		_new_page_requested = true;
	}

	// Requests to jump to the previous page in history
	// Returns false if history is empty
	bool request_last_page() {
		auto last = _page_history.pop_back();
		if (!last) {
			return false;
		}

		_request = last.value();
		_new_page_requested = true;
		return true;
	}

	// Returns the requested page, or else nullopt if no new page is requested
	std::optional<PageWithArgs> get_requested_page() {
		if (_new_page_requested) {
			_new_page_requested = false;
			return PageWithArgs{page(_request.page), &_request.args};

		} else
			return std::nullopt;
	}

	// Clears history and resets internal state
	void clear_history() {
		_page_history.clear();
		_new_page_requested = false;
	}

private:
	PageBase *page(PageId id) {
		return _pages[static_cast<std::underlying_type_t<PageId>>(id)];
	}
};

} // namespace MetaModule
