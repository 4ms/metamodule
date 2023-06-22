#pragma once
#include "lvgl/lvgl.h"
#include "pages/styles.hh"
#include "patch/patch_data.hh"

namespace MetaModule
{

enum class ParamAnimMethod {
	None,
	RotaryPot,
	LinearSlider,
	MomentaryButton,
	LatchingButton,
	Toggle2pos,
	Toggle3pos,
	Encoder
};

//TODO: Knob or Switch ==> rename to MParam?
struct AnimatedParam {
	lv_obj_t *obj;
	const MappedKnob &patchconf;
	ParamAnimMethod anim_method = ParamAnimMethod::RotaryPot;
	float last_pot_reading = 0.5f;
};

} // namespace MetaModule
