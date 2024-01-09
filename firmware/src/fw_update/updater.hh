#pragma once
#include "loaders/flash/firmware_flash_loader.hh"
#include "loaders/wifi/firmware_wifi_loader.hh"
#include "fw_update/manifest_parse.hh"
#include "fw_update/ram_buffer.hh"
#include "patch_file/file_storage_proxy.hh"
#include <cstdint>

namespace MetaModule
{

// Handle the process of updating firmware
class FirmwareUpdater {
public:
	enum State { Idle, Error, LoadingManifest, LoadingFilesToRAM, Writing, Success };

	FirmwareUpdater(FileStorageProxy &file_storage)
		: file_storage{file_storage} {
	}

	struct Status {
		State state{State::Idle};
		int file_size{0};
		int bytes_remaining{0};
		std::string error_message{};
	};

	bool start(std::string_view manifest_filename, Volume manifest_file_vol, uint32_t manifest_filesize) {
		if (manifest_filesize <= 4 * 1024 * 1024)
		{
			manifest_buffer = std::span<char>{(char *)ram_buffer.data(), manifest_filesize};

			if (file_storage.request_load_file(manifest_filename, manifest_file_vol, manifest_buffer))
			{
				vol = manifest_file_vol;
				state = State::LoadingManifest;
				return true;
			}
			else
			{
				abortWithMessage("Cannot request manifest file");
			}
		}
		else
		{
			abortWithMessage("Manifest file is too large");
			
		}

		return false;		
	}

	Status process() {
		int bytes_remaining = 0;

		switch (state) {
			case Idle:
			case Success:
			case Error:
				break;

			case LoadingManifest: {
				auto message = file_storage.get_message();

				if (message.message_type == FileStorageProxy::LoadFileToRamSuccess) {

					auto parseResult = parser.parse(manifest_buffer);

					if (parseResult and parseResult->files.size() > 0) {
						manifest = *parseResult;
						init_ram_loading();
						state = State::LoadingFilesToRAM;

					} else {
						abortWithMessage("Manifest file is invalid");
					}

				} else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
					abortWithMessage("Failed reading manifest file");
				}

			} break;

			case LoadingFilesToRAM: {
				if (!file_requested)
					start_reading_file();
				else
					check_reading_done();

				if (current_file_idx >= manifest.files.size())
					current_file_size = write_first_file();

			} break;

			case Writing: {
				auto [bytes_rem, err] = current_file_loader->load_next_block();

				if (err == FileLoaderBase::Error::Failed) {
					bytes_remaining = bytes_rem;
					abortWithMessage("Failed writing app to flash");

				} else if (bytes_rem > 0) {
					bytes_remaining = bytes_rem;

				} else {
					current_file_size = write_next_file();
				}

			} break;
			
		};

		if (state == State::Error)
			return {state, current_file_size, bytes_remaining, error_message};
		else
			return {state, current_file_size, bytes_remaining};
	}

private:
	void init_ram_loading() {
		current_file_idx = 0;
		file_requested = false;
		file_images.reserve(manifest.files.size());
	}

	// reads from disk to RAM
	void start_reading_file() {
		auto size = manifest.files[current_file_idx].filesize;

		if (current_file_idx == 0)
			file_images[current_file_idx] = {(char *)ram_buffer.data(), size};
		else
			file_images[current_file_idx] = std::span<char>{
				file_images[current_file_idx - 1].data() + file_images[current_file_idx - 1].size(), size};

		pr_trace("A7: request to load %s to 0x%x\n",
				 manifest.files[current_file_idx].filename.c_str(),
				 file_images[current_file_idx].data());

		if (file_storage.request_load_file(
				manifest.files[current_file_idx].filename, vol, file_images[current_file_idx]))
		{
			file_requested = true;
		} else {
			abortWithMessage("Failed to request firmware file");
		}
	}

	void check_reading_done() {
		auto message = file_storage.get_message();

		if (message.message_type == FileStorageProxy::LoadFileToRamSuccess) {
			pr_trace("A7: file loaded\n");
			current_file_idx++;
			file_requested = false;

		} else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
			abortWithMessage("Failed to load a firmware file");
		}
	}

	int write_first_file() {
		current_file_idx = 0;
		return start_writing_file();
	}

	int write_next_file() {
		current_file_idx++;
		return start_writing_file();
	}

	// writes from RAM to flash/wifi-uart
	int start_writing_file() {
		if (current_file_idx > manifest.files.size()) {
			state = State::Success;
			return 0;
		}

		int file_size = file_images[current_file_idx].size();
		auto &cur_file = manifest.files[current_file_idx];

		switch (cur_file.type) {

			case UpdateType::App:
				current_file_loader = std::make_unique<FirmwareFlashLoader>(file_images[current_file_idx]);
				break;

			case UpdateType::Wifi:
				current_file_loader = std::make_unique<FirmwareWifiLoader>(file_images[current_file_idx]);
				break;
				
			default:
				current_file_loader.reset();
				pr_err("Invalid update file type\n");
				break;
		}

		if (current_file_loader)
		{
			if (!current_file_loader->verify(cur_file.md5)) {
				abortWithMessage("App firmware file not valid");
				return file_size;
			}

			if (!current_file_loader->start()) {
				abortWithMessage("Could not start writing application firmware to flash");
				return file_size;
			}

			state = State::Writing;
		}

		return file_size;
	}

private:
	void abortWithMessage(const char* message)
	{
		state = State::Error;
		error_message = message;
	}

private:
	std::unique_ptr<FileLoaderBase> current_file_loader;

	ManifestParser parser;

	FileStorageProxy &file_storage;
	State state = State::Idle;

	Volume vol = Volume::USB;

	unsigned current_file_idx = 0;
	int current_file_size = 0;
	bool file_requested = false;

	std::span<char> manifest_buffer;

	std::string error_message = "";

	const std::span<uint8_t> ram_buffer = get_ram_buffer();

	UpdateManifest manifest;
	std::vector<std::span<char>> file_images;
};

} // namespace MetaModule
