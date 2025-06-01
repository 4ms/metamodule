#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "gui/elements/context.hh"
#include "gui/styles.hh"
#include "patch_play/patch_playloader.hh"
#include "pr_dbg.hh"
#include <cmath>

namespace MetaModule
{

struct DynamicDisplayDrawer {

	DynamicDisplayDrawer(PatchPlayLoader &patch_playloader,
						 std::span<const DrawnElement> drawn_elements,
						 unsigned module_id)
		: patch_playloader{patch_playloader}
		, module_id{module_id} {

		for (auto const &drawn_el : drawn_elements) {

			// Filter out other modules
			if (drawn_el.gui_element.module_idx != module_id)
				continue;

			// Copy useful data from the DynamicGraphicDisplays
			if (auto *graphic = std::get_if<DynamicGraphicDisplay>(&drawn_el.element)) {
				add_display(drawn_el.gui_element.idx.light_idx,
							graphic->width_mm,
							graphic->height_mm,
							drawn_el.gui_element.obj);
			}
		}
	}

	DynamicDisplayDrawer(PatchPlayLoader &patch_playloader, unsigned module_id)
		: patch_playloader{patch_playloader}
		, module_id{module_id} {
	}

	void add_display(unsigned light_idx, float width, float height, lv_obj_t *canvas) {
		pr_trace("Add display light_idx %u, w %f h %f, canvas %p\n", light_idx, width, height, canvas);
		displays.push_back({.id = light_idx, .width_mm = width, .height_mm = height, .lv_canvas = canvas});
	}

	// TODO: do we need to proivde the parent object?
	void prepare(lv_obj_t *parent_obj) {
		parent_canvas = parent_obj;

		for (auto &disp : displays) {
			// If size is 0, then don't make a buffer for it
			// This is done intentionally by rack::Module to create non-drawable elements
			// that need to be stepped
			if (disp.width_mm == 0 || disp.height_mm == 0) {
				pr_trace("DynDraw::prepare() Graphic display %u has zero size, will not draw\n", disp.id);
				disp.fullcolor_buffer.clear();
				disp.lv_canvas = nullptr;
				if (auto module = patch_playloader.get_plugin_module(module_id))
					module->show_graphic_display(disp.id, disp.fullcolor_buffer, 0, disp.lv_canvas);

			} else if (disp.lv_canvas == nullptr || !lv_obj_is_valid(disp.lv_canvas)) {
				pr_err("DynDraw::prepare(): id:%d lv object not valid\n", disp.id);

			} else {
				lv_obj_refr_size(disp.lv_canvas);
				auto w = lv_obj_get_width(disp.lv_canvas);
				auto h = lv_obj_get_height(disp.lv_canvas);

				pr_trace("DynDraw: id:%d Create buffer %u*%u lvgl px: %u bytes\n", disp.id, w, h, w * h * 3);

				// Create pixel buffers:
				disp.fullcolor_buffer.resize(w * h, 0);

				disp.lv_buffer.resize(LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(w, h), 0);

				lv_canvas_set_buffer(disp.lv_canvas, disp.lv_buffer.data(), w, h, LV_IMG_CF_TRUE_COLOR_ALPHA);

				// Debug border
				// lv_obj_set_style_border_color(disp.lv_canvas, lv_color_hex(0xFFFF00), LV_PART_MAIN);
				// lv_obj_set_style_border_opa(disp.lv_canvas, LV_OPA_50, LV_PART_MAIN);
				// lv_obj_set_style_border_width(disp.lv_canvas, 1, LV_PART_MAIN);

				if (auto module = patch_playloader.get_plugin_module(module_id))
					module->show_graphic_display(disp.id, disp.fullcolor_buffer, w, disp.lv_canvas);
			}
		}
	}

	void draw() {
		auto module = patch_playloader.get_plugin_module(module_id);

		if (!module || !parent_canvas || !lv_obj_is_valid(parent_canvas) || !lv_obj_is_visible(parent_canvas))
			return;

		for (auto &disp : displays) {
			// Debug::Pin2::high();

			// Draw all displays:
			// The module draws into fullcolor_buffer, and then we compare it against
			// lv_buffer to detect if any pixels changed.
			// If not, then we save a lot of time by not re-drawing the lv_canvas object.
			if (module->draw_graphic_display(disp.id)) {
				if (copy_and_compare_buffer(disp.lv_buffer, disp.fullcolor_buffer))
					lv_obj_invalidate(disp.lv_canvas);
			}

			// Debug::Pin2::low();
		}
	}

	void blur() {

		for (auto &disp : displays) {
			pr_trace("DynDraw::blur() Release graphic display id %u\n", disp.id);

			if (auto module = patch_playloader.get_plugin_module(module_id))
				module->hide_graphic_display(disp.id);

			disp.fullcolor_buffer.clear();
			disp.lv_buffer.clear();
		}
	}

	~DynamicDisplayDrawer() {
		blur();
	}

private:
	bool copy_and_compare_buffer(std::span<char> lv_buffer, std::span<uint32_t> fullcolor_buffer) {
		if ((fullcolor_buffer.size() * 3) > lv_buffer.size()) {
			pr_err("DynDraw buffer size error\n");
			return false;
		}

		unsigned buf_pos = 0;
		bool diff = false;
		for (auto pixel : fullcolor_buffer) {

			auto col = lv_color_make_rgb565(pixel >> 16, pixel >> 8, pixel);
			uint8_t alpha = (pixel >> 24) & 0xFF;

			if (lv_buffer[buf_pos] != (col.full & 0xFF)) {
				diff = true;
				lv_buffer[buf_pos] = col.full & 0xFF;
			}
			if (lv_buffer[buf_pos + 1] != (col.full >> 8)) {
				diff = true;
				lv_buffer[buf_pos + 1] = col.full >> 8;
			}
			if (lv_buffer[buf_pos + 2] != alpha) {
				diff = true;
				lv_buffer[buf_pos + 2] = alpha;
			}

			buf_pos += 3;
		}
		return diff;
	}

	PatchPlayLoader &patch_playloader;
	unsigned module_id = 0;

	struct Display {
		unsigned id{};
		float width_mm;
		float height_mm;
		lv_obj_t *lv_canvas{};
		std::vector<char> lv_buffer;
		std::vector<uint32_t> fullcolor_buffer;
	};
	std::vector<Display> displays;

	lv_obj_t *parent_canvas{};
};

} // namespace MetaModule
