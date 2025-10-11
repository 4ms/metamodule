#pragma once

namespace MetaModule
{

struct MissingPluginSettings {
	enum class Autoload { Ask = 0, Always = 1, Never = 2 };

	Autoload autoload = Autoload::Ask;
};

} // namespace MetaModule

