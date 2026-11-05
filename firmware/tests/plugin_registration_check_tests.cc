#include "doctest.h"
#include "src/dynload/plugin_registration_check.hh"
#include <string>

using namespace MetaModule;

namespace
{

void register_test_module(std::string_view brand, std::string_view module) {
	ModuleFactory::registerModuleType(brand, module, [] { return std::unique_ptr<CoreProcessor>{}; }, {}, "");
}

} // namespace

TEST_CASE("PluginRegistrationCheck::Recorder records modules registered while it's in scope") {
	register_test_module("RecorderTestBrand", "Before");

	{
		PluginRegistrationCheck::Recorder recorder;

		register_test_module("RecorderTestBrand", "A");
		// The brand as passed, not resolved to an existing brand
		register_test_module("recordertestbrand", "B");
		// The brand-less overload (registers under "4msCompany")
		ModuleFactory::registerModuleType("RecorderTestC", [] { return std::unique_ptr<CoreProcessor>{}; }, {}, "");

		auto const &recorded = recorder.registrations();
		REQUIRE(recorded.size() == 3);
		CHECK(recorded[0].brand == "RecorderTestBrand");
		CHECK(recorded[0].module_slug == "A");
		CHECK(recorded[1].brand == "recordertestbrand");
		CHECK(recorded[1].module_slug == "B");
		CHECK(recorded[2].brand == "4msCompany");
		CHECK(recorded[2].module_slug == "RecorderTestC");
	}

	SUBCASE("Stops recording when it goes out of scope") {
		PluginRegistrationCheck::Recorder recorder;
		CHECK(recorder.registrations().empty());
	}

	// Registering with no recorder must not crash
	register_test_module("RecorderTestBrand", "After");

	ModuleFactory::unregisterBrand("RecorderTestBrand");
	ModuleFactory::unregisterModule("4msCompany", "RecorderTestC");
}
