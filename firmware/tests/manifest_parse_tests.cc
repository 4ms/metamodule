#include "doctest.h"

#include "../src/fw_update/manifest_parse.hh"
#include <string_view>

namespace TestRymlInit
{
void init_once() {
	static bool already_init = false;
	static c4::yml::Callbacks callbacks;
	if (!already_init) {
		already_init = true;
		callbacks.m_error = [](const char *msg, size_t /*msg_len*/, c4::yml::Location loc, void * /*user_data*/) {
			//ignore errors
		};
		c4::yml::set_callbacks(callbacks);
	}
}
} // namespace TestRymlInit

TEST_CASE("Parse json") {
	TestRymlInit::init_once();

	MetaModule::ManifestParser p;

	std::string test_json = R"({
"version": 123,
"files": [
	{
		"type": "app",
		"name": "Main Application",
		"filename": "metamodule-main-v1.2.3.uimg",
		"filesize": 1234567,
		"md5": "abaa17e7f9d854b402fc97aa26182f7c",
		"address": 1234
	},
	{
		"type": "BadFile",
		"filename": "notfound.uimg",
		"filesize": 8888,
		"md5": "AAAABBBBCCCCDDDDEEEEFFFF11112222",
	},
	{
		"unknownKey": "invalid",
	},
	{
	},
	{
		"type": "wifi",
		"filename": "metamodule-wifi-v1.0.2.uimg",
		"filesize": 7654321,
		"md5": "1234567890ABCDEFFEDCBA9876543210",
	}
]
})";

	auto manifest = p.parse(test_json);

	CHECK(manifest.has_value());

	CHECK(manifest->version == 123);

	auto &files = manifest->files;

	CHECK(files.size() == 2);

	using namespace std::string_view_literals;

	CHECK(files[0].type == MetaModule::UpdateType::App);
	CHECK(files[0].filename == "metamodule-main-v1.2.3.uimg");
	CHECK(files[0].filesize == 1234567);
	CHECK(files[0].md5 == "abaa17e7f9d854b402fc97aa26182f7c"sv);
	CHECK(files[0].address == 1234);

	CHECK(files[1].type == MetaModule::UpdateType::Wifi);
	CHECK(files[1].filename == "metamodule-wifi-v1.0.2.uimg");
	CHECK(files[1].filesize == 7654321);
	CHECK(files[1].md5 == "1234567890ABCDEFFEDCBA9876543210"sv);
	CHECK(files[1].address == 0xFFFFFFFF);
}
