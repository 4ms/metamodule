#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/elements/element_info_view.hh"
#include "CoreModules/module_type_slug.hh"
#include <functional>
#include <memory>
#include <string_view>
#include <vector>

namespace MetaModule
{

class ModuleFactory {
public:
	using CreateModuleFunc = std::function<std::unique_ptr<CoreProcessor>()>;

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
	static std::vector<std::string> getAllModuleDisplayNames(std::string_view brand);
	static std::vector<std::string_view> getAllBrandDisplayNames();

	static void setModuleDisplayName(std::string_view combined_slug, std::string_view display_name);
	static std::string_view getModuleDisplayName(std::string_view combined_slug);
	static void setBrandDisplayName(std::string_view brand_name, std::string_view display_name);
	static std::string_view getBrandDisplayName(std::string_view brand_name);
	static std::string_view getBrandSlug(std::string_view display_name);
	static std::string_view getModuleSlug(std::string_view brand_slug, std::string_view display_name);

	static bool unregisterBrand(std::string_view brand_name);
};

} // namespace MetaModule
