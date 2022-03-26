#pragma once

#include <cstdint>
#include <span>
#include <string_view>

namespace FileIO
{
// Creates and writes to a file. Overwrites if existing.
bool create_file(const char *filename, const std::span<const unsigned char> data);
bool create_file(const char *filename, const unsigned char *data, unsigned sz);

// std::string read_file(std::string_view filename, uint32_t max_bytes = 0xFFFFFFFF);
uint32_t read_file(std::string_view filename, char *data, uint32_t max_bytes);

// struct Fil {};
// Fil next_ext_in_dir(std::string_view ext, std::string_view path);
}; // namespace FileIO
