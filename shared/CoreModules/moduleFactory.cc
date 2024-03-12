#include "moduleFactory.hh"
#include "util/seq_map.hh"

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

static constexpr int MAX_MODULE_TYPES = 512;

// SeqMap<ModuleTypeSlug, ModuleFactory::CreateModuleFunc, MAX_MODULE_TYPES>
auto &creation_funcs() {
	static SeqMap<ModuleTypeSlug, ModuleFactory::CreateModuleFunc, MAX_MODULE_TYPES> _creation_funcs{};
	return _creation_funcs;
}

// SeqMap<ModuleTypeSlug, ModuleInfoView, MAX_MODULE_TYPES>
auto &infos() {
	static SeqMap<ModuleTypeSlug, ModuleInfoView, MAX_MODULE_TYPES> _infos{};
	return _infos;
}

auto &faceplates() {
	static SeqMap<ModuleTypeSlug, std::string_view, MAX_MODULE_TYPES> _faceplates{};
	return _faceplates;
}

ModuleInfoView nullinfo{};

std::string _currentBrand;

} // namespace

bool ModuleFactory::registerModuleType(const ModuleTypeSlug &typeslug,
									   CreateModuleFunc funcCreate,
									   const ModuleInfoView &info,
									   std::string_view faceplate_filename) {
	bool already_exists = registerModuleCreationFunc(typeslug, funcCreate);
	registerModuleInfo(typeslug, info);
	registerModuleFaceplate(typeslug, faceplate_filename);
	return already_exists;
}

bool ModuleFactory::registerModuleInfo(const ModuleTypeSlug &typeslug, const ModuleInfoView &info) {
	if (!infos().key_exists(typeslug)) {
		pr_dbg("ModuleFactory::register %s to infos() %p\n", typeslug.c_str(), &infos());
		return infos().insert(typeslug, info);
	} else {
		pr_err("ModuleFactory: info for %s already exists\n", typeslug.c_str());
		return false;
	}
}

bool ModuleFactory::registerModuleCreationFunc(const ModuleTypeSlug &typeslug, CreateModuleFunc funcCreate) {
	if (!creation_funcs().key_exists(typeslug)) {
		pr_dbg("ModuleFactory::register %s to funcs %p\n", typeslug.c_str(), &creation_funcs());
		return creation_funcs().insert(typeslug, funcCreate);
	} else {
		pr_err("ModuleFactory: creation func for %s already exists\n", typeslug.c_str());
		return false;
	}
}

bool ModuleFactory::registerModuleFaceplate(const ModuleTypeSlug &typeslug, std::string_view faceplate) {
	if (!faceplates().key_exists(typeslug)) {
		pr_dbg("ModuleFactory::register %s to faceplate %.*s\n",
			   typeslug.c_str(),
			   (int)faceplate.size(),
			   faceplate.data());
		return faceplates().insert(typeslug, faceplate);
	} else {
		pr_err("ModuleFactory: faceplate for %s already exists\n", typeslug.c_str());
		return false;
	}
}

std::unique_ptr<CoreProcessor> ModuleFactory::create(const ModuleTypeSlug &typeslug) {
	if (auto f_create = creation_funcs().get(typeslug))
		return (*f_create)();
	else
		return nullptr;
}

ModuleInfoView &ModuleFactory::getModuleInfo(const ModuleTypeSlug &typeslug) {
	if (auto m = infos().get(typeslug))
		return *m;
	else
		return nullinfo;
}

std::string_view ModuleFactory::getModuleFaceplate(const ModuleTypeSlug &typeslug) {
	if (auto m = faceplates().get(typeslug))
		return *m;
	else
		return "";
}

bool ModuleFactory::isValidSlug(const ModuleTypeSlug &typeslug) {
	return infos().key_exists(typeslug) && creation_funcs().key_exists(typeslug);
}

std::vector<ModuleTypeSlug> ModuleFactory::getAllSlugs() {
	std::vector<ModuleTypeSlug> slugs;
	slugs.assign(infos().keys.begin(), std::next(infos().keys.begin(), infos().size()));
	return slugs;
}

void ModuleFactory::setCurrentBrand(std::string brandSlug) {
	_currentBrand = brandSlug;
}

std::string ModuleFactory::currentBrandPath() {
	return _currentBrand + std::string("/");
}

} // namespace MetaModule
