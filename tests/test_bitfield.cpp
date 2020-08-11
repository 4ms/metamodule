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

/*
template <int Z>
class SomePeriph {
public:
    SomePeriph() : a(Z) {}
    int a;
};

template <int Z, int Y>
class SomeOtherPeriph {
public:
    SomeOtherPeriph() : a(Z), b(Y) {
        //init Peripheral Z, channel Y
    }
    int a, b;
};


template <typename X>
auto constexpr create_SomePeriph(X x) {
    return SomePeriph<x()>();
}

template <typename X>
auto constexpr create_SomeOtherPeriph(X x) {
    return SomeOtherPeriph<std::get<0>(x()), std::get<1>(x())>();
}

void test2() {
  auto Channel1 = create_SomePeriph([] { return 1; });
  auto Channel2 = create_SomePeriph([] { return 2; });
  //
  auto OtherChannel3 = create_SomeOtherPeriph([] { return std::make_tuple(ADC2_BASE, 3); });
}
*/
