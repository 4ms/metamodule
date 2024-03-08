#pragma once
#include "lvgl.h"
#include <map>
#include <string>
#include <string_view>

namespace MetaModule
{

struct ComponentImages {

	static const std::string get_comp_path(const std::string_view filename) {
		if (filename.length() > 0)
			return LV_FS_FATFS_LETTER + std::string(":2:/") + std::string(filename);
		else
			return "";
	}
};
} // namespace MetaModule

//////////////////////////////
//remove this

struct PNGFileSystem {
	static bool register_file(std::string_view filename, lv_img_dsc_t const *filedata) {
		if (filename.size() == 0)
			return false;
		mock_fs[filename] = filedata;
		return true;
	}

private:
	static inline std::map<std::string_view, lv_img_dsc_t const *> mock_fs;
};
