#pragma once
#include "patch_file/file_storage_proxy.hh"
#include "update_file.hh"
#include <cstdint>
#include <string>

namespace MetaModule
{

class FirmwareUpdaterProxy {
public:
	enum State { Idle, Error, LoadingManifest, Verifying, Writing, Success };

	struct Status {
		State state{State::Idle};
		std::string name;
		std::size_t file_size{0};
		std::size_t bytes_completed{0};
		std::string error_message{};
	};

	FirmwareUpdaterProxy(FileStorageProxy &file_storage);

	bool start(std::string_view manifest_filename, Volume manifest_file_vol, uint32_t manifest_filesize);

	Status process();

private:
	void abortWithMessage(const char *message);
	void moveToState(State);
	void proceedWithNextFile();

	FileStorageProxy &file_storage;

	State state;
	std::string error_message;
	bool justEnteredState;

	Volume vol;
	std::span<char> manifestBuffer;
	UpdateManifest manifest;

	std::size_t current_file_idx;
	std::size_t current_file_size;
	std::string current_file_name;

	struct SharedMem {
		uint32_t bytes_processed;
		StaticString<32> checksum;
		std::array<uint8_t, 4 * 1024 * 1024> manifestBuffer;
	};

	SharedMem *sharedMem;
};

} // namespace MetaModule
