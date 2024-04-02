#pragma once
#include <cstdint>
#include <span>
#include <string_view>
#include <cstdint>

struct Hex {
	uint32_t x;
};

using putchar_t = void (*)(const char c);

template<putchar_t putc>
void printone(const char *str) {
	while (*str)
		putc(*str++);
}

template<putchar_t putc>
void printone(const unsigned char *str) {
	while (*str)
		putc(*str++);
}

template<putchar_t putc>
void printone(std::string_view str) {
	printone<putc>(str.data());
}

namespace
{
template<unsigned Place, putchar_t putc>
void print_digit(unsigned &value, bool &print_zero) {
	if (print_zero || value >= Place) {
		unsigned dig = value / Place;
		value -= dig * Place;
		putc(dig < 10 ? '0' + dig : 'A' + dig - 10);
		print_zero = true;
	}
}
} // namespace

template<putchar_t putc>
void printone(int32_t val) {
	if (!val) {
		putc('0');
		return;
	}

	unsigned uval;
	if (val < 0) {
		putc('-');
		uval = -val;
	} else
		uval = val;

	bool print_zero = false;
	print_digit<1000000000, putc>(uval, print_zero);
	print_digit<100000000, putc>(uval, print_zero);
	print_digit<10000000, putc>(uval, print_zero);
	print_digit<1000000, putc>(uval, print_zero);
	print_digit<100000, putc>(uval, print_zero);
	print_digit<10000, putc>(uval, print_zero);
	print_digit<1000, putc>(uval, print_zero);
	print_digit<100, putc>(uval, print_zero);
	print_digit<10, putc>(uval, print_zero);
	print_digit<1, putc>(uval, print_zero);
}

template<putchar_t putc>
void printone(Hex hex) {
	uint32_t value = hex.x;

	if (!value) {
		putc('0');
		return;
	}

	bool print_zero = false;
	print_digit<0x10000000, putc>(value, print_zero);
	print_digit<0x1000000, putc>(value, print_zero);
	print_digit<0x100000, putc>(value, print_zero);
	print_digit<0x10000, putc>(value, print_zero);
	print_digit<0x1000, putc>(value, print_zero);
	print_digit<0x100, putc>(value, print_zero);
	print_digit<0x10, putc>(value, print_zero);
	print_digit<0x1, putc>(value, print_zero);
}

template<putchar_t putc>
void printone(float f) {
	//TODO
	putc('?');
	printone<putc>(static_cast<int32_t>(f));
	putc('?');
}

// print<putc>(...):
// Define a putc(const char c) function and pass it as the template parameter.
// Usage examples:
// print<uart_putc>("Some ", stuff, 2, output());
// print<console_putc>("SomeVar = ", somevar);
// print<error>("Fail!");
// print<log>("Loaded in ", tm, " ms");
template<putchar_t putc, typename... Types>
void print(Types... args) {
	(printone<putc>(args), ...);
}
