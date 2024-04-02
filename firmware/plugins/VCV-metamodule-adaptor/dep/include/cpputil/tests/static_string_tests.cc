#include "doctest.h"
#include "util/static_string.hh"
#include <array>
#include <cstring>

TEST_CASE("Static String construction") {
	SUBCASE("Default (empty) constructor") {
		StaticString<3> emptystr;
		CHECK(emptystr._data[0] == '\0');
	}

	SUBCASE("const char* construction") {
		StaticString<3> ccstr{"ABC"};
		CHECK(ccstr._data[0] == 'A');
		CHECK(ccstr._data[1] == 'B');
		CHECK(ccstr._data[2] == 'C');
		CHECK(ccstr._data[3] == '\0');

		const char DEF[] = "DEF";
		StaticString<3> str{DEF};
		CHECK(str._data[0] == 'D');
		CHECK(str._data[1] == 'E');
		CHECK(str._data[2] == 'F');
		CHECK(str._data[3] == '\0');

		SUBCASE("Extra capacity doesn't change string") {
			StaticString<40> str40{DEF};
			CHECK(str40._data[0] == 'D');
			CHECK(str40._data[1] == 'E');
			CHECK(str40._data[2] == 'F');
			CHECK(str40._data[3] == '\0');
		}
	}
}

TEST_CASE("StaticString string_view ctor") {

	SUBCASE("Same size") {
		std::string_view sv{"1234567890"};
		StaticString<10> s{sv};
		CHECK(s.length() == 10);
		CHECK(s[0] == '1');
		CHECK(s[9] == '0');
	}
	SUBCASE("SV is larger size") {
		std::string_view sv{"0123456789"};
		StaticString<8> s{sv};
		CHECK(s.length() == 8);
		CHECK(s[0] == '0');
		CHECK(s[7] == '7');
		CHECK(s[8] == '\0');
	}
	SUBCASE("SV is smaller size") {
		std::string_view sv{"0123456789"};
		StaticString<12> s{sv};
		CHECK(s.length() == 10);
		CHECK(s[0] == '0');
		CHECK(s[9] == '9');
		CHECK(s[10] == '\0');
		// CHECK(s[11] == '\0'); // not necessarily true, [10] is the null-terminator
	}
	SUBCASE("SV is is of a larger string but ss is smaller size") {
		std::array<char, 26> _buf;
		for (char i = 0; auto &b : _buf)
			b = 'A' + i++;

		std::string_view sv{_buf.data(), _buf.size()};
		StaticString<12> s{sv.substr(2, 5)};
		CHECK(s.length() == 5);
		CHECK(s[0] == 'C');
		CHECK(s[1] == 'D');
		CHECK(s[2] == 'E');
		CHECK(s[3] == 'F');
		CHECK(s[4] == 'G');
		CHECK(s[5] == '\0');
	}
}

TEST_CASE("Static string reading") {
	SUBCASE(".c_str() returns actual data") {
		StaticString<3> str{"123"};
		CHECK(str.c_str()[0] == '1');
		CHECK(str.c_str()[1] == '2');
		CHECK(str.c_str()[2] == '3');
		CHECK(str.c_str()[3] == '\0');
	}

	SUBCASE("explicit const char * cast returns actual data") {
		StaticString<5> str{"123"};
		auto str2 = static_cast<const char *>(str);
		CHECK(str2[0] == '1');
		CHECK(str2[1] == '2');
		CHECK(str2[2] == '3');
		CHECK(str2[3] == '\0');
	}

	SUBCASE("implicit const char * cast returns actual data") {
		StaticString<5> str{"123"};
		CHECK_EQ(strcmp(str, "123"), 0);
	}
}

TEST_CASE("Static String comparison") {
	SUBCASE("Equality operator") {
		StaticString<3> str1{"123"};
		StaticString<3> str2{"123"};
		StaticString<3> str3{"abc"};
		CHECK_EQ(str1 == str2, true);
		CHECK_EQ(str1 == str3, false);
	}

	SUBCASE("Equality with different capacity StaticStrings") {
		StaticString<3> str1{"123"};
		StaticString<2> str2{"12"};
		CHECK_EQ(str1 == str2, false);
		CHECK_EQ(str2 == str1, false);

		StaticString<3> str3{"abc"};
		StaticString<5> str4{"abc"};
		CHECK_EQ(str3 == str4, true);
		CHECK_EQ(str4 == str3, true);
	}
}
