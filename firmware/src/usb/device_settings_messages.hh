#pragma once
#include "core_intercom/intercore_devicesettings_message.hh"
#include "drivers/inter_core_comm.hh"

namespace MetaModule
{

struct DeviceSettingsMessages {

	DeviceSettingsMessages(DeviceSettingsMessage *shared_message)
		: intercore_comm{*shared_message} {
	}

	struct Result {
		bool has_video_mode_change = false;
		bool video_enabled = false;
	};

	Result process() {
		Result result;

		auto message = intercore_comm.get_new_message();

		if (message.type != DeviceSettingsMessage::Type::None) {
			if (message.type == DeviceSettingsMessage::Type::SetVideoMode) {
				result.has_video_mode_change = true;
				result.video_enabled = message.video_enabled;
			}

			// Send empty ack to complete half-duplex turn
			DeviceSettingsMessage ack;
			while (!intercore_comm.send_message(ack))
				;
		}

		return result;
	}

private:
	static constexpr uint32_t IPCC_Chan = 4;
	mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, DeviceSettingsMessage, IPCC_Chan> intercore_comm;
};

} // namespace MetaModule
