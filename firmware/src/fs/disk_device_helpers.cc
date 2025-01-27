#include "disk_device_helpers.hh"
#include "ff.h"

uint32_t DiskHelper::get_file_size(DiskDevice &dev, std::string_view path) {
	FILINFO info;
	dev.stat(path, &info);
	return info.fsize;
}

bool DiskHelper::foreach_dir_entry(DiskDevice &dev, std::string_view path, DirEntryAction &&action) {

	return false;
}
