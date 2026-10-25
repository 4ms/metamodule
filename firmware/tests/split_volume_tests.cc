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
