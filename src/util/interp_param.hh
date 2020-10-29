#pragma once

template<typename T, unsigned int num_updates>
struct Interp {
	Interp()
		: cur_val{0}
		, step_size{0}
	{
		static_assert(num_updates > 0);
	}

	T cur_val;
	T step_size;
	bool nonzero_step = false;

	void set_new_value(T new_val)
	{
		T d = new_val - cur_val;
		step_size = d / num_updates;
		// nonzero_step = !(d == 0);
		nonzero_step = !(d < (T)(1e-8) && d > (T)(-1e-8));
	}
	T next()
	{
		cur_val += step_size;
		return cur_val;
	}

	bool did_change()
	{
		return nonzero_step;
	}
};
