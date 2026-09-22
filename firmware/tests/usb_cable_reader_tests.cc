#include "doctest.h"
#include "usb/usb_connection_status_block.hh"
#include <string_view>

// Tests for the reader side of the cross-core USB snapshot: turning a cable
// number into the UsbMidiCableInfo the plugin API hands back.

namespace
{

using namespace MetaModule;

// A device with two rx cables and one tx cable, already parsed into the shape
// copy_midi_jacks() publishes.
UsbDeviceState two_by_one_device() {
	UsbDeviceState d;
	d.status.connection = System::UsbConnectionType::HostMidiDevice;
	d.status.num_midi_rx_cables = 2;
	d.status.num_midi_tx_cables = 1;
	d.status.num_midi_out_jacks = 2;
	d.status.num_midi_in_jacks = 1;

	d.midi_out_jacks[0] = {"Port A", /*jack_id*/ 4, /*cable_num*/ 0, /*has_cable*/ true, /*embedded*/ true, true};
	d.midi_out_jacks[1] = {"Port B", 5, 1, true, true, true};
	d.rx_cable_out_jack_idx[0] = 0;
	d.rx_cable_out_jack_idx[1] = 1;

	d.midi_in_jacks[0] = {"Port A In", 1, 0, true, true, true};
	d.tx_cable_in_jack_idx[0] = 0;

	return d;
}

UsbConnectionStatusBlock published(UsbDeviceState const &d) {
	UsbConnectionStatusBlock block;
	block.publish(d);
	return block;
}

} // namespace

TEST_CASE("Cable lookup returns the port name and the requested cable number") {
	auto block = published(two_by_one_device());

	auto rx0 = block.read_rx_cable(0);
	CHECK(rx0.valid);
	CHECK(rx0.cable_num == 0);
	CHECK(std::string_view{rx0.name.c_str()} == "Port A");

	auto rx1 = block.read_rx_cable(1);
	CHECK(rx1.valid);
	CHECK(rx1.cable_num == 1);
	CHECK(std::string_view{rx1.name.c_str()} == "Port B");

	auto tx0 = block.read_tx_cable(0);
	CHECK(tx0.valid);
	CHECK(tx0.cable_num == 0);
	CHECK(std::string_view{tx0.name.c_str()} == "Port A In");
}

TEST_CASE("Cable numbers past what the device declared are invalid") {
	auto block = published(two_by_one_device());

	CHECK(!block.read_rx_cable(2).valid);  // only 2 rx cables (0 and 1)
	CHECK(!block.read_tx_cable(1).valid);  // only 1 tx cable
	CHECK(!block.read_rx_cable(System::MaxMidiCables).valid);
	CHECK(!block.read_rx_cable(9999).valid);
	CHECK(!block.read_tx_cable(System::MaxMidiCables + 100).valid);
}

TEST_CASE("Nothing attached: every cable is invalid") {
	UsbConnectionStatusBlock block;
	block.publish(UsbDeviceState{});

	for (unsigned c = 0; c < System::MaxMidiCables; c++) {
		CHECK(!block.read_rx_cable(c).valid);
		CHECK(!block.read_tx_cable(c).valid);
	}
}

TEST_CASE("A cable whose jack wasn't stored reports invalid rather than a bogus jack") {
	SUBCASE("cable maps to NoJackIdx") {
		// The device associated a jack id we never stored (see parse_midi_jacks).
		auto d = two_by_one_device();
		d.rx_cable_out_jack_idx[1] = NoJackIdx;

		auto block = published(d);
		CHECK(block.read_rx_cable(0).valid);
		CHECK(!block.read_rx_cable(1).valid);
	}

	SUBCASE("cable maps to a jack slot that isn't valid") {
		auto d = two_by_one_device();
		d.midi_out_jacks[1].valid = false;

		auto block = published(d);
		CHECK(block.read_rx_cable(0).valid);
		CHECK(!block.read_rx_cable(1).valid);
	}
}

TEST_CASE("One jack serving two cables reports each cable's own number") {
	// A device may list the same bJackID more than once in baAssocJackID. The
	// jack can only carry one cable_num (the parser stamps the last one), so the
	// number has to come from the lookup, not from the jack -- otherwise
	// read_rx_cable(0) hands back cable_num 1 and a module filtering on it
	// listens to the wrong stream.
	auto d = two_by_one_device();
	d.rx_cable_out_jack_idx[0] = 0;
	d.rx_cable_out_jack_idx[1] = 0;	  // both cables served by out_jacks[0]
	d.midi_out_jacks[0].cable_num = 1; // parser stamped the higher index

	auto block = published(d);

	auto rx0 = block.read_rx_cable(0);
	auto rx1 = block.read_rx_cable(1);
	CHECK(rx0.valid);
	CHECK(rx1.valid);
	CHECK(rx0.cable_num == 0);
	CHECK(rx1.cable_num == 1);
}

TEST_CASE("Reading status and name doesn't disturb the cable tables") {
	auto d = two_by_one_device();
	d.device_name.manufacturer.copy("Acme");
	d.device_name.product.copy("Controller");

	auto block = published(d);

	CHECK(block.read_status().num_midi_rx_cables == 2);
	CHECK(std::string_view{block.read_name().manufacturer.c_str()} == "Acme");
	CHECK(std::string_view{block.read_name().product.c_str()} == "Controller");
	CHECK(std::string_view{block.read_rx_cable(1).name.c_str()} == "Port B");

	// The name strings are no longer part of the status struct
	CHECK(block.read_status().connection == System::UsbConnectionType::HostMidiDevice);
}
