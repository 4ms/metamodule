#pragma once
#include "gui/pages/view_settings.hh"
#include <span>

namespace MetaModule::Settings
{

bool parse(std::span<char> yaml, ViewSettings *settings);

} // namespace MetaModule::Settings
