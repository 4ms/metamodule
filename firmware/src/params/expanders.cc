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

void button_exp_found(unsigned num) {
	_state.num_button_connected = num;
}

ConnectedState get_connected() {
	return _state;
}

} // namespace MetaModule::Expanders
