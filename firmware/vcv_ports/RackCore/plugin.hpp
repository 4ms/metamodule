#include <rack.hpp>
using namespace rack;

extern rack::plugin::Plugin *pluginInstance;

namespace rack::core
{

// METAMODULE: a MIDI "device" is one of the hardware's physical ports (USB, TRS,
// DIN5), so the port a module uses is just its device id. Inputs may choose
// AllDevices, but outputs have to choose one port.
namespace detail
{

inline std::string midiPortName(midi::Port &port, int device_id, bool suffix_only) {
	auto name = port.getDeviceName(device_id);
	return (suffix_only && device_id != midi::Port::AllDevices) ? name + " only" : name;
}

inline MenuItem *createMidiPortMenu(midi::Port &port, std::vector<int> ids, bool suffix_only) {
	return createSubmenuItem(
		"MIDI port",
		[&port, suffix_only] { return midiPortName(port, port.getDeviceId(), suffix_only); },
		[&port, ids, suffix_only](Menu *menu) {
			for (auto device_id : ids) {
				menu->addChild(createCheckMenuItem(
					midiPortName(port, device_id, suffix_only),
					"",
					[&port, device_id] { return port.getDeviceId() == device_id; },
					[&port, device_id] { port.setDeviceId(device_id); }));
			}
		});
}

} // namespace detail

inline MenuItem *createMidiPortMenuItem(midi::Input &input) {
	std::vector<int> ids{midi::Port::AllDevices};
	for (auto device_id : input.getDeviceIds())
		ids.push_back(device_id);

	return detail::createMidiPortMenu(input, ids, true);
}

inline MenuItem *createMidiPortMenuItem(midi::Output &output) {
	return detail::createMidiPortMenu(output, output.getDeviceIds(), false);
}

} // namespace rack::core
