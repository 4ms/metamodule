#include <string_view>

namespace MetaModule::ModuleTags
{

int tag_id(std::string_view tag);
std::string_view get_tag(int tag_id);
std::string_view normalize_tag(std::string_view tag);

} // namespace MetaModule::ModuleTags
