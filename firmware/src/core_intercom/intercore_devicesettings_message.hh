#pragma once
#include "usb/usb_device_mode.hh"
#include <cstdint>

namespace MetaModule
{

struct DeviceSettingsMessage {
	enum class Type : uint32_t {
		None,
		SetDeviceMode,
	};

	Type type = Type::None;
	UsbDeviceMode mode = UsbDeviceMode::Cdc;
};

} // namespace MetaModule
