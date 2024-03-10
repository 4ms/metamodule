#pragma once
#include <cstddef>
#include <functional>
#include <span>
#include <string_view>

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
	bool extract_files(std::function<uint32_t(std::string_view, std::span<const char>)>);

private:
	bool image_read(char *buf, int size);
	void tar_free(tar_t *archive);
	// bool extract_entry(tar_t *entry);
	std::vector<char> extract_entry(tar_t *entry);
};

} // namespace Tar
