#pragma once
#include "fw_update/update_file.hh"
#include "util/static_string.hh"
#include <cstddef>
#include <span>
#include <utility>

namespace MetaModule
{

class FirmwareFlashLoader {
public:
	enum class Error { None, Failed };

	FirmwareFlashLoader() {
	}

	bool verify(std::span<char> filedata, StaticString<32> md5, UpdateType image_type) {
		file = filedata;
		filesize = file.size();

		if (filesize & 0b01) {
			printf("Faking failed verification of image\n");
			return false;
		}
		return true;
	}

	bool start() {
		bytes_remaining = filesize;
		return true;
	}

	std::pair<int, Error> load_next_block() {
		bytes_remaining -= 4096;
		return {bytes_remaining, Error::None};
	}

private:
	size_t filesize = 0;
	int bytes_remaining = 0;
	std::span<char> file;
};

} // namespace MetaModule
