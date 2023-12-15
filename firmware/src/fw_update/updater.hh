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
struct FirmwareUpdater {
	enum State { Idle, Error, LoadingManifest, LoadingFilesToRAM, WritingApp, WritingWifi, Success };

	FirmwareUpdater(FileStorageProxy &file_storage)
		: file_storage{file_storage} {

		//Overwrite buffer with 0's in some key places
		//So we fail unless a valid file is loaded
		auto *uimg_header = reinterpret_cast<BootImageDef::ImageHeader *>(ram_buffer.data());
		uimg_header->ih_magic = 0;
		uimg_header->ih_size = 0;
	}

	bool verify_update(uint32_t filesize) {
		return false;
	}

	bool start(std::string_view manifest_filename, Volume manifest_file_vol, uint32_t manifest_filesize) {
		if (manifest_filesize > 4096) {
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

	struct Status {
		State state{State::Idle};
		int bytes_remaining{0};
		std::string error_message{};
	};

	// return flash_writer.start();
	Status process() {

		switch (state) {
			case Idle:
			case Success:
			case Error:
				break;

			case LoadingManifest: {
				auto message = file_storage.get_message();

				if (message.message_type == FileStorageProxy::LoadFileToRamSuccess) {

					files = parser.parse(manifest_buffer);

					if (files.size() > 0) {
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

				if (current_file_idx >= files.size())
					init_writing();

			} break;

			case WritingApp: {
				auto [bytes_remaining, err] = flash_loader.load_next_block();

				if (err == FirmwareFlashLoader::Error::Failed) {
					state = State::Error;
					return {state, bytes_remaining, "Failed writing app to flash"};

				} else if (bytes_remaining > 0) {
					return {state, bytes_remaining};

				} else {
					current_file_idx++;
					start_writing_file();
				}

			} break;

			case WritingWifi: {
			} break;
		};

		if (state == State::Error)
			return {state, 0, error_message};
		else
			return {state};
	}

	void init_ram_loading() {
		current_file_idx = 0;
		file_requested = false;
		file_images.reserve(files.size());
	}

	void start_reading_file() {
		auto size = files[current_file_idx].filesize;
		if (current_file_idx == 0)
			file_images[current_file_idx] = {(char *)ram_buffer.data(), size};
		else
			file_images[current_file_idx] = {file_images[current_file_idx].end(), size};

		if (file_storage.request_load_file(files[current_file_idx].filename, vol, file_images[current_file_idx]))
			file_requested = true;
		else {
			state = State::Error;
			error_message = "Failed to request firmware file";
		}
	}

	void check_reading_done() {
		auto message = file_storage.get_message();

		if (message.message_type == FileStorageProxy::LoadFileToRamSuccess) {
			current_file_idx++;
			file_requested = false;

		} else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
			state = State::Error;
			error_message = "Failed to load a firmware file";
		}
	}

	void init_writing() {
		current_file_idx = 0;
		start_writing_file();
	}

	void start_writing_file() {
		if (current_file_idx > files.size()) {
			state = State::Success;
			return;
		}

		if (files[current_file_idx].type == UpdateType::App) {

			if (!flash_loader.verify(as_u8(file_images[current_file_idx]))) {
				state = State::Error;
				error_message = "App firmware file not valid";
				return;
			}

			if (!flash_loader.start(as_u8(file_images[current_file_idx]))) {
				state = State::Error;
				error_message = "Could not start writing to Flash chip";
			}

			state = State::WritingApp;

		} else if (files[current_file_idx].type == UpdateType::Wifi) {

			state = State::WritingWifi;

			if (!wifi_loader.verify(as_u8(file_images[current_file_idx]))) {
				state = State::Error;
				error_message = "App firmware file not valid";
				return;
			}

			if (!wifi_loader.start(as_u8(file_images[current_file_idx]))) {
				state = State::Error;
				error_message = "Could not start writing to Flash chip";
			}

			state = State::WritingWifi;
		}
	}

private:
	FirmwareFlashLoader flash_loader;
	FirmwareWifiLoader wifi_loader;

	ManifestParser parser;

	FileStorageProxy &file_storage;
	State state;

	Volume vol;

	unsigned current_file_idx = 0;
	bool file_requested = false;

	std::span<char> manifest_buffer;

	std::string error_message = "";

	const std::span<uint8_t> ram_buffer = get_ram_buffer();

	std::vector<UpdateFile> files;
	std::vector<std::span<char>> file_images;

	static std::span<uint8_t> as_u8(std::span<char> s) {
		return {(uint8_t *)s.data(), s.size()};
	}
};

} // namespace MetaModule
