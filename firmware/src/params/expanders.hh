#pragma once

namespace MetaModule::Expanders
{

struct ConnectedState {
	// bool wifi_connected{}
	bool ext_audio_connected{};
	unsigned num_button_connected = 0;
};

void ext_audio_found(bool found);
void button_exp_found(unsigned num);
ConnectedState get_connected();

} // namespace MetaModule::Expanders
