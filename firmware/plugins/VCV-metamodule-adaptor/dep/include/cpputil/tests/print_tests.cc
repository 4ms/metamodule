#include "doctest.h"
#include "util/print.hh"
#include <climits>
#include <span>
#include <string_view>
#include <climits>

unsigned num_chars_printed = 0;
char buffer[128]{};

void putc(const char c) {
	buffer[num_chars_printed] = c;
	num_chars_printed++;
}

TEST_CASE("print() usage") {
	num_chars_printed = 0;
	print<putc>("Hi");
	CHECK(num_chars_printed == 2);
	CHECK(buffer[0] == 'H');
	CHECK(buffer[1] == 'i');

	num_chars_printed = 0;
	printone<putc>("Test");
	CHECK(num_chars_printed == 4);
	CHECK(buffer[0] == 'T');
	CHECK(buffer[1] == 'e');
	CHECK(buffer[2] == 's');
	CHECK(buffer[3] == 't');
}

const char *get_str(int x) {
	if (x == 0)
		return "abc";
	return "z";
}

std::string_view get_sv(int x) {
	if (x == 1)
		return "xy";
	return "Z";
}

TEST_CASE("print() multiple args usage") {
	num_chars_printed = 0;
	print<putc>("Hi", 1);
	CHECK(num_chars_printed == 3);
	CHECK(buffer[0] == 'H');
	CHECK(buffer[1] == 'i');
	CHECK(buffer[2] == '1');

	num_chars_printed = 0;
	print<putc>(-12, "Oh");
	CHECK(num_chars_printed == 5);
	CHECK(buffer[0] == '-');
	CHECK(buffer[1] == '1');
	CHECK(buffer[2] == '2');
	CHECK(buffer[3] == 'O');
	CHECK(buffer[4] == 'h');

	num_chars_printed = 0;
	print<putc>("O", get_sv(1), " ", get_str(0));
	CHECK(num_chars_printed == 7);
	CHECK(buffer[0] == 'O');
	CHECK(buffer[1] == 'x');
	CHECK(buffer[2] == 'y');
	CHECK(buffer[3] == ' ');
	CHECK(buffer[4] == 'a');
	CHECK(buffer[5] == 'b');
	CHECK(buffer[6] == 'c');
}

TEST_CASE("print ints") {
	num_chars_printed = 0;
	print<putc>(0);
	CHECK(num_chars_printed == 1);
	CHECK(buffer[0] == '0');

	num_chars_printed = 0;
	print<putc>(2);
	CHECK(num_chars_printed == 1);
	CHECK(buffer[0] == '2');

	num_chars_printed = 0;
	print<putc>(20);
	CHECK(num_chars_printed == 2);
	CHECK(buffer[0] == '2');
	CHECK(buffer[1] == '0');

	num_chars_printed = 0;
	print<putc>(201);
	CHECK(num_chars_printed == 3);
	CHECK(buffer[0] == '2');
	CHECK(buffer[1] == '0');
	CHECK(buffer[2] == '1');

	num_chars_printed = 0;
	print<putc>(1'234'567'890);
	CHECK(num_chars_printed == 10);
	CHECK(buffer[0] == '1');
	CHECK(buffer[1] == '2');
	CHECK(buffer[2] == '3');
	CHECK(buffer[3] == '4');
	CHECK(buffer[4] == '5');
	CHECK(buffer[5] == '6');
	CHECK(buffer[6] == '7');
	CHECK(buffer[7] == '8');
	CHECK(buffer[8] == '9');
	CHECK(buffer[9] == '0');

	num_chars_printed = 0;
	print<putc>(INT_MAX);
	CHECK(num_chars_printed == 10);
	CHECK(buffer[0] == '2');
	//...
	CHECK(buffer[9] == '7');

	num_chars_printed = 0;
	print<putc>(INT_MIN);
	CHECK(num_chars_printed == 11);
	CHECK(buffer[0] == '-');
	CHECK(buffer[1] == '2');
	//...
	CHECK(buffer[10] == '8');

	num_chars_printed = 0;
	print<putc>(-2);
	CHECK(num_chars_printed == 2);
	CHECK(buffer[0] == '-');
	CHECK(buffer[1] == '2');

	num_chars_printed = 0;
	print<putc>(-20);
	CHECK(num_chars_printed == 3);
	CHECK(buffer[0] == '-');
	CHECK(buffer[1] == '2');
	CHECK(buffer[2] == '0');

	num_chars_printed = 0;
	print<putc>(-201);
	CHECK(num_chars_printed == 4);
	CHECK(buffer[0] == '-');
	CHECK(buffer[1] == '2');
	CHECK(buffer[2] == '0');
	CHECK(buffer[3] == '1');
}

TEST_CASE("print Hex") {
	num_chars_printed = 0;
	print<putc>(Hex{0xD0B});
	CHECK(num_chars_printed == 3);
	CHECK(buffer[0] == 'D');
	CHECK(buffer[1] == '0');
	CHECK(buffer[2] == 'B');

	num_chars_printed = 0;
	print<putc>(Hex{0xABCD1234});
	CHECK(num_chars_printed == 8);
	CHECK(buffer[0] == 'A');
	CHECK(buffer[1] == 'B');
	CHECK(buffer[2] == 'C');
	CHECK(buffer[3] == 'D');
	CHECK(buffer[4] == '1');
	CHECK(buffer[5] == '2');
	CHECK(buffer[6] == '3');
	CHECK(buffer[7] == '4');

	num_chars_printed = 0;
	print<putc>(Hex{0xFFFFFFFF});
	CHECK(num_chars_printed == 8);
	CHECK(buffer[0] == 'F');
	CHECK(buffer[1] == 'F');
	CHECK(buffer[2] == 'F');
	CHECK(buffer[3] == 'F');
	CHECK(buffer[4] == 'F');
	CHECK(buffer[5] == 'F');
	CHECK(buffer[6] == 'F');
	CHECK(buffer[7] == 'F');

	num_chars_printed = 0;
	print<putc>(Hex{0x7FFFFFFF});
	CHECK(num_chars_printed == 8);
	CHECK(buffer[0] == '7');
	CHECK(buffer[1] == 'F');
	CHECK(buffer[2] == 'F');
	CHECK(buffer[3] == 'F');
	CHECK(buffer[4] == 'F');
	CHECK(buffer[5] == 'F');
	CHECK(buffer[6] == 'F');
	CHECK(buffer[7] == 'F');
}

namespace
{
unsigned num_chars_logged = 0;
unsigned num_chars_warned = 0;

auto CountPrintedFunc = [](auto) { num_chars_logged++; };
auto CountWarnedFunc = [](auto) { num_chars_warned++; };

void log(auto... x) { (print<CountPrintedFunc>(x), ...); }

void warn(auto... x) { (print<CountWarnedFunc>(x), ...); }
} // namespace

TEST_CASE("Wrapper template method usage") {
	num_chars_logged = 0;
	num_chars_warned = 0;

	SUBCASE("use log()") {
		log("One", 201, "Three");
		CHECK(num_chars_logged == 11);
		CHECK(num_chars_warned == 0);
	}

	SUBCASE("use warn()") {
		warn("e", -130, "Three");
		CHECK(num_chars_logged == 0);
		CHECK(num_chars_warned == 10);
	}
}
