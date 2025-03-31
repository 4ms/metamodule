#include "doctest.h"

#include "dynload/version_sort.hh"

TEST_CASE("Sort alphabetaically by plugin name, then in newest-first version order") {
	using namespace MetaModule;

	MetaModule::PluginFile a_1_3_2{.plugin_name = "a", .version_in_filename = "1.3.2"};
	MetaModule::PluginFile a_1_3_2_dev2{.plugin_name = "a", .version_in_filename = "1.3.2-dev-2"};
	MetaModule::PluginFile a_1_3_2_dev10{.plugin_name = "a", .version_in_filename = "1.3.2-dev-10"};
	MetaModule::PluginFile a_1_2_3{.plugin_name = "a", .version_in_filename = "1.2.3"};

	// 1.3.2 should be shown above 1.3.2-dev-2
	// Because -dev-2 is a pre-release
	CHECK(alpha_then_newest_version(a_1_3_2, a_1_3_2_dev2));

	// 1.3.2-dev-2 should be shown above 1.3.2-dev-10
	// Even though dev-10 is probably newer than dev-2, SemVer says we should sort lexically
	CHECK(alpha_then_newest_version(a_1_3_2_dev2, a_1_3_2_dev10));

	// 1.3.2-dev-10 is newer than 1.2.3
	CHECK(alpha_then_newest_version(a_1_3_2_dev10, a_1_2_3));

	// Extra checks:
	// 1.3.2 should be shown above 1.2.3
	CHECK(alpha_then_newest_version(a_1_3_2, a_1_2_3));

	// 1.3.2 should be shown above 1.3.2-dev-10
	CHECK(alpha_then_newest_version(a_1_3_2, a_1_3_2_dev10));

	MetaModule::PluginFile b_1_3_2{.plugin_name = "b", .version_in_filename = "1.3.2"};
	MetaModule::PluginFile b_1_2_3{.plugin_name = "b", .version_in_filename = "1.2.3"};

	CHECK(alpha_then_newest_version(a_1_2_3, b_1_3_2));
	CHECK(alpha_then_newest_version(a_1_2_3, b_1_2_3));
	CHECK(alpha_then_newest_version(a_1_3_2_dev10, b_1_2_3));
	CHECK(alpha_then_newest_version(a_1_3_2_dev10, b_1_3_2));

	CHECK(alpha_then_newest_version(b_1_3_2, b_1_2_3));
}
