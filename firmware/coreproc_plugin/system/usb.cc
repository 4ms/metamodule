#include "system/usb.hh"
#include "usb/usb_status_reader.hh"

namespace MetaModule::System
{

// The SDK enum (this namespace) mirrors the firmware enum; keep them in lockstep
// so the static_cast below is value-preserving.
static_assert((uint32_t)UsbConnection::None == (uint32_t)MetaModule::UsbConnection::None);
static_assert((uint32_t)UsbConnection::HostSearching == (uint32_t)MetaModule::UsbConnection::HostSearching);
static_assert((uint32_t)UsbConnection::HostMidiDevice == (uint32_t)MetaModule::UsbConnection::HostMidiDevice);
static_assert((uint32_t)UsbConnection::HostUsbDrive == (uint32_t)MetaModule::UsbConnection::HostUsbDrive);
static_assert((uint32_t)UsbConnection::DeviceWaiting == (uint32_t)MetaModule::UsbConnection::DeviceWaiting);
static_assert((uint32_t)UsbConnection::DeviceMidiHost == (uint32_t)MetaModule::UsbConnection::DeviceMidiHost);
static_assert((uint32_t)UsbConnection::DeviceVideoHost == (uint32_t)MetaModule::UsbConnection::DeviceVideoHost);
static_assert((uint32_t)UsbConnection::DeviceConsoleHost == (uint32_t)MetaModule::UsbConnection::DeviceConsoleHost);

UsbConnectionStatus get_usb_connection_status() {
	auto s = MetaModule::get_usb_connection_status_snapshot();

	UsbConnectionStatus out;
	out.connection = static_cast<UsbConnection>(s.connection);
	out.vid = s.vid;
	out.pid = s.pid;
	out.num_midi_in_jacks = s.num_midi_in_jacks;
	out.num_midi_out_jacks = s.num_midi_out_jacks;
	out.manufacturer = s.manufacturer;
	out.product = s.product;
	return out;
}

} // namespace MetaModule::System
