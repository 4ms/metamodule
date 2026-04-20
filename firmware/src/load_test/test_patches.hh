#pragma once
#include "console/pr_dbg.hh"
#include "fs/dir_tree.hh"
#include "fs/general_io.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "patch-serial/yaml_to_patch.hh"
#include "patch/patch_data.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/patches_default.hh"
#include "patch_play/patch_player.hh"
#include "static_buffers.hh"
#include "tester.hh"
#include <chrono>
#include <numeric>
#include <string>
#include <vector>

namespace MetaModule::LoadTest
{

struct PatchEntry {
	static constexpr std::array<unsigned, 5> blocksizes{32, 64, 128, 256, 512};
	std::string name;
	bool load_failed{false};
	std::array<ModuleLoadTester::Measurements, blocksizes.size()> times;
};

inline std::string patches_csv_header() {
	std::string s = "Patch,";
	pr_info("Patch,");
	for (unsigned int blocksize : PatchEntry::blocksizes) {
		s += "Block-" + std::to_string(blocksize) + ",";
		pr_info("Block-%u,", blocksize);
	}
	if (s.ends_with(","))
		s.pop_back();
	s += "\n";
	pr_info("\n");
	return s;
}

inline std::string patch_entry_to_csv(PatchEntry const &entry) {
	constexpr float sampletime = 1'000'000.f / 48000.f;

	std::string s = entry.name + ",";
	pr_info("%s,", entry.name.c_str());

	if (entry.load_failed) {
		for (auto i = 0u; i < PatchEntry::blocksizes.size(); i++) {
			s += "FAIL,";
			pr_info("FAIL,");
		}
	} else {
		for (auto const &m : entry.times) {
			char buf[16];
			snprintf(buf, 16, "%.3f,", m.average_run_time_after_first / sampletime);
			s += buf;
			pr_info("%.3f,", m.average_run_time_after_first / sampletime);
		}
	}

	if (s.ends_with(","))
		s.pop_back();
	s += "\n";
	pr_info("\n");
	return s;
}

// Runs PatchPlayer::update_patch() for 2048 total iterations,
// grouped in chunks of block_size, reporting the worst per-chunk averages.
inline ModuleLoadTester::Measurements run_loaded_patch(PatchPlayer &player, size_t block_size) {
	constexpr size_t min_total_iterations = 2048;

	std::vector<uint64_t> times(block_size, 0);
	ModuleLoadTester::Measurements worst{};

	size_t iterations = 0;
	while (iterations < min_total_iterations) {
		for (auto &tm : times) {
			tm = ModuleLoadTester::measure([&]() { player.update_patch(); });
		}

		auto current = ModuleLoadTester::Measurements{times};

		worst.first_run_time = std::max(worst.first_run_time, current.first_run_time);
		worst.average_run_time = std::max(worst.average_run_time, current.average_run_time);
		worst.worst_run_time_after_first =
			std::max(worst.worst_run_time_after_first, current.worst_run_time_after_first);
		worst.average_run_time_after_first =
			std::max(worst.average_run_time_after_first, current.average_run_time_after_first);

		iterations += block_size;
	}

	return worst;
}

inline void run_patch_entry(PatchPlayer &player, PatchData &pd, PatchEntry &entry) {
	auto res = player.load_patch(pd);
	if (!res.success) {
		pr_err("Patch '%s' failed to load: %s\n", entry.name.c_str(), res.error_string.c_str());
		entry.load_failed = true;
		return;
	}

	for (auto i = 0u; auto blocksize : PatchEntry::blocksizes) {
		hil_message("*ok\n");
		pr_trace("Patch '%s' block size %u\n", entry.name.c_str(), blocksize);
		entry.times[i] = run_loaded_patch(player, blocksize);
		i++;
	}

	if (player.is_loaded)
		player.unload_patch();
}

inline void test_default_patches(PatchPlayer &player, auto append_file) {
	for (uint32_t i = 0; i < DefaultPatches::num_patches(); i++) {
		auto raw = DefaultPatches::get_patch(i);
		auto filename = DefaultPatches::get_filename(i);

		// Strip trailing null terminators so the YAML parser doesn't see them
		while (!raw.empty() && raw.back() == '\0')
			raw = raw.subspan(0, raw.size() - 1);

		PatchEntry entry;
		entry.name = filename.c_str();

		printf("Testing patch %s\n", entry.name.c_str());
		lv_label_set_text_fmt(ui_MainMenuNowPlaying, "Testing %s", entry.name.c_str());

		// yaml_raw_to_patch parses in place, so make a writable copy
		std::string yaml(raw.data(), raw.size());

		PatchData pd;
		if (!yaml_raw_to_patch(yaml.data(), yaml.size(), pd)) {
			pr_err("Failed to parse default patch '%s'\n", entry.name.c_str());
			entry.load_failed = true;
		} else {
			pd.trim_empty_knobsets();
			pd.update_midi_poly_num();
			run_patch_entry(player, pd, entry);
		}

		append_file(patch_entry_to_csv(entry));
	}
}

inline bool request_test_patch_dir(FileStorageProxy &file_storage_proxy, DirTree<FileEntry> &dir_tree) {
	uint32_t timeout = get_time();
	while (!file_storage_proxy.request_dir_entries(&dir_tree, Volume::USB, "test-patches", "yml")) {
		if (get_time() - timeout > 1000) {
			pr_err("Dir entries request not made in 1 second\n");
			return false;
		}
	}

	timeout = get_time();
	while (true) {
		auto msg = file_storage_proxy.get_message();
		if (msg.message_type == FileStorageProxy::DirEntriesSuccess)
			return true;
		if (msg.message_type == FileStorageProxy::DirEntriesFailed) {
			pr_err("Dir entries request failed for test-patches/\n");
			return false;
		}
		if (get_time() - timeout > 4000) {
			pr_err("Dir entries request not responded to in 4 seconds\n");
			return false;
		}
	}
}

inline void
test_usb_patches(FileStorageProxy &file_storage_proxy, PatchPlayer &player, auto append_file) {
	auto &dir_tree = StaticBuffers::dir_tree;
	dir_tree = DirTree<FileEntry>{};

	if (!request_test_patch_dir(file_storage_proxy, dir_tree)) {
		pr_info("No test-patches/ directory found on USB drive\n");
		return;
	}

	pr_info("Found %zu patch files in test-patches/\n", dir_tree.files.size());

	for (auto const &file : dir_tree.files) {
		PatchEntry entry;
		entry.name = file.filename;

		printf("Testing patch %s\n", entry.name.c_str());
		lv_label_set_text_fmt(ui_MainMenuNowPlaying, "Testing %s", entry.name.c_str());

		std::string filedata;
		auto path = "test-patches/" + file.filename;
		auto bytes_read = FS::read_file(file_storage_proxy, filedata, {path, Volume::USB});
		if (!bytes_read || *bytes_read == 0) {
			pr_err("Failed to read patch file '%s'\n", path.c_str());
			entry.load_failed = true;
			append_file(patch_entry_to_csv(entry));
			continue;
		}

		PatchData pd;
		if (!yaml_string_to_patch(std::move(filedata), pd)) {
			pr_err("Failed to parse patch file '%s'\n", path.c_str());
			entry.load_failed = true;
		} else {
			pd.trim_empty_knobsets();
			pd.update_midi_poly_num();
			run_patch_entry(player, pd, entry);
		}

		append_file(patch_entry_to_csv(entry));
	}
}

inline void test_all_patches(FileStorageProxy &file_storage_proxy, auto append_file) {
	lv_show(ui_MainMenuNowPlayingPanel);
	lv_show(ui_MainMenuNowPlaying);

	append_file(patches_csv_header());

	PatchPlayer player;

	test_default_patches(player, append_file);
	test_usb_patches(file_storage_proxy, player, append_file);

	lv_label_set_text(ui_MainMenuNowPlaying, "Finished patch load tests");
}

} // namespace MetaModule::LoadTest
