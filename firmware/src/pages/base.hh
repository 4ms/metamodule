#pragma once
#include "conf/panel_conf.hh"
#include "lvgl/lvgl.h"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "util/geometry.hh"

namespace MetaModule
{

enum class PageChangeDirection { Back, Forward, Jump };

struct PatchInfo {
	PatchList &patch_list;
	PatchPlayer &patch_player;
	Params &params;
	MetaParams &metaparams;
	UiAudioMailbox &mbox;
};

struct PageBase {
	PatchList &patch_list;
	PatchPlayer &patch_player;
	Params &params;
	MetaParams &metaparams;
	UiAudioMailbox &mbox;

	PageBase(PatchInfo info)
		: patch_list{info.patch_list}
		, patch_player{info.patch_player}
		, params{info.params}
		, metaparams{info.metaparams}
		, mbox{info.mbox}
	{}
};
} // namespace MetaModule
