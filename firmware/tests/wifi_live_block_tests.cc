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
	block.load_seq = 3;
	block.load_id = 42;
	block.load_loc = {"stale.yml", Volume::SDCard};
	block.detail_request_count = 9;

	block.reset();

	CHECK(block.read().has_value());
	uint32_t last_handled = 0;
	CHECK_FALSE(block.take_load_request(last_handled).has_value());
	CHECK(block.detail_requests() == 0);
}

TEST_CASE("no load request until one is made") {
	WifiLiveBlock block;
	uint32_t last_handled = 0;
	CHECK_FALSE(block.take_load_request(last_handled).has_value());
}

TEST_CASE("a load request is taken once") {
	WifiLiveBlock block;
	uint32_t last_handled = 0;

	block.request_load({"My Patch.yml", Volume::SDCard});

	auto req = block.take_load_request(last_handled);
	REQUIRE(req.has_value());
	CHECK(std::string_view{req->filename} == "My Patch.yml");
	CHECK(req->vol == Volume::SDCard);

	CHECK_FALSE(block.take_load_request(last_handled).has_value());

	block.request_load({"Other.yml", Volume::USB});
	req = block.take_load_request(last_handled);
	REQUIRE(req.has_value());
	CHECK(std::string_view{req->filename} == "Other.yml");
}

TEST_CASE("load request read during a write is retried later") {
	WifiLiveBlock block;
	uint32_t last_handled = 0;
	block.request_load({"My Patch.yml", Volume::SDCard});

	block.load_seq = block.load_seq + 1; // odd: writer mid-update
	CHECK_FALSE(block.take_load_request(last_handled).has_value());

	block.load_seq = block.load_seq + 1;
	CHECK(block.take_load_request(last_handled).has_value());
}

TEST_CASE("Wi-Fi load is skipped for the patch that's already playing") {
	PatchLocation sent{"My Patch.yml", Volume::SDCard};

	CHECK(needs_wifi_load(sent, std::nullopt));
	CHECK(needs_wifi_load(sent, PatchLocation{"Other.yml", Volume::SDCard}));
	CHECK(needs_wifi_load(sent, PatchLocation{"My Patch.yml", Volume::USB}));
	// Already playing: the file change checker reloads it
	CHECK_FALSE(needs_wifi_load(sent, PatchLocation{"My Patch.yml", Volume::SDCard}));
}

TEST_CASE("detail requests are counted") {
	WifiLiveBlock block;
	CHECK(block.detail_requests() == 0);
	block.request_detail();
	block.request_detail();
	CHECK(block.detail_requests() == 2);
}
