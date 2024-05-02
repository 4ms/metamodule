#include "doctest.h"

#include "dynload/sym_list_parse.hh"
#include <string>
#include <string_view>

#include "console/pr_dbg.hh"

TEST_CASE("Parse yaml to vector of HostSymbols") {

	const std::string test_yaml = R"(Symbols:
  - Name: Symbol1
    Hash: 0x55559999
    Addr: 0x123
  - Name: Symbol2
    Addr: 0x234
  - Name: Symbol3
    Addr: 0x456
  - Name: Symbol4
    Addr: 0x567
  - Name: _Zsym1
    Addr: 0xc2000000
  - Name: _Zsym2
    Addr: 0xc2000001
)";

	auto syms = MetaModule::parse_symlist(test_yaml);

	CHECK(syms.size() == 6);
	CHECK(syms[0].name == "Symbol1");
	CHECK(syms[0].hash == 0x55559999);
	CHECK(syms[0].address == 0x123);

	CHECK(syms[1].name == "Symbol2");
	CHECK(syms[1].hash == 0);
	CHECK(syms[1].address == 0x234);

	CHECK(syms[2].name == "Symbol3");
	CHECK(syms[2].hash == 0);
	CHECK(syms[2].address == 0x456);

	CHECK(syms[3].name == "Symbol4");
	CHECK(syms[3].hash == 0);
	CHECK(syms[3].address == 0x567);

	CHECK(syms[4].name == "_Zsym1");
	CHECK(syms[4].hash == 0);
	CHECK(syms[4].address == 0xC2000000);

	CHECK(syms[5].name == "_Zsym2");
	CHECK(syms[5].hash == 0);
	CHECK(syms[5].address == 0xC2000001);
}
