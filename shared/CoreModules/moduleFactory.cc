#include "CoreModules/moduleFactory.hh"
#include "util/seq_map.hh"
#include <list>

#ifdef TESTPROJECT
#define pr_dbg(...)
#define pr_err(...)
#else
#include "console/pr_dbg.hh"
#endif

namespace MetaModule
{

namespace
{
//Lazily loaded maps, needed to avoid static-initialization ordering issues with CoreModules self-registering

struct ModuleRegistry {
	ModuleFactory::CreateModuleFunc creation_func;
	ModuleInfoView info;
	std::string faceplate;
	std::string display_name;
};

static constexpr int MAX_MODULE_TYPES = 512;
struct BrandRegistry {
	BrandTypeSlug brand_name;
	std::string display_name;
	SeqMap<ModuleTypeSlug, ModuleRegistry, MAX_MODULE_TYPES> modules;

	BrandRegistry(std::string_view brand)
		: brand_name{brand} {
	}
};

auto &registry() {
	static std::list<BrandRegistry> _registry{};
	return _registry;
}

ModuleInfoView nullinfo{};

} // namespace

static auto brand_registry(std::string_view brand) {
	return std::find_if(registry().begin(), registry().end(), [=](auto const &b) { return b.brand_name == brand; });
}

bool ModuleFactory::registerModuleType(std::string_view brand_name,
									   const ModuleTypeSlug &module_slug,
									   CreateModuleFunc funcCreate,
									   const ModuleInfoView &info,
									   std::string_view faceplate_filename) {

	if (auto brand_reg = brand_registry(brand_name); brand_reg != registry().end()) {
		// Brand exists: insert or overwrite existing entry
		if (brand_reg->modules.overwrite(module_slug, {funcCreate, info, std::string{faceplate_filename}, module_slug}))
		{
			brand_reg->display_name = brand_name;
			return true;
		} else {
			return false;
		}
	} else {
		// Brand does not exist, create it and insert entry
		auto &brand = registry().emplace_back(brand_name);
		brand.display_name = brand_name;
		return brand.modules.insert(module_slug, {funcCreate, info, std::string{faceplate_filename}, module_slug});
	}
}

bool ModuleFactory::registerModuleType(const ModuleTypeSlug &typeslug,
									   CreateModuleFunc funcCreate,
									   const ModuleInfoView &info,
									   std::string_view faceplate_filename) {
	return registerModuleType("4msCompany", typeslug, funcCreate, info, faceplate_filename);
}

static std::pair<std::string_view, std::string_view> brand_module(std::string_view combined_slug) {
	auto colon = combined_slug.find_first_of(':');
	if (colon != std::string_view::npos) {
		return {combined_slug.substr(0, colon), combined_slug.substr(colon + 1)};

	} else {
		auto module_slug = combined_slug;
		//search all brands for module slug
		for (auto &brand : registry()) {
			if (brand.modules.get(module_slug)) {
				// pr_dbg("Brand not specified, found %s in %s\n", module_slug.data(), brand.brand_name.c_str());
				return {brand.brand_name.c_str(), module_slug};
			}
		}
		return {"", ""};
	}
}

static ModuleRegistry *find_module(std::string_view combined_slug) {
	auto [brand, module_name] = brand_module(combined_slug);
	if (auto brand_reg = brand_registry(brand); brand_reg != registry().end()) {
		return brand_reg->modules.get(module_name);
	} else
		return nullptr;
}

std::unique_ptr<CoreProcessor> ModuleFactory::create(std::string_view combined_slug) {
	if (auto module = find_module(combined_slug)) {
		if (auto f_create = module->creation_func)
			return f_create();
	}

	return nullptr;
}

ModuleInfoView &ModuleFactory::getModuleInfo(std::string_view combined_slug) {
	if (auto module = find_module(combined_slug))
		return module->info;
	else
		return nullinfo;
}

std::string_view ModuleFactory::getModuleFaceplate(std::string_view combined_slug) {
	if (auto module = find_module(combined_slug))
		return module->faceplate;
	else
		return "";
}

std::string_view ModuleFactory::getModuleDisplayName(std::string_view combined_slug) {
	if (auto module = find_module(combined_slug))
		return module->display_name;
	else {
		[[maybe_unused]] auto [_, module_name] = brand_module(combined_slug);
		if (module_name.length())
			return module_name;
		else
			return combined_slug;
	}
}

std::string_view ModuleFactory::getModuleSlug(std::string_view brand_slug, std::string_view display_name) {
	if (auto brand_reg = brand_registry(brand_slug); brand_reg != registry().end()) {
		for (auto i = 0u; auto const &module : brand_reg->modules.vals) {
			if (module.display_name == display_name) {
				return brand_reg->modules.keys[i];
			}
			if (++i >= brand_reg->modules.size())
				break;
		}
	}
	return "";
}

std::string_view ModuleFactory::getBrandDisplayName(std::string_view brand_name) {
	if (auto brand_reg = brand_registry(brand_name); brand_reg != registry().end())
		return brand_reg->display_name;
	else
		return brand_name;
}

std::string_view ModuleFactory::getBrandSlug(std::string_view display_name) {
	auto found = std::find_if(
		registry().begin(), registry().end(), [&](auto const &brand) { return brand.display_name == display_name; });

	if (found != registry().end())
		return found->brand_name;
	else
		return "";
}

void ModuleFactory::setModuleDisplayName(std::string_view combined_slug, std::string_view display_name) {
	if (auto module = find_module(combined_slug))
		module->display_name = display_name;
}

void ModuleFactory::setBrandDisplayName(std::string_view brand_name, std::string_view display_name) {
	if (auto brand_reg = brand_registry(brand_name); brand_reg != registry().end()) {
		brand_reg->display_name = display_name;
	}
}

bool ModuleFactory::isValidSlug(std::string_view combined_slug) {
	if (auto module = find_module(combined_slug))
		return bool(module->creation_func);
	else
		return false;
}

bool ModuleFactory::isValidBrandModule(std::string_view brand, std::string_view module_name) {
	if (auto brand_reg = brand_registry(brand); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(module_name)) {
			return bool(module->creation_func);
		}
	}

	return false;
}

std::vector<ModuleTypeSlug> ModuleFactory::getAllSlugs(std::string_view brand) {
	std::vector<ModuleTypeSlug> slugs;
	auto modules = brand_registry(brand)->modules;
	slugs.assign(modules.keys.begin(), std::next(modules.keys.begin(), modules.size()));
	return slugs;
}

std::vector<std::string> ModuleFactory::getAllModuleDisplayNames(std::string_view brand) {
	std::vector<std::string> names;
	auto modules = brand_registry(brand)->modules;
	names.reserve(modules.size());
	for (unsigned i = 0; i < modules.size(); i++) {
		names.push_back(modules.vals[i].display_name);
	}
	return names;
}

std::vector<std::string_view> ModuleFactory::getAllBrandDisplayNames() {
	std::vector<std::string_view> brands;
	brands.resize(registry().size());
	for (auto &brand : registry()) {
		brands.push_back(brand.display_name);
	}
	return brands;
}

std::vector<BrandTypeSlug> ModuleFactory::getAllBrands() {
	std::vector<BrandTypeSlug> brands;
	brands.resize(registry().size());
	for (auto &brand : registry()) {
		brands.push_back(brand.brand_name.c_str());
	}
	return brands;
}

bool ModuleFactory::unregisterBrand(std::string_view brand_name) {
	auto removed = registry().remove_if([=](BrandRegistry &reg) { return reg.brand_name == brand_name; });
	return removed > 0;
}

} // namespace MetaModule
