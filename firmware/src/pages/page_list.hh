#pragma once
#include <optional>
#include <vector>

namespace MetaModule
{

//forward declare
struct PageBase;

class PageList {
	static inline PageBase *_requested_page = nullptr;
	static inline bool _new_page_requested = false;
	static inline std::vector<PageBase *> _history;

public:
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
		if (_history.empty())
			return std::nullopt;

		auto back = _history.back();
		_history.pop_back();
		return back;
	}
};
} // namespace MetaModule
