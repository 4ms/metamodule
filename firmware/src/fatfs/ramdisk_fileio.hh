#pragma once
#include "disk_ops.hh"
#include <cstdint>
#include <span>
#include <string_view>

namespace MetaModule
{
enum class Disk { RamDisk = 0 };

namespace RamDiskFileIO
{

bool register_disk(DiskOps *ops, Disk disk);
bool mount_disk(Disk disk);
bool unmount_disk(Disk disk);
bool format_disk(Disk disk);
bool create_default_files(Disk disk);

void vol_string(Disk disk, char vol[3]);

// Creates and writes to a file. Overwrites if existing.
bool create_file(const char *filename, const std::span<const char> data);
bool create_file(const char *filename, const char *data, unsigned sz);

uint32_t read_file(std::string_view filename, char *data, uint32_t max_bytes);

template<typename Action>
void for_each_file_regex(Disk disk, std::string_view regex, Action action) { //void action(const char *)) {
	DIR dj;
	FILINFO fileinfo;
	auto res = f_findfirst(&dj, &fileinfo, "", regex.data());
	while (res == FR_OK && fileinfo.fname[0]) {
		action(fileinfo.fname);
		res = f_findnext(&dj, &fileinfo);
	}
}

}; // namespace RamDiskFileIO

} // namespace MetaModule
