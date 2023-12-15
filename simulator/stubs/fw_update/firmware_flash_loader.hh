#pragma once
#include <array>
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

	uint8_t *buffer() {
		return ram_buffer.data();
	}

	bool verify(std::span<uint8_t> file) {
		filesize = file.size();

		if (filesize & 0b01) {
			printf("Faking failed verification of image\n");
			return false;
		}
		return true;
	}

	bool start(std::span<uint8_t> file) {
		bytes_remaining = filesize;
		return true;
	}

	enum class Error { None, Failed };

	std::pair<int, Error> load_next_block() {
		bytes_remaining -= 4096;
		return {bytes_remaining, Error::None};
	}

private:
	std::array<uint8_t, 1024> ram_buffer;

	size_t filesize = 0;
	int bytes_remaining = 0;
};

} // namespace MetaModule
