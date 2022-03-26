#include "fileio.hh"
#include "ff.h"

namespace FileIO
{

bool create_file(const char *filename, const std::span<const unsigned char> data) {
	return true;
}

bool create_file(const char *filename, const unsigned char *data, unsigned sz) {
	return true;
}

uint32_t read_file(std::string_view filename, char *data, uint32_t max_bytes) {
	return true;
}

} // namespace FileIO
