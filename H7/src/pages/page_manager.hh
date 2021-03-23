#pragma once
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "screen_buffer.hh"

namespace MetaModule
{
class PageManager {
	PatchList &patch_list;
	PatchPlayer &patch_player;
	Params &params;
	ScreenFrameBuffer &screen;

public:
	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, ScreenFrameBuffer &s)
		: patch_list{pl}
	, patch_player{pp} 
	, params{p}
	, screen{s}
	{}
};
} // namespace MetaModule
