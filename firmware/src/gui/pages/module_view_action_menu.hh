#pragma once
#include "fat_file_io.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/module_view_automap.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/roller_popup.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "patch_play/randomize_param.hh"
#include "patch_play/reset_param.hh"
#include <algorithm>
#include <vector>

namespace MetaModule
{

class ModuleViewActionMenu {
	struct Preset {
		std::string fname{};
		std::string path{};
	};

public:
	ModuleViewActionMenu(PatchModQueue &patch_mod_queue,
						 OpenPatchManager &patches,
						 PageList &page_list,
						 PatchPlayLoader &patch_playloader,
						 NotificationQueue &notify_queue,
						 FatFileIO &ramdisk)
		: ramdisk{ramdisk}
		, patches{patches}
		, page_list{page_list}
		, patch_playloader{patch_playloader}
		, patch_mod_queue{patch_mod_queue}
		, auto_map{patch_mod_queue, patches, notify_queue}
		, randomizer{patch_mod_queue}
		, reset_params_{patch_mod_queue}
		, group(lv_group_create())
		, moduleViewActionPresetBut{create_lv_list_button(ui_ModuleViewActionMenu, "Presets")} {
		lv_obj_set_parent(ui_ModuleViewActionMenu, lv_layer_top());
		lv_show(ui_ModuleViewActionMenu);
		lv_show(moduleViewActionPresetBut);
		lv_obj_set_x(ui_ModuleViewActionMenu, 160);
		lv_obj_set_height(ui_ModuleViewActionMenu, 240);

		lv_obj_move_foreground(ui_ModuleViewActionDeleteBut);

		lv_obj_add_event_cb(ui_ModuleViewActionBut, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionAutopatchBut, autopatch_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionAutopatchBut, scroll_top_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionAutoKnobSet, autopatch_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionDeleteBut, delete_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionRandomBut, random_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(moduleViewActionPresetBut, preset_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionResetBut, reset_but_cb, LV_EVENT_CLICKED, this);

		lv_group_add_obj(group, ui_ModuleViewActionAutopatchBut);
		lv_group_add_obj(group, ui_ModuleViewActionAutoKnobSet);
		lv_group_add_obj(group, ui_ModuleViewActionRandomBut);
		lv_group_add_obj(group, ui_ModuleViewActionResetBut);
		lv_group_add_obj(group, moduleViewActionPresetBut);
		lv_group_add_obj(group, ui_ModuleViewActionDeleteBut);
		lv_group_set_wrap(group, false);
	}

	void prepare_focus(lv_group_t *parent_group, unsigned module_idx) {
		this->module_idx = module_idx;
		base_group = parent_group;
		confirm_popup.init(lv_layer_top(), base_group);

		const auto module_slug = std::string{patches.get_view_patch()->module_slugs[module_idx]};
		const auto module_name = module_slug.substr(module_slug.find_first_of(':') + 1);
		const auto slug_name = module_slug.substr(0, module_slug.find_first_of(':'));
		cur_preset_idx = 0;
		preset_path = slug_name + "/presets/" + module_name;
		presets.clear();
		preset_map.clear();

		auto populate_vector = [this](std::string fullpath, unsigned time_stamp, unsigned size, DirEntryKind type) {
			if (fullpath.length() && type == DirEntryKind::File) {
				if (auto ext_pos = fullpath.find(".vcvm"); ext_pos != std::string::npos) {
					auto slash_pos = fullpath.find_last_of('/');
					slash_pos = (slash_pos == std::string::npos) ? 0 : slash_pos + 1;
					if (fullpath[slash_pos] != '.') {
						preset_map.push_back({fullpath.substr(slash_pos, ext_pos - slash_pos), fullpath});
					}
				}
			}
		};

		if (ramdisk.foreach_dir_entry_recursive(preset_path.c_str(), populate_vector, 2)) {
			std::ranges::sort(preset_map, std::less{}, &Preset::fname);

			for (auto &p : preset_map) {
				if (p.fname.find_first_of('_') == 2) {
					// some vcv presets have an ugly 'xx_' prefix.. let's remove it
					if (isdigit(p.fname[0]) && isdigit(p.fname[1]))
						p.fname = p.fname.substr(3);
				}
				presets += p.fname + '\n';
			}
			if (presets.size()) {
				presets.pop_back(); //remove trailing '/n'
			}
			lv_enable(moduleViewActionPresetBut);
		} else {
			lv_disable(moduleViewActionPresetBut);
		}
		preset_popup.init(lv_layer_sys(), group);
	}

	void back() {
		if (preset_popup.is_visible()) {
			preset_popup.hide();
		} else if (confirm_popup.is_visible()) {
			confirm_popup.hide();
		} else if (auto_map.is_visible()) {
			auto_map.hide();
		} else if (visible) {
			hide();
		}
	}

	void hide() {
		preset_popup.hide();
		confirm_popup.hide();
		hide_menu();
	}

	void hide_menu() {
		if (visible) {
			DropOutToRight_Animation(ui_ModuleViewActionMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && base_group)
				lv_indev_set_group(indev, base_group);
			visible = false;
		}
	}

	void show() {
		lv_group_focus_obj(ui_ModuleViewActionAutopatchBut);

		if (!visible) {
			lv_show(ui_ModuleViewActionMenu);
			DropInFromLeft_Animation(ui_ModuleViewActionMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && group)
				lv_indev_set_group(indev, group);
			visible = true;
		}
	}

	bool is_visible() {
		return visible;
	}

	void update() {
		process_delete_module();
		auto_map.update();
	}

private:
	void process_delete_module() {
		if (delete_state == DeleteState::TryRequest) {
			patches.get_view_patch()->remove_module(module_idx);

			if (patches.get_view_patch() == patches.get_playing_patch()) {
				patch_playloader.remove_module(module_idx);
			}

			page_list.remove_history_matching_args(PageArguments{.module_id = module_idx});
			page_list.request_new_page_no_history(PageId::PatchView,
												  PageArguments{.patch_loc_hash = patches.get_view_patch_loc_hash()});

			patches.mark_view_patch_modified();
			delete_state = DeleteState::Idle;
		}
	}

	void auto_map_all() {
		hide();
		auto_map.prepare_focus(module_idx, group);
		auto_map.map_all();
		// auto_map.show();
	}

	void auto_map_single_knobset() {
		hide();
		auto_map.prepare_focus(module_idx, group);
		auto_map.map_knobs_single_knobset();
	}

	void randomize() {
		randomizer.randomize(module_idx, patches.get_view_patch());
	}

	void reset_params() {
		reset_params_.reset(module_idx, patches.get_view_patch());
		patch_mod_queue.put(LoadModuleState{.module_id = static_cast<uint16_t>(module_idx), .data = ""});
	}

	static void menu_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);
		if (page->visible)
			page->hide();
		else
			page->show();
	}

