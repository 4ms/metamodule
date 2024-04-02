#include "doctest.h"
#include "util/int_to_str.hh"
#include <span>
#include <climits>

TEST_CASE("int to str chop") {
	char b[5] = {0x7F, 0x7F, 0x7F, 0x7F, 0x7F};
	std::span<char, 5> buf{b};

	SUBCASE("Basic usage") {
		int_to_str_chop(123, buf);
		CHECK(buf[0] == '1');
		CHECK(buf[1] == '2');
		CHECK(buf[2] == '3');
		CHECK(buf[3] == '\0');
		CHECK(buf[4] == 0x7F);
	}

	SUBCASE("Zero") {
		int_to_str_chop(0, buf);
		CHECK(buf[0] == '0');
		CHECK(buf[1] == '\0');
	}

	SUBCASE("Overflow drops leading digits") {
		int_to_str_chop(12345, buf);
		//The '1' is dropped
		CHECK(buf[0] == '2');
		CHECK(buf[1] == '3');
		CHECK(buf[2] == '4');
		CHECK(buf[3] == '5');
		CHECK(buf[4] == '\0');
	}

	SUBCASE("Negative") {
		int_to_str_chop(-123, buf);
		CHECK(buf[0] == '-');
		CHECK(buf[1] == '1'); //3
		CHECK(buf[2] == '2'); //2
		CHECK(buf[3] == '3'); // \0
		CHECK(buf[4] == '\0');
		int_to_str_chop(-12345, buf);
		//The '123' is dropped and the - is ended
		CHECK(buf[0] == '-');
		CHECK(buf[1] == '3');
		CHECK(buf[2] == '4');
		CHECK(buf[3] == '5');
		CHECK(buf[4] == '\0');
	}
}

TEST_CASE("num digits") {
	CHECK(num_digits(1) == 1);
	CHECK(num_digits(12) == 2);
	CHECK(num_digits(123) == 3);
	CHECK(num_digits(1234) == 4);
	CHECK(num_digits(12345) == 5);
	CHECK(num_digits(123456) == 6);
	CHECK(num_digits(1234567) == 7);
	CHECK(num_digits(12345678) == 8);
	CHECK(num_digits(123456789) == 9);
	CHECK(num_digits(1234'567'890) == 10);
	CHECK(num_digits(INT_MAX) == 10);
	CHECK(num_digits(UINT_MAX) == 10);
}

TEST_CASE("int_to_str") {

	char b[5] = {0x7F, 0x7F, 0x7F, 0x7F, 0x7F};
	std::span<char, 5> buf{b};

	SUBCASE("Basic usage") {
		CHECK(int_to_str(123, buf));
		CHECK(buf[0] == '1');
		CHECK(buf[1] == '2');
		CHECK(buf[2] == '3');
		CHECK(buf[3] == '\0');
		CHECK(buf[4] == 0x7F);

		CHECK(int_to_str(1234, buf));
		CHECK(buf[0] == '1');
		CHECK(buf[1] == '2');
		CHECK(buf[2] == '3');
		CHECK(buf[3] == '4');
		CHECK(buf[4] == 0);
	}
	SUBCASE("Zero") {
		CHECK(int_to_str(0, buf));
		CHECK(buf[0] == '0');
		CHECK(buf[1] == '\0');
	}

	SUBCASE("Overflow returns false") {
		CHECK_FALSE(int_to_str(12345, buf));
		CHECK_FALSE(int_to_str(-12345, buf));
		CHECK_FALSE(int_to_str(-1234, buf));
	}

	SUBCASE("Negative") {
		int_to_str(-1, buf);
		CHECK(buf[0] == '-');
		CHECK(buf[1] == '1');
		CHECK(buf[2] == '\0');
		CHECK(buf[3] == 0x7F);
		CHECK(buf[4] == 0x7F);

		int_to_str(-12, buf);
		CHECK(buf[0] == '-');
		CHECK(buf[1] == '1');
		CHECK(buf[2] == '2');
		CHECK(buf[3] == '\0');
		CHECK(buf[4] == 0x7F);

		int_to_str(-123, buf);
		CHECK(buf[0] == '-');
		CHECK(buf[1] == '1');
		CHECK(buf[2] == '2');
		CHECK(buf[3] == '3');
		CHECK(buf[4] == '\0');
	}
}
