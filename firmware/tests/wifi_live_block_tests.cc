#include "doctest.h"
#include "wifi/wifi_live_block.hh"

using namespace MetaModule;

TEST_CASE("published live data reads back") {
	WifiLiveBlock block;

	WifiLiveData data{};
	data.patch_name.copy("My Patch");
	data.playing = true;
	data.modules_valid = true;
	data.overhead = 41;
	data.num_modules = 3;
	data.modules[1] = 123;
	data.modules[2] = 7;
	data.module_cores[1] = 0;
	data.module_cores[2] = 1;
	data.core_loads = {210, 255};
	block.publish(data);

	auto read = block.read();
	REQUIRE(read.has_value());
	CHECK(std::string_view{read->patch_name} == "My Patch");
	CHECK(read->playing);
	CHECK(read->modules_valid);
	CHECK(read->overhead == 41);
	CHECK(read->num_modules == 3);
	CHECK(read->modules[1] == 123);
	CHECK(read->modules[2] == 7);
	CHECK(read->module_cores[2] == 1);
	CHECK(read->core_loads[0] == 210);
	CHECK(read->core_loads[1] == 255);
}

TEST_CASE("nothing published yet reads as not playing") {
	WifiLiveBlock block;
	auto read = block.read();
	REQUIRE(read.has_value());
	CHECK_FALSE(read->playing);
	CHECK_FALSE(read->modules_valid);
	CHECK(read->num_modules == 0);
}

TEST_CASE("read during a write gives up instead of returning torn data") {
	WifiLiveBlock block;
	block.data_seq = 1; // odd: writer mid-update
	CHECK_FALSE(block.read().has_value());
}

TEST_CASE("reset clears what was left in memory from before a reboot") {
	WifiLiveBlock block;
	block.data_seq = 7; // odd: would block reading forever
	block.detail_request_count = 9;

	block.reset();

	CHECK(block.read().has_value());
	CHECK(block.detail_requests() == 0);
}

TEST_CASE("detail requests are counted") {
	WifiLiveBlock block;
	CHECK(block.detail_requests() == 0);
	block.request_detail();
	block.request_detail();
	CHECK(block.detail_requests() == 2);
}
