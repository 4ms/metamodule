#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/elements/element_info_view.hh"
#include "CoreModules/module_type_slug.hh"
#include <memory>
#include <string_view>
#include <vector>

namespace MetaModule
{

class ModuleFactory {
public:
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();

	ModuleFactory() = delete;
	static bool
	registerModuleType(const ModuleTypeSlug &typeslug, CreateModuleFunc funcCreate, const ModuleInfoView &info);
	static bool registerModuleType(const ModuleTypeSlug &typeslug, const ModuleInfoView &info);
	static bool registerModuleType(const ModuleTypeSlug &typeslug, CreateModuleFunc funcCreate);
	static bool registerModuleFaceplate(const ModuleTypeSlug &typeslug, std::string_view filename);

	static std::unique_ptr<CoreProcessor> create(const ModuleTypeSlug &typeslug);

	static ModuleInfoView &getModuleInfo(const ModuleTypeSlug &typeslug);
	static std::string_view getModuleFaceplate(const ModuleTypeSlug &typeslug);

	// Returns true if slug is valid and registered.
	static bool isValidSlug(const ModuleTypeSlug &typeslug);

	static std::vector<ModuleTypeSlug> getAllSlugs();

	static void setCurrentBrand(std::string slug);
	static std::string currentBrandPath();
};

} // namespace MetaModule
