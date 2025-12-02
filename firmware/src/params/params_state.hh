#pragma once

namespace MetaModule
{

// Put all fields that the GUI needs to see here
struct ParamsState {
	void clear() {
	}

	void reset_change_flags() {
	}

	friend void copy(ParamsState &dst, ParamsState const &src) {
	}

	friend void transfer_events(ParamsState &dst, ParamsState const &src) {
	}
};

} // namespace MetaModule
