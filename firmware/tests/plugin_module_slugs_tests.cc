#include "doctest.h"
#include "src/dynload/plugin_module_slugs.hh"
#include <string>
#include <vector>

using namespace MetaModule;

namespace
{

void register_test_module(std::string_view brand, std::string_view module) {
	ModuleFactory::registerModuleType(brand, module, [] { return std::unique_ptr<CoreProcessor>{}; }, {}, "");
}

} // namespace

TEST_CASE("module_is_from_plugin: brands match any module in the brand") {
	using PluginModuleSlugs::module_is_from_plugin;

	CHECK(module_is_from_plugin("Jack Test:Jack Test", "Jack Test"));
	CHECK(module_is_from_plugin("Jack Test:Other", "Jack Test"));
	CHECK_FALSE(module_is_from_plugin("Jack Test:Jack Test", "jacktest"));
	CHECK_FALSE(module_is_from_plugin("Befaco:EvenVCO", "Jack Test"));

	SUBCASE("Case-insensitive, like ModuleFactory lookups") {
		CHECK(module_is_from_plugin("jack test:Jack Test", "Jack Test"));
	}

	SUBCASE("A brand that's a prefix of another doesn't match") {
		CHECK_FALSE(module_is_from_plugin("Jack Test 2:Mod", "Jack Test"));
	}
}

TEST_CASE("module_is_from_plugin: combined slugs match only that module") {
	using PluginModuleSlugs::module_is_from_plugin;

	CHECK(module_is_from_plugin("Befaco:Extra", "Befaco:Extra"));
	CHECK_FALSE(module_is_from_plugin("Befaco:EvenVCO", "Befaco:Extra"));
	CHECK_FALSE(module_is_from_plugin("Other:Extra", "Befaco:Extra"));
	CHECK_FALSE(module_is_from_plugin("Befaco:ExtraLong", "Befaco:Extra"));
}

TEST_CASE("module_is_from_plugin: resolves brand aliases") {
	using PluginModuleSlugs::module_is_from_plugin;

	ModuleFactory::registerBrandAlias("SlugsTestBrand", "SlugsTestAlias");

	CHECK(module_is_from_plugin("SlugsTestAlias:Mod", "SlugsTestBrand"));
	CHECK(module_is_from_plugin("SlugsTestAlias:Mod", "SlugsTestBrand:Mod"));
	CHECK_FALSE(module_is_from_plugin("SlugsTestAlias:Other", "SlugsTestBrand:Mod"));
}

TEST_CASE("module_is_from_plugin: list of plugin slugs") {
	using PluginModuleSlugs::module_is_from_plugin;

	std::vector<std::string> plugin_slugs{"NewBrand", "Befaco:Extra"};

	CHECK(module_is_from_plugin("NewBrand:Anything", plugin_slugs));
	CHECK(module_is_from_plugin("Befaco:Extra", plugin_slugs));
	CHECK_FALSE(module_is_from_plugin("Befaco:EvenVCO", plugin_slugs));
	CHECK_FALSE(module_is_from_plugin("HubMedium", plugin_slugs));
	CHECK_FALSE(module_is_from_plugin("Befaco:Extra", std::vector<std::string>{}));
}

TEST_CASE("PluginModuleSlugs::unregister removes the plugin's modules, and not others in a shared brand") {
	// A brand that existed before the plugin was loaded
	register_test_module("SlugsSharedBrand", "Original1");
	register_test_module("SlugsSharedBrand", "Original2");

	// The plugin adds a module to it, and creates its own brand
	register_test_module("SlugsSharedBrand", "FromPlugin");
	register_test_module("SlugsPluginBrand", "A");
	register_test_module("SlugsPluginBrand", "B");

	std::vector<std::string> plugin_slugs{"SlugsPluginBrand", "SlugsSharedBrand:FromPlugin"};

	CHECK(PluginModuleSlugs::unregister(plugin_slugs) == 2);

	CHECK_FALSE(ModuleFactory::isRegisteredBrand("SlugsPluginBrand"));
	CHECK_FALSE(ModuleFactory::isValidBrandModule("SlugsSharedBrand", "FromPlugin"));
	CHECK(ModuleFactory::isValidBrandModule("SlugsSharedBrand", "Original1"));
	CHECK(ModuleFactory::isValidBrandModule("SlugsSharedBrand", "Original2"));

	SUBCASE("Unregistering again finds nothing") {
		CHECK(PluginModuleSlugs::unregister(plugin_slugs) == 0);
	}

	ModuleFactory::unregisterBrand("SlugsSharedBrand");
}
