#include "doctest.h"
#include "patch_file/patch_list_helper.hh"

TEST_CASE("base_dir") {
	using namespace MetaModule;
	PatchDirList pdl;

	auto &vol = pdl.volume_root(Volume::USB);
	vol.name = "USB root";

	vol.files.emplace_back("banana.yml", 1, 12222021, "banana");
	vol.files.emplace_back("abc.txt", 123, 12232021, "abc");

	auto &d1 = vol.dirs.emplace_back();

	d1.name = "/Dir1";
	d1.files.emplace_back("abc.txt", 124, 12242021, "abc");
	d1.files.emplace_back("def.txt", 456, 12252021, "def");

	auto &d2 = vol.dirs.emplace_back();
	d2.name = "/Dir2";
	d2.files.emplace_back("xyz2.yml", 998, 12272021, "xyz2");
	d2.files.emplace_back("xyz.yml", 999, 12272021, "xyz");
	d2.files.emplace_back("abc.txt", 125, 12262021, "abc");

	PatchListHelper patch_list_helper{pdl};

	auto abc_root = patch_list_helper.base_dir(Volume::USB, "abc.txt");
	CHECK(abc_root.name == "USB root");

	auto dir1abc_root = patch_list_helper.base_dir(Volume::USB, "Dir1/abc.txt");
	CHECK(dir1abc_root.name == "/Dir1");

	{
		auto tree = patch_list_helper.base_dir(Volume::USB, "/Dir2/xyz2.yml");
		CHECK(tree.name == "/Dir2");
	}
	{
		auto tree = patch_list_helper.base_dir(Volume::USB, "Dir2/abc.txt");
		CHECK(tree.name == "/Dir2");
	}
	{
		auto tree = patch_list_helper.base_dir(Volume::USB, "Dir3/abc.txt");
		CHECK(tree.name == "USB root");
	}
}

TEST_CASE("file_name") {
	using namespace MetaModule;

	std::string a = "/Dir1/filen.yml";
	CHECK(PatchListHelper::file_name(a) == "filen.yml");

	std::string b = "Dir1/filen.yml";
	CHECK(PatchListHelper::file_name(b) == "filen.yml");

	std::string c = "/Dir1/AnotherDir/filen.yml";
	CHECK(PatchListHelper::file_name(c) == "filen.yml");

	std::string d = "filen.yml";
	CHECK(PatchListHelper::file_name(d) == "filen.yml");

	std::string e = "/Dir1/";
	CHECK(PatchListHelper::file_name(e) == "");

	std::string f = "/filename.yml";
	CHECK(PatchListHelper::file_name(f) == "filename.yml");
}
