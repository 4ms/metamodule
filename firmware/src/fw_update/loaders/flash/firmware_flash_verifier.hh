#pragma once

#include "../abstract_loader.hh"

namespace MetaModule
{

class FirmwareFlashVerifier : public FileWorkerBase{
public:
	FirmwareFlashVerifier(std::span<char> filedata, StaticString<32> md5_chars, uint32_t address)
	{
		size = filedata.size();
	}

	Error start() override
	{
		// TODO: implement
		return Error::None;
	}

	std::pair<std::size_t, Error> process() override
	{
		// TODO: implement
		return {size, Error::Mismatch};
	}
private:
	std::size_t size;
};

} // namespace MetaModule
