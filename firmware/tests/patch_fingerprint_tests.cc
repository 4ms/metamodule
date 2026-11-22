#include "doctest.h"
#include "patch_file/patch_fingerprint.hh"
#include <vector>

using namespace MetaModule;

// Same vectors as 4ms-vcv tests/patch_fingerprint_tests.cc: both sides must agree
TEST_CASE("patch fingerprint") {
	CHECK(patch_fingerprint(std::vector<BrandModuleSlug>{}) == 2166136261u);
	CHECK(patch_fingerprint(std::vector<BrandModuleSlug>{"HubMedium"}) == 89770027u);
	CHECK(patch_fingerprint(std::vector<BrandModuleSlug>{"HubMedium", "4ms:EnOsc"}) == 1445992889u);
	CHECK(patch_fingerprint(std::vector<BrandModuleSlug>{"4ms:EnOsc", "HubMedium"}) == 2785609493u);
	CHECK(patch_fingerprint(std::vector<BrandModuleSlug>{"HubMedium", "Befaco:EvenVCO", "Befaco:EvenVCO"}) ==
		  4103304475u);
}
