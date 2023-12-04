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
	PageList page_list;

	page_list.register_page(&pagea, pagea.id);
	page_list.register_page(&pageb, pageb.id);
	page_list.register_page(&pagec, pagec.id);
	page_list.register_page(&paged, paged.id);

	// printf("a = %p\n", &pagea);
	// printf("b = %p\n", &pageb);
	// printf("c = %p\n", &pagec);
	// printf("d = %p\n", &paged);

	PageArguments args{};

	std::optional<PageWithArgs> pwa;

	// printf("start at page a\n");
	page_list.request_initial_page(pagea.id, args);

	pwa = page_list.get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagea);

	// printf("page a gets a ui event, requests page b\n");
	page_list.request_new_page(pageb.id, args);
	//pageManager gets the page and jumps to it
	pwa = page_list.get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pageb);

	// printf("page b gets a ui event to go back (to pagea)\n");
	CHECK(page_list.request_last_page());
	pwa = page_list.get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagea);

	// printf("page a gets a ui event to go to page c\n");
	page_list.request_new_page(pagec.id, args);
	//pageManager gets the page and jumps to it
	pwa = page_list.get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagec);

	// printf("page c gets a ui event to go to page d\n");
	page_list.request_new_page(paged.id, args);
	//pageManager gets the page and jumps to it
	pwa = page_list.get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &paged);

	// printf("page d gets a ui event to go back multiple times\n");
	// d -> c -> a -> stop
	CHECK(page_list.request_last_page());
	pwa = page_list.get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagec);

	CHECK(page_list.request_last_page());
	pwa = page_list.get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagea);

	CHECK_FALSE(page_list.request_last_page());
	pwa = page_list.get_requested_page();
	CHECK(!pwa.has_value());
}

TEST_CASE("request_new_page() without get_requested() will still add to the history") {
	PageList page_list;

	page_list.clear_history();

	PageBase pagea{PageId::PatchSel};
	PageBase pageb{PageId::PatchView};

	page_list.register_page(&pagea, pagea.id);
	page_list.register_page(&pageb, pageb.id);

	PageArguments args{};
	std::optional<PageWithArgs> pwa;

	page_list.request_new_page(pagea.id, args);
	//Oops! didn't actually jump to page a, since we didn't ever call get_requested_page()
	page_list.request_new_page(pageb.id, args);

	pwa = page_list.get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pageb);
	CHECK(page_list.request_last_page());

	//Here we see page a is still in the history
	//Bug? Should it be fixed? Doesn't matter?
	pwa = page_list.get_requested_page();
	CHECK(pwa);
	CHECK(pwa->page == &pagea);
}

TEST_CASE("Push arguments") {
	PageList page_list;
	page_list.clear_history();

	PageBase pagea{PageId::PatchSel};
	PageBase pageb{PageId::PatchView};
	PageBase pagec{PageId::ModuleView};
	PageBase paged{PageId::Settings};

	page_list.register_page(&pagea, pagea.id);
	page_list.register_page(&pageb, pageb.id);
	page_list.register_page(&pagec, pagec.id);
	page_list.register_page(&paged, paged.id);

	std::optional<PageWithArgs> pwa;

	// Can use empty args
	page_list.request_new_page(pagea.id, {});
	pwa = page_list.get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == std::nullopt);

	// Can set some args
	page_list.request_new_page(pagea.id, {.module_id = 2});
	pwa = page_list.get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == 2);
	CHECK(pwa->args->mappedknob_id == std::nullopt);

	page_list.request_new_page(pagea.id, {.module_id = 3, .mappedknob_id = 5});
	pwa = page_list.get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == 3);
	CHECK(pwa->args->mappedknob_id == 5);

	page_list.request_new_page(pagea.id, {.view_knobset_id = 9});
	pwa = page_list.get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == std::nullopt);
	CHECK(pwa->args->mappedknob_id == std::nullopt);
	CHECK(pwa->args->view_knobset_id == 9);

	//History works
	page_list.request_last_page();
	pwa = page_list.get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == 3);
	CHECK(pwa->args->mappedknob_id == 5);

	page_list.request_last_page();
	pwa = page_list.get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == 2);
	CHECK(pwa->args->mappedknob_id == std::nullopt);

	page_list.request_last_page();
	pwa = page_list.get_requested_page();
	CHECK(pwa->args->patch_loc == std::nullopt);
	CHECK(pwa->args->module_id == std::nullopt);
}
