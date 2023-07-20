#include "doctest.h"

#include "gui/pages/page_list.hh"

using namespace MetaModule;

namespace MetaModule
{
struct PageBase {
public:
	int x;
};
} // namespace MetaModule

TEST_CASE("typical use case") {
	PageList::clear_history();

	PageBase pagea{1};
	PageBase pageb{2};
	PageBase pagec{3};
	PageBase paged{4};

	// printf("a = %p\n", &pagea);
	// printf("b = %p\n", &pageb);
	// printf("c = %p\n", &pagec);
	// printf("d = %p\n", &paged);

	// printf("start at page a\n");
	PageList::request_new_page(pagea);
	CHECK(PageList::get_requested_page().value_or(nullptr) == &pagea);

	// printf("page a gets a ui event, requests page b\n");
	PageList::request_new_page(pageb);
	//pageManager gets the page and jumps to it
	CHECK(PageList::get_requested_page().value_or(nullptr) == &pageb);

	// printf("page b gets a ui event to go back (to pagea)\n");
	CHECK(PageList::request_last_page());
	CHECK(PageList::get_requested_page().value_or(nullptr) == &pagea);

	// printf("page a gets a ui event to go to page c\n");
	PageList::request_new_page(pagec);
	//pageManager gets the page and jumps to it
	CHECK(PageList::get_requested_page().value_or(nullptr) == &pagec);

	// printf("page c gets a ui event to go to page d\n");
	PageList::request_new_page(paged);
	//pageManager gets the page and jumps to it
	CHECK(PageList::get_requested_page().value_or(nullptr) == &paged);

	// printf("page d gets a ui event to go back multiple times\n");
	// d -> c -> a -> stop
	CHECK(PageList::request_last_page());
	CHECK(PageList::get_requested_page().value_or(nullptr) == &pagec);
	CHECK(PageList::request_last_page());
	CHECK(PageList::get_requested_page().value_or(nullptr) == &pagea);

	CHECK_FALSE(PageList::request_last_page());
	CHECK(PageList::get_requested_page().value_or(nullptr) == nullptr);
}

TEST_CASE("request_new_page() without get_requested() will still add to the history") {
	PageList::clear_history();

	PageBase pagea{1};
	PageBase pageb{2};

	// printf("a = %p\n", &pagea);
	// printf("b = %p\n", &pageb);
	// printf("c = %p\n", &pagec);
	// printf("d = %p\n", &paged);

	PageList::request_new_page(pagea);
	//Oops! didn't actually jump to page a, since we didn't ever call get_requested_page()
	PageList::request_new_page(pageb);
	CHECK(PageList::get_requested_page().value_or(nullptr) == &pageb);
	CHECK(PageList::request_last_page());

	//Here we see page a is still in the history
	//Bug? Should it be fixed? Doesn't matter?
	CHECK(PageList::get_requested_page().value_or(nullptr) == &pagea);
}
