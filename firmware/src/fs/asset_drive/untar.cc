#include "untar.hh"
#include "pr_dbg.hh"
#include <cstdlib>
#include <cstring>
#include <functional>
#include <list>
#include <string>

namespace Tar
{

struct TarRaw {
	char name[100]; // file name
	char mode[8];	// permissions
	char uid[8];	// user id (octal)
	char gid[8];	// group id (octal)
	char size[12];	// size (octal)
	char mtime[12]; // modification time (octal)
	char check[8];
	// sum of unsigned characters in block, with spaces in the check field while calculation is done (octal)
	char type;			 // file type
	char link_name[100]; // name of linked file
	char ustar[8];		 // ustar\000
	char owner[32];		 // user name (string)
	char group[32];		 // group name (string)
	char major[8];		 // device major number
	char minor[8];		 // device minor number
	char prefix[155];
	char padding[12];

	enum : char {
		REGULAR = 0,
		NORMAL = '0',
		HARDLINK = '1',
		SYMLINK = '2',
		CHAR = '3',
		BLOCK = '4',
		DIRECTORY = '5',
		FIFO = '6',
		CONTIGUOUS = '7',
	};
};
static_assert(sizeof(TarRaw) == 512);

static int iszeroed(TarRaw *buf, size_t size);
static unsigned oct2uint(char *oct, unsigned size);
static bool is_file(char entry_type);
static bool is_dir(char entry_type);
static std::string entry_name(TarRaw *entry);
static bool is_ustar(TarRaw *entry);

Archive::Archive(std::span<const char> filedata)
	: filedata{filedata} {

	if (filedata.size() == 0) {
		pr_err("No data");
		return;
	}

	bool update = true;

	int count = 0;
	unsigned offset = 0;
	for (count = 0;; count++) {
		TarRaw buffer;

		if (update) {
			if (!image_read(&buffer, 512)) {
				pr_err("Failed to read byte %zu + 512\n", read_pos);
				return;
			}
		}

		update = true;
		// if current block is all zeros
		if (iszeroed(&buffer, 512)) {
			if (!image_read(&buffer, 512)) {
				pr_err("Failed to read byte %zu + 512\n", read_pos);
				return;
			}

			// check if next block is all zeros as well
			if (iszeroed(&buffer, 512)) {
				break;
			}

			update = false;
		}

		auto size = oct2uint(buffer.size, 11);
		auto type = is_file(buffer.type) ? TarEntry::File : is_dir(buffer.type) ? TarEntry::Dir : TarEntry::Unknown;

		// Cannot use emplace_back with earlier Clang
		archive.push_back({.name = entry_name(&buffer), .size = size, .file_offset = offset, .type = type});

		// skip over data and unfilled block
		unsigned jump = size;
		if (jump % 512) {
			jump += 512 - (jump % 512);
		}

		offset += 512 + jump;
		image_seek_relative(jump);
	}

	num_entries = count;
}

bool Archive::extract_files(std::function<uint32_t(std::string_view, std::span<const char>)> write) {
	bool all_entries_ok = true;

	for (auto &entry : archive) {
		auto name = entry.name;

		if (entry.type == TarEntry::File) {
			if (auto filedata = extract_file_entry(entry); filedata.size() > 0) {
				pr_dump("Extracted %zu bytes for %s\n", filedata.size(), name.c_str());
				write(name, filedata);
			} else {
				all_entries_ok = false;
				pr_err("Failed to extract %s\n", name.c_str());
			}
		} else {
			pr_trace("Skipping non-file entry %s\n", name.c_str());
		}
	}

	return all_entries_ok;
}

std::vector<char> Archive::extract_file_entry(TarEntry const &entry) {
	image_seek_absolute(512 + entry.file_offset);

	std::vector<char> filedata(entry.size);
	image_read(filedata.data(), entry.size);
	return filedata;
}

void Archive::print_info() {
	for (auto &entry : archive) {
		pr_info("- %s\n", entry.name.c_str());
	}
}

bool Archive::image_read(TarRaw *buf, int size) {
	if (read_pos + size > filedata.size())
		return false;
	std::memcpy(buf, filedata.data() + read_pos, size);
	read_pos += size;
	return true;
}

bool Archive::image_read(char *buf, int size) {
	return image_read(reinterpret_cast<TarRaw *>(buf), size);
}

void Archive::image_seek_absolute(unsigned new_pos) {
	read_pos = new_pos;
}

void Archive::image_seek_relative(int advance) {
	read_pos += advance;
}

std::string entry_name(TarRaw *entry) {
	// Note: TarRaw::name is not necessarily null-terminated
	auto name = std::string_view{entry->name, 100};

	if (auto nullpos = name.find_first_of('\0'); nullpos != std::string::npos)
		name = name.substr(0, nullpos);

	if (is_ustar(entry) && entry->prefix[0] != '\0') {
		// USTar format for filename: prefix/name
		// Note: TarRaw::prefix is not necessarily null-terminated
		auto prefix = std::string_view{entry->prefix, 100};
		if (auto nullpos = prefix.find_first_of('\0'); nullpos != std::string::npos)
			prefix = prefix.substr(0, nullpos);

		return std::string{prefix} + "/" + std::string{name};

	} else
		return std::string{name};
}

bool is_ustar(TarRaw *entry) {
	return std::string_view{entry->ustar} == std::string_view{"ustar"};
}

bool is_file(char entry_type) {
	return (entry_type == TarRaw::REGULAR) || (entry_type == TarRaw::NORMAL) || (entry_type == TarRaw::CONTIGUOUS);
}

bool is_dir(char entry_type) {
	return (entry_type == TarRaw::DIRECTORY);
}

int iszeroed(TarRaw *entry, size_t size) {
	auto *buf = reinterpret_cast<char *>(entry);

	for (size_t i = 0; i < size; buf++, i++) {
		if (*(char *)buf) {
			return 0;
		}
	}
	return 1;
}

unsigned oct2uint(char *oct, unsigned size) {
	unsigned int out = 0;
	unsigned i = 0;
	while ((i < size) && oct[i]) {
		out = (out << 3) | (unsigned int)(oct[i++] - '0');
	}
	return out;
}

} // namespace Tar
