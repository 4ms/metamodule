#include "doctest.h"

#include "../src/fw_update/manifest_parse.hh"

TEST_CASE("Parse json") {
	MetaModule::ManifestParser p;

	std::string test_json = R"({
"version": 123,
"files": [
	{
		"type": "app",
		"filename": "metamodule-main-v1.2.3.uimg",
		"filesize": 1234567,
		"md5": "abaa17e7f9d854b402fc97aa26182f7c",
		"version":
		{
			"major": 5,
			"minor": 3
		}
	},
	{
		"type": "wifi",
		"filename": "metamodule-wifi-v1.0.2.uimg",
		"filesize": 7654321,
		"md5": "1234567890ABCDEFFEDCBA9876543210",
		"version":
		{
			"minor": 8,
			"revision": 1
		}
	},
	{
		"type": "BadFile",
		"filename": "metamodule-nope-v1.0.2.uimg",
		"filesize": 8888,
		"md5": "AAAABBBBCCCCDDDDEEEEFFFF11112222",
	}
]
})";

	auto manifest = p.parse(test_json);

	CHECK(manifest.version == 123);

	auto &files = manifest.files;

	CHECK(files.size() == 3);

	CHECK(files[0].type == MetaModule::UpdateType::App);
	CHECK(files[0].filename == "metamodule-main-v1.2.3.uimg");
	CHECK(files[0].filesize == 1234567);
	CHECK(files[0].md5[0] == 0xabaa17e7);
	CHECK(files[0].md5[1] == 0xf9d854b4);
	CHECK(files[0].md5[2] == 0x02fc97aa);
	CHECK(files[0].md5[3] == 0x26182f7c);
	CHECK(files[0].version.major == 5);
	CHECK(files[0].version.minor == 3);
	CHECK(files[0].version.revision == 0);

	CHECK(files[1].type == MetaModule::UpdateType::Wifi);
	CHECK(files[1].filename == "metamodule-wifi-v1.0.2.uimg");
	CHECK(files[1].filesize == 7654321);
	CHECK(files[1].md5[0] == 0x12345678);
	CHECK(files[1].md5[1] == 0x90ABCDEF);
	CHECK(files[1].md5[2] == 0xFEDCBA98);
	CHECK(files[1].md5[3] == 0x76543210);
	CHECK(files[1].version.major == 0);
	CHECK(files[1].version.minor == 8);
	CHECK(files[1].version.revision == 1);

	CHECK(files[2].type == MetaModule::UpdateType::Invalid);
	CHECK(files[2].filename == "metamodule-nope-v1.0.2.uimg");
	CHECK(files[2].filesize == 8888);
	CHECK(files[2].md5[0] == 0xAAAABBBB);
	CHECK(files[2].md5[1] == 0xCCCCDDDD);
	CHECK(files[2].md5[2] == 0xEEEEFFFF);
	CHECK(files[2].md5[3] == 0x11112222);
}
