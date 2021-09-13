#pragma once
#include "conf/panel_conf.hh"
#include "pages/geometry.hh"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "screen_buffer.hh"

namespace MetaModule
{
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
	ScreenFrameBuffer &screen;

	PageBase(PatchInfo info, ScreenFrameBuffer &screen_)
		: patch_list{info.patch_list}
		, patch_player{info.patch_player}
		, params{info.params}
		, metaparams{info.metaparams}
		, mbox{info.mbox}
		, screen{screen_}
	{}
};
} // namespace MetaModule
