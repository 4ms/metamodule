#include "firmware_writer.hh"
 
#include <wifi/flasher/flasher.h>
#include <wifi/comm/wifi_interface.hh>
#include "flash_loader/flash_loader.hh"

#include "hash/hash_processor.hh"

namespace MetaModule
{

FirmwareWriter::FirmwareWriter(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
	: sdcard_{sdcard_fileio}
	, usbdrive_{usb_fileio} {
}

std::optional<IntercoreStorageMessage> FirmwareWriter::handle_message(const IntercoreStorageMessage& message)
{
	if (message.message_type == StartChecksumCompare)
	{
		pr_dbg("-> Compare with checksum %s at 0x%08x\n", message.checksum.c_str(), message.address);

		if (message.flashTarget == IntercoreStorageMessage::FlashTarget::WIFI)
		{
			return compareChecksumWifi(message.address, message.length, {message.checksum.data()});
		}
		else if (message.flashTarget == IntercoreStorageMessage::FlashTarget::QSPI)
		{
			return compareChecksumQSPI(message.address, message.length, {message.checksum.data()});
		}
		else
		{
			pr_err("Undefined flash target %u\n", message.flashTarget);
			return IntercoreStorageMessage{.message_type = ChecksumFailed};
		}
	}
	else if (message.message_type == StartFlashing)
	{
		pr_dbg("-> Start flashing to 0x%08x\n", message.address);

		FatFileIO *fileio = (message.vol_id == Volume::USB)	   ? &usbdrive_ :
							(message.vol_id == Volume::SDCard) ? &sdcard_ :
																	nullptr;

		if (fileio != nullptr)
		{
			if (message.flashTarget == IntercoreStorageMessage::FlashTarget::WIFI)
			{
				return flashWifi(fileio, message.filename, message.address, message.length, *message.bytes_processed);
			}
			else if (message.flashTarget == IntercoreStorageMessage::FlashTarget::QSPI)
			{
				return flashQSPI(fileio, message.filename, message.address, message.length, *message.bytes_processed);
			}
			else
			{
				pr_err("Undefined flash target %u\n", message.flashTarget);
				return IntercoreStorageMessage{.message_type = FlashingFailed};
			}
		}
		else
		{
			pr_err("Invalid volume id %u for update file\n", message.vol_id);
			return IntercoreStorageMessage{.message_type = FlashingFailed};
		}
	}
	else
	{
		return std::nullopt;
	}


}

IntercoreStorageMessage FirmwareWriter::compareChecksumWifi(uint32_t address, uint32_t length, Checksum_t checksum)
{
	IntercoreStorageMessage returnValue;

	// Stop wifi reception before long running operation
	#ifdef ENABLE_WIFI_BRIDGE
	WifiInterface::stop();
	#endif

	auto result = Flasher::init(230400);

	if (result == ESP_LOADER_SUCCESS)
	{
		result = Flasher::verify(address, length, checksum);
		if (result == ESP_LOADER_ERROR_INVALID_MD5)
		{
			returnValue = {.message_type = ChecksumMismatch};
		}
		else if (result == ESP_LOADER_SUCCESS)
		{
			pr_dbg("-> Checksum matches\n");
			returnValue = {.message_type = ChecksumMatch};
		}
		else
		{
			pr_dbg("-> Cannot get checksum\n");
			returnValue = {.message_type = ChecksumFailed};
		}
	}
	else
	{
		pr_err("Cannot connect to wifi bootloader\n");
		returnValue = {.message_type = ChecksumFailed};
	}

	Flasher::deinit();

	return returnValue;
}

IntercoreStorageMessage FirmwareWriter::flashWifi(FatFileIO* fileio, std::string_view filename, uint32_t address, const uint32_t length, uint32_t& bytesWritten)
{
	IntercoreStorageMessage returnValue;

	// Stop wifi reception before long running operation
	#ifdef ENABLE_WIFI_BRIDGE
	WifiInterface::stop();
	#endif

	auto result = Flasher::init(230400);

	if (result == ESP_LOADER_SUCCESS)
	{
		std::array<uint8_t, 1024> BatchBuffer;

		result = Flasher::flash_start(address, length, BatchBuffer.size());

		if (result == ESP_LOADER_SUCCESS)
		{
			bool error_during_writes = false;

			while (bytesWritten < length)
			{
				auto to_read = std::min<std::size_t>(length - bytesWritten, BatchBuffer.size());

				auto thisReadBuffer = std::span<char>((char*)BatchBuffer.data(), to_read);
				auto bytesRead = fileio->read_file(filename, thisReadBuffer, bytesWritten);

				if (bytesRead == to_read)
				{
					result = Flasher::flash_process(std::span<uint8_t>((uint8_t*)thisReadBuffer.data(), thisReadBuffer.size()));
					if (result != ESP_LOADER_SUCCESS)
					{
						error_during_writes = true;
						break;
					}
					else
					{
						bytesWritten += to_read;
					}
				}
				else
				{
					pr_err("Cannot read from update file in range %u - %u\n", bytesWritten, bytesWritten+to_read);
					error_during_writes = true;
					break;
				}
			}

			if (not error_during_writes)
			{
				pr_dbg("-> Flashing completed\n");
				returnValue = {.message_type = FlashingOk};
			}
			else
			{
				pr_dbg("-> Flashing failed\n");
				returnValue = {.message_type = FlashingFailed};
			}
		}
		else
		{
			pr_err("Cannot start flashing wifi\n");
			returnValue = {.message_type = FlashingFailed};
		}
	}
	else
	{
		pr_err("Cannot connect to wifi bootloader\n");
		returnValue = {.message_type = FlashingFailed};
	}

	Flasher::deinit();

	return returnValue;
}

IntercoreStorageMessage FirmwareWriter::compareChecksumQSPI(uint32_t address, uint32_t length, Checksum_t checksum)
{
	FlashLoader loader;
	MD5Processor processor;
	
	const std::size_t BlockSize = 4096;
	std::array<uint8_t, BlockSize> BlockBuffer;

	std::size_t offset = 0;
	while (offset < length)
	{
		auto bytesToRead = std::min<std::size_t>(length-offset, BlockBuffer.size());
		auto thisReadArea = std::span<uint8_t>(BlockBuffer.data(), bytesToRead);

		auto read_result = loader.read_sectors(address + offset, thisReadArea);
		
		if (read_result)
		{
			processor.update(thisReadArea);
			offset += bytesToRead;
		}
		else
		{
			return {.message_type = ChecksumFailed};
		}
	}

	auto str_digest = to_hex_string(processor.getDigest());
	auto str_digest_sv = std::string_view(str_digest.data(), str_digest.size());

	auto match = checksum.compare(str_digest_sv) == 0;

	return {.message_type = match ? ChecksumMatch : ChecksumMismatch};
}

IntercoreStorageMessage FirmwareWriter::flashQSPI(FatFileIO* fileio, std::string_view filename, uint32_t address, const uint32_t length, uint32_t& bytesWritten)
{
    FlashLoader loader;

	// Stop wifi reception before long running operation
	#ifdef ENABLE_WIFI_BRIDGE
	WifiInterface::stop();
	#endif

	constexpr static uint32_t FlashSectorSize = 4096;
	std::array<uint8_t, FlashSectorSize> BatchBuffer;
	bytesWritten = 0;

	bool errorDetected = false;

    if (loader.check_flash_chip())
	{
		while (bytesWritten < length)
		{
			auto to_read = std::min<std::size_t>(length - bytesWritten, BatchBuffer.size());

			auto thisReadBuffer = std::span<char>((char*)BatchBuffer.data(), to_read);
			auto bytesRead = fileio->read_file(filename, thisReadBuffer, bytesWritten);

			if (bytesRead == to_read)
			{
				auto success = loader.write_sectors(address + bytesWritten, thisReadBuffer);

				if (success)
				{
					bytesWritten += to_read;
				}
				else
				{
					errorDetected = true;
					break;
				}
			}
			else
			{
				pr_err("Cannot read from update file in range %u - %u\n", bytesWritten, bytesWritten+to_read);
				errorDetected = true;
				break;
			}
		}
	}
	else
	{
		errorDetected = true;
	}


	return errorDetected ? IntercoreStorageMessage{.message_type = FlashingFailed} : IntercoreStorageMessage{.message_type = FlashingOk};
}



} // namespace MetaModule
