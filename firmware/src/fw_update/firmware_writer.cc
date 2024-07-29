#include "firmware_writer.hh"
#include "hash/hash_processor.hh"
#include "wifi/comm/wifi_interface.hh"
#include "wifi/flasher/flasher.h"

namespace MetaModule
{

FirmwareWriter::FirmwareWriter(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio, FlashLoader &flash_loader)
	: sdcard_{sdcard_fileio}
	, usbdrive_{usb_fileio}
	, loader_{flash_loader} {
}

std::optional<IntercoreStorageMessage> FirmwareWriter::handle_message(const IntercoreStorageMessage &message) {
	using enum IntercoreStorageMessage::FlashTarget;

	if (message.message_type == StartChecksumCompare) {
		pr_dbg("-> Compare with checksum %s at 0x%08x\n", message.checksum.c_str(), message.address);

		if (message.flashTarget == WIFI) {
			return compareChecksumWifi(message.address, message.length, {message.checksum.data()});

		} else if (message.flashTarget == QSPI) {
			return compareChecksumQSPI(
				message.address, message.length, {message.checksum.data()}, *message.bytes_processed);

		} else {
			pr_err("Undefined flash target %u\n", message.flashTarget);
			return IntercoreStorageMessage{.message_type = ChecksumFailed};
		}

	} else if (message.message_type == StartFlashing) {
		pr_dbg("-> Start flashing to 0x%08x\n", message.address);
		auto buf = std::span<uint8_t>{(uint8_t *)message.buffer.data(), message.buffer.size()};

		if (message.flashTarget == WIFI) {
			return flashWifi(buf, message.address, message.uncompressed_size, *message.bytes_processed);

		} else if (message.flashTarget == QSPI) {
			return flashQSPI(buf, message.address, *message.bytes_processed);

		} else {
			pr_err("Undefined flash target %u\n", message.flashTarget);
			return IntercoreStorageMessage{.message_type = FlashingFailed};
		}

	} else {
		return std::nullopt;
	}
}

IntercoreStorageMessage FirmwareWriter::compareChecksumWifi(uint32_t address, uint32_t length, Checksum_t checksum) {
	IntercoreStorageMessage returnValue;

// Stop wifi reception before long running operation
#ifdef ENABLE_WIFI_BRIDGE
	WifiInterface::stop();
#endif

	auto result = Flasher::init(230400);

	if (result == ESP_LOADER_SUCCESS) {

		if (result == ESP_LOADER_SUCCESS) {
			result = Flasher::verify(address, length, checksum);
			if (result == ESP_LOADER_ERROR_INVALID_MD5) {
				returnValue = {.message_type = ChecksumMismatch};
			} else if (result == ESP_LOADER_SUCCESS) {
				pr_dbg("-> Checksum matches\n");
				returnValue = {.message_type = ChecksumMatch};
			} else {
				pr_dbg("-> Cannot get checksum\n");
				returnValue = {.message_type = ChecksumFailed};
			}
		} else {
			pr_err("Cannot write dummy byte to wifi flash\n");
			returnValue = {.message_type = ChecksumFailed};
		}
	} else {
		pr_err("Cannot connect to wifi bootloader\n");
		returnValue = {.message_type = ChecksumFailed};
	}

	Flasher::deinit();

	return returnValue;
}

IntercoreStorageMessage FirmwareWriter::flashWifi(std::span<uint8_t> buffer, uint32_t address, std::optional<uint32_t> uncompressed_size, uint32_t &bytesWritten) {
	IntercoreStorageMessage returnValue;

// Stop wifi reception before long running operation
#ifdef ENABLE_WIFI_BRIDGE
	WifiInterface::stop();
#endif

	auto result = Flasher::init(230400);

	if (result == ESP_LOADER_SUCCESS) {
		const std::size_t BatchSize = 1024;

		result = Flasher::flash_start(address, buffer.size(), BatchSize, uncompressed_size);

		if (result == ESP_LOADER_SUCCESS) {
			bool error_during_writes = false;

			while (bytesWritten < buffer.size()) {
				auto to_read = std::min<std::size_t>(buffer.size() - bytesWritten, BatchSize);
				auto thisBatch = buffer.subspan(bytesWritten, to_read);

				result = Flasher::flash_process(thisBatch, uncompressed_size.has_value());

				if (result != ESP_LOADER_SUCCESS) {
					error_during_writes = true;
					break;
				} else {
					bytesWritten += to_read;
				}
			}

			if (not error_during_writes)
			{
				result = Flasher::flash_finish(uncompressed_size.has_value());
				error_during_writes = result != ESP_LOADER_SUCCESS;
			}

			if (not error_during_writes) {
				pr_dbg("-> Flashing completed\n");
				returnValue = {.message_type = FlashingOk};
			} else {
				pr_dbg("-> Flashing failed\n");
				returnValue = {.message_type = FlashingFailed};
			}
		} else {
			pr_err("Cannot start flashing wifi\n");
			returnValue = {.message_type = FlashingFailed};
		}
	} else {
		pr_err("Cannot connect to wifi bootloader\n");
		returnValue = {.message_type = FlashingFailed};
	}

	Flasher::deinit();

	return returnValue;
}

IntercoreStorageMessage
FirmwareWriter::compareChecksumQSPI(uint32_t address, uint32_t length, Checksum_t checksum, uint32_t &bytesChecked) {

	// Stop wifi reception before long running operation
#ifdef ENABLE_WIFI_BRIDGE
	WifiInterface::stop();
#endif

	MD5Processor processor;

	const std::size_t BlockSize = 4096;
	std::array<uint8_t, BlockSize> BlockBuffer;

	std::size_t offset = 0;
	while (offset < length) {
		auto bytesToRead = std::min<std::size_t>(length - offset, BlockBuffer.size());
		auto thisReadArea = std::span<uint8_t>(BlockBuffer.data(), bytesToRead);

		auto read_result = loader_.read_sectors(address + offset, thisReadArea);

		if (read_result) {
			processor.update(thisReadArea);
			offset += bytesToRead;
			bytesChecked = offset;
		} else {
			return {.message_type = ChecksumFailed};
		}
	}

	auto str_digest = to_hex_string(processor.getDigest());
	auto str_digest_sv = std::string_view(str_digest.data(), str_digest.size());

	auto match = checksum.compare(str_digest_sv) == 0;

	return {.message_type = match ? ChecksumMatch : ChecksumMismatch};
}

IntercoreStorageMessage FirmwareWriter::flashQSPI(std::span<uint8_t> buffer, uint32_t address, uint32_t &bytesWritten) {

// Stop wifi reception before long running operation
#ifdef ENABLE_WIFI_BRIDGE
	WifiInterface::stop();
#endif

	const uint32_t FlashSectorSize = 4096;
	const std::size_t BatchSize = FlashSectorSize;
	bytesWritten = 0;

	bool errorDetected = false;

	if (loader_.check_flash_chip()) {
		while (bytesWritten < buffer.size()) {
			auto to_read = std::min<std::size_t>(buffer.size() - bytesWritten, BatchSize);
			auto thisBatch = buffer.subspan(bytesWritten, to_read);

			auto success = loader_.write_sectors(address + bytesWritten, thisBatch);

			if (success) {
				bytesWritten += to_read;
			} else {
				errorDetected = true;
				break;
			}
		}
	} else {
		errorDetected = true;
	}

	return errorDetected ? IntercoreStorageMessage{.message_type = FlashingFailed} :
						   IntercoreStorageMessage{.message_type = FlashingOk};
}

} // namespace MetaModule
