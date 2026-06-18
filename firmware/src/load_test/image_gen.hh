#pragma once
#include "CoreModules/moduleFactory.hh"
#include "console/pr_dbg.hh"
#include "dynload/plugin_manager.hh"
#include "general_io.hh"
#include "gui/dyn_display.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/ui.hh"
#include "load_test/bmp_writer.hh"
#include "load_test/test_manager.hh"
#include "lvgl.h"
#include "patch/module_type_slug.hh"
#include "patch/patch_data.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

namespace MetaModule
{

// Renders every loaded module's faceplate (exactly as the ModuleView module
// drawer renders it at 240px height) and saves each as a 24-bit BMP under
// "module-images/<brand>/<module>.bmp" on the USB drive.
//
// Triggered like the CPU load tests: a file named "run_image_gen" on the USB
// drive whose contents begin with "all" (or, in the future, a brand slug to
// filter by). Requires LV_USE_SNAPSHOT to capture the canvas plus its child
// element objects (knobs/jacks/lights).
struct ModuleImageGen {
	static constexpr uint32_t Height = 240;
	static constexpr Volume OutVol = Volume::USB;

	static bool should_run(FileStorageProxy &file_storage_proxy) {
		if (FS::file_size(file_storage_proxy, {"run_image_gen", Volume::USB}).has_value()) {
			std::string contents;
			FS::read_file(file_storage_proxy, contents, {"run_image_gen", Volume::USB});
			return read_filter(contents).size() > 0;
		}
		return false;
	}

	static void run(FileStorageProxy &file_storage_proxy,
					Ui &ui,
					PluginManager &plugin_manager,
					OpenPatchManager &open_patch_manager) {
		pr_info("Running module image generation\n");

		std::string contents;
		FS::read_file(file_storage_proxy, contents, {"run_image_gen", Volume::USB});
		auto filter = read_filter(contents); // "all" => every brand, else a brand slug

		if (!CpuLoadTest::preload_all_plugins(plugin_manager)) {
			pr_err("Failed preloading plugins for image generation\n");
			hil_message("*failure\n");
			return;
		}

		lv_show(ui_MainMenuNowPlayingPanel);
		lv_show(ui_MainMenuNowPlaying);

		PatchPlayer player;
		PatchPlayLoader playloader{file_storage_proxy, open_patch_manager, player};

		unsigned rendered = 0;
		unsigned skipped = 0;

		for (auto brand : ModuleFactory::getAllBrands()) {
			if (filter != "all" && filter != brand)
				continue;

			for (auto slug : ModuleFactory::getAllModuleSlugs(brand)) {
				BrandModuleSlug full_slug = std::string(brand) + ":" + std::string(slug);

				printf("Rendering %s\n", full_slug.c_str());
				lv_label_set_text_fmt(ui_MainMenuNowPlaying, "Rendering %s", full_slug.c_str());
				ui.update_screen();

				if (render_and_save(file_storage_proxy, player, playloader, full_slug, brand, slug))
					rendered++;
				else
					skipped++;

				hil_message("*ok\n");
			}
		}

		pr_info("Module image generation finished: %u rendered, %u skipped\n", rendered, skipped);
		lv_label_set_text_fmt(ui_MainMenuNowPlaying, "Done: %u images, %u skipped", rendered, skipped);
		hil_message("*success\n");
	}

private:
	// Returns the first whitespace-trimmed line of the trigger file contents.
	static std::string read_filter(std::string_view contents) {
		auto end = contents.find_first_of("\r\n");
		auto line = contents.substr(0, end == std::string_view::npos ? contents.size() : end);
		auto first = line.find_first_not_of(" \t");
		if (first == std::string_view::npos)
			return "";
		auto last = line.find_last_not_of(" \t");
		return std::string(line.substr(first, last - first + 1));
	}

