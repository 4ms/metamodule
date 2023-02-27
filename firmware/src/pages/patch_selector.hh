#pragma once
#include "pages/base.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"
#include "pages/page_list.hh"
#include "pages/styles.hh"
#include "printf.h"
#include "stm32xx.h"

namespace MetaModule
{

struct PatchSelectorPage : PageBase {
	PatchSelectorPage(PatchInfo info)
		: PageBase{info}
		, base(lv_obj_create(nullptr)) {
		PageList::register_page(this, PageId::PatchSel);

		init_bg(base);

		roller = lv_roller_create(base);
		lv_group_add_obj(group, roller);

		lv_obj_add_event_cb(roller, patchlist_select_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(roller, patchlist_scroll_cb, LV_EVENT_KEY, this);

		lv_obj_add_style(roller, &Gui::roller_style, LV_PART_MAIN);
		lv_obj_add_style(roller, &Gui::plain_border_style, (int)LV_PART_MAIN | LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
		lv_obj_add_style(roller, &Gui::roller_sel_style, LV_PART_SELECTED);

		lv_obj_set_pos(roller, 0, 30);
		lv_obj_set_size(roller, 320, 210);

		header_text = lv_label_create(base);
		lv_label_set_text_static(header_text, "Select a Patch:");
		lv_obj_add_style(header_text, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_align(base, LV_ALIGN_TOP_MID);
		lv_obj_set_pos(header_text, 0, 0);
		lv_obj_set_width(header_text, 320);

		// wait_cont = lv_obj_create(base);
		// lv_obj_set_align(wait_cont, LV_ALIGN_CENTER);
		// lv_obj_add_style(wait_cont, &style_wait_cont, LV_PART_MAIN);
		// lv_cont_set_layout(wait_cont, LV_LAYOUT_CENTER);
		// lv_cont_set_fit(wait_cont, LV_FIT_TIGHT);

		// wait_text = lv_label_create(wait_cont);
		// lv_obj_add_style(wait_text, &style_popup_patchname, LV_PART_MAIN);
		// lv_obj_set_align(wait_text, LV_ALIGN_CENTER);
		// lv_label_set_text(wait_text, "Refreshing Patches...");

		// lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);

		// wait_group = lv_group_create();
	}

	void init() override {
		state = State::TryingToRequestPatchList;
	}

	void prepare_focus() override {
		state = State::TryingToRequestPatchList;
	}

	//void refresh_patchlist_list(PatchFileList &patchfiles) {
	//	//TODO: try using pmr::vector with monotonic stack buffer
	//	lv_obj_del(roller);
	//	roller = lv_list_create(base);
	//	lv_group_add_obj(group, roller);
	//	lv_obj_add_event_cb(roller, patchlist_event_cb, LV_EVENT_VALUE_CHANGED, this);
	//	lv_obj_add_style(roller, &Gui::roller_style, LV_PART_MAIN);
	//	lv_obj_add_style(roller, &Gui::plain_border_style, (int)LV_PART_MAIN | LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
	//	lv_obj_add_style(roller, &Gui::roller_sel_style, LV_PART_SELECTED);
	//	lv_obj_set_pos(roller, 0, 30);
	//	lv_obj_set_size(roller, 320, 210);

	//	std::vector<PatchFile> usb;
	//	std::vector<PatchFile> sdcard;
	//	std::vector<PatchFile> norflash;
	//	usb.reserve(patchfiles.size());
	//	sdcard.reserve(patchfiles.size());
	//	norflash.reserve(patchfiles.size());

	//	for (auto &p : patchfiles) {
	//		if (p.volume == Volume::USB)
	//			usb.push_back(p);
	//		if (p.volume == Volume::SDCard)
	//			sdcard.push_back(p);
	//		if (p.volume == Volume::NorFlash)
	//			norflash.push_back(p);
	//	}
	//	if (usb.size()) {
	//		lv_list_add_text(roller, "USB Drive");
	//		for (auto &p : usb) {
	//			lv_list_add_btn(roller, nullptr /*LV_SYMBOL_USB*/, p.patchname.c_str());
	//		}
	//	}
	//	if (sdcard.size()) {
	//		lv_list_add_text(roller, "SD Card");
	//		for (auto &p : sdcard) {
	//			lv_list_add_btn(roller, nullptr /*LV_SYMBOL_SD_CARD*/, p.patchname.c_str());
	//		}
	//	}
	//	if (norflash.size()) {
	//		lv_list_add_text(roller, "Internal");
	//		for (auto &p : norflash) {
	//			lv_list_add_btn(roller, nullptr /*LV_SYMBOL_DRIVE*/, p.patchname.c_str());
	//		}
	//	}
	//}

	void refresh_patchlist(PatchFileList &patchfiles) {
		num_usb = patchfiles.usb.size();
		num_sdcard = patchfiles.sdcard.size();
		num_norflash = patchfiles.norflash.size();

		//TODO: try using pmr::string with monotonic stack buffer
		std::string patchnames;
		patchnames.reserve((sizeof(PatchFile::patchname) + 1) * (num_usb + num_norflash + num_sdcard) + 128);

		if (num_usb) {
			patchnames += "USB Drive\n";
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
			patchnames += "Norflash\n";
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

		unsigned default_sel = patchnames.size() > 10 ? 5 : patchnames.size() / 2;
		lv_roller_set_selected(roller, default_sel, LV_ANIM_OFF);

		printf_("Patch Selector refreshed:\nUSB: %ld patches from %p\nSD : %ld patches from %p\nNOR: %ld patches "
				"from %p\n",
				patchfiles.usb.size(),
				patchfiles.usb.data(),
				patchfiles.sdcard.size(),
				patchfiles.sdcard.data(),
				patchfiles.norflash.size(),
				patchfiles.norflash.data());
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
					refresh_patchlist(patch_storage.get_patch_list());
					state = State::Idle;
				} else if (message == PatchStorageProxy::PatchListUnchanged)
					state = State::Idle;
				//else other messages ==> error? repeat request? idle?
			} break;

			case State::Idle: {
				//periodically check if patchlist needs updating:
				uint32_t now = HAL_GetTick();
				if (now - last_refresh_check_tm > 1000) { //poll media once per second
					last_refresh_check_tm = now;
					state = State::TryingToRequestPatchList;
				}
			} break;

			case State::TryingToRequestPatchData:
				if (patch_storage.request_viewpatch(selected_patch_vol, selected_patch))
					state = State::RequestedPatchData;
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
					} else {
						printf_("Error parsing patch id %d, bytes_read = %d\n", selected_patch, message.bytes_read);
						state = State::Idle;
					}
				} else if (message.message_type == PatchStorageProxy::PatchDataLoadFail) {
					printf_("Error loading patch id %d\n", selected_patch);
					state = State::Idle;
					//TODO: handle error... try reloading patch list?
				}
			} break;

