#pragma once
#include "math.hh"
#include <cmath>
#include "drivers/stm32xx.h"

template <int ACCEL = 150, int LAG = 200, int MORPH_LAG = 333>
class AccelParam {

	const float fACCEL;
	const float SPEED;
	const float MORPH_SPEED;

public:
	AccelParam(float initval = 0.f)
		: cur_val_(initval)
		, dest_(initval)
		, fACCEL(static_cast<float>(ACCEL))
		, SPEED(1.f/LAG)
		, MORPH_SPEED(1.f/MORPH_LAG)
	{}

	float update(int32_t motion)
	{
		update_dest(motion);
		update_val();
		return cur_val_;
	}

	float read()
	{
		return cur_val_;
	}

private:
	void update_dest(int32_t inc)
	{
		if (inc == 0)
			return;

		uint32_t now = HAL_GetTick();
		float new_inc;

		if ((last_inc * inc) < 0 || last_inc_time == 0) // different sign = changed direction
			dest_ += SPEED * inc;
		else {
			uint32_t time_since = (now - last_inc_time);
			if (time_since > ACCEL * abs(inc))
				time_since = ACCEL * abs(inc);
			else if (time_since == 0)
				time_since = 1;
			dest_ += (inc * SPEED * ACCEL / (float)time_since);
		}
		last_inc_time = now;
		dest_ = MathTools::constrain(dest_, -1.0f, 1.0f);
	}

	void update_val()
	{
		if (fabsf(cur_val_ - dest_) < 0.0001f) {
			cur_val_ = dest_;
		} else if (cur_val_ < dest_) {
			cur_val_ += MORPH_SPEED;
			if (cur_val_ > dest_)
				cur_val_ = dest_;
		} else if (cur_val_ > dest_) {
			cur_val_ -= MORPH_SPEED;
			if (cur_val_ < dest_)
				cur_val_ = dest_;
		}
	}

	float cur_val_;
	float dest_;
	int32_t last_inc = 0;
	uint32_t last_inc_time = 0;
};

