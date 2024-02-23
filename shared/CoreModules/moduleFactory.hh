#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/elements/element_info_view.hh"
#include "CoreModules/module_type_slug.hh"
#include <memory>
#include <vector>

// #ifdef TESTPROJECT
// #define pr_dbg(...)
// #else
// #include "console/pr_dbg.hh"
// #endif

// Why does this not work?
// extern "C" {
//typedef struct lv_img_dsc_t lv_img_dsc_t;
// // struct lv_img_dsc_t;
// }
namespace MetaModule
{

class ModuleFactory {
public:
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();
	using FaceplatePtr = void *;
	static inline constexpr int MAX_MODULE_TYPES = 512;

	ModuleFactory() = delete;
	static bool
	registerModuleType(const ModuleTypeSlug &typeslug, CreateModuleFunc funcCreate, const ModuleInfoView &info);
	static bool registerModuleType(const ModuleTypeSlug &typeslug, const ModuleInfoView &info);
	static bool registerModuleType(const ModuleTypeSlug &typeslug, CreateModuleFunc funcCreate);
	static bool registerModuleFaceplate(const ModuleTypeSlug &typeslug, FaceplatePtr faceplate);

	static std::unique_ptr<CoreProcessor> create(const ModuleTypeSlug &typeslug);

	static ModuleInfoView &getModuleInfo(const ModuleTypeSlug &typeslug);
	static FaceplatePtr getModuleFaceplate(const ModuleTypeSlug &typeslug);

	// Returns true if slug is valid and registered.
	static bool isValidSlug(const ModuleTypeSlug &typeslug);

	static std::vector<ModuleTypeSlug> getAllSlugs();
};

} // namespace MetaModule
