#pragma once

#include "loaders/abstract_loader.hh"
#include "fw_update/manifest_parse.hh"
#include "fw_update/ram_buffer.hh"
#include "patch_file/file_storage_proxy.hh"
#include <cstdint>
#include <memory>

namespace MetaModule
{

// Handle the process of updating firmware
class FirmwareUpdater {
public:
	enum State { Idle, Error, LoadingManifest, LoadingFilesToRAM, Writing, Success };

	struct Status {
		State state{State::Idle};
		int file_size{0};
		int bytes_remaining{0};
		std::string error_message{};
	};

public:

	FirmwareUpdater(FileStorageProxy &file_storage);

	bool start(std::string_view manifest_filename, Volume manifest_file_vol, uint32_t manifest_filesize);

	Status process();

private:
	void start_reading_file();
	void check_reading_done();
	int start_writing_file();

private:
	void abortWithMessage(const char* message);
	void moveToState(State);

private:
	std::unique_ptr<FileLoaderBase> current_file_loader;

	ManifestParser parser;

	FileStorageProxy &file_storage;
	State state;

	Volume vol;

	unsigned int current_file_idx;
	int current_file_size;
	bool file_requested;

	std::span<char> manifest_buffer;

	std::string error_message;

	const std::span<uint8_t> ram_buffer = get_ram_buffer();

	UpdateManifest manifest;
	std::vector<std::span<char>> file_images;
};

} // namespace MetaModule
