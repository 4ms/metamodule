#include "moduleFactory.hh"
#include "util/seq_map.hh"

// #ifdef TESTPROJECT
// #define pr_dbg(...)
// #else
// #include "console/pr_dbg.hh"
// #endif

namespace MetaModule
{

namespace
{

SeqMap<ModuleTypeSlug, ModuleFactory::CreateModuleFunc, ModuleFactory::MAX_MODULE_TYPES> &creation_funcs() {
	static SeqMap<ModuleTypeSlug, ModuleFactory::CreateModuleFunc, ModuleFactory::MAX_MODULE_TYPES> _creation_funcs{};
	return _creation_funcs;
}

SeqMap<ModuleTypeSlug, ModuleInfoView, ModuleFactory::MAX_MODULE_TYPES> &infos() {
	static SeqMap<ModuleTypeSlug, ModuleInfoView, ModuleFactory::MAX_MODULE_TYPES> _infos{};
	return _infos;
}

// FIXME: why does auto not work for return type?
SeqMap<ModuleTypeSlug, ModuleFactory::FaceplatePtr, ModuleFactory::MAX_MODULE_TYPES> &faceplates() {
	static SeqMap<ModuleTypeSlug, ModuleFactory::FaceplatePtr, ModuleFactory::MAX_MODULE_TYPES> _faceplates{};
	return _faceplates;
}

ModuleInfoView nullinfo{};

} // namespace

bool ModuleFactory::registerModuleType(const ModuleTypeSlug &typeslug,
									   CreateModuleFunc funcCreate,
									   const ModuleInfoView &info) {
	bool already_exists = creation_funcs().key_exists(typeslug);
	infos().insert(typeslug, info);
	creation_funcs().insert(typeslug, funcCreate);
	// pr_dbg("ModuleFactory::register %s to infos() %p, funcs %p\n", typeslug.c_str(), &infos(), &creation_funcs());
	return already_exists;
}

bool ModuleFactory::registerModuleType(const ModuleTypeSlug &typeslug, const ModuleInfoView &info) {
	bool already_exists = creation_funcs().key_exists(typeslug);
	infos().insert(typeslug, info);
	// pr_dbg("ModuleFactory::register %s to infos() %p\n", typeslug.c_str(), &infos());
	return already_exists;
}

bool ModuleFactory::registerModuleType(const ModuleTypeSlug &typeslug, CreateModuleFunc funcCreate) {
	bool already_exists = creation_funcs().key_exists(typeslug);
	creation_funcs().insert(typeslug, funcCreate);
	// pr_dbg("ModuleFactory::register %s to funcs %p\n", typeslug.c_str(), &creation_funcs());
	return already_exists;
}

bool ModuleFactory::registerModuleFaceplate(const ModuleTypeSlug &typeslug, FaceplatePtr faceplate) {
	if (faceplates().key_exists(typeslug)) {
		return false;
	} else {
		return faceplates().insert(typeslug, faceplate);
	}
}

std::unique_ptr<CoreProcessor> ModuleFactory::create(const ModuleTypeSlug &typeslug) {
	if (auto f_create = creation_funcs().get(typeslug))
		return (*f_create)();
	else
		return nullptr;
}

std::string_view ModuleFactory::getModuleTypeName(const ModuleTypeSlug &typeslug) {
	if (auto m = infos().get(typeslug))
		return m->description;
	return "Not found.";
}

ModuleInfoView &ModuleFactory::getModuleInfo(const ModuleTypeSlug &typeslug) {
	if (auto m = infos().get(typeslug))
		return *m;
	else
		return nullinfo;
}

ModuleFactory::FaceplatePtr ModuleFactory::getModuleFaceplate(const ModuleTypeSlug &typeslug) {
	if (auto m = faceplates().get(typeslug))
		return *m;
	else
		return nullptr;
}

bool ModuleFactory::isValidSlug(const ModuleTypeSlug &typeslug) {
	return infos().key_exists(typeslug) && creation_funcs().key_exists(typeslug);
}

std::vector<ModuleTypeSlug> ModuleFactory::getAllSlugs() {
	std::vector<ModuleTypeSlug> slugs;
	slugs.assign(infos().keys.begin(), std::next(infos().keys.begin(), infos().size()));
	return slugs;
}

} // namespace MetaModule
