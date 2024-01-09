#pragma once
#include "fw_update/update_file.hh"
#include <cstdint>
#include <span>
#include "../abstract_loader.hh"

namespace MetaModule
{

class FirmwareWifiLoader : public FileLoaderBase
{
public:
	FirmwareWifiLoader(std::span<char> filedata);

	bool verify(StaticString<32> md5);

	bool start();

	std::pair<int, Error> load_next_block();
	
private:
	int bytes_remaining = 0;
	std::span<char> file;
};
} // namespace MetaModule
