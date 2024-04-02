#include "doctest.h"
#include <cstdint>
//
#include "util/voct_calibrator.hh"

TEST_CASE("Normal usage with integer") {
	using VoctCalibrator = VoctCalibrator<int16_t>;
	VoctCalibrator vcal;

	// Offset is value for C0
	vcal.reset();
	vcal.record_measurement(VoctCalibrator::C0, 20);
	CHECK(vcal.offset() == 20);

	// Resets to 0
	vcal.reset();
	CHECK(vcal.offset() == 0);
	CHECK(vcal.slope() == 0);

	// Offset can be deduced without measuring C0
	vcal.record_measurement(VoctCalibrator::C1, 1060);
	vcal.record_measurement(VoctCalibrator::C2, 2060);
	CHECK(vcal.slope() == 1000);
	CHECK(vcal.offset() == 60);

	// Can handle inverted slope (also new measurements overwrite old)
	vcal.record_measurement(VoctCalibrator::C1, 2060);
	vcal.record_measurement(VoctCalibrator::C2, 1060);
	CHECK(vcal.slope() == -1000);
	CHECK(vcal.offset() == 3060);

	// Measuring C0 is a special case, and offset will always be negative that
	vcal.reset();
	vcal.record_measurement(VoctCalibrator::C0, 20);
	vcal.record_measurement(VoctCalibrator::C1, 1060);
	vcal.record_measurement(VoctCalibrator::C2, 2060);
	CHECK(vcal.offset() == 20);

	vcal.reset();
	vcal.record_measurement(VoctCalibrator::C1, 1060);
	vcal.record_measurement(VoctCalibrator::C2, 2060);
	CHECK(vcal.offset() == 60);
	vcal.record_measurement(VoctCalibrator::C0, 20);
	CHECK(vcal.offset() == 20);

	// Can just measure C0 and one other point
	vcal.reset();
	vcal.record_measurement(VoctCalibrator::C0, 20);
	vcal.record_measurement(VoctCalibrator::C2, 2060);
	CHECK(vcal.slope() == 1020);
	CHECK(vcal.offset() == 20);

	// Measuring a third point keeps the last two only
	vcal.reset();
	vcal.record_measurement(VoctCalibrator::C1, 1060);
	vcal.record_measurement(VoctCalibrator::C2, 2060);
	CHECK(vcal.slope() == (2060 - 1060));
	CHECK(vcal.offset() == 60);
	vcal.record_measurement(VoctCalibrator::C3, 3080);
	CHECK(vcal.slope() == (3080 - 2060));
	CHECK(vcal.offset() == 20);
}

TEST_CASE("Works with float") {
	using VoctCalibrator = VoctCalibrator<float>;
	VoctCalibrator vcal;

	vcal.reset();
	vcal.record_measurement(VoctCalibrator::C0, 19.5f);
	CHECK(vcal.offset() == 19.5f);

	vcal.reset();
	vcal.record_measurement(VoctCalibrator::C1, 1061);
	vcal.record_measurement(VoctCalibrator::C3, 2060);
	CHECK(vcal.slope() == ((2060.f - 1061.f) / 2.f));
	CHECK(vcal.offset() == 561.5f);

	vcal.reset();
	vcal.record_measurement(VoctCalibrator::C1, 1061.5f);
	vcal.record_measurement(VoctCalibrator::C3, 2060.75f);
	CHECK(vcal.slope() == ((2060.75f - 1061.5f) / 2.f));
	CHECK(vcal.offset() == (1061.5f - vcal.slope()));
}
