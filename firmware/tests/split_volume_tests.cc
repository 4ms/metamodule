#include "doctest.h"
#include "fs/helpers.hh"

using namespace MetaModule;

TEST_CASE("split_volume: volume prefix and leading slash are stripped") {
	auto check = [](std::string_view fullpath, std::string_view expected_path, Volume expected_vol) {
		auto [path, vol] = split_volume(fullpath);
		CHECK(path == expected_path);
		CHECK(vol == expected_vol);
	};

	check("sdc:/dir/patch.yml", "dir/patch.yml", Volume::SDCard);
	check("sdc:dir/patch.yml", "dir/patch.yml", Volume::SDCard);
	check("usb:/patch.yml", "patch.yml", Volume::USB);
	check("ram:/patch.yml", "patch.yml", Volume::RamDisk);
	check("nor:/patch.yml", "patch.yml", Volume::NorFlash);

	SUBCASE("Alternative labels") {
		check("USB:/patch.yml", "patch.yml", Volume::USB);
		check("SD Card:/dir/patch.yml", "dir/patch.yml", Volume::SDCard);
		check("Internal:/patch.yml", "patch.yml", Volume::NorFlash);
	}

	SUBCASE("Only one leading slash is stripped") {
		check("sdc://dir", "/dir", Volume::SDCard);
	}
}

TEST_CASE("split_volume: no volume prefix defaults to RamDisk and keeps the path as-is") {
	auto [path, vol] = split_volume("/dir/patch.yml");
	CHECK(path == "/dir/patch.yml");
	CHECK(vol == Volume::RamDisk);
}

TEST_CASE("split_volume: empty paths") {
	SUBCASE("Volume prefix only") {
		auto [path, vol] = split_volume("sdc:");
		CHECK(path.empty());
		CHECK(vol == Volume::SDCard);
	}

	SUBCASE("Volume prefix and slash") {
		auto [path, vol] = split_volume("usb:/");
		CHECK(path.empty());
		CHECK(vol == Volume::USB);
	}

	SUBCASE("Empty string") {
		auto [path, vol] = split_volume("");
		CHECK(path.empty());
		CHECK(vol == Volume::RamDisk);
	}
}

TEST_CASE("split_volume: path from a C string is still null-terminated") {
	// Callers pass path.data() to FatFS, which expects a C string
	const char *fullpath = "sdc:/dir/patch.yml";
	auto [path, vol] = split_volume(fullpath);
	CHECK(path.data() == fullpath + 5);
	CHECK(path.data()[path.size()] == '\0');
}

TEST_CASE("split_volume + make_full_path: rebuilds the path with the volume's canonical prefix") {
	// The syscalls rebuild SD Card and USB paths this way for FatFS on the M4,
	// which needs the prefix to pick the drive
	auto rebuild = [](std::string_view fullpath) {
		auto [path, vol] = split_volume(fullpath);
		return make_full_path(vol, path);
	};

	CHECK(rebuild("sdc:/dir/patch.yml") == "sdc:/dir/patch.yml");
	CHECK(rebuild("sdc:dir/patch.yml") == "sdc:/dir/patch.yml");
	CHECK(rebuild("usb:/dir/") == "usb:/dir/");
	CHECK(rebuild("SD Card:/dir/patch.yml") == "sdc:/dir/patch.yml");
	CHECK(rebuild("USB:/patch.yml") == "usb:/patch.yml");
	CHECK(rebuild("sdc:/") == "sdc:/");
	CHECK(rebuild("usb:") == "usb:/");
}

TEST_CASE("make_full_path: '..' can't go above the volume root") {
	// Without the prefix, FatFS on the M4 would use whichever drive was used last
	CHECK(make_full_path(Volume::SDCard, "../x") == "sdc:/x");
	CHECK(make_full_path(Volume::SDCard, "a/../../x") == "sdc:/x");
	CHECK(make_full_path(Volume::SDCard, "..") == "sdc:/");
	CHECK(make_full_path(Volume::USB, "a/..") == "usb:/");
	CHECK(make_full_path(Volume::USB, "a/../b/./c/") == "usb:/b/c/");
	CHECK(make_full_path(Volume::SDCard, "/a//b") == "sdc:/a/b");
	CHECK(make_full_path(Volume::SDCard, "") == "sdc:/");
}

TEST_CASE("make_full_path(dir, file): joins a dir and a file name") {
	CHECK(make_full_path("", "p.yml") == "/p.yml");
	CHECK(make_full_path("", "") == "/");
	CHECK(make_full_path("dir", "p.yml") == "dir/p.yml");
	CHECK(make_full_path("dir/", "p.yml") == "dir/p.yml");
	CHECK(make_full_path("dir", "") == "dir/");
	CHECK(make_full_path("/dir", "p.yml") == "/dir/p.yml");
	CHECK(make_full_path("a/./b", "x/p.yml") == "a/b/x/p.yml");
}

TEST_CASE("make_full_path(dir, file): '..' can't go above the volume root") {
	CHECK(make_full_path("..", "p.yml") == "p.yml"); // was "..p.yml"
	CHECK(make_full_path("../x", "p.yml") == "x/p.yml");
	CHECK(make_full_path("a/../..", "") == "/");
	CHECK(make_full_path("", "../p.yml") == "/p.yml");
	CHECK(make_full_path("dir", "../p.yml") == "p.yml");
	CHECK(make_full_path("a/b", "../p.yml") == "a/p.yml");
}

TEST_CASE("make_full_path(vol, dir, file): '..' can't go above the volume root") {
	CHECK(make_full_path(Volume::SDCard, "", "p.yml") == "sdc:/p.yml");
	CHECK(make_full_path(Volume::SDCard, "dir", "p.yml") == "sdc:/dir/p.yml");
	CHECK(make_full_path(Volume::USB, "dir", "") == "usb:/dir/");
	CHECK(make_full_path(Volume::SDCard, "..", "p.yml") == "sdc:/p.yml");
	CHECK(make_full_path(Volume::SDCard, "../x", "p.yml") == "sdc:/x/p.yml");
	CHECK(make_full_path(Volume::SDCard, "", "../p.yml") == "sdc:/p.yml");
	CHECK(make_full_path(Volume::USB, "a/../..", "") == "usb:/");
}
