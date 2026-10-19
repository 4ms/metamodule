// Tests for the flat form of PatchDirList and DirTree<FileEntry> that crosses cores on MP2
// (patch_file/dir_list_serial.hh)
#include "doctest.h"
#include "patch_file/dir_list_serial.hh"
#include <array>

using namespace MetaModule;

TEST_CASE("PatchDirList round-trips, with copy_patchlist() semantics") {
	PatchDirList src;
	src.mark_mounted(Volume::SDCard, true);
	src.mark_mounted(Volume::NorFlash, true);
	auto &sd = src.volume_root(Volume::SDCard);
	sd.name = "SD root";
	sd.files.emplace_back("a.yml", 100, 1111, "Patch A");
	sd.files.emplace_back("b.yml", 200, 2222, "Patch B", Volume::USB);
	auto &dir = sd.dirs.emplace_back("/drums");
	dir.files.emplace_back("kick.yml", 300, 3333, "Kick");
	src.volume_root(Volume::NorFlash).files.emplace_back("default.yml", 400, 4444, "Default");

	std::array<char, 4096> buf;
	auto bytes = DirListSerial::serialize(src, buf);
	REQUIRE(bytes > 0);

	PatchDirList dst;
	// Stale entries in volumes the fs core owns are replaced; the A-core's RamDisk entries are kept
	dst.volume_root(Volume::SDCard).files.emplace_back("stale.yml", 1, 1, "Stale");
	dst.volume_root(Volume::RamDisk).files.emplace_back("recent.yml", 5, 5, "Recent");

	REQUIRE(DirListSerial::deserialize(std::span{buf}.first(bytes), dst));

	CHECK(dst.is_mounted(Volume::SDCard));
	CHECK(dst.is_mounted(Volume::NorFlash));
	CHECK_FALSE(dst.is_mounted(Volume::USB));

	auto &dsd = dst.volume_root(Volume::SDCard);
	CHECK(dsd.name == "SD root");
	REQUIRE(dsd.files.size() == 2);
	CHECK(dsd.files[0].filename == "a.yml");
	CHECK(dsd.files[0].filesize == 100);
	CHECK(dsd.files[0].timestamp == 1111);
	CHECK(std::string_view(dsd.files[0].patchname) == "Patch A");
	CHECK_FALSE(dsd.files[0].link_vol.has_value());
	CHECK(dsd.files[1].link_vol == Volume::USB);
	REQUIRE(dsd.dirs.size() == 1);
	CHECK(dsd.dirs[0].name == "/drums");
	REQUIRE(dsd.dirs[0].files.size() == 1);
	CHECK(dsd.dirs[0].files[0].filename == "kick.yml");

	REQUIRE(dst.volume_root(Volume::NorFlash).files.size() == 1);
	CHECK(dst.volume_root(Volume::NorFlash).files[0].filename == "default.yml");

	REQUIRE(dst.volume_root(Volume::RamDisk).files.size() == 1);
	CHECK(dst.volume_root(Volume::RamDisk).files[0].filename == "recent.yml");
}

TEST_CASE("DirTree<FileEntry> round-trips and replaces the destination") {
	DirTree<FileEntry> src{"/samples"};
	src.files.push_back({"a.wav", 10, 20});
	src.files.push_back({"b.wav", 30, 40});
	src.dirs.push_back({"loops"});
	src.dirs.push_back({"one-shots"});

	std::array<char, 1024> buf;
	auto bytes = DirListSerial::serialize(src, buf);
	REQUIRE(bytes > 0);

	DirTree<FileEntry> dst;
	dst.files.push_back({"stale.wav", 1, 1});

	REQUIRE(DirListSerial::deserialize(std::span{buf}.first(bytes), dst));
	CHECK(dst.name == "/samples");
	REQUIRE(dst.files.size() == 2);
	CHECK(dst.files[1].filename == "b.wav");
	CHECK(dst.files[1].filesize == 30);
	CHECK(dst.files[1].timestamp == 40);
	REQUIRE(dst.dirs.size() == 2);
	CHECK(dst.dirs[1].name == "one-shots");
}

TEST_CASE("Serializing into a buffer that's too small fails") {
	DirTree<FileEntry> src{"/"};
	for (int i = 0; i < 20; i++)
		src.files.push_back({"a-fairly-long-file-name.wav", 1, 2});

	std::array<char, 64> buf;
	CHECK(DirListSerial::serialize(src, buf) == 0);
}

TEST_CASE("Truncated, corrupt, or mismatched data is rejected") {
	DirTree<FileEntry> src{"/"};
	src.files.push_back({"a.wav", 1, 2});
	std::array<char, 256> buf;
	auto bytes = DirListSerial::serialize(src, buf);
	REQUIRE(bytes > 0);

	DirTree<FileEntry> dst;

	SUBCASE("truncated") {
		CHECK_FALSE(DirListSerial::deserialize(std::span{buf}.first(bytes - 1), dst));
	}

	SUBCASE("huge count") {
		// The file count follows the magic and the (1-char) name
		auto count_pos = 4 + 4 + 1;
		uint32_t huge = 0x7FFF'FFFF;
		std::memcpy(&buf[count_pos], &huge, 4);
		CHECK_FALSE(DirListSerial::deserialize(std::span{buf}.first(bytes), dst));
	}

	SUBCASE("wrong type") {
		PatchDirList list;
		CHECK_FALSE(DirListSerial::deserialize(std::span{buf}.first(bytes), list));
	}
}
