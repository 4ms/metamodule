#pragma once
#include <cstdint>
#include <span>
#include <utility>

namespace MetaModule
{

class FirmwareWifiLoader {
public:
	enum class Error { None, Failed };

	bool verify(std::span<uint8_t> file) {
		return true;
	}

	bool start(std::span<uint8_t> file) {
		bytes_remaining = file.size();
		return true;
	}

	std::pair<int, Error> load_next_block() {
		//simulate activity
		bytes_remaining -= 4096;
		return {bytes_remaining, Error::None};
	}

private:
	int bytes_remaining = 0;
};
} // namespace MetaModule
