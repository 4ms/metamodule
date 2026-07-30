#pragma once
#include <cstdint>

namespace MetaModule
{

// How the single USB-C / OTG-HS port chooses its data role.
//   Auto:        FUSB302 DRP toggle-polling auto-detects host vs device (default).
//   ForceHost:   always act as a USB host (ignore DRP auto-detection).
//   ForceDevice: always act as a USB device (ignore DRP auto-detection).
enum class UsbRoleMode : uint32_t {
	Auto,
	ForceHost,
	ForceDevice,
};

} // namespace MetaModule
