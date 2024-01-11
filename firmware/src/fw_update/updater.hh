#pragma once

#include "loaders/abstract_loader.hh"
#include "patch_file/file_storage_proxy.hh"
#include "update_file.hh"
#include <cstdint>
#include <memory>

namespace MetaModule
{

// Handle the process of updating firmware
class FirmwareUpdater {
public:
	enum State { Idle, Error, LoadingManifest, StartLoadingFileToRam, LoadingFileToRAM, StartVerify, Verifying, StartWriting, Writing, Success };

	struct Status {
		State state{State::Idle};
		std::size_t file_size{0};
		std::size_t bytes_completed{0};
		std::string error_message{};
	};

public:

	FirmwareUpdater(FileStorageProxy &file_storage);

	bool start(std::string_view manifest_filename, Volume manifest_file_vol, uint32_t manifest_filesize);

	Status process();

private:
	bool start_reading_file();
	bool start_writing_file();
	bool start_verifying_file();

private:
	void abortWithMessage(const char* message);
	void moveToState(State);

private:
	std::unique_ptr<FileWorkerBase> current_file_loader;

	FileStorageProxy &file_storage;
	State state;

	Volume vol;

	unsigned int current_file_idx;
	std::size_t current_file_size;

	std::span<char> manifest_buffer;

	std::string error_message;

	const std::span<uint8_t> ram_buffer;

	UpdateManifest manifest;
	std::vector<std::span<char>> file_images;
};

} // namespace MetaModule