	// Draws one module into an off-screen canvas, snapshots it (canvas + child
	// element objects, including any module-drawn graphic displays), encodes a
	// BMP and writes it. Returns false if the module has no faceplate or
	// rendering/saving failed.
	static bool render_and_save(FileStorageProxy &file_storage_proxy,
								PatchPlayer &player,
								PatchPlayLoader &playloader,
								BrandModuleSlug const &full_slug,
								std::string_view brand,
								std::string_view module_slug) {

		ModuleDrawer drawer{.container = nullptr, .height = Height};

		auto [faceplate, width] = drawer.read_faceplate(full_slug.c_str());
		if (faceplate.empty() || width <= 0) {
			pr_warn("Skipping %s: no faceplate\n", full_slug.c_str());
			return false;
		}

		// Blank patch holding just this module. blank_patch() seeds a HubMedium
		// at index 0; our module lands at the returned index.
		PatchData patch;
		patch.blank_patch(full_slug);
		auto module_id = patch.add_module(full_slug);

		// Off-screen container parented to the active screen so the canvas gets
		// real coordinates (needed by the snapshot). It is never flushed to the
		// display because update_screen() is not called while it exists.
		lv_obj_t *container = lv_obj_create(lv_scr_act());
		if (!container)
			return false;
		lv_obj_remove_style_all(container);
		lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_size(container, width, Height);
		drawer.container = container;

		// Faceplate is drawn into this buffer; element objects are drawn on top
		// as children of the canvas. Width can exceed 240, so size dynamically.
		std::vector<lv_color_t> canvas_buf((size_t)width * Height);
		lv_obj_t *canvas = drawer.draw_faceplate(faceplate, width, canvas_buf);
		if (!canvas) {
			lv_obj_del(container);
			return false;
		}

		// Static elements (knobs/jacks/lights) plus the empty canvases for any
		// dynamic graphic displays. A blank patch means no mappings, so
		// draw_mapped_elements draws no map rings.
		std::vector<DrawnElement> drawn_elements;
		drawer.draw_mapped_elements(patch, module_id, 0, canvas, drawn_elements, false);

		// Clear overflow so the snapshot is exactly the faceplate rectangle
		// (no extra margin around overhanging child draws).
		lv_obj_clear_flag(canvas, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
		lv_obj_update_layout(canvas);

		// Dynamic graphic displays are painted by the live module instance. Load
		// the module into the player so the dynamic-display drawer can fetch it
		// via get_plugin_module(); if it can't be instantiated we still save the
		// static faceplate image. `dyn` owns the display pixel buffers the canvas
		// objects point at, so it must outlive the snapshot.
		DynamicDisplay dyn{playloader};
		auto res = player.load_patch(patch);
		if (res.success) {
			player.update_patch_singlecore();
			dyn.prepare_module(drawn_elements, module_id, canvas);
			dyn.draw();
		} else {
			pr_warn("Could not load %s for dynamic displays: %s\n", full_slug.c_str(), res.error_string.c_str());
		}

		bool ok = snapshot_and_write(file_storage_proxy, canvas, width, brand, module_slug);

		dyn.blur();			   // releases display buffers / calls hide_graphic_display
		lv_obj_del(container); // frees canvas and all child element objects
		if (player.is_loaded)
			player.unload_patch();

		return ok;
	}

	static bool snapshot_and_write(FileStorageProxy &file_storage_proxy,
								   lv_obj_t *canvas,
								   lv_coord_t faceplate_width,
								   std::string_view brand,
								   std::string_view module_slug) {

		const auto cf = LV_IMG_CF_TRUE_COLOR; // RGB565, 2 bytes/pixel
		uint32_t buf_size = lv_snapshot_buf_size_needed(canvas, cf);
		if (buf_size == 0) {
			pr_warn("Snapshot size unavailable for %.*s\n", (int)module_slug.size(), module_slug.data());
			return false;
		}

		std::vector<uint8_t> snap(buf_size);
		lv_img_dsc_t dsc;

		// Temporarily widen the display resolution so a full
		// scanline of the widest module always fits, then restore it.
		// LVGL's software image blend (lv_draw_sw_img.c) sizes its per-line work
		// for an alpha or transformed child to `screen_width / image_width`,
		// and if screen_width < image_width, then the blend loop spins forever.
		lv_disp_t *disp = lv_obj_get_disp(canvas);
		const lv_coord_t saved_hor = disp->driver->hor_res;
		const lv_coord_t saved_ver = disp->driver->ver_res;
		const lv_coord_t wide = std::max<lv_coord_t>({saved_hor, saved_ver, 2048});
		disp->driver->hor_res = wide;
		disp->driver->ver_res = wide;

		auto snap_res = lv_snapshot_take_to_buf(canvas, cf, &dsc, snap.data(), buf_size);

		disp->driver->hor_res = saved_hor;
		disp->driver->ver_res = saved_ver;

		if (snap_res != LV_RES_OK) {
			pr_warn("Snapshot failed for %.*s\n", (int)module_slug.size(), module_slug.data());
			return false;
		}

		const uint16_t *src = reinterpret_cast<const uint16_t *>(snap.data());
		const uint32_t snap_w = dsc.header.w;
		const uint32_t snap_h = dsc.header.h;

		// The snapshot may be larger than the faceplate: lv_snapshot pads the
		// area by the object's extended draw size (e.g. light shadows) on all
		// sides. Crop back to the centered faceplate rectangle so the BMP shows
		// just the module, with no black margin.
		const uint32_t target_w = (faceplate_width > 0) ? (uint32_t)faceplate_width : snap_w;
		const uint32_t target_h = Height;

		std::vector<uint16_t> cropped;
		std::span<const uint16_t> pixels;
		uint32_t out_w, out_h;

		if (snap_w >= target_w && snap_h >= target_h) {
			const uint32_t ext_x = (snap_w - target_w) / 2;
			const uint32_t ext_y = (snap_h - target_h) / 2;
			out_w = target_w;
			out_h = target_h;
			cropped.resize((size_t)out_w * out_h);
			for (uint32_t y = 0; y < out_h; y++) {
				const uint16_t *src_row = src + (size_t)(y + ext_y) * snap_w + ext_x;
				std::copy(src_row, src_row + out_w, cropped.data() + (size_t)y * out_w);
			}
			pixels = cropped;
		} else {
			out_w = snap_w;
			out_h = snap_h;
			pixels = std::span<const uint16_t>{src, (size_t)snap_w * snap_h};
		}

		auto bmp = encode_bmp24_from_rgb565(pixels, out_w, out_h);

		std::string path = "module-images/" + std::string(brand) + "/" + std::string(module_slug) + ".bmp";

		auto wrote = FS::write_file(file_storage_proxy, std::span<const char>{bmp.data(), bmp.size()}, {path, OutVol});
		if (!wrote)
			pr_err("Failed writing %s\n", path.c_str());

		return wrote;
	}
};

} // namespace MetaModule
