#pragma once
#include "disk_ops.hh"
#include <cstdint>
#include <span>
#include <string_view>

namespace MetaModule
{
enum class Disk { NORFlash = 0 };

namespace FileIO
{

bool register_disk(DiskOps *ops, Disk disk);
bool mount_disk(Disk disk);
bool unmount_disk(Disk disk);
bool format_disk(Disk disk);
bool create_default_files(Disk disk);

void vol_string(Disk disk, char vol[3]);

// Creates and writes to a file. Overwrites if existing.
bool create_file(const char *filename, const std::span<const unsigned char> data);
bool create_file(const char *filename, const unsigned char *data, unsigned sz);

uint32_t read_file(std::string_view filename, char *data, uint32_t max_bytes);

// struct Fil {};
// Fil next_ext_in_dir(std::string_view ext, std::string_view path);

}; // namespace FileIO

} // namespace MetaModule
