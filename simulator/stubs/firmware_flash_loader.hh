#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace MetaModule
{

class FirmwareFlashLoader {
public:
	FirmwareFlashLoader() {
	}

	uint8_t *buffer() {
		return ram_buffer.data();
	}

	bool verify_image(size_t filesize) {
		image_size = filesize;

		if (filesize & 0b01) {
			printf("Faking failed verification of image\n");
			return false;
		}
		return true;
	}

	bool start() {
		bytes_remaining = image_size;
		return true;
	}

	enum class Error { None, Failed };

	std::pair<int, Error> load_next_block() {
		bytes_remaining -= 4096;
		return {bytes_remaining, Error::None};
	}

private:
	std::array<uint8_t, 1024> ram_buffer;

	size_t image_size = 0;
	int bytes_remaining = 0;
};

} // namespace MetaModule
