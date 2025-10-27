#pragma once
#include "util/math.hh"

#include <cstdio>
#include <optional>

namespace MetaModule
{

class CatchupParam {
	using T = float;
	static constexpr T Max = T{1};
	static constexpr T Tolerance = T{5.f} / T{4095};

	T last_module_val{0};
	T last_phys_val{0};

	float fade_phys_breakpoint{0};
	float fade_coef_a{1.f};
	float fade_coef_b{1.f};
	float fade_offset_b{0.f};

	float encoder_resolution{0.01f};

	enum class State { Tracking, Catchup } state = State::Catchup;

public:
	enum class Mode { ResumeOnMotion, ResumeOnEqual, LinearFade, Encoder } mode = Mode::ResumeOnMotion;

	// Called when a physical knob changes value.
	// - cur_phys_val is the new physical value of the knob.
	// - cur_module_val is the value the module reports the knob is at.
	// Returns the value that we should set the module param, or nullopt if we shouldn't set anything
	std::optional<T> update(T cur_phys_val, T cur_module_val) {

		if (mode == Mode::Encoder) {
			return std::clamp<T>(cur_phys_val * encoder_resolution + cur_module_val, 0, 1);
		}

		last_phys_val = cur_phys_val;

		// ResumeOnMotion mode always returns knob physical value.
		// This is because update() is only called when knob moves.
		if (mode == Mode::ResumeOnMotion) {
			return enter_tracking(cur_phys_val);
		}

		if (state == State::Tracking) {
			// Change to Catchup mode if module changes value
			if (MathTools::abs_diff(last_module_val, cur_module_val) >= Tolerance) {
				enter_catchup();
				return {};
			} else {
				//Otherwise return the physical knob value
				return cur_phys_val;
			}
		}

		if (mode == Mode::ResumeOnEqual) {
			return update_resume_equal(cur_phys_val, cur_module_val);
		}

		if (mode == Mode::LinearFade) {
			return update_linear_fade(cur_phys_val, cur_module_val);
		}

		return {};
	}

	void reset_phys_val(T phys_val, T module_val) {
		if (mode == Mode::LinearFade) {
			if (MathTools::abs_diff(module_val, phys_val) < Tolerance) {
				enter_tracking(phys_val);
			} else {
				calc_linear_fade_coef(phys_val, module_val);
				enter_catchup();
			}
		} else {

			// If phys knob value jumps (e.g. loaded a knobset or patch and knobs are in a different position)
			// then enter catchup mode
			if (MathTools::abs_diff(phys_val, module_val) < Tolerance) {
				enter_tracking(phys_val);
			}

			else if (MathTools::abs_diff(last_phys_val, phys_val) >= Tolerance)
			{
				enter_catchup();

			} else if (MathTools::abs_diff(last_module_val, module_val) >= Tolerance) {
				enter_catchup();
			}
		}

		last_phys_val = phys_val;
		last_module_val = module_val;
	}

	void set_mode(Mode newmode) {
		mode = newmode;

		if (mode == Mode::LinearFade) {
			if (last_module_val == last_phys_val)
				state = State::Tracking;
		}
	}

	bool is_tracking() const {
		return state == State::Tracking;
	}

	// After setting the module's param value, the caller should query the module
	// for the param value it actually saved, then pass that along to this function.
	// In case a module modifies the value sent to it, e.g. quantizes it to a value
	// then this allows CatchupParam to see that happen.
	void report_actual_module_val(T val) {
		last_module_val = val;
	}

private:
	std::optional<T> update_resume_equal(T scaled_phys_val, T module_val) {
		// Exit catchup mode if module and physical values are close
		if (MathTools::abs_diff(module_val, scaled_phys_val) < Tolerance) {
			return enter_tracking(scaled_phys_val);
		}
		return {};
	}

	T update_linear_fade(T phys_val, T module_val) {
		// Re-calc fade coef if module changed its own value
		if (MathTools::abs_diff(module_val, last_module_val) >= Tolerance) {
			calc_linear_fade_coef(phys_val, module_val);
		}

		// Exit by moving physical knob to min or max (0 or 1)
		if (phys_val <= Tolerance || phys_val >= (Max - Tolerance)) {
			enter_tracking(phys_val);
		}

		float new_module_val{};

		if (phys_val > fade_phys_breakpoint)
			new_module_val = phys_val * fade_coef_b + fade_offset_b;
		else
			new_module_val = phys_val * fade_coef_a;

		last_module_val = new_module_val;
		return new_module_val;
	}

public:
	T enter_tracking(T phys_val) {
		last_module_val = phys_val;
		state = State::Tracking;
		return phys_val;
	}

private:
	void enter_catchup() {
		if (state != State::Catchup && mode == Mode::LinearFade) {
			// pr_dbg("Should not get here!\n");
		}
		state = State::Catchup;
	}

	void calc_linear_fade_coef(T phys_val, T module_val) {
		if (phys_val == 0 && module_val == 0) {
			fade_coef_a = 1.f;
			fade_coef_b = 1.f;
			fade_offset_b = 0.f;
		} else {
			fade_phys_breakpoint = phys_val;
			fade_coef_a = module_val / std::max(phys_val, Tolerance); //cannot be 0
			fade_coef_b = (Max - module_val) / std::min(Max - phys_val, Max - Tolerance);
			fade_offset_b = module_val - phys_val * fade_coef_b;
		}
	}
};

} // namespace MetaModule
