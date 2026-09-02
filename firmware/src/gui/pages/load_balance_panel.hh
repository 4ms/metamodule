#pragma once
#include "CoreModules/moduleFactory.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "params/metaparams.hh"
#include "patch/patch_data.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/view_settings.hh"
#include <algorithm>
#include <array>
#include <string>
#include <vector>

namespace MetaModule
{

// Shows how the patch's modules are split between the two CPU cores, and lets the
// user try a different split.
struct LoadBalancePanel {

	LoadBalancePanel(PatchPlayLoader &patch_playloader,
					 OpenPatchManager &patches,
					 MetaParams const &metaparams,
					 ModuleDisplaySettings const &view_settings,
					 PageList &page_list,
					 PageArguments &page_args)
		: group(lv_group_create())
		, patch_playloader{patch_playloader}
		, patches{patches}
		, metaparams{metaparams}
		, view_settings{view_settings}
		, page_list{page_list}
		, page_args{page_args} {

		create_objects();

		lv_hide(panel);

		lv_obj_add_event_cb(recalc_button, recalc_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(save_button, save_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(undo_button, undo_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(close_button, close_cb, LV_EVENT_CLICKED, this);
	}

	void set_patch(PatchData *cur_patch) {
		patch = cur_patch;
	}

	bool is_visible() const {
		return is_showing;
	}

	void show(lv_group_t *cur_group) {
		if (!patch)
			return;

		parent_group = cur_group;

		undo_cores = patch->module_cores;
		undo_loads = patch->module_loads;
		did_change = false;

		patch_playloader.set_live_load_detail(true);
		last_box_update_tick = lv_tick_get();

		refresh();

		lv_show(panel);
		lv_group_activate(group);
		lv_group_focus_obj(close_button);
		lv_group_set_editing(group, false);
		is_showing = true;
	}

	void hide() {
		if (trials_running) {
			patch_playloader.abort_rebalance_trials();
			trials_running = false;
		}

		patch_playloader.set_live_load_detail(false);

		lv_hide(panel);
		if (parent_group)
			lv_group_activate(parent_group);
		is_showing = false;
	}

	void back_event() {
		hide();
	}

	void update() {
		if (!is_showing)
			return;

		if (trials_running) {
			patch_playloader.update_rebalance_trials(lv_tick_get());

			if (patch_playloader.rebalance_trials_active()) {
				lv_label_set_text_fmt(module_name_label,
									  "Trying arrangement %u of %u...",
									  patch_playloader.rebalance_trials_current(),
									  patch_playloader.rebalance_trials_total());
			} else {
				trials_running = false;
				refresh();
				lv_group_focus_obj(recalc_button);
			}
		}

		update_cpu_load();

		// Re-scale the module boxes to the live loads, slowly so they don't jitter
		auto now = lv_tick_get();
		if (!trials_running && now - last_box_update_tick >= BoxUpdatePeriodMs) {
			last_box_update_tick = now;
			update_box_widths();
		}
	}

private:
	void refresh() {
		for (auto core = 0u; core < NumCores; core++) {
			auto row = bar_rows[core];

			// Remove the boxes and markers from the previous refresh
			for (auto *box : boxes[core])
				lv_group_remove_obj(box);
			if (cable_boxes[core])
				lv_group_remove_obj(cable_boxes[core]);
			lv_obj_clean(row);
			boxes[core].clear();
			full_core_markers[core] = nullptr;
			cable_boxes[core] = nullptr;
		}

		bool has_balance = patch && patch->has_load_balance(NumCores);

		if (!has_balance) {
			if (patch && patch->module_slugs.size() <= 1)
				lv_label_set_text(no_balance_label, "This patch has no modules.");
			else
				lv_label_set_text(no_balance_label, "Play this patch to calculate its load balance.");
		}
		lv_show(no_balance_label, !has_balance);
		for (auto core = 0u; core < NumCores; core++) {
			lv_show(bar_conts[core], has_balance);
		}

		if (has_balance) {
			// Scale bars to fit screen if over 100%
			bar_scale_ppm = OneCorePpm;
			for (auto core = 0u; core < NumCores; core++)
				bar_scale_ppm = std::max(bar_scale_ppm, core_load_ppm(core));

			for (auto core = 0u; core < NumCores; core++) {
				for (auto module_id = 1u; module_id < patch->module_cores.size(); module_id++) {
					if (patch->module_cores[module_id] == core)
						add_box(core, module_id, load_ppm(module_id));
				}

				// Each core's cable-processing time, sized by the live measurements
				add_cable_box(core);
			}

			// Marker at the 100% point, shown when a bar is scaled to over 100%
			for (auto core = 0u; core < NumCores; core++) {
				add_full_core_marker(core);
				lv_show(full_core_markers[core], bar_scale_ppm > OneCorePpm);
			}

			for (auto core = 0u; core < NumCores; core++)
				lv_label_set_text_fmt(core_labels[core], "Core %u: %u%%", core + 1, core_load_ppm(core) / 10000);
		}

		// put the buttons at the end of the group
		for (auto *button : {recalc_button, save_button, undo_button, close_button}) {
			lv_group_remove_obj(button);
			lv_group_add_obj(group, button);
		}

		show_module_info(0);
		update_cpu_load();

		lv_enable(recalc_button, patch_playloader.is_view_patch_playing() && patch && patch->module_slugs.size() > 2);
		lv_enable(undo_button, did_change);
		lv_enable(save_button, can_save());

		clear_focus_states();
	}

	void clear_focus_states() {
		for (auto *button : {recalc_button, save_button, undo_button, close_button})
			lv_obj_clear_state(button, LV_STATE_FOCUSED | LV_STATE_FOCUS_KEY | LV_STATE_EDITED);

		for (auto const &core_boxes : boxes) {
			for (auto *box : core_boxes)
				lv_obj_clear_state(box, LV_STATE_FOCUSED | LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
		}

		for (auto *box : cable_boxes) {
			if (box)
				lv_obj_clear_state(box, LV_STATE_FOCUSED | LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
		}
	}

	void update_cpu_load() {
		bool already_on_screen = view_settings.float_loadmeter;
		bool playing = patch_playloader.is_view_patch_playing();

		lv_show(cpu_load_label, !already_on_screen && playing);

		if (!already_on_screen && playing)
			lv_label_set_text_fmt(cpu_load_label, "Total CPU: %d%%", metaparams.audio_load);

		auto live = patch_playloader.get_live_load();
		bool show_live = playing && live.valid;

		lv_show(live_load_label, show_live);

		if (show_live) {
			// Cable loads show as grey boxes in the bars (highlight one to see its %).
			// Sync shows core 1's waits at the first + second join
			lv_label_set_text_fmt(live_load_label,
								  "Mappings: %u%% MIDI: %u%%\nSync: %u%%+%u%%  Overhead: %u%%",
								  (unsigned)std::round(live.mappings / 10.f),
								  (unsigned)std::round(live.midi / 10.f),
								  (unsigned)std::round(live.sync / 10.f),
								  (unsigned)std::round(live.sync2 / 10.f),
								  (unsigned)std::round(live.overhead / 10.f));

			if (patch && patch->has_load_balance(NumCores)) {
				for (auto core = 0u; core < NumCores && core < live.core_modules.size(); core++) {
					lv_label_set_text_fmt(core_labels[core],
										  "Core %u: %u%%",
										  core + 1,
										  (unsigned)std::round(live.core_modules[core] / 10.f));
				}
			}

			update_module_load_label(live);
		}
	}

	// Estimated load (measured when the balance was calculated) plus the live
	// measurement, for the currently focused module or cable box
	void update_module_load_label(LiveLoadMeter::Loads const &live) {
		if (info_cables_core >= 0) {
			bool playing = patch_playloader.is_view_patch_playing();
			if (playing && live.valid) {
				auto tenths = info_cables_core == 0 ? live.cables : live.core2_cables;
				lv_label_set_text_fmt(module_load_label, "%u.%u%%", tenths / 10u, tenths % 10u);
			} else {
				lv_label_set_text(module_load_label, "");
			}
			return;
		}

		if (info_module_id == 0 || !patch || info_module_id >= patch->module_loads.size()) {
			lv_label_set_text(module_load_label, "");
			return;
		}

		bool playing = patch_playloader.is_view_patch_playing();
		auto load = 0u;
		if (playing && live.valid && info_module_id < live.modules.size()) {
			load = (unsigned)std::round(live.modules[info_module_id] / 10.f);
		} else {
			load = (unsigned)std::round(load_ppm(info_module_id) / 10000.f);
		}
		lv_label_set_text_fmt(module_load_label, "%u%%", load);
	}

	// Scale ppm to current sample rate
	uint32_t load_ppm(unsigned module_id) const {
		if (module_id >= patch->module_loads.size())
			return 0;

		auto ppm = patch->module_loads[module_id];

		auto cur_sr = patch_playloader.get_audio_settings().sample_rate;
		if (cur_sr > 0 && cur_sr != LoadBalanceRefSamplerate)
			ppm = (uint32_t)((uint64_t)ppm * cur_sr / LoadBalanceRefSamplerate);

		return ppm;
	}

	uint32_t core_load_ppm(unsigned core) const {
		uint32_t sum = 0;
		for (auto module_id = 1u; module_id < patch->module_cores.size(); module_id++) {
			if (patch->module_cores[module_id] == core)
				sum += load_ppm(module_id);
		}
		return sum;
	}

	// Where 100% of a core falls, as a percentage of the bar's width
	lv_coord_t full_core_pct() const {
		return (lv_coord_t)((uint64_t)OneCorePpm * 100 / bar_scale_ppm);
	}

	// A line across the bar at the 100% point, drawn on top of the modules
	void add_full_core_marker(unsigned core) {
		auto marker = lv_obj_create(bar_rows[core]);
		lv_obj_add_flag(marker, LV_OBJ_FLAG_FLOATING);
		lv_obj_clear_flag(marker, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_size(marker, 3, lv_pct(100));
		lv_obj_set_x(marker, lv_pct(full_core_pct()));
		lv_obj_set_style_radius(marker, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(marker, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_all(marker, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_color(marker, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(marker, LV_OPA_COVER, LV_PART_MAIN);

		full_core_markers[core] = marker;
	}

	void set_box_width(lv_obj_t *box, uint32_t ppm) {
		auto width_pct = (lv_coord_t)std::min<uint64_t>((uint64_t)ppm * 100 / bar_scale_ppm, 100);
		lv_obj_set_width(box, lv_pct(std::max<lv_coord_t>(width_pct, 1)));
	}

	// A box at the end of the bar showing the core's cable-processing time.
	void add_cable_box(unsigned core) {
		auto box = lv_obj_create(bar_rows[core]);

		lv_obj_set_width(box, lv_pct(1));
		lv_obj_set_height(box, lv_pct(100));
		lv_obj_set_style_radius(box, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(box, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_all(box, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(box, LV_OPA_COVER, LV_PART_MAIN);
		lv_obj_set_style_bg_color(box, lv_color_hex(0x888888), LV_PART_MAIN);
		lv_obj_clear_flag(box, LV_OBJ_FLAG_SCROLLABLE);

		for (auto state : {LV_STATE_FOCUSED, LV_STATE_FOCUS_KEY}) {
			lv_obj_set_style_outline_color(box, Gui::orange_highlight, LV_PART_MAIN | state);
			lv_obj_set_style_outline_opa(box, LV_OPA_COVER, LV_PART_MAIN | state);
			lv_obj_set_style_outline_width(box, 2, LV_PART_MAIN | state);
			lv_obj_set_style_outline_pad(box, 0, LV_PART_MAIN | state);
		}

		lv_obj_set_user_data(box, (void *)(uintptr_t)core);
		lv_obj_add_event_cb(box, cable_box_focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(box, box_defocus_cb, LV_EVENT_DEFOCUSED, this);

		lv_group_add_obj(group, box);
		lv_hide(box);

		cable_boxes[core] = box;
	}

	// Re-scale the module boxes and the 100% markers to the live measurements
	void update_box_widths() {
		if (!patch || !patch->has_load_balance(NumCores) || !patch_playloader.is_view_patch_playing())
			return;

		auto live = patch_playloader.get_live_load();
		if (!live.valid)
			return;

		// Live loads are tenths of a percent; boxes are scaled in ppm
		auto live_ppm = [&live](unsigned module_id) -> uint32_t {
			return module_id < live.modules.size() ? live.modules[module_id] * 1000u : 0;
		};

		std::array<uint32_t, NumCores> cable_ppm{};
		cable_ppm[0] = live.cables * 1000u;
		if constexpr (NumCores > 1)
			cable_ppm[1] = live.core2_cables * 1000u;

		// Scale bars to fit screen if over 100%
		bar_scale_ppm = OneCorePpm;
		for (auto core = 0u; core < NumCores; core++) {
			uint32_t sum = cable_ppm[core];
			for (auto module_id = 1u; module_id < patch->module_cores.size(); module_id++) {
				if (patch->module_cores[module_id] == core)
					sum += live_ppm(module_id);
			}
			bar_scale_ppm = std::max(bar_scale_ppm, sum);
		}

		for (auto core = 0u; core < NumCores; core++) {
			for (auto *box : boxes[core])
				set_box_width(box, live_ppm((unsigned)(uintptr_t)lv_obj_get_user_data(box)));

			if (auto *cable_box = cable_boxes[core]) {
				set_box_width(cable_box, cable_ppm[core]);
				lv_show(cable_box, true);
			}

			if (auto *marker = full_core_markers[core]) {
				lv_show(marker, bar_scale_ppm > OneCorePpm);
				lv_obj_set_x(marker, lv_pct(full_core_pct()));
			}
		}
	}

	void add_box(unsigned core, unsigned module_id, uint32_t ppm) {
		auto box = lv_obj_create(bar_rows[core]);

		set_box_width(box, ppm);
		lv_obj_set_height(box, lv_pct(100));
		lv_obj_set_style_radius(box, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(box, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_all(box, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(box, LV_OPA_COVER, LV_PART_MAIN);
		lv_obj_set_style_bg_color(box, Gui::knob_palette[module_id % 6], LV_PART_MAIN);
		lv_obj_clear_flag(box, LV_OBJ_FLAG_SCROLLABLE);

		for (auto state : {LV_STATE_FOCUSED, LV_STATE_FOCUS_KEY}) {
			lv_obj_set_style_outline_color(box, Gui::orange_highlight, LV_PART_MAIN | state);
			lv_obj_set_style_outline_opa(box, LV_OPA_COVER, LV_PART_MAIN | state);
			lv_obj_set_style_outline_width(box, 2, LV_PART_MAIN | state);
			lv_obj_set_style_outline_pad(box, 0, LV_PART_MAIN | state);
		}

		lv_obj_set_user_data(box, (void *)(uintptr_t)module_id);
		lv_obj_add_event_cb(box, box_focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(box, box_defocus_cb, LV_EVENT_DEFOCUSED, this);
		lv_obj_add_event_cb(box, box_click_cb, LV_EVENT_CLICKED, this);

		lv_group_add_obj(group, box);
		boxes[core].push_back(box);
	}

	// module_id of 0 (the hub) means "nothing selected"
	void show_module_info(unsigned module_id) {
		info_cables_core = -1;

		if (module_id == 0 || !patch || module_id >= patch->module_slugs.size()) {
			info_module_id = 0;
			lv_label_set_text(module_name_label, "");
			lv_label_set_text(module_load_label, "");
			return;
		}

		info_module_id = module_id;
		lv_label_set_text(module_name_label, module_display_name(module_id).c_str());
		update_module_load_label(patch_playloader.get_live_load());
	}

	void show_cables_info(unsigned core) {
		info_module_id = 0;
		info_cables_core = (int)core;

		lv_label_set_text_fmt(module_name_label, "Cables (Core %u)", core + 1);
		update_module_load_label(patch_playloader.get_live_load());
	}

	// e.g. "Ensemble Oscillator #1/4", or the user's alias if the module has one
	std::string module_display_name(unsigned module_id) const {
		auto alias = patch->get_module_alias((uint16_t)module_id);
		if (!alias.empty())
			return std::string{alias};

		auto slug = patch->module_slugs[module_id];

		std::string name{ModuleFactory::getModuleDisplayName(slug)};
		if (name.empty())
			name = std::string{std::string_view{slug}};

		// Count how many modules share this slug, and which one this is
		unsigned total = 0;
		unsigned index = 0;
		for (auto id = 1u; id < patch->module_slugs.size(); id++) {
			if (patch->module_slugs[id] == slug) {
				total++;
				if (id == module_id)
					index = total;
			}
		}

		if (total > 1)
			name += " #" + std::to_string(index) + "/" + std::to_string(total);

		return name;
	}

	bool can_save() const {
		auto vol = patches.get_view_patch_vol();
		return vol != Volume::RamDisk && vol != Volume::MaxVolumes;
	}

	static void box_focus_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<LoadBalancePanel *>(event->user_data);
		page->show_module_info((unsigned)(uintptr_t)lv_obj_get_user_data(event->target));
		lv_obj_scroll_to_y(page->panel, 0, LV_ANIM_ON);
	}

	// Moving off a module (onto another module or onto a button) clears the name:
	// if the next thing focused is a module, its own FOCUSED event fills it back in.
	static void box_defocus_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		static_cast<LoadBalancePanel *>(event->user_data)->show_module_info(0);
	}

	static void cable_box_focus_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<LoadBalancePanel *>(event->user_data);
		page->show_cables_info((unsigned)(uintptr_t)lv_obj_get_user_data(event->target));
	}

	// Clicking a module's box jumps to it in ModuleView. Changing pages closes
	// this panel (PatchViewPage::blur() -> desc_panel.hide() -> this->hide())
	static void box_click_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<LoadBalancePanel *>(event->user_data);

		auto module_id = (unsigned)(uintptr_t)lv_obj_get_user_data(event->target);
		if (module_id == 0 || !page->patch || module_id >= page->patch->module_slugs.size())
			return;

		page->page_args.module_id = module_id;
		page->page_args.element_indices = {};
		page->page_args.detail_mode = false;
		page->page_list.update_state(PageId::PatchView, page->page_args);
		page->page_list.request_new_page(PageId::ModuleView, page->page_args);
	}

	static void recalc_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<LoadBalancePanel *>(event->user_data);

		if (!page->patch_playloader.is_view_patch_playing())
			return;

		// Try several arrangements live and keep the best
		page->patch_playloader.start_rebalance_trials(lv_tick_get());
		page->trials_running = true;
		page->patches.mark_view_patch_modified();
		page->did_change = true;

		lv_enable(page->recalc_button, false);
	}

	static void undo_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<LoadBalancePanel *>(event->user_data);

		page->patch->module_cores = page->undo_cores;
		page->patch->module_loads = page->undo_loads;

		if (page->patch_playloader.is_view_patch_playing())
			page->patch_playloader.apply_load_balance(page->undo_cores, page->undo_loads);

		page->did_change = false;

		page->refresh();
		lv_group_focus_obj(page->close_button);
	}

	static void save_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<LoadBalancePanel *>(event->user_data);

		if (!page->can_save())
			return;

		page->patch_playloader.request_save_patch();
		page->hide();
	}

	static void close_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		static_cast<LoadBalancePanel *>(event->user_data)->hide();
	}

	void create_objects() {
		panel = lv_obj_create(lv_layer_top());
		lv_obj_set_size(panel, lv_pct(100), lv_pct(100));
		lv_obj_set_pos(panel, 0, 0);
		lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
		lv_obj_set_style_pad_all(panel, 8, LV_PART_MAIN);
		lv_obj_set_style_pad_row(panel, 4, LV_PART_MAIN);
		lv_obj_set_style_radius(panel, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_color(panel, lv_color_hex(0x202328), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(panel, 255, LV_PART_MAIN);
		lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN);

		auto title_row = lv_obj_create(panel);
		lv_obj_set_width(title_row, lv_pct(100));
		lv_obj_set_height(title_row, LV_SIZE_CONTENT);
		lv_obj_set_flex_flow(title_row, LV_FLEX_FLOW_ROW);
		lv_obj_set_flex_align(title_row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
		lv_obj_set_style_pad_all(title_row, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(title_row, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(title_row, 0, LV_PART_MAIN);
		lv_obj_clear_flag(title_row, LV_OBJ_FLAG_SCROLLABLE);

		auto title = lv_label_create(title_row);
		lv_label_set_text(title, "CPU Load Balancing");
		lv_obj_set_style_text_font(title, &ui_font_MuseoSansRounded70014, LV_PART_MAIN);
		lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
		lv_obj_set_flex_grow(title, 1);

		cpu_load_label = lv_label_create(title_row);
		lv_label_set_text(cpu_load_label, "");
		lv_obj_set_style_text_font(cpu_load_label, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);
		lv_obj_set_style_text_color(cpu_load_label, Gui::orange_highlight, LV_PART_MAIN);

		no_balance_label = lv_label_create(panel);
		lv_label_set_long_mode(no_balance_label, LV_LABEL_LONG_WRAP);
		lv_obj_set_width(no_balance_label, lv_pct(100));
		lv_obj_set_style_text_font(no_balance_label, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);
		lv_obj_set_style_text_color(no_balance_label, Gui::grey_highlight, LV_PART_MAIN);

		for (auto core = 0u; core < NumCores; core++) {
			auto cont = lv_obj_create(panel);
			lv_obj_set_width(cont, lv_pct(100));
			lv_obj_set_height(cont, LV_SIZE_CONTENT);
			lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
			lv_obj_set_style_pad_all(cont, 0, LV_PART_MAIN);
			lv_obj_set_style_pad_row(cont, 2, LV_PART_MAIN);
			lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN);
			lv_obj_set_style_bg_opa(cont, 0, LV_PART_MAIN);
			lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
			bar_conts[core] = cont;

			core_labels[core] = lv_label_create(cont);
			lv_obj_set_style_text_font(core_labels[core], &ui_font_MuseoSansRounded50014, LV_PART_MAIN);
			lv_obj_set_style_text_color(core_labels[core], lv_color_hex(0xFFFFFF), LV_PART_MAIN);
			lv_label_set_text(core_labels[core], "");

			auto row = lv_obj_create(cont);
			lv_obj_set_width(row, lv_pct(100));
			lv_obj_set_height(row, 24);
			lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
			lv_obj_set_style_pad_all(row, 2, LV_PART_MAIN);
			lv_obj_set_style_pad_column(row, 1, LV_PART_MAIN);
			lv_obj_set_style_radius(row, 0, LV_PART_MAIN);
			lv_obj_set_style_border_width(row, 1, LV_PART_MAIN);
			lv_obj_set_style_border_color(row, lv_color_hex(0x000000), LV_PART_MAIN);
			lv_obj_set_style_bg_color(row, lv_color_hex(0x111111), LV_PART_MAIN);
			lv_obj_set_style_bg_opa(row, 255, LV_PART_MAIN);
			lv_obj_clear_flag(row, LV_OBJ_FLAG_SCROLLABLE);
			bar_rows[core] = row;
		}

		live_load_label = lv_label_create(panel);
		lv_label_set_long_mode(live_load_label, LV_LABEL_LONG_WRAP);
		lv_obj_set_width(live_load_label, lv_pct(100));
		lv_obj_set_style_text_font(live_load_label, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);
		lv_obj_set_style_text_color(live_load_label, Gui::grey_highlight, LV_PART_MAIN);
		lv_label_set_text(live_load_label, "");
		lv_hide(live_load_label);

		module_name_label = lv_label_create(panel);
		lv_label_set_long_mode(module_name_label, LV_LABEL_LONG_DOT);
		lv_obj_set_width(module_name_label, lv_pct(100));
		lv_obj_set_style_text_font(module_name_label, &ui_font_MuseoSansRounded70014, LV_PART_MAIN);
		lv_obj_set_style_text_color(module_name_label, Gui::orange_highlight, LV_PART_MAIN);
		lv_label_set_text(module_name_label, "");

		module_load_label = lv_label_create(panel);
		lv_obj_set_style_text_font(module_load_label, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);
		lv_obj_set_style_text_color(module_load_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
		lv_label_set_text(module_load_label, "");

		auto button_row = lv_obj_create(panel);
		lv_obj_set_width(button_row, lv_pct(100));
		lv_obj_set_height(button_row, LV_SIZE_CONTENT);
		lv_obj_set_flex_flow(button_row, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_flex_align(button_row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
		lv_obj_set_style_pad_all(button_row, 4, LV_PART_MAIN);
		lv_obj_set_style_pad_column(button_row, 8, LV_PART_MAIN);
		lv_obj_set_style_pad_row(button_row, 8, LV_PART_MAIN);
		lv_obj_set_style_border_width(button_row, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(button_row, 0, LV_PART_MAIN);
		lv_obj_clear_flag(button_row, LV_OBJ_FLAG_SCROLLABLE);

		recalc_button = create_button(button_row, "Re-balance");
		save_button = create_button(button_row, "Save");
		undo_button = create_button(button_row, "Undo");
		close_button = create_button(button_row, "Close");

		lv_group_set_wrap(group, false);
		lv_group_add_obj(group, recalc_button);
		lv_group_add_obj(group, save_button);
		lv_group_add_obj(group, undo_button);
		lv_group_add_obj(group, close_button);
	}

	static constexpr unsigned NumCores = MulticorePlayer::NumCores;

	// 100% of one core, in the parts-per-million the loads are stored in
	static constexpr uint32_t OneCorePpm = 1'000'000;

	// How much CPU time a full-width bar represents. Normally one core, but more than
	// that when a core is overloaded and its modules wouldn't otherwise fit.
	uint32_t bar_scale_ppm = OneCorePpm;

	lv_group_t *group;
	lv_group_t *parent_group = nullptr;

	PatchData *patch = nullptr;

	bool is_showing = false;
	bool did_change = false;

	// Module whose name/load are shown in the info labels (0 = none)
	unsigned info_module_id = 0;

	// Core whose cable box is focused (-1 = none)
	int info_cables_core = -1;

	// The boxes re-scale to live loads at a slow rate, so they don't jitter
	static constexpr uint32_t BoxUpdatePeriodMs = 200;
	uint32_t last_box_update_tick = 0;

	// Rebalance trials in progress (started by the Re-calculate button)
	bool trials_running = false;

	std::vector<uint16_t> undo_cores;
	std::vector<uint32_t> undo_loads;

	lv_obj_t *panel = nullptr;
	lv_obj_t *no_balance_label = nullptr;
	lv_obj_t *cpu_load_label = nullptr;
	lv_obj_t *live_load_label = nullptr;
	std::array<lv_obj_t *, NumCores> bar_conts{};
	std::array<lv_obj_t *, NumCores> bar_rows{};
	std::array<lv_obj_t *, NumCores> core_labels{};
	std::array<lv_obj_t *, NumCores> full_core_markers{};
	std::array<lv_obj_t *, NumCores> cable_boxes{};
	std::array<std::vector<lv_obj_t *>, NumCores> boxes{};
	lv_obj_t *module_name_label = nullptr;
	lv_obj_t *module_load_label = nullptr;
	lv_obj_t *recalc_button = nullptr;
	lv_obj_t *save_button = nullptr;
	lv_obj_t *undo_button = nullptr;
	lv_obj_t *close_button = nullptr;

	PatchPlayLoader &patch_playloader;
	OpenPatchManager &patches;
	MetaParams const &metaparams;
	ModuleDisplaySettings const &view_settings;
	PageList &page_list;
	PageArguments &page_args;
};

} // namespace MetaModule
