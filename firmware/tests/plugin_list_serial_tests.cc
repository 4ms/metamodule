// Tests for the flat form of PluginFileList that crosses cores on MP2 (dynload/plugin_list_serial.hh)
#include "doctest.h"
#include "dynload/plugin_list_serial.hh"
#include <array>
#include <memory>

using namespace MetaModule;

TEST_CASE("PluginFileList round-trips and replaces the destination") {
	std::array<char, 4096> buf;
	PluginListSerial::Writer w{buf};
	CHECK(w.max_size() == MaxPlugins);
	CHECK(w.push_back({Volume::USB, "metamodule-plugins/BrandX-v1.2.3.mm2plugin", "BrandX-v1.2.3", 123456, ""}));
	CHECK(w.push_back({Volume::SDCard, "/Other.mm2plugin", "Other", 42, "0.9"}));
	auto bytes = w.finish();
	REQUIRE(bytes > 0);

	// Big: on the heap
	auto dst = std::make_unique<PluginFileList>();
	dst->push_back({Volume::USB, "stale", "stale", 1, ""});

	REQUIRE(PluginListSerial::deserialize(std::span{buf}.first(bytes), *dst));
	REQUIRE(dst->size() == 2);

	auto &a = (*dst)[0];
	CHECK(a.vol == Volume::USB);
	CHECK(std::string_view(a.full_path) == "metamodule-plugins/BrandX-v1.2.3.mm2plugin");
	CHECK(std::string_view(a.plugin_name) == "BrandX-v1.2.3");
	CHECK(a.file_size == 123456);
	CHECK(std::string_view(a.version_in_filename) == "");

	auto &b = (*dst)[1];
	CHECK(b.vol == Volume::SDCard);
	CHECK(std::string_view(b.full_path) == "/Other.mm2plugin");
	CHECK(std::string_view(b.plugin_name) == "Other");
	CHECK(b.file_size == 42);
	CHECK(std::string_view(b.version_in_filename) == "0.9");
}

TEST_CASE("Empty PluginFileList") {
	std::array<char, 16> buf;
	PluginListSerial::Writer w{buf};
	auto bytes = w.finish();
	REQUIRE(bytes == 8);

	auto dst = std::make_unique<PluginFileList>();
	REQUIRE(PluginListSerial::deserialize(std::span{buf}.first(bytes), *dst));
	CHECK(dst->size() == 0);
}

TEST_CASE("A plugin that doesn't fit is dropped, and the ones before it are kept") {
	// Room for the header (8 bytes) and two short entries (32 bytes each), not a long one
	std::array<char, 80> buf;
	PluginListSerial::Writer w{buf};
	CHECK(w.push_back({Volume::USB, "a.mm2plugin", "a", 1, ""}));
	CHECK_FALSE(w.push_back({Volume::USB, std::string(100, 'x').c_str(), "x", 2, ""}));
	CHECK(w.push_back({Volume::SDCard, "b.mm2plugin", "b", 3, ""}));
	auto bytes = w.finish();
	REQUIRE(bytes > 0);

	auto dst = std::make_unique<PluginFileList>();
	REQUIRE(PluginListSerial::deserialize(std::span{buf}.first(bytes), *dst));
	REQUIRE(dst->size() == 2);
	CHECK(std::string_view((*dst)[0].plugin_name) == "a");
	CHECK(std::string_view((*dst)[1].plugin_name) == "b");
}

TEST_CASE("No more than MaxPlugins") {
	std::vector<char> buf(64 * 1024);
	PluginListSerial::Writer w{buf};
	for (auto i = 0u; i < MaxPlugins; i++)
		CHECK(w.push_back({Volume::USB, "p.mm2plugin", "p", i, ""}));
	CHECK_FALSE(w.push_back({Volume::USB, "p.mm2plugin", "p", 0, ""}));
	auto bytes = w.finish();

	auto dst = std::make_unique<PluginFileList>();
	REQUIRE(PluginListSerial::deserialize(std::span{buf}.first(bytes), *dst));
	CHECK(dst->size() == MaxPlugins);
	CHECK((*dst)[MaxPlugins - 1].file_size == MaxPlugins - 1);
}

TEST_CASE("Buffer too small for the header") {
	std::array<char, 4> buf;
	PluginListSerial::Writer w{buf};
	CHECK(w.finish() == 0);
}

TEST_CASE("Corrupt plugin lists are rejected") {
	std::array<char, 256> buf;
	PluginListSerial::Writer w{buf};
	w.push_back({Volume::USB, "a.mm2plugin", "a", 1, ""});
	auto bytes = w.finish();

	auto dst = std::make_unique<PluginFileList>();

	SUBCASE("truncated") {
		CHECK_FALSE(PluginListSerial::deserialize(std::span{buf}.first(bytes - 1), *dst));
	}

	SUBCASE("wrong magic") {
		buf[0] ^= 1;
		CHECK_FALSE(PluginListSerial::deserialize(std::span{buf}.first(bytes), *dst));
	}

	SUBCASE("bad volume") {
		uint32_t vol = static_cast<uint32_t>(Volume::MaxVolumes);
		std::memcpy(buf.data() + 8, &vol, sizeof vol);
		CHECK_FALSE(PluginListSerial::deserialize(std::span{buf}.first(bytes), *dst));
	}

	SUBCASE("count too big for the buffer") {
		uint32_t count = 1000;
		std::memcpy(buf.data() + 4, &count, sizeof count);
		CHECK_FALSE(PluginListSerial::deserialize(std::span{buf}.first(bytes), *dst));
	}
}
