#include "untar.hh"
#include "pr_dbg.hh"
#include <cstdlib>
#include <cstring>

namespace Tar
{

static unsigned image_read(std::span<const char> data, char *buf, int size, unsigned read_pos);
static int iszeroed(char *buf, size_t size);
static unsigned oct2uint(char *oct, unsigned size);

constexpr inline unsigned RECORDSIZE = 10240;

void print_info(std::span<char> data) {
	tar_t *archive = nullptr;
	pr_dbg("Reading %p\n", data.data());
	read(data, &archive);

	tar_t *entry = archive;
	pr_dbg("Read.\n");
	while (entry) {
		pr_info("- %s\n", entry->name);
		entry = entry->next;
	}

	pr_dbg("freeing\n");
	tar_free(archive);
}

bool read(std::span<char> data, tar_t **archive) {
	unsigned read_pos = 0;

	if (data.size() == 0)
		pr_err("No data");

	if (!archive || *archive) {
		pr_err("Archive must be a pointer to a null pointer");
	}

	unsigned offset = 0;
	int count = 0;

	tar_t **tar = archive;
	char update = 1;

	for (count = 0;; count++) {
		// *tar = new tar_t[1]{};
		// std::memset(tar[0], 0, sizeof(tar_t));
		*tar = (tar_t *)std::calloc(1, sizeof(tar_t));

		if (update)
			read_pos = image_read(data, (*tar)->block, 512, read_pos);

		update = 1;
		// if current block is all zeros
		if (iszeroed((*tar)->block, 512)) {
			read_pos = image_read(data, (*tar)->block, 512, read_pos);

			// check if next block is all zeros as well
			if (iszeroed((*tar)->block, 512)) {
				tar_free(*tar);
				*tar = nullptr;

				// skip to end of record
				read_pos += (RECORDSIZE - (offset % RECORDSIZE));

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

	return count;
}

int iszeroed(char *buf, size_t size) {
	for (size_t i = 0; i < size; buf++, i++) {
		if (*(char *)buf) {
			return 0;
		}
	}
	return 1;
}

unsigned image_read(std::span<const char> data, char *buf, int size, unsigned read_pos) {
	std::memcpy(buf, data.data() + read_pos, size);
	return read_pos + size;
}

unsigned oct2uint(char *oct, unsigned size) {
	unsigned int out = 0;
	unsigned i = 0;
	while ((i < size) && oct[i]) {
		out = (out << 3) | (unsigned int)(oct[i++] - '0');
	}
	return out;
}

void tar_free(tar_t *archive) {
	while (archive) {
		tar_t *next = archive->next;
		free(archive);
		// delete archive;
		archive = next;
	}
}

} // namespace Tar
