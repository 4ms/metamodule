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
};

static constexpr int MAX_MODULE_TYPES = 512;
struct BrandRegistry {
	ModuleTypeSlug brand_name;
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
									   const ModuleTypeSlug &typeslug,
									   CreateModuleFunc funcCreate,
									   const ModuleInfoView &info,
									   std::string_view faceplate_filename) {

	if (auto brand_reg = brand_registry(brand_name); brand_reg != registry().end()) {
		// Brand exists: insert or overwrite existing entry
		return brand_reg->modules.overwrite(typeslug, {funcCreate, info, std::string{faceplate_filename}});
	} else {
		// Brand does not exist, create it and insert entry
		auto &brand = registry().emplace_back(brand_name);
		return brand.modules.insert(typeslug, {funcCreate, info, std::string{faceplate_filename}});
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

std::unique_ptr<CoreProcessor> ModuleFactory::create(std::string_view combined_slug) {
	auto [brand, module_name] = brand_module(combined_slug);
	if (auto brand_reg = brand_registry(brand); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(module_name)) {
			if (auto f_create = module->creation_func)
				return f_create();
		}
	}

	return nullptr;
}

ModuleInfoView &ModuleFactory::getModuleInfo(std::string_view combined_slug) {
	auto [brand, module_name] = brand_module(combined_slug);
	if (auto brand_reg = brand_registry(brand); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(module_name)) {
			return module->info;
		}
	}
	return nullinfo;
}

std::string_view ModuleFactory::getModuleFaceplate(std::string_view combined_slug) {
	auto [brand, module_name] = brand_module(combined_slug);
	if (auto brand_reg = brand_registry(brand); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(module_name)) {
			return module->faceplate;
		}
	}

	return "";
}

bool ModuleFactory::isValidSlug(std::string_view combined_slug) {
	auto [brand, module_name] = brand_module(combined_slug);
	if (auto brand_reg = brand_registry(brand); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(module_name)) {
			return bool(module->creation_func);
		}
	}

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

std::vector<BrandTypeSlug> ModuleFactory::getAllBrands() {
	std::vector<BrandTypeSlug> brands;
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
