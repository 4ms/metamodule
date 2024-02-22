#pragma once
#include "fw_update/ram_buffer.hh" //path must be exactly this, or else simulator build picks wrong file
#include "patch_file/file_storage_proxy.hh"
#include <cstdint>
#include <string>

namespace MetaModule
{

class PluginFinderProxy {
public:
	enum State { Idle, Error, ReadingPlugin, LoadingPlugin, Success };

	struct Status {
		State state{State::Idle};
		std::string name;
		std::string error_message{};
	};

	PluginFinderProxy(FileStorageProxy &file_storage);

	bool start();

	Status process();

private:
	FileStorageProxy &file_storage;

	State state{State::Idle};

	OneTimeArenaAllocator allocator;
};

} // namespace MetaModule
