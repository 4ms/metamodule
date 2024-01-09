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

	std::pair<std::size_t, Error> load_next_block();
	
private:
	std::size_t bytes_completed = 0;
	std::span<char> file;
};
} // namespace MetaModule
