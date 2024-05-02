#pragma once
#include <cstddef>
#include <functional>
#include <list>
#include <span>
#include <string>
#include <string_view>

namespace Tar
{

struct TarRaw;
struct TarEntry {
	std::string name{};
	unsigned size{};
	unsigned file_offset{};
	enum EntryType { Unknown, File, Dir } type{EntryType::Unknown};
};

class Archive {
	std::span<const char> filedata;
	unsigned read_pos = 0;
	unsigned num_entries = 0;

	std::list<TarEntry> archive;

public:
	Archive(std::span<const char> filedata);

	void print_info();
	using extract_func_t = std::function<uint32_t(std::string_view, std::span<const char>)>;
	bool extract_files(extract_func_t func);

private:
	bool image_read(char *buf, int size);
	bool image_read(TarRaw *buf, int size);
	std::vector<char> extract_file_entry(TarEntry const &entry);
	void image_seek_relative(int advance);
	void image_seek_absolute(unsigned new_pos);
};

} // namespace Tar
