#pragma once
#include "audio/calibration_data_reader.hh"
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "flash_loader/flash_loader.hh"

namespace MetaModule
{

class CalibrationMessageHandler {
	FlashLoader &loader;
	CalibrationDataReader reader;

public:
	CalibrationMessageHandler(FlashLoader &loader)
		: loader{loader}
		, reader{loader} {
	}

	std::optional<IntercoreStorageMessage> handle_message(const IntercoreStorageMessage &message) {
		using enum IntercoreStorageMessage::MessageType;

		if (message.message_type == RequestReadFlash) {
			pr_trace("CalibrationDataManager got message to read flash at 0x%x\n", message.address);

			if (message.address == CalDataFlashOffset) {

				if (message.buffer.data() && message.buffer.size() >= sizeof(CalData)) {

					auto *caldata = new (message.buffer.data()) CalData;
					if (!reader.read_calibration(caldata))
						caldata->reset_to_default();

					return IntercoreStorageMessage{.message_type = ReadFlashOk, .bytes_read = sizeof(CalData)};

				} else {
					pr_err("Buffer size is not large enough to read CalData\n");

					return IntercoreStorageMessage{.message_type = ReadFlashOk, .bytes_read = sizeof(CalData)};
				}
			}
		}

		// Writing is handled by FirmwareWriter, via the StartFlashing message

		// Message not handled, pass it on to other handlers
		return std::nullopt;
	}
};

} // namespace MetaModule
