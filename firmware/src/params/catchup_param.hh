#pragma once
#include "console/pr_dbg.hh"
#include "debug.hh"
#include "util/math.hh"
#include <optional>

namespace MetaModule
{

class CatchupParam {
	using T = float;
	static constexpr T Max = T{1};
	static constexpr T Tolerance = T{5.f} / T{4095};

	T last_module_val{0};
	T last_phys_val{0};
	float fade_phys_val{0};
	float fade_mod_val{0};

	enum class State { Tracking, Catchup } state = State::Catchup;

public:
	enum class Mode { ResumeOnMotion, ResumeOnEqual, LinearFade } mode = Mode::LinearFade;

	// Called when a physical knob changes value.
	std::optional<T> update(T cur_phys_val, T cur_module_val) {
		last_phys_val = cur_phys_val;

		if (state == State::Tracking) {
			// Change to Catchup mode if module changes value
			if (MathTools::abs_diff(last_module_val, cur_module_val) >= Tolerance) {
				pr_dbg("update(): m:%f=>%f  ->c\n", last_module_val, cur_module_val);
				last_module_val = cur_module_val;
				enter_catchup();
				return {};

			} else {
				pr_dbg("update(): m:%f=>%f (t)\n", last_module_val, cur_module_val);
				last_module_val = cur_phys_val;
				return cur_phys_val;
			}
		}

		if (mode == Mode::ResumeOnMotion) {
			return update_resume_motion(cur_phys_val, cur_module_val);
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
				pr_dbg("reset(): m:%f p:%f  ->t\n", module_val, phys_val);
			} else {
				fade_phys_val = std::clamp(phys_val, Tolerance, Max - Tolerance); //cannot be 0 or Max
				fade_mod_val = module_val;
				pr_dbg("reset(): m:%f p:%f  ->c\n", module_val, phys_val);
				enter_catchup();
			}
		} else {

			// If phys knob value jumps (e.g. loaded a knobset or patch and knobs are in a different position)
			// then enter catchup mode
			if (MathTools::abs_diff(last_phys_val, phys_val) >= Tolerance) {
				enter_catchup();
			}
		}

		last_phys_val = phys_val;
		last_module_val = module_val;
	}

	void set_mode(Mode newmode) {
		mode = newmode;
		// TODO: does it matter if we're in the Tracking or Catchup state when the mode changes?
	}

	bool is_tracking() const {
		return state == State::Tracking;
	}

private:
	T update_resume_motion(T phys_val, T) {
		// Since update() is only is called if the physical value changed
		// then always start tracking
		return enter_tracking(phys_val);
	}

	std::optional<T> update_resume_equal(T phys_val, T module_val) {
		// Exit catchup mode if module and physical values are close
		if (MathTools::abs_diff(module_val, phys_val) < Tolerance) {
			return enter_tracking(phys_val);
		}
		return {};
	}

	T update_linear_fade(T phys_val, T) {
		// Exit by moving physical knob to min or max (0 or 1)
		if (phys_val <= Tolerance || phys_val >= (Max - Tolerance)) {
			enter_tracking(phys_val);
		}

		// TODO: cache these coefficients
		if (phys_val > fade_phys_val)
			return (phys_val - fade_phys_val) * (Max - fade_mod_val) / (Max - fade_phys_val) + fade_mod_val;
		else
			return phys_val * fade_mod_val / fade_phys_val;
	}

	T enter_tracking(T phys_val) {
		Debug::Pin1::high();

		state = State::Tracking;

		Debug::Pin1::low();

		return phys_val;
	}

	void enter_catchup() {
		if (state != State::Catchup && mode == Mode::LinearFade) {
			pr_dbg("Should not get here!\n");
		}

		Debug::Pin0::high();

		state = State::Catchup;

		Debug::Pin0::low();
	}
};

} // namespace MetaModule
