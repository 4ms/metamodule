#pragma once
#include "pages/fonts.hh"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "screen_buffer.hh"

namespace MetaModule
{
enum Page : unsigned {
	PatchOverview = 0,
	ModulesInPatch,
	JackMap,
	PotMap,
	PatchLayout,
	PatchSelector,
	DebugInfo,
	BouncingBalls,

	LAST_PAGE,
};

struct DisplayPage {
	DisplayPage() = delete;
};

class PageManager {
public:
	PatchList &patch_list;
	PatchPlayer &patch_player;
	Params &params;
	ScreenFrameBuffer &screen;

	Page cur_page;

	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, ScreenFrameBuffer &s)
		: patch_list{pl}
		, patch_player{pp}
		, params{p}
		, screen{s}
		, cur_page{Page::PatchOverview}
	{}

	void init();
	void next_page();
	void prev_page();
	void jump_to_page(Page p);
	void display_current_page();
};
} // namespace MetaModule
