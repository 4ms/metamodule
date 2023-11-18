#pragma once
#include "lvgl.h"
#include <map>
#include <string_view>

// Mock read-only filesystem: given a file name, return the file contents
// TODO: replace with real filesystem (LittleFS for NORFlash)
// TODO: use /plugin/BRAND/res/components/ directories
// TODO: integrate this with module faceplates (/plugin/BRAND/res/modules/)
struct PNGFileSystem {
	static lv_img_dsc_t const *read(std::string_view filename) {
		if (mock_fs.contains(filename))
			return mock_fs[filename];
		else
			return nullptr;
	}

	static bool register_file(std::string_view filename, lv_img_dsc_t const *filedata) {
		if (filename.size() == 0)
			return false;
		mock_fs[filename] = filedata;
		return true;
	}

private:
	static inline std::map<std::string_view, lv_img_dsc_t const *> mock_fs;
};
