#include "rack_model_lookup.hh"
#include "CoreModules/moduleFactory.hh"
#include "util/string_compare.hh"
#include <algorithm>
#include <string>
#include <vector>

namespace MetaModule::RackModelLookup
{

namespace
{
struct Entry {
	std::string brand;
	std::string slug;
	rack::plugin::Model *model;
};

std::vector<Entry> &entries() {
	static std::vector<Entry> list;
	return list;
}
} // namespace

void add(std::string_view brand, std::string_view slug, rack::plugin::Model *model) {
	entries().push_back({std::string{brand}, std::string{slug}, model});
}

void remove_brand(std::string_view brand) {
	std::erase_if(entries(), [&](auto const &entry) { return entry.brand == brand; });
}

rack::plugin::Model *find(std::string_view combined_slug) {
	auto colon = combined_slug.find_first_of(':');
	auto slug = colon == std::string_view::npos ? combined_slug : combined_slug.substr(colon + 1);
	auto brand = colon == std::string_view::npos ? "" : ModuleFactory::cleanupBrandName(combined_slug.substr(0, colon));

	auto matches = [&](Entry const &entry) {
		return entry.slug == slug && (brand.empty() || equal_ci(entry.brand, brand));
	};

	if (auto it = std::ranges::find_if(entries(), matches); it != entries().end())
		return it->model;
	return nullptr;
}

} // namespace MetaModule::RackModelLookup
