#include "doctest.h"

#include <string>
#include "fw_update/hash/hash_processor.hh"
using namespace MetaModule;

TEST_CASE("Test MD5") {

	MD5Processor processor;
	
	auto digest = processor.getDigest();

	auto str_digest = to_hex_string(digest);

	CHECK("d41d8cd98f00b204e9800998ecf8427e" == std::string(str_digest.data(), str_digest.size()));
}
