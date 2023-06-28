#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pages/styles.hh"
#include "patch/patch_data.hh"
#include <vector>

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

// FIXME: all these names need to be changed

struct AnimatedParam {
	lv_obj_t *obj;
	const MappedKnob *patchconf;
	const BaseElement &el;
	uint32_t param_idx;
	ParamAnimMethod anim_method = ParamAnimMethod::RotaryPot;
	float last_pot_reading = 0.5f;
};

struct AnimatedInJack {
	lv_obj_t *obj;
	const MappedInputJack *patchconf;
	const BaseElement &el;
	uint32_t input_idx;
};

struct AnimatedOutJack {
	lv_obj_t *obj;
	const MappedOutputJack *patchconf;
	const BaseElement &el;
	uint32_t output_idx;
};

struct AnimatedLight {
	lv_obj_t *obj;
	const BaseElement &el;
	uint16_t light_idx;
};

struct Mappings {
	std::vector<AnimatedParam> knobs;
	std::vector<AnimatedLight> lights;
	std::vector<AnimatedInJack> injacks;
	std::vector<AnimatedOutJack> outjacks;
};

////////////////////////////
////////////////////////////

struct Drawn {
	lv_obj_t *obj;
	uint32_t idx; //param_idx, light_idx, etc
	std::optional<uint32_t> mapped_panel_element_id;

	// float last_value = 0.5f;
	// Get these from visting info.elements[element_idx], when matching ParamElement
	// float min = 0.f;
	// float max = 1.f;
	// float get_mapped_val(float val) const {
	// 	return (max - min) * val + min;
	// }
};
struct DrawnElement {
	Drawn drawn;
	Element &element;
};

using Mappings2 = std::vector<DrawnElement>;

} // namespace MetaModule
