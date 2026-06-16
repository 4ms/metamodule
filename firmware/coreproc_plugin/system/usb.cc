#include "system/usb.hh"
#include "usb/usb_status_reader.hh"

namespace MetaModule::System
{

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
