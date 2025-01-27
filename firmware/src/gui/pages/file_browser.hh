#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"

namespace MetaModule
{

struct FileBrowserDialog {
	FileBrowserDialog(FileStorageProxy &file_storage, NotificationQueue &notify_queue, PageList &page_list)
		: file_storage{file_storage}
		, notify_queue{notify_queue}
		, page_list{page_list} {
	}

private:
	FileStorageProxy &file_storage;
	NotificationQueue &notify_queue;
	PageList &page_list;
};
} // namespace MetaModule
