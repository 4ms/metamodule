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
	std::string brand_name;
	SeqMap<ModuleTypeSlug, ModuleRegistry, MAX_MODULE_TYPES> modules;
};

auto &registry() {
	static std::list<BrandRegistry> _registry{};
	return _registry;
}

ModuleInfoView nullinfo{};

} // namespace

static auto brand_registry(std::string_view brand) {
	return std::find_if(registry().begin(), registry().end(), [=](auto b) { return b.brand_name == brand; });
}

bool ModuleFactory::registerModuleType(std::string_view brand_name,
									   const ModuleTypeSlug &typeslug,
									   CreateModuleFunc funcCreate,
									   const ModuleInfoView &info,
									   std::string_view faceplate_filename) {

	if (auto brand_reg = brand_registry(brand_name); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(typeslug); module) {
			// pr_warn("Module %s already registered\n", typeslug.c_str());
			return false;
		} else {
			return brand_reg->modules.insert(typeslug, {funcCreate, info, std::string{faceplate_filename}});
		}
	} else {
		// Brand does not exist:
		auto brand = registry().emplace_back(BrandRegistry{std::string{brand_name}, {}});
		return brand.modules.insert(typeslug, {funcCreate, info, std::string{faceplate_filename}});
	}
}
bool ModuleFactory::registerModuleType(const ModuleTypeSlug &typeslug,
									   CreateModuleFunc funcCreate,
									   const ModuleInfoView &info,
									   std::string_view faceplate_filename) {
	return registerModuleType("4ms", typeslug, funcCreate, info, faceplate_filename);
}

bool ModuleFactory::registerModuleInfo(std::string_view brand_name,
									   const ModuleTypeSlug &typeslug,
									   const ModuleInfoView &info,
									   std::string_view faceplate) {

	if (auto brand_reg = brand_registry(brand_name); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(typeslug)) {
			module->info = info;
			module->faceplate = std::string{faceplate};
			return true;

		} else {

			// Module does not exist
			return brand_reg->modules.insert(typeslug, {{}, info, std::string{faceplate}});
		}

	} else {
		// Brand does not exist:
		auto brand = registry().emplace_back(BrandRegistry{std::string{brand_name}, {}});
		return brand.modules.insert(typeslug, {{}, info, std::string{faceplate}});
	}
}

bool ModuleFactory::registerModuleCreationFunc(std::string_view brand_name,
											   const ModuleTypeSlug &typeslug,
											   CreateModuleFunc funcCreate) {

	if (auto brand_reg = brand_registry(brand_name); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(typeslug)) {
			module->creation_func = funcCreate;
			return true;
		} else {
			return brand_reg->modules.insert(typeslug, {funcCreate, {}, {}});
		}
	} else {
		// Brand does not exist:
		auto brand = registry().emplace_back(BrandRegistry{std::string{brand_name}, {}});
		return brand.modules.insert(typeslug, {funcCreate, {}, {}});
	}
}

static std::string_view brand(std::string_view combined_slug) {
	auto colon = combined_slug.find_first_of(':');
	if (colon == std::string_view::npos)
		return "";
	return combined_slug.substr(0, colon);
}

std::unique_ptr<CoreProcessor> ModuleFactory::create(const ModuleTypeSlug &typeslug) {
	if (auto brand_reg = brand_registry(brand(typeslug)); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(typeslug)) {
			if (auto f_create = module->creation_func)
				return (*f_create)();
		}
	}

	return nullptr;
}

ModuleInfoView &ModuleFactory::getModuleInfo(const ModuleTypeSlug &typeslug) {
	if (auto brand_reg = brand_registry(brand(typeslug)); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(typeslug)) {
			return module->info;
		}
	}
	return nullinfo;
}

std::string_view ModuleFactory::getModuleFaceplate(const ModuleTypeSlug &typeslug) {
	if (auto brand_reg = brand_registry(brand(typeslug)); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(typeslug)) {
			return module->faceplate;
		}
	}

	return "";
}

bool ModuleFactory::isValidSlug(const ModuleTypeSlug &typeslug) {
	if (auto brand_reg = brand_registry(brand(typeslug)); brand_reg != registry().end()) {
		if (auto module = brand_reg->modules.get(typeslug)) {
			return bool(module->creation_func) && module->info.elements.size() > 0;
		}
	}

	return false;
}

std::vector<ModuleTypeSlug> ModuleFactory::getAllSlugs() {
	std::vector<ModuleTypeSlug> slugs;
	for (auto &brand : registry()) {
		slugs.insert(
			slugs.end(), brand.modules.keys.begin(), std::next(brand.modules.keys.begin(), brand.modules.keys.size()));
	}
	return slugs;
}

// std::vector<ModuleTypeSlug> getAllFaceplateSlugs() {
// 	std::vector<ModuleTypeSlug> slugs;
// 	slugs.assign(faceplates().keys.begin(), std::next(faceplates().keys.begin(), infos().size()));
// 	return slugs;
// }

std::vector<ModuleTypeSlug> getAllBrands() {
	std::vector<ModuleTypeSlug> brands;
	for (auto &brand : registry()) {
		brands.push_back(brand.brand_name.c_str());
	}
	// {"4ms", "Befaco", "MIClones", "HetrickCV", "Nonlinearcircuits", "Scanner Darkly"};
	return brands;
}

} // namespace MetaModule
