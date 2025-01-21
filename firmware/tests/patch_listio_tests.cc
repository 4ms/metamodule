#include "doctest.h"
#include "patch_file/patch_listio.hh"

TEST_CASE("base_dir") {
	using namespace MetaModule;
	PatchDirList pdl;

	auto &vol = pdl.volume_root(Volume::USB);
	vol.name = "USB root";

	vol.files.emplace_back("banana.yml", 1, 12222021, "banana");
	vol.files.emplace_back("abc.txt", 123, 12232021, "abc");

	auto &d1 = vol.dirs.emplace_back();

	d1.name = "Dir1";
	d1.files.emplace_back("abc.txt", 124, 12242021, "abc");
	d1.files.emplace_back("def.txt", 456, 12252021, "def");

	auto &d2 = vol.dirs.emplace_back();
	d2.name = "Dir2";
	d2.files.emplace_back("xyz.yml", 999, 12272021, "xyz");
	d2.files.emplace_back("abc.txt", 125, 12262021, "abc");
	d2.files.emplace_back("xyz2.yml", 998, 12272021, "xyz2");

	auto abc_root = PatchListIO::base_dir(pdl, Volume::USB, "abc.txt");
	CHECK(abc_root.name == "USB root");
	CHECK(abc_root.files[1].filename == "abc.txt");
	CHECK(abc_root.files[1].filesize == 123);

	auto dir1abc_root = PatchListIO::base_dir(pdl, Volume::USB, "Dir1/abc.txt");
	CHECK(dir1abc_root.name == "Dir1");
	CHECK(dir1abc_root.files[0].filename == "abc.txt");
	CHECK(dir1abc_root.files[0].filesize == 124);

	auto dir2abc_root = PatchListIO::base_dir(pdl, Volume::USB, "Dir2/abc.txt");
	CHECK(dir2abc_root.name == "Dir2");
	CHECK(dir2abc_root.files[1].filename == "abc.txt");
	CHECK(dir2abc_root.files[1].filesize == 125);
}
