#pragma once
#include <string_view>

namespace rack::plugin
{
struct Model;
}

namespace MetaModule::RackModelLookup
{

void add(std::string_view brand, std::string_view slug, rack::plugin::Model *model);
void remove_brand(std::string_view brand);
rack::plugin::Model *find(std::string_view combined_slug);

} // namespace MetaModule::RackModelLookup
