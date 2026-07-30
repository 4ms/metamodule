#pragma once
#include "usb/usb_device_mode.hh"
#include "usb/usb_role_mode.hh"
#include <cstdint>

namespace MetaModule
{

struct DeviceSettingsMessage {
	enum class Type : uint32_t {
		None,
		SetDeviceMode,
		SetRoleMode,
	};

	Type type = Type::None;
	UsbDeviceMode mode = UsbDeviceMode::Cdc;
	UsbRoleMode role = UsbRoleMode::Auto;
};

} // namespace MetaModule
