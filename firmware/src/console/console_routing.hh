#pragma once

namespace MetaModule::ConsoleRouting
{

// Included in main_m4.cc and usb_serial_device.cc
// TODO: share this in a different way, can main_m4 get it from usb_serial_device?
inline bool usb_console_active = false;

} // namespace MetaModule::ConsoleRouting
