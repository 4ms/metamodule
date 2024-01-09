#pragma once
#include "fw_update/firmware_flash_loader.hh"
#include "fw_update/firmware_wifi_loader.hh"
#include "fw_update/manifest_parse.hh"
#include "fw_update/ram_buffer.hh"
#include "fw_update/uimg_header.hh"
#include "patch_file/file_storage_proxy.hh"
#include <cstdint>

namespace MetaModule
{

// Handle the process of updating firmware
class FirmwareUpdater {
public:
	enum State { Idle, Error, LoadingManifest, LoadingFilesToRAM, WritingApp, WritingWifi, Success };

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
		if (manifest_filesize > 4 * 1024 * 1024) {
			pr_err("manifest file is too large\n");
			state = State::Error;
			return false;
		}

		manifest_buffer = std::span<char>{(char *)ram_buffer.data(), manifest_filesize};

		if (file_storage.request_load_file(manifest_filename, manifest_file_vol, manifest_buffer))
			state = State::LoadingManifest;
		else
			state = State::Error;

		vol = manifest_file_vol;

		return state != State::Error;
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
						state = State::Error;
						error_message = "Manifest file is invalid";
					}

				} else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
					state = State::Error;
					error_message = "Failed reading manifest file";
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

			case WritingApp: {
				auto [bytes_rem, err] = flash_loader.load_next_block();

				if (err == FirmwareFlashLoader::Error::Failed) {
					state = State::Error;
					bytes_remaining = bytes_rem;
					error_message = "Failed writing app to flash";

				} else if (bytes_rem > 0) {
					bytes_remaining = bytes_rem;

				} else {
					current_file_size = write_next_file();
				}

			} break;

			case WritingWifi: {
				auto [bytes_rem, err] = wifi_loader.load_next_block();

				if (err == FirmwareWifiLoader::Error::Failed) {
					state = State::Error;
					bytes_remaining = bytes_rem;
					error_message = "Failed writing firmware to wifi module";

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
			state = State::Error;
			error_message = "Failed to request firmware file";
		}
	}

	void check_reading_done() {
		auto message = file_storage.get_message();

		if (message.message_type == FileStorageProxy::LoadFileToRamSuccess) {
			pr_trace("A7: file loaded\n");
			current_file_idx++;
			file_requested = false;

		} else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
			state = State::Error;
			error_message = "Failed to load a firmware file";
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

			case UpdateType::App: {
				if (!flash_loader.verify(file_images[current_file_idx], cur_file.md5, cur_file.type)) {
					state = State::Error;
					error_message = "App firmware file not valid";
					return file_size;
				}

				if (!flash_loader.start()) {
					state = State::Error;
					error_message = "Could not start writing application firmware to flash";
					return file_size;
				}

				state = State::WritingApp;
			} break;

			case UpdateType::WifiApp:
			case UpdateType::WifiFirmware:
			case UpdateType::WifiFilesystem: {
				if (!wifi_loader.verify(file_images[current_file_idx], cur_file.md5, cur_file.type)) {
					state = State::Error;
					error_message = "Wifi firmware file not valid";
					return file_size;
				}

				if (!wifi_loader.start()) {
					state = State::Error;
					error_message = "Could not start writing to Wifi module";
					return file_size;
				}

				state = State::WritingWifi;
			} break;

			default:
				pr_err("Invalid update file type\n");
				break;
		}

		return file_size;
	}

private:
	FirmwareFlashLoader flash_loader;
	FirmwareWifiLoader wifi_loader;

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
