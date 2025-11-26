#pragma once

namespace MetaModule::Expanders
{

struct ConnectedState {
	// bool wifi_connected{}
	bool ext_audio_connected{};
};

void ext_audio_found(bool found);
ConnectedState get_connected();

} // namespace MetaModule::Expanders
