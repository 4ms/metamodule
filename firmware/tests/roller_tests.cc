#include "doctest.h"
#include <string>
#include <string_view>

TEST_CASE("handle names with \\n or \\0 in them") {
	std::string opts;
	opts = "A\n";

	std::string line = "Item \n With\n linebreaks \n";
	auto sv = std::string_view{line};

	using namespace std::literals;
	opts.append(sv.substr(0, sv.find_first_of("\0\n"sv)));

	CHECK(opts == "A\nItem ");
}
