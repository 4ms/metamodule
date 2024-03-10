#pragma once
#include <cstddef>
#include <span>

namespace Tar
{

struct tar_t;

class Archive {
	std::span<const char> filedata;
	unsigned read_pos = 0;
	unsigned num_entries = 0;

	//std::list<tar_t> archive;
	tar_t *archive = nullptr;

public:
	Archive(std::span<const char> filedata);
	~Archive();
	void print_info();

private:
	bool image_read(char *buf, int size);
	void tar_free(tar_t *archive);
};

} // namespace Tar
