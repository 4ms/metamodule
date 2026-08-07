#include <rack.hpp>
using namespace rack;

extern rack::plugin::Plugin *pluginInstance;

namespace rack::core
{

// METAMODULE: a MIDI "device" is one of the hardware's physical ports (USB, TRS,
// DIN5), so the port a module listens to is just its device id, and AllDevices
// means don't filter. Shared by every module with a "MIDI port" menu item.
inline std::string midiPortMenuName(midi::Input &input, int device_id) {
	auto name = input.getDeviceName(device_id);
	return device_id == midi::Port::AllDevices ? name : name + " only";
}

// Builds the "MIDI port" submenu. Place it directly above "MIDI channel":
// the two read as a pair, one narrowing by jack and the other by channel.
inline MenuItem *createMidiPortMenuItem(midi::Input &input) {
	return createSubmenuItem(
		"MIDI port", [&] { return midiPortMenuName(input, input.getDeviceId()); }, [&](Menu *menu) {
			auto add_port = [&](int device_id) {
				menu->addChild(createCheckMenuItem(
					midiPortMenuName(input, device_id),
					"",
					[&, device_id]() { return input.getDeviceId() == device_id; },
					[&, device_id]() { input.setDeviceId(device_id); }));
			};

			add_port(midi::Port::AllDevices);
			for (auto device_id : input.getDeviceIds())
				add_port(device_id);
		});
}

} // namespace rack::core
