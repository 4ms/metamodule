#include "expanders.hh"

namespace MetaModule::Expanders
{

namespace
{
ConnectedState _state{};
}

void ext_audio_found(bool found) {
	_state.ext_audio_connected = found;
}

ConnectedState get_connected() {
	return _state;
}

} // namespace MetaModule::Expanders
