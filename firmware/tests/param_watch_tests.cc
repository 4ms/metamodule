#include "doctest.h"

#include "src/patch_play/param_watch.hh"

TEST_CASE("ranges") {
	using namespace MetaModule;

	ParamWatcher pw;

	CHECK(pw.active_watched_params().size() == 1);

	{
		pw.start_watching_param(1, 2);
		auto a = pw.active_watched_params();
		CHECK(a.size() == 1);
		CHECK(a[0].module_id == 1);
	}

	{
		pw.start_watching_param(3, 4);
		auto a = pw.active_watched_params();
		CHECK(a.size() == 2);
		CHECK(a[0].module_id == 1);
		CHECK(a[1].module_id == 3);
	}

	{
		pw.start_watching_param(5, 6);
		auto a = pw.active_watched_params();
		CHECK(a.size() == 3);
	}

	{
		pw.start_watching_param(7, 8);
		auto a = pw.active_watched_params();
		CHECK(a.size() == 4);
	}

	{
		pw.stop_watching_param(3, 4);
		auto a = pw.active_watched_params();
		// Still has four because we removed one in the middle
		CHECK(a.size() == 4);
		CHECK(a[0].module_id == 1);
		CHECK(a[1].is_active() == false);
		CHECK(a[2].module_id == 5);
		CHECK(a[3].module_id == 7);
	}

	{
		pw.stop_watching_param(7, 8);
		auto a = pw.active_watched_params();
		// Now has three because we removed one at the end
		CHECK(a.size() == 3);
		CHECK(a[0].module_id == 1);
		CHECK(a[1].is_active() == false);
		CHECK(a[2].module_id == 5);
	}

	{
		pw.start_watching_param(9, 10);
		auto a = pw.active_watched_params();
		// Still has 3 because we replaced the first inactive
		CHECK(a.size() == 3);
		CHECK(a[0].module_id == 1);
		CHECK(a[1].module_id == 9);
		CHECK(a[2].module_id == 5);
	}

	{
		pw.stop_watching_param(1, 2);
		auto a = pw.active_watched_params();
		// Now has 2 because we removed the first (and the span slides up)
		CHECK(a.size() == 2);
		CHECK(a[0].module_id == 9);
		CHECK(a[1].module_id == 5);
	}
}
