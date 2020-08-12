#include "CppUTest/TestHarness.h"
#include <fff.h>

#include "bitfield.hh"

TEST_GROUP(bitfield_tests){
	BitFieldBase<uint8_t> bf8;
	BitFieldBase<uint16_t> bf16;
	BitFieldBase<uint32_t> bf32;

	void setup(){
	}

	void teardown(){}
};

enum bits8 : uint8_t {
	BIT8_0 = 1,
	BIT8_1 = 2,
	BIT8_2 = 4,
	BIT8_3 = 8,

	BIT8_7 = 128,
};

enum bitsDefault {
	BITdef_0 = 1,
	BITdef_1 = 0xFFFFFFF0,	
};

TEST(bitfield_tests, single_bit_equals_itself)
{
	LONGS_EQUAL(bf8.bitfield(BIT8_0), BIT8_0);
	LONGS_EQUAL(bf16.bitfield(BIT8_1), BIT8_1);
	LONGS_EQUAL(bf32.bitfield(BIT8_2), BIT8_2);
}

TEST(bitfield_tests, two_single_bits_equals_OR)
{
	LONGS_EQUAL(bf8.bitfield(BIT8_0, BIT8_3), BIT8_0 | BIT8_3);
	LONGS_EQUAL(bf8.bitfield(BIT8_3, BIT8_7), BIT8_3 | BIT8_7);
}

TEST(bitfield_tests, overlapping_bits_equals_OR)
{
	uint8_t num1 = 0b1100;
	uint8_t num2 = 0b1010;
	LONGS_EQUAL(bf8.bitfield(num1, num2), num1 | num2);
}

TEST(bitfield_tests, overflow_ignores_higher_bits)
{
	uint32_t big_num = 0x89ABCD5A;
	uint32_t big_num2 = 0x89ABCDE6;
	uint8_t bottom_byte = static_cast<uint8_t>(0x000000FF & big_num);
	uint8_t bottom_byte2 = static_cast<uint8_t>(0x000000FF & big_num2);
	LONGS_EQUAL(bf8.bitfield(big_num, big_num2), bottom_byte | bottom_byte2);
}

TEST(bitfield_tests, underflow_zeroes_top_bits)
{
	uint8_t little_num = 0x12;
	uint8_t little_num2 = 0x2D;
	uint32_t big_little_num = 0x00000012;
	uint32_t big_little_num2 = 0x0000002D;
	LONGS_EQUAL(bf32.bitfield(little_num, little_num2), big_little_num | big_little_num2);
}

