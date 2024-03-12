#include "untar.hh"
#include "pr_dbg.hh"
#include <cstdlib>
#include <cstring>
#include <functional>
#include <string>

namespace Tar
{

static int iszeroed(char *buf, size_t size);
static unsigned oct2uint(char *oct, unsigned size);
static bool is_file(char entry_type);
static bool is_dir(char entry_type);
static std::string entry_name(tar_t *entry);
static bool is_ustar(tar_t *entry);

struct tar_t {
	char original_name[100]; // original filenme; only availible when writing into a tar
	unsigned int begin;		 // location of data in file (including metadata)
	union {
		union {
			// UStar format (POSIX IEEE P1003.1)
			struct {
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
			};
		};

		char block[512]; // raw memory (500 octets of actual data, padded to 1 block)
	};

	tar_t *next;

	static constexpr unsigned RECORDSIZE = 10240;
	static constexpr char REGULAR = 0;
	static constexpr char NORMAL = '0';
	static constexpr char HARDLINK = '1';
	static constexpr char SYMLINK = '2';
	static constexpr char CHAR = '3';
	static constexpr char BLOCK = '4';
	static constexpr char DIRECTORY = '5';
	static constexpr char FIFO = '6';
	static constexpr char CONTIGUOUS = '7';
};

Archive::Archive(std::span<const char> filedata)
	: filedata{filedata} {

	if (filedata.size() == 0) {
		pr_err("No data");
		return;
	}

	unsigned offset = 0;
	int count = 0;

	tar_t **tar = &archive;
	char update = 1;

	for (count = 0;; count++) {
		// *tar = new tar_t[1]{};
		// std::memset(tar[0], 0, sizeof(tar_t));
		*tar = (tar_t *)std::calloc(1, sizeof(tar_t));

		if (update) {
			if (!image_read((*tar)->block, 512)) {
				pr_err("Failed to read byte %zu + 512\n", read_pos);
				return;
			}
		}

		update = 1;
		// if current block is all zeros
		if (iszeroed((*tar)->block, 512)) {
			if (!image_read((*tar)->block, 512)) {
				pr_err("Failed to read byte %zu + 512\n", read_pos);
				return;
			}

			// check if next block is all zeros as well
			if (iszeroed((*tar)->block, 512)) {
				// tar_free(*tar);
				free(*tar);
				*tar = nullptr;

				// skip to end of record
				read_pos += (tar_t::RECORDSIZE - (offset % tar_t::RECORDSIZE));

				break;
			}

			update = 0;
		}

		// set current entry's file offset
		(*tar)->begin = offset;

		// skip over data and unfilled block
		unsigned int jump = oct2uint((*tar)->size, 11);
		if (jump % 512) {
			jump += 512 - (jump % 512);
		}

		// move file descriptor
		offset += 512 + jump;
		read_pos += jump;

		// ready next value
		tar = &((*tar)->next);
	}

	num_entries = count;
}

bool Archive::extract_files(std::function<uint32_t(std::string_view, std::span<const char>)> write) {
	tar_t *entry = archive;

	bool all_entries_ok = true;
	while (entry) {
		auto name = entry_name(entry);
		if (auto filedata = extract_entry(entry); filedata.size() > 0) {
			pr_info("Extracted %zu bytes for %s\n", filedata.size(), name.c_str());
			write(name, filedata);
		} else {
			all_entries_ok = false;
			pr_err("Failed to extract %s\n", name.c_str());
		}
		entry = entry->next;
	}

	return all_entries_ok;
}

std::vector<char> Archive::extract_entry(tar_t *entry) {
	if (is_file(entry->type)) {
		const unsigned int size = oct2uint(entry->size, 11);
		// std::string_view filename = entry->name;

		read_pos = 512 + entry->begin;
		std::vector<char> filedata(size);
		image_read(filedata.data(), size);
		return filedata;
	} else if (is_dir(entry->type)) {
		return {};
	} else
		return {};
}

Archive::~Archive() {
	while (archive) {
		tar_t *next = archive->next;
		free(archive);
		// delete archive;
		archive = next;
	}
}

void Archive::print_info() {
	tar_t *entry = archive;
	while (entry) {
		pr_info("- %s\n", entry_name(entry).c_str());
		entry = entry->next;
	}
}

bool Archive::image_read(char *buf, int size) {
	if (read_pos + size > filedata.size())
		return false;
	std::memcpy(buf, filedata.data() + read_pos, size);
	read_pos += size;
	return true;
}

std::string entry_name(tar_t *entry) {
	auto name = std::string_view{entry->name, 100};
	if (auto nullpos = name.find_first_of('\0'); nullpos != std::string::npos)
		name = name.substr(0, nullpos);

	if (is_ustar(entry) && entry->prefix[0] != '\0') {
		auto prefix = std::string_view{entry->prefix, 100};
		if (auto nullpos = prefix.find_first_of('\0'); nullpos != std::string::npos)
			prefix = prefix.substr(0, nullpos);
		return std::string{prefix} + "/" + std::string{name};
	} else
		return std::string{name};
}

bool is_ustar(tar_t *entry) {
	return std::string_view{entry->ustar} == std::string_view{"ustar"};
}

bool is_file(char entry_type) {
	return (entry_type == tar_t::REGULAR) || (entry_type == tar_t::NORMAL) || (entry_type == tar_t::CONTIGUOUS);
}

bool is_dir(char entry_type) {
	return (entry_type == tar_t::DIRECTORY);
}

int iszeroed(char *buf, size_t size) {
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
