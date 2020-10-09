#include "CppUTest/TestHarness.h"
#include "processors/tools/kneeCompress.h"
#include "fff.h"
#define FLOATS_NEARLY_EQUAL(e, a) DOUBLES_EQUAL(static_cast<double>(e), static_cast<double>(a), 0.000001);

TEST_GROUP(kneecomp_tests){
	void setup(){}
	void teardown(){}
};

TEST(kneecomp_tests, check_float_under_threshold_is_passthrough)
{
	KneeCompressor<float> c{0.75f};

	//under the threshold, value is unchanged
	FLOATS_NEARLY_EQUAL(0.0f, c.compress(0.0f));
	FLOATS_NEARLY_EQUAL(0.5f, c.compress(0.5f));
	FLOATS_NEARLY_EQUAL(0.75f, c.compress(0.75f));

	FLOATS_NEARLY_EQUAL(-0.5f, c.compress(-0.5f));
	FLOATS_NEARLY_EQUAL(-0.75f, c.compress(-0.75f));
}

TEST(kneecomp_tests, check_positive_floats_over_threshold_do_a_knee_bend)
{
	KneeCompressor<float> c{0.75f};

	float c85 = c.compress(0.85f);
	float c95 = c.compress(0.95f);
	float c99 = c.compress(0.99f);
	float c100 = c.compress(1.00f);

	//compressed value must keep increasing past knee
	CHECK(c85 > 0.75f);
	CHECK(c95 > c85);
	CHECK(c99 > c95);
	CHECK(c100 > c99);

	//compressed value must be less than uncompressed
	CHECK(c85 < 0.85f);
	CHECK(c95 < 0.95f);
	CHECK(c99 < 0.99f);
	CHECK(c100 < 1.0f);
}

TEST(kneecomp_tests, check_negative_floats_over_threshold_do_a_knee_bend)
{
	KneeCompressor<float> c{0.75f};

	float c85 = c.compress(-0.85f);
	float c95 = c.compress(-0.95f);
	float c99 = c.compress(-0.99f);
	float c100 = c.compress(-1.00f);

	//compressed value must keep increasing past knee
	CHECK(c85 < -0.75f);
	CHECK(c95 < c85);
	CHECK(c99 < c95);
	CHECK(c100 < c99);

	//compressed value must be less than uncompressed
	CHECK(c85 > -0.85f);
	CHECK(c95 > -0.95f);
	CHECK(c99 > -0.99f);
	CHECK(c100 > -1.0f);
}


constexpr int32_t INTVAL(const int bits, const float percent) {
	return static_cast<int32_t>(static_cast<float>(1U<<(bits-1)) * percent);
}

static const int32_t VAL100 = INTVAL(24, 1.0f);
static const int32_t VAL99 = INTVAL(24, 0.99f);
static const int32_t VAL95 = INTVAL(24, 0.95f);
static const int32_t VAL85 = INTVAL(24, 0.85f);
static const int32_t VAL75 = INTVAL(24, 0.75f);
static const int32_t VAL50 = INTVAL(24, 0.50f);
static const int32_t VALn100 = -VAL100 - 1U;

TEST(kneecomp_tests, check_int32_t_under_threshold_is_passthrough)
{
	KneeCompressor<int32_t> c{24, 0.75f};

	//under the threshold, value is unchanged
	LONGS_EQUAL(0, c.compress(0));
	LONGS_EQUAL(VAL50, c.compress(VAL50));
	LONGS_EQUAL(VAL75, c.compress(VAL75));

	LONGS_EQUAL(-VAL50, c.compress(-VAL50));
	LONGS_EQUAL(-VAL75, c.compress(-VAL75));
}

TEST(kneecomp_tests, check_positive_int32_ts_over_threshold_do_a_knee_bend)
{
	KneeCompressor<int32_t> c{24, 0.75f};

	int32_t c85 = c.compress(VAL85);
	int32_t c95 = c.compress(VAL95);
	int32_t c99 = c.compress(VAL99);
	int32_t c100 = c.compress(VAL100);

	//compressed value must keep increasing past knee
	CHECK(c85 > VAL75);
	CHECK(c95 > c85);
	CHECK(c99 > c95);
	CHECK(c100 > c99);

	//compressed value must be less than uncompressed
	CHECK(c85 < VAL85);
	CHECK(c95 < VAL95);
	CHECK(c99 < VAL99);
	CHECK(c100 < VAL100);
}

TEST(kneecomp_tests, check_negative_int32_ts_over_threshold_do_a_knee_bend)
{
	KneeCompressor<int32_t> c{24, 0.75f};

	int32_t c85 = c.compress(-VAL85);
	int32_t c95 = c.compress(-VAL95);
	int32_t c99 = c.compress(-VAL99);
	int32_t c100 = c.compress(-VAL100);

	//compressed value must keep increasing past knee
	CHECK(c85 < -VAL75);
	CHECK(c95 < c85);
	CHECK(c99 < c95);
	CHECK(c100 < c99);

	//compressed value must be less than uncompressed
	CHECK(c85 > -VAL85);
	CHECK(c95 > -VAL95);
	CHECK(c99 > -VAL99);
	CHECK(c100 > -VAL100);
}

