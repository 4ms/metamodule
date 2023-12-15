#include "doctest.h"

#include "../src/fw_update/manifest_parse.hh"

TEST_CASE("Parse json") {
	MetaModule::ManifestParser p;

	std::string test_json = R"({
"updates": [
	{
		"type": "app",
		"filename": "metamodule-main-v1.2.3.uimg",
		"filesize": 1234567,
		"md5": "abaa17e7f9d854b402fc97aa26182f7c"
	},
	{
		"type": "wifi",
		"filename": "metamodule-wifi-v1.0.2.uimg",
		"filesize": 7654321,
		"md5": "1234567890ABCDEFFEDCBA9876543210"
	},
	{
		"type": "BadFile",
		"filename": "metamodule-nope-v1.0.2.uimg",
		"filesize": 8888,
		"md5": "AAAABBBBCCCCDDDDEEEEFFFF11112222",
	}
]
})";

	p.parse(test_json);

	CHECK(p.files.size() == 3);

	CHECK(p.files[0].type == MetaModule::UpdateType::App);
	CHECK(p.files[0].filename == "metamodule-main-v1.2.3.uimg");
	CHECK(p.files[0].filesize == 1234567);
	CHECK(p.files[0].md5[0] == 0xabaa17e7);
	CHECK(p.files[0].md5[1] == 0xf9d854b4);
	CHECK(p.files[0].md5[2] == 0x02fc97aa);
	CHECK(p.files[0].md5[3] == 0x26182f7c);

	CHECK(p.files[1].type == MetaModule::UpdateType::Wifi);
	CHECK(p.files[1].filename == "metamodule-wifi-v1.0.2.uimg");
	CHECK(p.files[1].filesize == 7654321);
	CHECK(p.files[1].md5[0] == 0x12345678);
	CHECK(p.files[1].md5[1] == 0x90ABCDEF);
	CHECK(p.files[1].md5[2] == 0xFEDCBA98);
	CHECK(p.files[1].md5[3] == 0x76543210);

	CHECK(p.files[2].type == MetaModule::UpdateType::Invalid);
	CHECK(p.files[2].filename == "metamodule-nope-v1.0.2.uimg");
	CHECK(p.files[2].filesize == 8888);
	CHECK(p.files[2].md5[0] == 0xAAAABBBB);
	CHECK(p.files[2].md5[1] == 0xCCCCDDDD);
	CHECK(p.files[2].md5[2] == 0xEEEEFFFF);
	CHECK(p.files[2].md5[3] == 0x11112222);
}
