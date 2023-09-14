#pragma once
#include "gui/message_queue.hh"
#include "gui/pages/page_manager.hh"
#include "params/params_dbg_print.hh"
#include "params/sync_params.hh"
#include "patch_file/patch_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

class Ui {

public:
	Ui(PatchPlayLoader &patch_playloader,
	   PatchStorageProxy &patch_storage,
	   SyncParams &sync_params,
	   PatchModQueue &patch_mod_queue);
	void update();

private:
	void page_update_task();

	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;

	MessageQueue msg_queue;
	PageManager page_manager;
	ParamsState params;
	MetaParams metaparams;

	ParamDbgPrint print_dbg_params{params, metaparams};
	int32_t throttle_ctr = 10;
	uint32_t last_update_tm = 0;
};

} // namespace MetaModule
