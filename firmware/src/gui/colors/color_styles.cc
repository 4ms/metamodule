#include "gui/colors/color_styles.hh"
#include "gui/colors/color_scheme.hh"

namespace MetaModule::ColorStyles
{

namespace
{
// These are atomic styles that assign a color to one property.
lv_style_t bg_styles[METACOLOR_COUNT];
lv_style_t bg_grad_styles[METACOLOR_COUNT];
lv_style_t bg_img_recolor_styles[METACOLOR_COUNT];
lv_style_t text_styles[METACOLOR_COUNT];
lv_style_t border_styles[METACOLOR_COUNT];
lv_style_t outline_styles[METACOLOR_COUNT];
lv_style_t line_styles[METACOLOR_COUNT];
lv_style_t arc_styles[METACOLOR_COUNT];
lv_style_t shadow_styles[METACOLOR_COUNT];
lv_style_t img_recolor_styles[METACOLOR_COUNT];

// For each color in the active scheme, 
// update/set the color of the each style's relevant part
void apply_colors() {
	for (unsigned i = 0; i < METACOLOR_COUNT; i++) {
		auto color = mc(static_cast<MetaColorId>(i));
		lv_style_set_bg_color(&bg_styles[i], color);
		lv_style_set_bg_grad_color(&bg_grad_styles[i], color);
		lv_style_set_bg_img_recolor(&bg_img_recolor_styles[i], color);
		lv_style_set_text_color(&text_styles[i], color);
		lv_style_set_border_color(&border_styles[i], color);
		lv_style_set_outline_color(&outline_styles[i], color);
		lv_style_set_line_color(&line_styles[i], color);
		lv_style_set_arc_color(&arc_styles[i], color);
		lv_style_set_shadow_color(&shadow_styles[i], color);
		lv_style_set_img_recolor(&img_recolor_styles[i], color);
	}
}
} // namespace

void init() {
	static bool is_init = false;
	if (!is_init) {
		for (unsigned i = 0; i < METACOLOR_COUNT; i++) {
			lv_style_init(&bg_styles[i]);
			lv_style_init(&bg_grad_styles[i]);
			lv_style_init(&bg_img_recolor_styles[i]);
			lv_style_init(&text_styles[i]);
			lv_style_init(&border_styles[i]);
			lv_style_init(&outline_styles[i]);
			lv_style_init(&line_styles[i]);
			lv_style_init(&arc_styles[i]);
			lv_style_init(&shadow_styles[i]);
			lv_style_init(&img_recolor_styles[i]);
		}
	}
	is_init = true;
	apply_colors();
}

void reapply_scheme() {
	apply_colors();
	lv_obj_report_style_change(nullptr);
}

} // namespace MetaModule::ColorStyles

extern "C" {

lv_style_t *scheme_bg(MetaColorId id) {
	return &MetaModule::ColorStyles::bg_styles[id];
}
lv_style_t *scheme_bg_grad(MetaColorId id) {
	return &MetaModule::ColorStyles::bg_grad_styles[id];
}
lv_style_t *scheme_bg_img_recolor(MetaColorId id) {
	return &MetaModule::ColorStyles::bg_img_recolor_styles[id];
}
lv_style_t *scheme_text(MetaColorId id) {
	return &MetaModule::ColorStyles::text_styles[id];
}
lv_style_t *scheme_border(MetaColorId id) {
	return &MetaModule::ColorStyles::border_styles[id];
}
lv_style_t *scheme_outline(MetaColorId id) {
	return &MetaModule::ColorStyles::outline_styles[id];
}
lv_style_t *scheme_line(MetaColorId id) {
	return &MetaModule::ColorStyles::line_styles[id];
}
lv_style_t *scheme_arc(MetaColorId id) {
	return &MetaModule::ColorStyles::arc_styles[id];
}
lv_style_t *scheme_shadow(MetaColorId id) {
	return &MetaModule::ColorStyles::shadow_styles[id];
}
lv_style_t *scheme_img_recolor(MetaColorId id) {
	return &MetaModule::ColorStyles::img_recolor_styles[id];
}

} // extern "C"
