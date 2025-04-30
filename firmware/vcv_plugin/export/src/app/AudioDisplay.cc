#include <app/AudioDisplay.hpp>

namespace rack::app
{

void AudioDriverChoice::onAction(const ActionEvent &e) {
}
void AudioDriverChoice::step() {
}

void AudioDeviceChoice::onAction(const ActionEvent &e) {
}
void AudioDeviceChoice::step() {
}

void AudioSampleRateChoice::onAction(const ActionEvent &e) {
}
void AudioSampleRateChoice::step() {
}

void AudioBlockSizeChoice ::onAction(const ActionEvent &e) {
}
void AudioBlockSizeChoice ::step() {
}

void AudioDeviceMenuChoice ::onAction(const ActionEvent &e) {
}

void AudioDisplay::setAudioPort(audio::Port *port) {
}

void AudioButton::setAudioPort(audio::Port *port) {
}
void AudioButton::onAction(const ActionEvent &e) {
}

void appendAudioMenu(ui::Menu *menu, audio::Port *port) {
}

} // namespace rack::app
