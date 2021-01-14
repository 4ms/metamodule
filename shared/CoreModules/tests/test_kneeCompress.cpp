#include "doctest.h"
#include "processors/tools/kneeCompress.h"
#include <stdint.h>

TEST_CASE("check_float_under_threshold_is_passthrough")
{
	KneeCompressor<float> c{0.75f};

	// under the threshold, value is unchanged
	CHECK_EQ(c.compress(0.0f), doctest::Approx(0.0f));
	CHECK_EQ(c.compress(0.5f), doctest::Approx(0.5f));
	CHECK_EQ(c.compress(0.75f), doctest::Approx(0.75f));
	CHECK_EQ(c.compress(-0.5f), doctest::Approx(-0.5f));
	CHECK_EQ(c.compress(-0.75f), doctest::Approx(-0.75f));
}

TEST_CASE("check_positive_floats_over_threshold_do_a_knee_bend")
{
	KneeCompressor<float> c{0.75f};

	float c85 = c.compress(0.85f);
	float c95 = c.compress(0.95f);
	float c99 = c.compress(0.99f);
	float c100 = c.compress(1.00f);

	// compressed value must keep increasing past knee
	CHECK(c85 > 0.75f);
	CHECK(c95 > c85);
	CHECK(c99 > c95);
	CHECK(c100 > c99);

	// compressed value must be less than uncompressed
	CHECK(c85 < 0.85f);
	CHECK(c95 < 0.95f);
	CHECK(c99 < 0.99f);
	CHECK(c100 < 1.0f);
}

TEST_CASE("check_negative_floats_over_threshold_do_a_knee_bend")
{
	KneeCompressor<float> c{0.75f};

	float c85 = c.compress(-0.85f);
	float c95 = c.compress(-0.95f);
	float c99 = c.compress(-0.99f);
	float c100 = c.compress(-1.00f);

	// compressed value must keep increasing past knee
	CHECK(c85 < -0.75f);
	CHECK(c95 < c85);
	CHECK(c99 < c95);
	CHECK(c100 < c99);

	// compressed value must be less than uncompressed
	CHECK(c85 > -0.85f);
	CHECK(c95 > -0.95f);
	CHECK(c99 > -0.99f);
	CHECK(c100 > -1.0f);
}

constexpr int32_t INTVAL(const int bits, const float percent)
{
	return static_cast<int32_t>(static_cast<float>(1U << (bits - 1)) * percent);
}

static const int32_t VAL100 = INTVAL(24, 1.0f);
static const int32_t VAL99 = INTVAL(24, 0.99f);
static const int32_t VAL95 = INTVAL(24, 0.95f);
static const int32_t VAL85 = INTVAL(24, 0.85f);
static const int32_t VAL75 = INTVAL(24, 0.75f);
static const int32_t VAL50 = INTVAL(24, 0.50f);
static const int32_t VALn100 = -VAL100 - 1U;

TEST_CASE("check_int32_t_under_threshold_is_passthrough")
{
	KneeCompressor<int32_t> c{24, 0.75f};

	// under the threshold, value is unchanged
	CHECK_EQ(0, c.compress(0));
	CHECK_EQ(VAL50, c.compress(VAL50));
	CHECK_EQ(VAL75, c.compress(VAL75));
	CHECK_EQ(-VAL50, c.compress(-VAL50));
	CHECK_EQ(-VAL75, c.compress(-VAL75));
}

TEST_CASE("check_positive_int32_ts_over_threshold_do_a_knee_bend")
{
	KneeCompressor<int32_t> c{24, 0.75f};

	int32_t c85 = c.compress(VAL85);
	int32_t c95 = c.compress(VAL95);
	int32_t c99 = c.compress(VAL99);
	int32_t c100 = c.compress(VAL100);

	// compressed value must keep increasing past knee
	CHECK(c85 > VAL75);
	CHECK(c95 > c85);
	CHECK(c99 > c95);
	CHECK(c100 > c99);

	// compressed value must be less than uncompressed
	CHECK(c85 < VAL85);
	CHECK(c95 < VAL95);
	CHECK(c99 < VAL99);
	CHECK(c100 < VAL100);
}

TEST_CASE("check_negative_int32_ts_over_threshold_do_a_knee_bend")
{
	KneeCompressor<int32_t> c{24, 0.75f};

	int32_t c85 = c.compress(-VAL85);
	int32_t c95 = c.compress(-VAL95);
	int32_t c99 = c.compress(-VAL99);
	int32_t c100 = c.compress(-VAL100);

	// compressed value must keep increasing past knee
	CHECK(c85 < -VAL75);
	CHECK(c95 < c85);
	CHECK(c99 < c95);
	CHECK(c100 < c99);

	// compressed value must be less than uncompressed
	CHECK(c85 > -VAL85);
	CHECK(c95 > -VAL95);
	CHECK(c99 > -VAL99);
	CHECK(c100 > -VAL100);
}

TEST_CASE("check_int32_past_bounds")
{
	KneeCompressor<int32_t> c{24, 0.75f};

	int32_t c100 = c.compress(VAL100);
	int32_t c110 = c.compress(INTVAL(24, 1.1f));
	int32_t c150 = c.compress(INTVAL(24, 1.5f));

	int32_t cn100 = c.compress(VALn100);
	int32_t cn110 = c.compress(-INTVAL(24, 1.1f));
	int32_t cn150 = c.compress(-INTVAL(24, 1.5f));

	CHECK(c150 < INTVAL(24, 1.5f));
	CHECK(c110 < INTVAL(24, 1.1f));

	CHECK(c150 > c110);
	CHECK(c110 > c100);

	CHECK(cn150 > -INTVAL(24, 1.5f));
	CHECK(cn110 > -INTVAL(24, 1.1f));

	CHECK(cn150 < cn110);
	CHECK(cn110 < cn100);
}

