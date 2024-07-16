#include "gui/pages/view_settings.hh"
#include <span>
#include <string>

namespace MetaModule::Settings
{

uint32_t serialize(ViewSettings const &settings, std::span<char> buffer);

} // namespace MetaModule::Settings
