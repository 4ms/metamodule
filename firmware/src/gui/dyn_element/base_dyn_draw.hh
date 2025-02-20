#pragma once
#include "lvgl.h"

namespace MetaModule
{

struct BaseDynDraw {
	virtual ~BaseDynDraw() = default;
	virtual void draw() = 0;
	virtual void prepare(lv_obj_t *module_canvas, unsigned height) = 0;
	virtual void blur() = 0;
};

} // namespace MetaModule
