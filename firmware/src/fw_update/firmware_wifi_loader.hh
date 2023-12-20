#pragma once
#include "fw_update/update_file.hh"
#include "pr_dbg.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

class FirmwareWifiLoader {
public:
	enum class Error { None, Failed };

	bool verify(std::span<char> filedata, StaticString<32> md5, UpdateType image_type) {
		pr_dbg("MD5 is %s\n", md5.c_str());
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
