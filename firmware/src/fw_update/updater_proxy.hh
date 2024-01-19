#pragma once
#include <cstdint>
#include <string>
#include "patch_file/file_storage_proxy.hh"
#include "update_file.hh"

namespace MetaModule
{

class FirmwareUpdaterProxy {
public:
	enum State { Idle, Error, LoadingManifest, Verifying, Writing, Success };

	struct Status {
		State state{State::Idle};
		std::size_t file_size{0};
		std::size_t bytes_completed{0};
		std::string error_message{};
	};

public:

	FirmwareUpdaterProxy(FileStorageProxy &file_storage);

	bool start(std::string_view manifest_filename, Volume manifest_file_vol, uint32_t manifest_filesize);

	Status process();

private:
	void abortWithMessage(const char* message);
	void moveToState(State);
	void proceedWithNextFile();

private:
	FileStorageProxy &file_storage;

	State state;
	std::string error_message;
	bool justEnteredState;

	Volume vol;
	std::span<char> manifest_buffer;
	UpdateManifest manifest;

	std::size_t current_file_idx;
	std::size_t current_file_size;

};

} // namespace MetaModule
