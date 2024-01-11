#pragma once

#include "../abstract_loader.hh"

namespace MetaModule
{

class FirmwareWifiLoader : public FileWorkerBase
{
public:
	FirmwareWifiLoader(std::span<char> filedata, std::size_t address);

	Error start() override;

	std::pair<std::size_t, Error> process();
	
private:
	std::span<char> file;
	std::size_t bytes_completed = 0;
};
} // namespace MetaModule
