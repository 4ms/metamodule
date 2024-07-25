#pragma once
#include "user_settings/settings.hh"
#include <span>

namespace MetaModule::Settings
{

bool parse(std::span<char> yaml, UserSettings *settings);

} // namespace MetaModule::Settings
