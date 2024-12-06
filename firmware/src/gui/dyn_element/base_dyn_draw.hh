#pragma once
#include "lvgl.h"

namespace MetaModule
{

struct BaseDynDraw {
	virtual ~BaseDynDraw() = default;
	virtual void draw(lv_obj_t *canvas) = 0;
	// virtual void prepare_focus(lv_obj_t *module_canvas);
};

} // namespace MetaModule
