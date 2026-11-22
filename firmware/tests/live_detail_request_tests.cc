#include "doctest.h"
#include "wifi/live_detail_request.hh"

using MetaModule::LiveDetailRequest;

TEST_CASE("no detail until the first request") {
	LiveDetailRequest req;
	CHECK_FALSE(req.update(0, 0));
	CHECK_FALSE(req.update(0, 10'000));
}

TEST_CASE("a request keeps detail on for 3 seconds") {
	LiveDetailRequest req;
	CHECK(req.update(1, 1000));
	CHECK(req.update(1, 3999));
	CHECK(req.update(1, 4000));
	CHECK_FALSE(req.update(1, 4001));
}

TEST_CASE("each new request restarts the timeout") {
	LiveDetailRequest req;
	CHECK(req.update(1, 1000));
	CHECK(req.update(2, 3500));
	CHECK(req.update(2, 6000));
	CHECK_FALSE(req.update(2, 6501));
	CHECK(req.update(3, 7000));
}

TEST_CASE("timer wrap-around") {
	LiveDetailRequest req;
	CHECK(req.update(5, 0xFFFF'FF00));
	CHECK(req.update(5, 100)); // 356 ms later
	CHECK_FALSE(req.update(5, 3000));
}
