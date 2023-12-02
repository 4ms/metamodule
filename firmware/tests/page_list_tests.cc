#include "doctest.h"

#include "gui/pages/page_list.hh"

using namespace MetaModule;

namespace MetaModule
{
struct PageBase {
public:
	PageId id;
};
} // namespace MetaModule

TEST_CASE("typical use case") {

	PageBase pagea{PageId::PatchSel};
	PageBase pageb{PageId::PatchView};
	PageBase pagec{PageId::ModuleView};
	PageBase paged{PageId::Settings};

	PageList::register_page(&pagea, pagea.id);
	PageList::register_page(&pageb, pageb.id);
	PageList::register_page(&pagec, pagec.id);
	PageList::register_page(&paged, paged.id);

	// printf("a = %p\n", &pagea);
	// printf("b = %p\n", &pageb);
	// printf("c = %p\n", &pagec);
	// printf("d = %p\n", &paged);

	PageArguments args{};

	std::optional<PageWithArgs> pwa;

	// printf("start at page a\n");
	PageList::request_initial_page(pagea.id, args);

	pwa = PageList::get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagea);

	// printf("page a gets a ui event, requests page b\n");
	PageList::request_new_page(pageb.id, args);
	//pageManager gets the page and jumps to it
	pwa = PageList::get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pageb);

	// printf("page b gets a ui event to go back (to pagea)\n");
	CHECK(PageList::request_last_page());
	pwa = PageList::get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagea);

	// printf("page a gets a ui event to go to page c\n");
	PageList::request_new_page(pagec.id, args);
	//pageManager gets the page and jumps to it
	pwa = PageList::get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagec);

	// printf("page c gets a ui event to go to page d\n");
	PageList::request_new_page(paged.id, args);
	//pageManager gets the page and jumps to it
	pwa = PageList::get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &paged);

	// printf("page d gets a ui event to go back multiple times\n");
	// d -> c -> a -> stop
	CHECK(PageList::request_last_page());
	pwa = PageList::get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagec);

	CHECK(PageList::request_last_page());
	pwa = PageList::get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagea);

	CHECK_FALSE(PageList::request_last_page());
	pwa = PageList::get_requested_page();
	CHECK(!pwa.has_value());
}

TEST_CASE("request_new_page() without get_requested() will still add to the history") {
	PageList::clear_history();

	PageBase pagea{PageId::PatchSel};
	PageBase pageb{PageId::PatchView};

	PageList::register_page(&pagea, pagea.id);
	PageList::register_page(&pageb, pageb.id);

	PageArguments args{};
	std::optional<PageWithArgs> pwa;

	PageList::request_new_page(pagea.id, args);
	//Oops! didn't actually jump to page a, since we didn't ever call get_requested_page()
	PageList::request_new_page(pageb.id, args);

	pwa = PageList::get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pageb);
	CHECK(PageList::request_last_page());

	//Here we see page a is still in the history
	//Bug? Should it be fixed? Doesn't matter?
	pwa = PageList::get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagea);
}

TEST_CASE("Push arguments") {
	PageList::clear_history();

	PageBase pagea{PageId::PatchSel};
	PageBase pageb{PageId::PatchView};
	PageBase pagec{PageId::ModuleView};
	PageBase paged{PageId::Settings};

	PageList::register_page(&pagea, pagea.id);
	PageList::register_page(&pageb, pageb.id);
	PageList::register_page(&pagec, pagec.id);
	PageList::register_page(&paged, paged.id);

	std::optional<PageWithArgs> pwa;

	// Can use empty args
	PageList::request_new_page(pagea.id, {});
	pwa = PageList::get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == std::nullopt);

	// Can set some args
	PageList::request_new_page(pagea.id, {.module_id = 2});
	pwa = PageList::get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == 2);
	CHECK(pwa->args->mappedknob_id == std::nullopt);

	PageList::request_new_page(pagea.id, {.module_id = 3, .mappedknob_id = 5});
	pwa = PageList::get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == 3);
	CHECK(pwa->args->mappedknob_id == 5);

	PageList::request_new_page(pagea.id, {.view_knobset_id = 9});
	pwa = PageList::get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == std::nullopt);
	CHECK(pwa->args->mappedknob_id == std::nullopt);
	CHECK(pwa->args->view_knobset_id == 9);

	//History works
	PageList::request_last_page();
	pwa = PageList::get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == 3);
	CHECK(pwa->args->mappedknob_id == 5);

	PageList::request_last_page();
	pwa = PageList::get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == 2);
	CHECK(pwa->args->mappedknob_id == std::nullopt);

	PageList::request_last_page();
	pwa = PageList::get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == std::nullopt);
}
