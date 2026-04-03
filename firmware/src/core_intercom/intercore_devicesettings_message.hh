#pragma once
#include <cstdint>

namespace MetaModule
{

struct DeviceSettingsMessage {
	enum class Type : uint32_t {
		None,
		SetVideoMode,
	};

	Type type = Type::None;
	bool video_enabled = false;
};

} // namespace MetaModule
