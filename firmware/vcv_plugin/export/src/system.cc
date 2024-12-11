#include "console/pr_dbg.hh"
#include <system.hpp>

namespace rack::system
{

static FILE *openFile(std::string const &path) {
	FILE *f = std::fopen(path.c_str(), "rb");
	if (!f) {
		pr_err("Cannot open file %s\n", path.c_str());
		return {};
	}

	return f;
}

static size_t getLength(FILE *f) {
	// Get file size so we can make a single allocation
	std::fseek(f, 0, SEEK_END);
	size_t len = std::ftell(f);
	std::fseek(f, 0, SEEK_SET);

	return len;
}

std::vector<uint8_t> readFile(const std::string &path) {
	std::vector<uint8_t> data;

	if (auto f = openFile(path)) {
		auto len = getLength(f);

		data.resize(len);

		std::fread(data.data(), 1, len, f);
		std::fclose(f);
	}

	return data;
}

uint8_t *readFile(const std::string &path, size_t *size) {
	if (auto f = openFile(path)) {
		auto len = getLength(f);

		auto *data = (uint8_t *)std::malloc(len);
		if (!data) {
			pr_err("rack::readFile(%s, sz) failed to allocate %zu bytes\n", path.c_str(), len);
			return data;
		}
		std::fread(data, 1, len, f);
		std::fclose(f);

		if (size)
			*size = len;

		return data;
	} else {
		pr_err("rack::readFile(%s, sz) failed to open\n", path.c_str());
		return nullptr;
	}
}

} // namespace rack::system
