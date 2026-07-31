#include "system/usb.hh"
#include "usb/usb_status_reader.hh"

namespace MetaModule::System
{

UsbConnectionStatus get_usb_connection_status() {
	return MetaModule::get_usb_connection_status_snapshot();
}

UsbMidiJackInfo get_usb_midi_in_jack_info(unsigned num) {
	return MetaModule::get_usb_midi_in_jack_snapshot(num);
}

UsbMidiJackInfo get_usb_midi_out_jack_info(unsigned num) {
	return MetaModule::get_usb_midi_out_jack_snapshot(num);
}

UsbMidiJackInfo get_usb_midi_rx_cable(unsigned cable_num) {
	return MetaModule::get_usb_midi_rx_cable_snapshot(cable_num);
}

UsbMidiJackInfo get_usb_midi_tx_cable(unsigned cable_num) {
	return MetaModule::get_usb_midi_tx_cable_snapshot(cable_num);
}

} // namespace MetaModule::System
