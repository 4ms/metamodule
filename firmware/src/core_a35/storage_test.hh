#pragma once
#include "drivers/stm32xx.h"
#include "patch_file/file_storage_proxy.hh"
#include <algorithm>
#include <cstdio>
#include <string_view>

namespace MetaModule
{

// Bring-up test of FileStorageProxy (A35) <-> PatchStorage (M33), the path the GUI's patch
// selector and file browser use:
// - request the patch list every second, and print it whenever it changes (e.g. SD card in/out)
// - the first time there's a patch, load it and print its size and first line
// - then list the files on the SD card (or NOR flash if there's no card)
class StorageTest {
	using enum IntercoreStorageMessage::MessageType;

public:
	StorageTest(FileStorageProxy &proxy)
		: proxy{proxy} {
	}

	void process() {
		auto now = HAL_GetTick();

		if (waiting && now - request_tm > 4000) {
			printf("Storage: no response from M33 in 4s\n");
			waiting = false;
		}

		if (!waiting && now - request_tm > 1000) {
			if (proxy.request_patchlist())
				start_wait(now);
		}

		auto message = proxy.get_message();
		switch (message.message_type) {
			case None:
				break;

			case PatchListUnchanged:
				waiting = false;
				break;

			case PatchListChanged:
				waiting = false;
				print_patch_list();
				if (!loaded_patch)
					load_first_patch(now);
				break;

			case LoadFileOK: {
				waiting = false;
				std::string_view data{proxy.get_patch_data(message.bytes_read).data(), message.bytes_read};
				// The default patches start with a blank line (they're stored as R"(\n...)" strings)
				data.remove_prefix(std::min(data.find_first_not_of("\r\n"), data.size()));
				auto first_line = data.substr(0, data.find('\n'));
				printf("Storage: loaded %s:%s, %u bytes, timestamp %u. First non-blank line: \"%.*s\"\n",
					   PatchDirList::get_vol_name(message.vol_id).data(),
					   message.filename.c_str(),
					   (unsigned)message.bytes_read,
					   (unsigned)message.timestamp,
					   (int)first_line.size(),
					   first_line.data());
				list_dir(now);
			} break;

			case LoadFileFailed:
				waiting = false;
				printf("Storage: loading %s FAILED\n", message.filename.c_str());
				break;

			case DirEntriesSuccess:
				waiting = false;
				print_dir_entries();
				break;

			case DirEntriesFailed:
				waiting = false;
				printf("Storage: listing files FAILED\n");
				break;

			default:
				waiting = false;
				printf("Storage: unexpected response %u\n", (unsigned)message.message_type);
				break;
		}
	}

private:
	FileStorageProxy &proxy;
	bool waiting = false;
	uint32_t request_tm = 0;
	bool loaded_patch = false;
	Volume listed_vol{};
	DirTree<FileEntry> dir_tree;

	void start_wait(uint32_t now) {
		waiting = true;
		request_tm = now;
	}

	void print_patch_list() {
		auto &list = proxy.get_patch_list();
		printf("Storage: patch list changed:\n");
		for (auto vol : PatchDirList::vols) {
			auto &root = list.volume_root(vol);
			auto num_files = root.files.size();
			for (auto const &dir : root.dirs)
				num_files += dir.files.size();

			printf("  %-8s %s, %u patches in %u dirs\n",
				   PatchDirList::get_vol_name(vol).data(),
				   list.is_mounted(vol) ? "mounted" : "-",
				   (unsigned)num_files,
				   (unsigned)root.dirs.size());

			for (auto i = 0u; auto const &file : root.files) {
				if (++i > 5) {
					printf("    ...\n");
					break;
				}
				printf("    %s \"%s\" (%u bytes)\n", file.filename.c_str(), file.patchname.c_str(), (unsigned)file.filesize);
			}
		}
	}

	void load_first_patch(uint32_t now) {
		auto &list = proxy.get_patch_list();
		for (auto vol : {Volume::SDCard, Volume::USB, Volume::NorFlash}) {
			auto &root = list.volume_root(vol);
			if (root.files.size()) {
				if (proxy.request_load_patch({.filename = root.files[0].filename.c_str(), .vol = vol})) {
					loaded_patch = true;
					start_wait(now);
				}
				return;
			}
		}
	}

	void list_dir(uint32_t now) {
		auto &list = proxy.get_patch_list();
		listed_vol = list.is_mounted(Volume::SDCard) ? Volume::SDCard : Volume::NorFlash;
		if (proxy.request_dir_entries(&dir_tree, listed_vol, "/", ""))
			start_wait(now);
	}

	void print_dir_entries() {
		printf("Storage: %s:/ has %u files and %u dirs:\n",
			   PatchDirList::get_vol_name(listed_vol).data(),
			   (unsigned)dir_tree.files.size(),
			   (unsigned)dir_tree.dirs.size());
		for (auto const &dir : dir_tree.dirs)
			printf("    [dir] %s\n", dir.name.c_str());
		for (auto i = 0u; auto const &file : dir_tree.files) {
			if (++i > 20) {
				printf("    ...\n");
				break;
			}
			printf("    %s (%u bytes)\n", file.filename.c_str(), (unsigned)file.filesize);
		}
	}
};

} // namespace MetaModule
