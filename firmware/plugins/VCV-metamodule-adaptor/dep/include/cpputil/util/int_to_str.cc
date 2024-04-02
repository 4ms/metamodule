#include <span>
#include <cstdint>
#include <cstddef>
#include <span>

///// Method #1: fill available buffer spots, truncating

namespace
{

template<unsigned Place>
constexpr size_t Log10() {
	return Log10<Place / 10>() + 1;
}

template<>
constexpr size_t Log10<1>() {
	return 1;
}

template<unsigned Place>
char digit(unsigned &value, unsigned avail) {
	if (value > Place) {
		unsigned dig = value / Place;
		value -= dig * Place;
		return avail > Log10<Place>() ? '0' + dig : 0;
	}
	return 0;
}
} // namespace

void int_to_str_chop(int32_t value, const std::span<char> buf) {
	if (buf.size() <= 1)
		return;

	if (value == 0) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	unsigned len = 0;
	if (value < 0) {
		buf[len++] = '-';
		value = -value;
	}
	unsigned val = value;

	if (char dig = digit<1000000000>(val, buf.size() - len); dig)
		buf[len++] = dig;
	if (char dig = digit<100000000>(val, buf.size() - len); dig)
		buf[len++] = dig;
	if (char dig = digit<10000000>(val, buf.size() - len); dig)
		buf[len++] = dig;
	if (char dig = digit<1000000>(val, buf.size() - len); dig)
		buf[len++] = dig;
	if (char dig = digit<100000>(val, buf.size() - len); dig)
		buf[len++] = dig;
	if (char dig = digit<10000>(val, buf.size() - len); dig)
		buf[len++] = dig;
	if (char dig = digit<1000>(val, buf.size() - len); dig)
		buf[len++] = dig;
	if (char dig = digit<100>(val, buf.size() - len); dig)
		buf[len++] = dig;
	if (char dig = digit<10>(val, buf.size() - len); dig)
		buf[len++] = dig;
	if (char dig = digit<1>(val, buf.size() - len); dig)
		buf[len++] = dig;

	buf[len] = '\0';
}

//////////////// Method 2: return false if value exceeds buffer space

namespace
{
template<unsigned Place>
char _digit(unsigned &value) {
	if (value >= Place) {
		unsigned dig = value / Place;
		value -= dig * Place;
		return '0' + dig;
	}
	return 0;
}
} // namespace

unsigned num_digits(unsigned value) {
	if (value < 10)
		return 1;
	if (value < 100)
		return 2;
	if (value < 1000)
		return 3;
	if (value < 10000)
		return 4;
	if (value < 100000)
		return 5;
	return num_digits(value / 100000) + 5;
}

bool int_to_str(int32_t value, const std::span<char> buf) {
	int len = 0;
	if (value < 0) {
		if (!buf.size())
			return false;
		buf[len++] = '-';
		value = -value;
	}
	if (value == 0) {
		buf[0] = '0';
		buf[1] = '\0';
		return true;
	}

	auto num_dig = num_digits(value);
	if ((num_dig + len + 1) > buf.size())
		return false;

	unsigned val = value;

	if (char dig = _digit<1000000000>(val); dig)
		buf[len++] = dig;
	if (char dig = _digit<100000000>(val); dig)
		buf[len++] = dig;
	if (char dig = _digit<10000000>(val); dig)
		buf[len++] = dig;
	if (char dig = _digit<1000000>(val); dig)
		buf[len++] = dig;
	if (char dig = _digit<100000>(val); dig)
		buf[len++] = dig;
	if (char dig = _digit<10000>(val); dig)
		buf[len++] = dig;
	if (char dig = _digit<1000>(val); dig)
		buf[len++] = dig;
	if (char dig = _digit<100>(val); dig)
		buf[len++] = dig;
	if (char dig = _digit<10>(val); dig)
		buf[len++] = dig;
	if (char dig = _digit<1>(val); dig)
		buf[len++] = dig;

	buf[len] = '\0';
	return true;
}