			case State::Closing:
				break;
		}

		//TODO: Display state: "Refreshing...", "Loading..."

		// if (should_show_patchview) {
		// 	should_show_patchview = false;
		// 	printf_("Requesting new page: PatchView, patch id %d\n", selected_patch);
		// 	patch_storage.load_view_patch(selected_patch);
		// 	blur();
		// }

		// lv_indev_set_group(lv_indev_get_next(nullptr), wait_group);
		// lv_obj_clear_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);

		// 		if (!patchlist_was_ready) {
		// 			// lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
		// 			lv_indev_set_group(lv_indev_get_next(nullptr), group);
		// 			lv_group_set_editing(group, true);
		// 			patchlist_was_ready = true;
		// 		}
	}

	void blur() override {
		// lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
	}

	static void patchlist_scroll_cb(lv_event_t *event) {
		auto _instance = static_cast<PatchSelectorPage *>(event->user_data);
		auto idx = lv_roller_get_selected(_instance->roller);
		printf_("Scrolled to %d from %d\n", idx, _instance->last_idx);

		auto usb_hdr = 0;
		auto sd_hdr = _instance->num_sdcard ? (_instance->num_usb ? _instance->num_usb + 1 : 0) : 0;
		uint32_t nor_hdr = 0;
		if (_instance->num_norflash) {
			if (_instance->num_usb)
				nor_hdr += 1 + _instance->num_usb;
			if (_instance->num_sdcard)
				nor_hdr += 1 + _instance->num_sdcard;
		}
		// auto nor_hdr = _instance->num_norflash ? (_instance->num_usb ? 1 + _instance->num_usb + _instance->num_sdcard) : 0;
		printf_("usbh %d, sdh %d, nor %d\n", usb_hdr, sd_hdr, nor_hdr);

		if (idx == usb_hdr || idx == sd_hdr || idx == nor_hdr) {
			printf_("Scrolled to header\n");
			if (idx == 0)
				lv_roller_set_selected(_instance->roller, 1, LV_ANIM_OFF);
			else if (idx > _instance->last_idx)
				lv_roller_set_selected(_instance->roller, idx + 1, LV_ANIM_OFF);
			else if (idx < _instance->last_idx)
				lv_roller_set_selected(_instance->roller, idx - 1, LV_ANIM_OFF);
		}
		_instance->last_idx = lv_roller_get_selected(_instance->roller);
	}

	static void patchlist_select_cb(lv_event_t *event) {
		auto _instance = static_cast<PatchSelectorPage *>(event->user_data);
		auto idx = lv_roller_get_selected(_instance->roller);
		if (!idx || idx == _instance->num_usb || idx == (_instance->num_usb + _instance->num_sdcard + 1)) {
			printf_("Selected a header: %d\n", idx);
			return;
		}
		if (idx < _instance->num_usb) {
			_instance->selected_patch_vol = Volume::USB;
			_instance->selected_patch = idx - 1;
			printf_("Selected USB: %d => %d\n", idx, _instance->selected_patch);
		} else if (idx < (_instance->num_sdcard + _instance->num_usb + 1)) {
			_instance->selected_patch_vol = Volume::SDCard;
			_instance->selected_patch = idx - _instance->num_usb - 1;
			printf_("Selected SD: %d => %d\n", idx, _instance->selected_patch);
		} else {
			_instance->selected_patch_vol = Volume::NorFlash;
			_instance->selected_patch = idx - _instance->num_usb - _instance->num_sdcard - 2;
			printf_("Selected NOR: %d => %d\n", idx, _instance->selected_patch);
		}
	}

private:
	uint32_t selected_patch = 0;
	Volume selected_patch_vol = Volume::NorFlash;
	uint32_t last_idx = 0;

	lv_obj_t *roller;
	lv_obj_t *header_text;
	lv_obj_t *base;
	const std::string_view leader = "  ";
	uint32_t num_usb;
	uint32_t num_sdcard;
	uint32_t num_norflash;

	enum class State {
		Idle,

		TryingToRequestPatchList,
		RequestedPatchList,

		TryingToRequestPatchData,
		RequestedPatchData,

		Closing,
	} state;

	uint32_t last_refresh_check_tm = 0;
};

} // namespace MetaModule
