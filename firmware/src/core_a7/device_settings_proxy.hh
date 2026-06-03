#pragma once
#include "core_intercom/intercore_devicesettings_message.hh"
#include "drivers/inter_core_comm.hh"

namespace MetaModule
{

namespace StaticBuffers
{
extern DeviceSettingsMessage icc_device_settings_message;
} // namespace StaticBuffers

struct DeviceSettingsProxy {

	static bool send_device_mode(UsbDeviceMode mode) {
		DeviceSettingsMessage msg;
		msg.type = DeviceSettingsMessage::Type::SetDeviceMode;
		msg.mode = mode;
		return comm.send_message(msg);
	}

private:
	static constexpr uint32_t IPCC_Chan = 4;
	using Comm = mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Initiator, DeviceSettingsMessage, IPCC_Chan>;
	static inline Comm comm{StaticBuffers::icc_device_settings_message};
};

} // namespace MetaModule
