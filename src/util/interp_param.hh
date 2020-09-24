#pragma once

template<typename T, int num_updates>
struct Interp {
	Interp() 
		:cur_val{0}
		,step_size{0}
		{}

	T cur_val;
	T step_size;

	void set_new_value(T new_val) 
	{
		step_size = (new_val - cur_val) / num_updates;
	}
	T next() {
		cur_val += step_size;
		return cur_val;
	}
};
