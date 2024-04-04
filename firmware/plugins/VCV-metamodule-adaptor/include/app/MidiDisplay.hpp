#pragma once
#include <app/LedDisplay.hpp>
#include <app/SvgButton.hpp>
#include <app/common.hpp>
#include <midi.hpp>
#include <ui/Menu.hpp>

namespace rack::app
{

struct MidiDriverChoice : LedDisplayChoice {
	midi::Port *port{};
};

struct MidiDeviceChoice : LedDisplayChoice {
	midi::Port *port{};
};

struct MidiChannelChoice : LedDisplayChoice {
	midi::Port *port{};
};

struct MidiDisplay : LedDisplay {
	MidiDriverChoice *driverChoice{};
	LedDisplaySeparator *driverSeparator{};
	MidiDeviceChoice *deviceChoice{};
	LedDisplaySeparator *deviceSeparator{};
	MidiChannelChoice *channelChoice{};
	void setMidiPort(midi::Port *port) {
	}
};

struct MidiButton : SvgButton {
	midi::Port *port{};
	void setMidiPort(midi::Port *port) {
	}
};

void appendMidiMenu(ui::Menu *menu, midi::Port *port) {
}

} // namespace rack::app
