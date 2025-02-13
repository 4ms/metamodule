#include <app/MidiDisplay.hpp>

namespace rack::app
{

void MidiDriverChoice::onAction(const ActionEvent &e) {
}
void MidiDriverChoice::step() {
}

void MidiDeviceChoice::onAction(const ActionEvent &e) {
}
void MidiDeviceChoice::step() {
}

void MidiDisplay::setMidiPort(midi::Port *port) {
}

void MidiButton::setMidiPort(midi::Port *port) {
}
void MidiButton::onAction(const ActionEvent &e) {
}

void appendMidiMenu(ui::Menu *menu, midi::Port *port) {
}

} // namespace rack::app
