#pragma once
#include "pages/base.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"
#include "pages/page_list.hh"
#include "pages/styles.hh"
#include "printf.h"

//exported:
#include "slsexport/patchsel/ui.h"
extern "C" void ui_PatchSelector_screen_init();
LV_FONT_DECLARE(lv_font_montserrat_10);
LV_FONT_DECLARE(lv_font_montserrat_16);

namespace MetaModule
{

//TODO: keep our place in the list when changing media (if possible)
//Keep track of hovered_patch_id/vol
//And restore that after a refresh:
struct PatchSelectorPage : PageBase {
	PatchSelectorPage(PatchInfo info)
		: PageBase{info} {
		PageList::register_page(this, PageId::PatchSel);

		ui_PatchSelector_screen_init();
		base = ui_PatchSelector;  //NOLINT
		roller = ui_patchlist;	  //NOLINT
		nor_but = ui_Flashbut;	  //NOLINT
		usb_but = ui_USBbut;	  //NOLINT
		sd_but = ui_SDbut;		  //NOLINT
		spinner = ui_waitspinner; //NOLINT

		init_bg(base);

		lv_group_add_obj(group, roller);
		lv_obj_add_event_cb(roller, patchlist_select_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(roller, patchlist_scroll_cb, LV_EVENT_KEY, this);
	}

	void init() override {
		state = State::TryingToRequestPatchList;
	}

	void prepare_focus() override {
		state = State::TryingToRequestPatchList;
		lv_obj_add_flag(spinner, LV_OBJ_FLAG_HIDDEN);
	}

	void refresh_patchlist(PatchFileList &patchfiles) {
		num_usb = patchfiles.usb.size();
		num_sdcard = patchfiles.sdcard.size();
		num_norflash = patchfiles.norflash.size();

		//TODO: try using pmr::string with monotonic stack buffer
		std::string patchnames;
		patchnames.reserve((sizeof(PatchFile::patchname) + sizeof(leader) + 1 /*newline*/) *
							   (num_usb + num_norflash + num_sdcard + 3 /*headers*/) +
						   32 /*just in case*/);

		if (num_usb) {
			patchnames += "USB Drive\n";
			// patchnames += LV_SYMBOL_USB;
			for (auto &p : patchfiles.usb) {
				patchnames += leader;
				patchnames += std::string_view{p.patchname};
				patchnames += '\n';
			}
		}
		if (num_sdcard) {
			patchnames += "SD Card\n";
			for (auto &p : patchfiles.sdcard) {
				patchnames += leader;
				patchnames += std::string_view{p.patchname};
				patchnames += '\n';
			}
		}
		if (num_norflash) {
			patchnames += "Internal\n";
			for (auto &p : patchfiles.norflash) {
				patchnames += leader;
				patchnames += std::string_view{p.patchname};
				patchnames += '\n';
			}
		}

		// remove trailing \n
		if (patchnames.length() > 0)
			patchnames.pop_back();

		lv_roller_set_options(roller, patchnames.c_str(), LV_ROLLER_MODE_NORMAL);

		//refresh header positions
		usb_hdr = 0;
		sd_hdr = 0;
		if (num_sdcard) {
			if (num_usb)
				sd_hdr += 1 + num_usb;
		}

		nor_hdr = 0;
		if (num_norflash) {
			if (num_usb)
				nor_hdr += 1 + num_usb;
			if (num_sdcard)
				nor_hdr += 1 + num_sdcard;
		}

		//TODO: check if the patch we were on exists (same name, and volume is mounted), and select it instead
		// For now, we just select the first patch of the first volume
		highlighted_idx = 1;
		highlighted_vol = num_usb ? Volume::USB : num_sdcard ? Volume::SDCard : Volume::NorFlash;
		lv_roller_set_selected(roller, highlighted_idx, LV_ANIM_ON);

		printf_("Patch Selector refreshed:\nUSB: %ld patches\nSD: %ld patches\nNOR: %ld patches\n",
				patchfiles.usb.size(),
				patchfiles.sdcard.size(),
				patchfiles.norflash.size());
	}

	void refresh_volume_labels() {
		//Disable unmounted media:
		if (num_usb)
			lv_obj_clear_state(usb_but, LV_STATE_DISABLED);
		else
			lv_obj_add_state(usb_but, LV_STATE_DISABLED);

		if (num_sdcard)
			lv_obj_clear_state(sd_but, LV_STATE_DISABLED);
		else
			lv_obj_add_state(sd_but, LV_STATE_DISABLED);

		if (num_norflash)
			lv_obj_clear_state(nor_but, LV_STATE_DISABLED);
		else
			lv_obj_add_state(nor_but, LV_STATE_DISABLED);

		// Highlight (CHECKED) the selected volume
		if (highlighted_vol == Volume::USB)
			lv_obj_add_state(usb_but, LV_STATE_CHECKED);
		else
			lv_obj_clear_state(usb_but, LV_STATE_CHECKED);

		if (highlighted_vol == Volume::SDCard)
			lv_obj_add_state(sd_but, LV_STATE_CHECKED);
		else
			lv_obj_clear_state(sd_but, LV_STATE_CHECKED);

		if (highlighted_vol == Volume::NorFlash)
			lv_obj_add_state(nor_but, LV_STATE_CHECKED);
		else
			lv_obj_clear_state(nor_but, LV_STATE_CHECKED);
	}

	void update() override {
		// Check if M4 sent us a message:

		switch (state) {
			case State::TryingToRequestPatchList:
				if (patch_storage.request_patchlist())
					state = State::RequestedPatchList;
				break;

			case State::RequestedPatchList: {
				auto message = patch_storage.get_message().message_type;
				if (message == PatchStorageProxy::PatchListChanged) {
					show_spinner();
					state = State::ReloadingPatchList;
				} else if (message == PatchStorageProxy::PatchListUnchanged) {
					hide_spinner();
					state = State::Idle;
				}
				//else other messages ==> error? repeat request? idle?
			} break;

			case State::ReloadingPatchList:
				refresh_patchlist(patch_storage.get_patch_list());
				refresh_volume_labels();
				hide_spinner();
				state = State::Idle;
				break;

			case State::Idle: {
				//periodically check if patchlist needs updating:
				uint32_t now = lv_tick_get();
				if (now - last_refresh_check_tm > 1000) { //poll media once per second
					last_refresh_check_tm = now;
					state = State::TryingToRequestPatchList;
				}
			} break;

			case State::TryingToRequestPatchData:
				if (patch_storage.request_viewpatch(selected_patch_vol, selected_patch)) {
					state = State::RequestedPatchData;
					show_spinner();
				}
				break;

			case State::RequestedPatchData: {
				auto message = patch_storage.get_message();

				if (message.message_type == PatchStorageProxy::PatchDataLoaded) {
					// Try to parse the patch and open the PatchView page
					if (patch_storage.parse_view_patch(message.bytes_read)) {
						auto view_patch = patch_storage.get_view_patch();
						printf_("Parsed patch: %.31s\n", view_patch.patch_name.data());
						PageList::set_selected_patch_id(selected_patch);
						PageList::request_new_page(PageId::PatchView);
						state = State::Closing;
						hide_spinner();
					} else {
						printf_("Error parsing patch id %d, bytes_read = %d\n", selected_patch, message.bytes_read);
						state = State::Idle;
						hide_spinner();
					}
				} else if (message.message_type == PatchStorageProxy::PatchDataLoadFail) {
					printf_("Error loading patch id %d\n", selected_patch);
					state = State::Idle;
					lv_group_set_editing(group, true);
					hide_spinner();
					//TODO: handle error... try reloading patch list?
				}
			} break;

			case State::Closing:
				break;
		}
	}

	void blur() override {
		hide_spinner();
	}

	void show_spinner() {
		// lv_obj_clear_flag(spinner, LV_OBJ_FLAG_HIDDEN);
	}

	void hide_spinner() {
		// lv_obj_add_flag(spinner, LV_OBJ_FLAG_HIDDEN);
	}

	static void patchlist_scroll_cb(lv_event_t *event) {
		auto _instance = static_cast<PatchSelectorPage *>(event->user_data);
		auto idx = lv_roller_get_selected(_instance->roller);

		if (idx == _instance->usb_hdr || idx == _instance->sd_hdr || idx == _instance->nor_hdr) {
			if (idx == 0)
				lv_roller_set_selected(_instance->roller, 1, LV_ANIM_OFF);
			else if (idx > _instance->highlighted_idx)
				lv_roller_set_selected(_instance->roller, idx + 1, LV_ANIM_OFF);
			else if (idx < _instance->highlighted_idx)
				lv_roller_set_selected(_instance->roller, idx - 1, LV_ANIM_OFF);
			idx = lv_roller_get_selected(_instance->roller);
		}

		auto [_, vol] = _instance->calc_patch_id_vol(idx);
		_instance->highlighted_vol = vol;
		_instance->highlighted_idx = idx;
		_instance->refresh_volume_labels();
	}

	static void patchlist_select_cb(lv_event_t *event) {
		auto _instance = static_cast<PatchSelectorPage *>(event->user_data);
		patchlist_scroll_cb(event);

		auto [patch_id, vol] = _instance->calc_patch_id_vol(_instance->highlighted_idx);
		_instance->selected_patch_vol = vol;
		_instance->selected_patch = patch_id;
		_instance->state = State::TryingToRequestPatchData;

		printf_("Selected vol %d, patch %d\n", (uint32_t)_instance->selected_patch_vol, _instance->selected_patch);
	}

	std::pair<uint32_t, Volume> calc_patch_id_vol(uint32_t roller_idx) {
		auto vol = (num_norflash && roller_idx > nor_hdr) ? Volume::NorFlash :
				   (num_sdcard && roller_idx > sd_hdr)	  ? Volume::SDCard :
															Volume::USB;
		if (vol == Volume::USB)
			return {roller_idx - 1 - usb_hdr, vol};
		if (vol == Volume::SDCard)
			return {roller_idx - 1 - sd_hdr, vol};
		if (vol == Volume::NorFlash)
			return {roller_idx - 1 - nor_hdr, vol};
		return {0, Volume::NorFlash};
	}

private:
	uint32_t selected_patch = 0;
	Volume selected_patch_vol = Volume::NorFlash;
	uint32_t highlighted_idx = 0;
	Volume highlighted_vol = Volume::NorFlash;

	lv_obj_t *roller;
	// lv_obj_t *header_text;
	lv_obj_t *base;
	lv_obj_t *usb_but;
	lv_obj_t *sd_but;
	lv_obj_t *nor_but;
	lv_obj_t *spinner;

	const std::string_view leader = "   ";
	uint32_t num_usb;
	uint32_t num_sdcard;
	uint32_t num_norflash;

	unsigned usb_hdr = 0;
	unsigned sd_hdr = 0;
	unsigned nor_hdr = 0;

	enum class State {
		Idle,

		TryingToRequestPatchList,
		RequestedPatchList,
		ReloadingPatchList,

		TryingToRequestPatchData,
		RequestedPatchData,

		Closing,
	} state;

	uint32_t last_refresh_check_tm = 0;
};

} // namespace MetaModule
