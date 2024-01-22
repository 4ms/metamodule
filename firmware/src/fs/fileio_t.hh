#pragma once
#include "fs/dir_entry_kind.hh"
#include <functional>
#include <span>
#include <string_view>
#include <cstdint>

using FileAction = std::function<void(const std::string_view filename, uint32_t timestamp, uint32_t filesize)>;

using DirEntryAction =
	std::function<void(std::string_view filename, uint32_t timestamp, uint32_t filesize, DirEntryKind entry_type)>;

template<typename T>
concept FileIoC = requires(T t,
						   std::string_view filename,
						   std::string_view path,
						   const std::span<const char> const_data,
						   std::span<char> read_buffer,
						   FileAction action,
						   DirEntryAction direntry_action,
						   uint32_t tm,
						   std::size_t length) {
	{
		t.update_or_create_file(filename, const_data)
	} -> std::convertible_to<bool>;
	{
		t.foreach_file_with_ext(filename, action)
	} -> std::convertible_to<bool>;
	{
		t.foreach_dir_entry(path, direntry_action)
	} -> std::convertible_to<bool>;
	{
		t.read_file(filename, read_buffer, length)
	} -> std::integral;
	{
		t.volname()
	} -> std::convertible_to<std::string_view>;
	{
		t.is_mounted()
	} -> std::same_as<bool>;

	t.delete_file(filename);
	t.set_file_timestamp(filename, tm);
};