	static void autopatch_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);

		if (event->target == ui_ModuleViewActionAutopatchBut)
			page->auto_map_all();
		else
			page->auto_map_single_knobset();
	}

	static void random_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);
		page->randomize();
	}

	static void scroll_top_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		lv_obj_scroll_to_y(ui_ModuleViewActionMenu, 0, LV_ANIM_ON);
	}

	void preset_but_cb() {
		preset_popup.show(
			[this](unsigned opt) {
				cur_preset_idx = opt;
				const auto filename = preset_map[opt].path;
				const auto preset_file_size = ramdisk.get_file_size(filename);

				auto mod_request = LoadModuleState{.module_id = static_cast<uint16_t>(module_idx)};
				mod_request.data.resize(preset_file_size);

				auto bytes_read = ramdisk.read_file(filename, mod_request.data);
				if (bytes_read == 0) {
					pr_err("Failed to read preset file\n");
				} else {
					patch_mod_queue.put(std::move(mod_request));
				}
			},
			"Presets",
			presets.c_str(),
			cur_preset_idx);
	}

	static void preset_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);
		page->preset_but_cb();
	}

	static void reset_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);
		page->reset_params();
	}

	static void delete_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);

		std::string confirm_msg =
			"Remove this module, all its mappings, and all connected cables from the patch? This cannot be undone.";

		page->confirm_popup.show(
			[page](unsigned choice) {
				if (choice == 1) {
					page->delete_state = DeleteState::TryRequest;
				}
			},
			confirm_msg.c_str(),
			"Delete");
	}

	FatFileIO &ramdisk;
	OpenPatchManager &patches;
	PageList &page_list;
	PatchPlayLoader &patch_playloader;
	PatchModQueue &patch_mod_queue;

	ConfirmPopup confirm_popup;

	ModuleViewAutoMapDialog auto_map;
	RandomizeParams randomizer;
	ResetParams reset_params_;

	unsigned module_idx = 0;
	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	bool visible = false;

	lv_obj_t *moduleViewActionPresetBut;
	std::string preset_path{};
	uint16_t cur_preset_idx{};
	std::string presets{};
	std::vector<Preset> preset_map{};
	RollerPopup preset_popup{"Select Preset"};

	enum class DeleteState { Idle, TryRequest, Requested } delete_state = DeleteState::Idle;
};

} // namespace MetaModule
