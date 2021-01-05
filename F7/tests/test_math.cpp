#include "CppUTest/TestHarness.h"
#include "util/math.hh"
#include <array>
#include <fff.h>
using namespace MathTools;
TEST_GROUP(math_tests){

	void setup(){}

	void teardown(){}

};

TEST(math_tests, wrapping)
{
	uint32_t a = 0;
	LONGS_EQUAL(1, wrap<5>(a + 1));
	a++;
	LONGS_EQUAL(2, wrap<5>(a + 1));
	a++;
	LONGS_EQUAL(3, wrap<5>(a + 1));
	a++;
	LONGS_EQUAL(4, wrap<5>(a + 1));
	a++;
	LONGS_EQUAL(0, wrap<5>(a + 1));
}

TEST(math_tests, log2test)
{
	LONGS_EQUAL(Log2<1>::val, 0);
	LONGS_EQUAL(Log2<2>::val, 1);
	LONGS_EQUAL(Log2<4>::val, 2);
	LONGS_EQUAL(Log2<8>::val, 3);

	LONGS_EQUAL(Log2<32767>::val, 14);
	LONGS_EQUAL(Log2<32768>::val, 15);

	LONGS_EQUAL(Log2<65535>::val, 15);
	LONGS_EQUAL(Log2<65536>::val, 16);
}

TEST(math_tests, ipow_test)
{
	UNSIGNED_LONGS_EQUAL(1, ipow(1, 11111));
	UNSIGNED_LONGS_EQUAL(1, ipow(2, 0));
	UNSIGNED_LONGS_EQUAL(2, ipow(2, 1));
	UNSIGNED_LONGS_EQUAL(4, ipow(2, 2));
	UNSIGNED_LONGS_EQUAL(32768, ipow(2, 15));
	UNSIGNED_LONGS_EQUAL(65536, ipow(2, 16));
	UNSIGNED_LONGS_EQUAL(0x80000000U, ipow(2, 31));
}
TEST(math_tests, ipow_overflow)
{
	UNSIGNED_LONGS_EQUAL(0x00000000, ipow(2, 32));
}

TEST(math_tests, sizeof_type_test)
{
	uint8_t u8 = 0;
	int8_t i8 = 0;
	uint16_t u16 = 0;
	int16_t i16 = 0;

	LONGS_EQUAL(32767, bipolar_type_range(u16));
	LONGS_EQUAL(32767, bipolar_type_range(i16));

	LONGS_EQUAL(127, bipolar_type_range(u8));
	LONGS_EQUAL(127, bipolar_type_range(i8));
}
