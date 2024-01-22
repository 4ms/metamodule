#include "firmware_writer.hh"
 
#include <wifi/flasher/flasher.h>

namespace MetaModule
{

FirmwareWriter::FirmwareWriter(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
	: sdcard_{sdcard_fileio}
	, usbdrive_{usb_fileio} {
}

void FirmwareWriter::handle_message(IntercoreStorageMessage &message)
{
	if (message.message_type == StartChecksumCompare)
	{
		message.message_type = None;

		pr_dbg("-> Compare with checksum %s at 0x%08x\n", message.checksum.c_str(), message.address);

		pending_send_message = compareChecksumWifi(message.address, message.length, {message.checksum.data()});
	}
	else if (message.message_type == StartFlashing)
	{
		message.message_type = None;

		pr_dbg("-> Start flashing to 0x%08x\n", message.address);

		FatFileIO *fileio = (message.vol_id == Volume::USB)	   ? &usbdrive_ :
							(message.vol_id == Volume::SDCard) ? &sdcard_ :
																	nullptr;

		if (fileio != nullptr)
		{
			pending_send_message = flashWifi(fileio, message.filename, message.address, message.length, *message.bytes_processed);
		}
		else
		{
			pr_err("Invalid volume id %u for update file\n", message.vol_id);
			pending_send_message.message_type = FlashingFailed;
		}
	}

}

IntercoreStorageMessage FirmwareWriter::compareChecksumWifi(uint32_t address, uint32_t length, Checksum_t checksum)
{
	IntercoreStorageMessage returnValue;

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

void FirmwareWriter::send_pending_message(InterCoreComm &comm) {
	if (pending_send_message.message_type != None) {
		if (comm.send_message(pending_send_message))
			pending_send_message.message_type = None;
	}
}



} // namespace MetaModule
