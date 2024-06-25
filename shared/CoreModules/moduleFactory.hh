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

	static bool registerModuleType(std::string_view brand_name,
								   const ModuleTypeSlug &typeslug,
								   CreateModuleFunc funcCreate,
								   const ModuleInfoView &info,
								   std::string_view faceplate_filename);

	// defaults to brand = "4ms"
	static bool registerModuleType(const ModuleTypeSlug &typeslug,
								   CreateModuleFunc funcCreate,
								   const ModuleInfoView &info,
								   std::string_view faceplate_filename);

	static std::unique_ptr<CoreProcessor> create(std::string_view combined_slug);

	static ModuleInfoView &getModuleInfo(std::string_view combined_slug);
	static std::string_view getModuleFaceplate(std::string_view combined_slug);

	// Returns true if slug is valid and registered.
	static bool isValidSlug(std::string_view combined_slug);
	static bool isValidBrandModule(std::string_view brand, std::string_view module_name);

	static std::vector<ModuleTypeSlug> getAllSlugs(std::string_view brand);
	static std::vector<ModuleTypeSlug> getAllBrands();
};

} // namespace MetaModule
