#include "updater_proxy.hh"
#include "fw_update/update_path.hh"
#include "manifest_parse.hh"
#include "pr_dbg.hh"
#include <algorithm>
#include <cassert>

namespace MetaModule
{

auto GetTargetForUpdateType = [](UpdateType val) -> std::optional<IntercoreStorageMessage::FlashTarget> {
	switch (val) {
		case UpdateType::Wifi:
			return IntercoreStorageMessage::FlashTarget::WIFI;
		case UpdateType::App:
			return IntercoreStorageMessage::FlashTarget::QSPI;
		default:
			return std::nullopt;
	}
};

FirmwareUpdaterProxy::FirmwareUpdaterProxy(FileStorageProxy &file_storage)
	: file_storage{file_storage}
	, state(Idle)
	, sharedMem(nullptr)
	, allocator(get_ram_buffer()) {
}

bool FirmwareUpdaterProxy::start(std::string_view manifest_filename,
								 Volume manifest_file_vol,
								 uint32_t manifest_filesize) {

	allocator.reset();

	if (auto sharedMemPtr = allocator.allocate(sizeof(SharedMem)); sharedMemPtr) {

		sharedMem = new (sharedMemPtr) SharedMem;

		if (auto manifestPtr = allocator.allocate(manifest_filesize); manifestPtr) {

			manifestBuffer = std::span<char>((char *)manifestPtr, manifest_filesize);

			if (file_storage.request_load_file(manifest_filename, manifest_file_vol, manifestBuffer)) {
				vol = manifest_file_vol;
				moveToState(State::LoadingManifest);
				return true;
			} else {
				abortWithMessage("Cannot request manifest file");
			}
		} else {
			abortWithMessage("Manifest file is too large");
		}

	} else {
		abortWithMessage("Cannot allocate shared memory");
	}

	return false;
}

FirmwareUpdaterProxy::Status FirmwareUpdaterProxy::process() {
	error_message = "";

	switch (state) {
		case Idle:
		case Success:
		case Error:
			break;

		case LoadingManifest: {
			auto message = file_storage.get_message();

			if (message.message_type == FileStorageProxy::LoadFileToRamSuccess) {
				ManifestParser parser;

				auto parseResult = parser.parse(manifestBuffer);
				if (!parseResult) {
					abortWithMessage("Manifest file is invalid");
					break;
				}

				// uncomment the following to ignore files that point to bootloader areas
				// std::erase_if(parseResult->files,
				// 			  [](auto file) { return file.type == UpdateType::App and file.address < 0x80000; });

				if (parseResult->files.size() > 0) {
					manifest = *parseResult;

					for (auto &file : manifest.files) {
						file.filename = std::string{UpdateFileDirectory} + file.filename;
					}

					moveToState(State::LoadingUpdateFiles);

				} else {
					abortWithMessage("Manifest file has no valid files");
				}

			} else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
				abortWithMessage("Failed reading manifest file");
			}

		} break;

		case LoadingUpdateFiles: {

			bool requestLoadingCurrentFile = false;

			if (justEnteredState) {
				justEnteredState = false;

				current_file_idx = 0;
				requestLoadingCurrentFile = true;
			} else {
				auto message = file_storage.get_message();

				if (message.message_type != FileStorageProxy::None) {
					if (message.message_type == FileStorageProxy::LoadFileToRamSuccess) {
						current_file_idx++;

						if (current_file_idx == manifest.files.size()) {
							current_file_idx = 0;
							moveToState(Verifying);
						} else {
							requestLoadingCurrentFile = true;
						}
					} else {
						abortWithMessage("Failed loading update file");
					}
				}
			}

			if (requestLoadingCurrentFile) {
				auto &thisFile = manifest.files[current_file_idx];

				if (auto thisFileBuffer = allocator.allocate(thisFile.filesize); thisFileBuffer) {
					auto requestResult = file_storage.request_load_file(
						thisFile.filename, vol, {(char *)thisFileBuffer, thisFile.filesize});

					if (requestResult) {
						loadedFiles.emplace_back(thisFileBuffer, thisFile.filesize);
					} else {
						abortWithMessage("Cannot request loading update file");
					}
				} else {
					abortWithMessage("Cannot allocate buffer for update file");
				}
			}

		} break;

		case Verifying: {
			if (justEnteredState) {
				justEnteredState = false;
				pr_dbg("Start verifying file %u of %u\n", current_file_idx + 1, manifest.files.size());

				auto &thisFile = manifest.files[current_file_idx];

				if (auto target = GetTargetForUpdateType(thisFile.type); target) {
					if (auto checksumValue = thisFile.md5; checksumValue) {
						sharedMem->bytes_processed = 0;
						current_file_size = thisFile.filesize;
						current_file_name = thisFile.name;

						auto result = file_storage.request_checksum_compare(
							*target, *checksumValue, thisFile.address, thisFile.filesize, &sharedMem->bytes_processed);

						if (not result) {
							abortWithMessage("Cannot trigger comparing checksums");
						}
					} else {
						pr_dbg("Skipping verify step because no checksum is defined");
						moveToState(Writing);
					}
				} else {
					abortWithMessage("Invalid update file type");
				}
			} else {
				switch (file_storage.get_message().message_type) {
					case FileStorageProxy::ChecksumMatch:
						proceedWithNextFile();
						break;

					case FileStorageProxy::ChecksumMismatch:
						moveToState(Writing);
						break;

					case FileStorageProxy::WifiExpanderCommError:
					case FileStorageProxy::ReadFlashFailed:
					case FileStorageProxy::ChecksumFailed:
						abortWithMessage("Error when comparing checksums");
						break;

					case FileStorageProxy::WifiExpanderNotConnected:
						error_message = "No Wifi Expander: skipping " + manifest.files[current_file_idx].filename;
						proceedWithNextFile();
						break;

					default:
						break;
				}
			}
		} break;

		case Writing: {
			if (justEnteredState) {
				justEnteredState = false;
				pr_dbg("Start flashing file %u of %u\n", current_file_idx + 1, manifest.files.size());

				auto &thisFile = manifest.files[current_file_idx];
				auto &thisLoadedFile = loadedFiles[current_file_idx];

				sharedMem->bytes_processed = 0;
				current_file_size = thisFile.filesize;
				current_file_name = thisFile.name;

				if (auto target = GetTargetForUpdateType(thisFile.type); target) {
					auto result = file_storage.request_file_flash(
						*target, thisLoadedFile, thisFile.address, &sharedMem->bytes_processed);

					if (not result) {
						// this is not an error, just need to retry
						justEnteredState = true;
					}
				} else {
					abortWithMessage("Invalid update file type");
				}
			} else {
				switch (file_storage.get_message().message_type) {
					case FileStorageProxy::FlashingOk:
						proceedWithNextFile();
						break;

					case FileStorageProxy::FlashingFailed:
						abortWithMessage("Error when flashing file");
						break;

					default:
						break;
				}
			}

		} break;

		default:
			pr_err("Undefined state\n");
			abortWithMessage("Internal Error");
	}

	return Status{state, current_file_name, current_file_size, sharedMem->bytes_processed, error_message};
}

void FirmwareUpdaterProxy::abortWithMessage(const char *message) {
	state = State::Error;
	error_message = message;
}

void FirmwareUpdaterProxy::proceedWithNextFile() {
	current_file_idx++;
	if (current_file_idx < manifest.files.size()) {
		moveToState(Verifying);
	} else {
		moveToState(Success);
	}
}

void FirmwareUpdaterProxy::moveToState(State newState) {
	justEnteredState = true;
	pr_trace("Updater: Move state %u -> %u\n", state, newState);
	state = newState;
}

} // namespace MetaModule
