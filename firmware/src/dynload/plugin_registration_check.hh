#pragma once
#include "CoreModules/register_module.hh"
#include <string>
#include <string_view>
#include <vector>

namespace MetaModule::PluginRegistrationCheck
{

// Records each module that a native plugin registers while it's being loaded
// (from its static constructors and from init()), so the loader can check
// that the brand and module slugs match the plugin's plugin.json/plugin-mm.json.
//
// Native plugins can only register modules by calling register_module(). The
// dynloader rebinds plugins' import of it to register_module_from_plugin(),
// below. VCV-style plugins register through Plugin::addModel(), which always
// uses the plugin's brand slug.

struct Registration {
	std::string brand;
	std::string module_slug;
};

namespace Internal
{
inline std::vector<Registration> registrations;
inline bool recording = false;
} // namespace Internal

// Records registrations while it's in scope. Only one plugin is loaded at a time.
struct Recorder {
	Recorder() {
		Internal::registrations.clear();
		Internal::recording = true;
	}

	~Recorder() {
		Internal::recording = false;
		Internal::registrations.clear();
	}

	Recorder(Recorder const &) = delete;
	Recorder &operator=(Recorder const &) = delete;

	std::vector<Registration> const &registrations() const {
		return Internal::registrations;
	}
};

// Plugins' calls to register_module() land here
inline bool register_module_from_plugin(std::string_view brand_slug,
										std::string_view module_slug,
										CreateModuleFunc funcCreate,
										ModuleInfoView const &info,
										std::string_view faceplate_filename) {
	if (Internal::recording)
		Internal::registrations.push_back({std::string{brand_slug}, std::string{module_slug}});

	return register_module(brand_slug, module_slug, std::move(funcCreate), info, faceplate_filename);
}

// Mangled name of the register_module() overload that plugins import
// (part of the plugin ABI: see metamodule-plugin-sdk/api-symbols.txt)
constexpr std::string_view RegisterModuleSymbol =
	"_ZN10MetaModule15register_moduleESt17basic_string_viewIcSt11char_traitsIcEES3_St8functionIFSt10unique_"
	"ptrI13CoreProcessorSt14default_deleteIS6_EEvEERKNS_14ModuleInfoViewES3_";

inline void *symbol_redirect(std::string_view name) {
	if (name == RegisterModuleSymbol)
		return reinterpret_cast<void *>(&register_module_from_plugin);
	return nullptr;
}

} // namespace MetaModule::PluginRegistrationCheck
