using namespace MathTools;
TEST_CASE("math_tests: wrapping")
{
	uint32_t a = 0;
	CHECK(1 == wrap<5>(a + 1));
	a++;
	CHECK(2 == wrap<5>(a + 1));
	a++;
	CHECK(3 == wrap<5>(a + 1));
	a++;
	CHECK(4 == wrap<5>(a + 1));
	a++;
	CHECK(0 == wrap<5>(a + 1));
}

TEST_CASE("math_tests: log2test")
{
	CHECK(Log2<1>::val == 0);
	CHECK(Log2<2>::val == 1);
	CHECK(Log2<4>::val == 2);
	CHECK(Log2<8>::val == 3);

	CHECK(Log2<32767>::val == 14);
	CHECK(Log2<32768>::val == 15);

	CHECK(Log2<65535>::val == 15);
	CHECK(Log2<65536>::val == 16);
}

TEST_CASE("math_tests: ipow_test")
{
	CHECK(1 == ipow(1, 11111));
	CHECK(1 == ipow(2, 0));
	CHECK(2 == ipow(2, 1));
	CHECK(4 == ipow(2, 2));
	CHECK(32768 == ipow(2, 15));
	CHECK(65536 == ipow(2, 16));
	CHECK(0x80000000U == ipow(2, 31));
}
TEST_CASE("math_tests: ipow_overflow")
{
	CHECK(0x00000000 == ipow(2, 32));
}

TEST_CASE("math_tests: sizeof_type_test")
{
	uint8_t u8 = 0;
	int8_t i8 = 0;
	uint16_t u16 = 0;
	int16_t i16 = 0;

	CHECK(32767 == bipolar_type_range(u16));
	CHECK(32767 == bipolar_type_range(i16));

	CHECK(127 == bipolar_type_range(u8));
	CHECK(127 == bipolar_type_range(i8));
}
