#include "calibrate/calibration_data.hh"
#include "doctest.h"

TEST_CASE("Calibration validation") {

	CHECK(MetaModule::Calibration::from_volts(10.3f) == doctest::Approx(8388608.f));

	MetaModule::CalData caldata;

	caldata.reset_to_default();
	CHECK(caldata.validate());

	SUBCASE("NAN fails") {
		float slope = NAN;
		float offset = caldata.out_cal[0].offset();
		caldata.out_cal[0].set_slope_offset(slope, offset);

		CHECK_FALSE(caldata.validate());

		slope = caldata.out_cal[1].slope();
		offset = NAN;
		caldata.out_cal[0].set_slope_offset(slope, offset);

		CHECK_FALSE(caldata.validate());
	}

	SUBCASE("Slope off by too much fails") {
		// pass:
		float slope = -814000;
		float offset = 0;
		caldata.out_cal[0].set_slope_offset(slope, offset);

		CHECK(caldata.validate());

		slope = -750000;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK_FALSE(caldata.validate());

		slope = -930000;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK_FALSE(caldata.validate());

		slope = 0;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK_FALSE(caldata.validate());

		slope = INFINITY;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK_FALSE(caldata.validate());
	}

	SUBCASE("Offset off by too much fails") {
		// pass:
		float slope = -814000;
		float offset = 0;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK(caldata.validate());

		//pass
		offset = 0.5;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK(caldata.validate());

		//pass
		offset = -0.3;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK(caldata.validate());

		offset = 0.7;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK_FALSE(caldata.validate());

		offset = -0.7;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK_FALSE(caldata.validate());

		offset = -88888888888.f;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK_FALSE(caldata.validate());

		offset = 88888888888.f;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK_FALSE(caldata.validate());

		offset = INFINITY;
		caldata.out_cal[0].set_slope_offset(slope, offset);
		CHECK_FALSE(caldata.validate());
	}
}
