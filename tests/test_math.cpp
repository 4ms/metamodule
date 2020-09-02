#include "CppUTest/TestHarness.h"
#include "util/math.hh"
#include <array>
#include <fff.h>

TEST_GROUP(math_tests){

	void setup(){}

	void teardown(){}

};

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
	LONGS_EQUAL(1, ipow(1, 1));
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
