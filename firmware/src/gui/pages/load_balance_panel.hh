#pragma once
#include "CoreModules/moduleFactory.hh"
#include "gui/helpers/lv_helpers.hh"
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
					 ModuleDisplaySettings const &view_settings)
		: group(lv_group_create())
		, patch_playloader{patch_playloader}
		, patches{patches}
		, metaparams{metaparams}
		, view_settings{view_settings} {

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

		refresh();

		lv_show(panel);
		lv_group_activate(group);
		lv_group_focus_obj(close_button);
		lv_group_set_editing(group, false);
		is_showing = true;
	}

	void hide() {
		lv_hide(panel);
		if (parent_group)
			lv_group_activate(parent_group);
		is_showing = false;
	}

	void back_event() {
		hide();
	}

	void update() {
		if (is_showing)
			update_cpu_load();
	}

private:
	void refresh() {
		for (auto core = 0u; core < NumCores; core++) {
			auto row = bar_rows[core];

			// Remove the boxes from the previous refresh
			for (auto *box : boxes[core])
				lv_group_remove_obj(box);
			lv_obj_clean(row);
			boxes[core].clear();
		}

		bool has_balance = patch && patch->has_load_balance(NumCores);

		if (!has_balance) {
			// A patch with only one module doesn't get split between the cores at all
			if (patch && patch->module_slugs.size() <= 2)
				lv_label_set_text(no_balance_label, "This patch is too small to need load balancing.");
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
			}

			// Put a marker at 100% if any bar is over 100%
			if (bar_scale_ppm > OneCorePpm) {
				for (auto core = 0u; core < NumCores; core++)
					add_full_core_marker(core);
			}

			for (auto core = 0u; core < NumCores; core++)
				lv_label_set_text_fmt(core_labels[core], "Core %u: %u%%", core + 1, core_load_percent(core));
		}

		// put the buttons at the end of the group
		for (auto *button : {recalc_button, save_button, undo_button, close_button}) {
			lv_group_remove_obj(button);
			lv_group_add_obj(group, button);
		}

		show_module_info(0);
		update_cpu_load();

		// Nothing to measure unless this patch is the one that's playing
		lv_enable(recalc_button, patch_playloader.is_view_patch_playing());
		lv_enable(undo_button, did_change);
		lv_enable(save_button, can_save());

		clear_focus_states();
	}

	void clear_focus_states() {
		auto unfocus = [](lv_obj_t *obj) {
			lv_obj_clear_state(obj, LV_STATE_FOCUSED | LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
		};

		for (auto *button : {recalc_button, save_button, undo_button, close_button})
			unfocus(button);

		for (auto const &core_boxes : boxes) {
			for (auto *box : core_boxes)
				unfocus(box);
		}
	}

	void update_cpu_load() {
		bool already_on_screen = view_settings.float_loadmeter;
		bool playing = patch_playloader.is_view_patch_playing();

		lv_show(cpu_load_label, !already_on_screen && playing);

		if (!already_on_screen && playing)
			lv_label_set_text_fmt(cpu_load_label, "Total CPU: %d%%", metaparams.audio_load);
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

	unsigned core_load_percent(unsigned core) const {
		return core_load_ppm(core) / 10000;
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
		lv_obj_set_size(marker, 2, lv_pct(100));
		lv_obj_set_x(marker, lv_pct(full_core_pct()));
		lv_obj_set_style_radius(marker, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(marker, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_all(marker, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_color(marker, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(marker, LV_OPA_COVER, LV_PART_MAIN);
	}

	void add_box(unsigned core, unsigned module_id, uint32_t ppm) {
		auto box = lv_obj_create(bar_rows[core]);

		auto width_pct = (lv_coord_t)std::min<uint64_t>((uint64_t)ppm * 100 / bar_scale_ppm, 100);
		lv_obj_set_width(box, lv_pct(std::max<lv_coord_t>(width_pct, 1)));
		lv_obj_set_height(box, lv_pct(100));
		lv_obj_set_style_radius(box, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(box, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_all(box, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(box, LV_OPA_COVER, LV_PART_MAIN);
		lv_obj_set_style_bg_color(box, Gui::knob_palette[module_id % Gui::knob_palette.size()], LV_PART_MAIN);
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

		lv_group_add_obj(group, box);
		boxes[core].push_back(box);
	}

	// module_id of 0 (the hub) means "nothing selected"
	void show_module_info(unsigned module_id) {
		if (module_id == 0 || !patch || module_id >= patch->module_slugs.size()) {
			lv_label_set_text(module_name_label, "");
			lv_label_set_text(module_load_label, "");
			return;
		}

		lv_label_set_text(module_name_label, module_display_name(module_id).c_str());

		if (module_id < patch->module_loads.size()) {
			auto ppm = load_ppm(module_id);
			lv_label_set_text_fmt(module_load_label, "%u.%u%%", unsigned(ppm / 10000), unsigned((ppm / 1000) % 10));
		} else {
			lv_label_set_text(module_load_label, "");
		}
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
	}

	// Moving off a module (onto another module or onto a button) clears the name:
	// if the next thing focused is a module, its own FOCUSED event fills it back in.
	static void box_defocus_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		static_cast<LoadBalancePanel *>(event->user_data)->show_module_info(0);
	}

	static void recalc_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<LoadBalancePanel *>(event->user_data);

		if (!page->patch_playloader.is_view_patch_playing())
			return;

		page->patch_playloader.recalculate_load_balance();
		page->patches.mark_view_patch_modified();
		page->did_change = true;

		page->refresh();
		lv_group_focus_obj(page->recalc_button);
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

		recalc_button = create_button(button_row, "Re-calculate");
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

	std::vector<uint16_t> undo_cores;
	std::vector<uint32_t> undo_loads;

	lv_obj_t *panel = nullptr;
	lv_obj_t *no_balance_label = nullptr;
	lv_obj_t *cpu_load_label = nullptr;
	std::array<lv_obj_t *, NumCores> bar_conts{};
	std::array<lv_obj_t *, NumCores> bar_rows{};
	std::array<lv_obj_t *, NumCores> core_labels{};
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
};

} // namespace MetaModule
