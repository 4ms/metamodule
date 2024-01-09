#pragma once
#include "fw_update/update_file.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

class FirmwareWifiLoader {
public:
	enum class Error { None, Failed };

	bool verify(std::span<char> filedata, StaticString<32> md5, UpdateType image_type);

	bool start();

	std::pair<int, Error> load_next_block();
	
private:
	int bytes_remaining = 0;
	std::span<char> file;
};
} // namespace MetaModule
