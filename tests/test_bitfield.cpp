#include "CppUTest/TestHarness.h"
#include <fff.h>

#include "bitfield.hh"

TEST_GROUP(bitfield_tests){
	BitFieldBase<uint8_t> bf8;
	BitFieldBase<uint16_t> bf16;
	BitFieldBase<uint32_t> bf32;

	void setup(){}

	void teardown(){}
};

enum bits8 : uint8_t {
	BIT0 = 0,
	BIT1 = 1,
	BIT2 = 2,
	BIT3 = 4,
	BIT4 = 8
};

TEST(bitfield_tests, single_bit_correct)
{
	LONGS_EQUAL(bf8.bitfield(BIT0), BIT0);
	LONGS_EQUAL(bf8.bitfield(BIT1), BIT1);
}

TEST(bitfield_tests, two_bits_correct)
{
	LONGS_EQUAL(bf8.bitfield(BIT1, BIT3), BIT1 + BIT3);
	LONGS_EQUAL(bf8.bitfield(BIT0, BIT4), BIT0 + BIT4);
}

