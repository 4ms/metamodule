#pragma once
#include <cstddef>
#include <cstdint>
#include <span>
#include <utility>

namespace MetaModule
{

class FirmwareFlashLoader {
public:
	FirmwareFlashLoader() {
	}

	bool verify(std::span<char> file, std::span<uint32_t, 4> md5) {
		filesize = file.size();

		if (filesize & 0b01) {
			printf("Faking failed verification of image\n");
			return false;
		}
		return true;
	}

	bool start(std::span<char> file) {
		bytes_remaining = filesize;
		return true;
	}

	enum class Error { None, Failed };

	std::pair<int, Error> load_next_block() {
		bytes_remaining -= 4096;
		return {bytes_remaining, Error::None};
	}

private:
	size_t filesize = 0;
	int bytes_remaining = 0;
};

} // namespace MetaModule
