#pragma once
#include <string>

namespace MetaModule
{

struct PluginFileLoader {
	enum class State {
		NotInit,
		Error,
		InvalidPlugin,
		RamDiskFull,
		Idle,
		RequestList,
		WaitingForList,
		GotList,
		PrepareForReadingPlugin,
		RequestReadPlugin,
		LoadingPlugin,
		UntarPlugin,
		ProcessingPlugin,
		Success
	};

	struct Status {
		State state{State::NotInit};
		std::string name;
		std::string error_message;
	};
};

} // namespace MetaModule
