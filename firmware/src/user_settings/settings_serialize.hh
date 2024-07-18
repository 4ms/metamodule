#include "user_settings/settings.hh"
#include <span>

namespace MetaModule::Settings
{

uint32_t serialize(UserSettings const &settings, std::span<char> buffer);

} // namespace MetaModule::Settings
