#pragma once
#include "core_intercom/intercore_devicesettings_message.hh"

// STUB: stands in for src/core_a7/device_settings_proxy.hh, which sends the USB settings to the M4.
// FIXME: send them to the M33 when it does USB. Until then, sending always succeeds.

namespace MetaModule
{

struct DeviceSettingsProxy {
	static bool send_device_mode(UsbDeviceMode) {
		return true;
	}

	static bool send_role_mode(UsbRoleMode) {
		return true;
	}
};

} // namespace MetaModule
