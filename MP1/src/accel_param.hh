#pragma once
#include "drivers/stm32xx.h"
#include "math.hh"
#include <cmath>

class AccelParam {
public:
	AccelParam(int acceleration = 150, int lag = 200, int catchup_lag = 333, float initval = 0.f)
		: cur_val_(initval)
		, dest_(initval)
		, ACCEL(acceleration)
		, fACCEL(static_cast<float>(ACCEL))
		, SPEED(1.f / lag)
		, MORPH_SPEED(1.f / catchup_lag)
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
	float cur_val_;
	float dest_;
	int32_t last_inc = 0;
	uint32_t last_inc_time = 0;

	const int ACCEL;
	const float fACCEL;
	const float SPEED;
	const float MORPH_SPEED;

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
			dest_ += (inc * SPEED * fACCEL / (float)time_since);
		}
		last_inc_time = now;
		dest_ = MathTools::constrain(dest_, 0.0f, 1.0f);
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
};

