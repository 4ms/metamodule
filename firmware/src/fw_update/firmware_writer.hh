#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fat_file_io.hh"
#include <cstring>
#include <optional>

#include <wifi/flasher/flasher.h>

namespace MetaModule
{

struct FirmwareWriter {
	using InterCoreComm = mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;

	FirmwareWriter(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio} {
	}

	void handle_message(IntercoreStorageMessage &message)
	{
		if (message.message_type == StartChecksumCompare)
		{
			message.message_type = None;

			pr_dbg("-> Compare with checksum %s at 0x%08x\n", message.checksum.c_str(), message.address);

			auto result = Flasher::init(230400);

			if (result == ESP_LOADER_SUCCESS)
			{
				result = Flasher::verify(message.address, message.length, {message.checksum.data(), 32});
				if (result == ESP_LOADER_ERROR_INVALID_MD5)
				{
					pending_send_message.message_type = ChecksumMismatch;
				}
				else if (result == ESP_LOADER_SUCCESS)
				{
					pr_dbg("-> Checksum matches\n");
					pending_send_message.message_type = ChecksumMatch;
				}				
			}
			else
			{
				pr_err("Cannot connect to wifi bootloader\n");
				pending_send_message.message_type = ChecksumFailed;
			}

			Flasher::deinit();
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
				auto result = Flasher::init(230400);

				if (result == ESP_LOADER_SUCCESS)
				{
					uint32_t& bytesWritten = *message.bytes_processed;
					const uint32_t bytesTotal = message.length;

					std::array<uint8_t, 1024> BatchBuffer;

					result = Flasher::flash_start(message.address, message.length, BatchBuffer.size());

					if (result == ESP_LOADER_SUCCESS)
					{
						bool error_during_writes = false;

						while (bytesWritten < bytesTotal)
						{
							auto to_read = std::min<std::size_t>(bytesTotal - bytesWritten, BatchBuffer.size());

							auto thisReadBuffer = std::span<char>((char*)BatchBuffer.data(), to_read);
							auto bytesRead = fileio->read_file(message.filename, thisReadBuffer, bytesWritten);

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
							pending_send_message.message_type = FlashingOk;
						}
						else
						{
							pr_dbg("-> Flashing failed\n");
							pending_send_message.message_type = FlashingFailed;
						}
					}
					else
					{
						pr_err("Cannot start flashing wifi\n");
						pending_send_message.message_type = FlashingFailed;
					}
				}
				else
				{
					pr_err("Cannot connect to wifi bootloader\n");
					pending_send_message.message_type = FlashingFailed;
				}

				Flasher::deinit();
			}
			else
			{
				pr_err("Invalid volume id %u for update file\n", message.vol_id);
				pending_send_message.message_type = FlashingFailed;
			}
		}

	}

	void send_pending_message(InterCoreComm &comm) {
		if (pending_send_message.message_type != None) {
			if (comm.send_message(pending_send_message))
				pending_send_message.message_type = None;
		}
	}

private:
	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;
	
	IntercoreStorageMessage pending_send_message{.message_type = None};

};

} // namespace MetaModule
