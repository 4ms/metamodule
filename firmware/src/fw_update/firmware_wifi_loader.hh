#pragma once
#include "pr_dbg.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

class FirmwareWifiLoader {
public:
	enum class Error { None, Failed };

	bool verify(std::span<char> file, std::span<uint32_t, 4> md5) {
		pr_dbg("MD5 is %08x %08x %08x %08x\n", md5[0], md5[1], md5[2], md5[3]);
		pr_dbg("Wifi image at %p, size: %zu\n", file.data(), file.size());
		file = filedata;
		return true;
	}

	bool start() {
		bytes_remaining = file.size();
		return true;
	}

	std::pair<int, Error> load_next_block() {
		//simulate activity
		if (bytes_remaining > 0) {
		pr_dbg("Wifi bytes remaining: %d\n", bytes_remaining);
		bytes_remaining -= 4096;
		}
		return {bytes_remaining, Error::None};
	}

private:
	int bytes_remaining = 0;
	std::span<char> file;
};
} // namespace MetaModule
