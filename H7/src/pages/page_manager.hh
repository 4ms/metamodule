#pragma once
#include "Adafruit_GFX_Library/Fonts/FreeMono12pt7b.h"
#include "Adafruit_GFX_Library/Fonts/FreeSans9pt7b.h"
#include "Adafruit_GFX_Library/Fonts/FreeSansBold18pt7b.h"
#include "pages/bouncing_ball.hh"
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

class DisplayPage {
	//
};


class PageManager {
public:
	PatchList &patch_list;
	PatchPlayer &patch_player;
	Params &params;
	ScreenFrameBuffer &screen;

	Page cur_page;

	Color bgcolor = Colors::pink;
	Color patch_fgcolor = Colors::blue.blend(Colors::black, 0.5f);
	Color load_fgcolor = Colors::blue;
	Color pots_fgcolor = Colors::black;

public:
	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, ScreenFrameBuffer &s)
		: patch_list{pl}
		, patch_player{pp}
		, params{p}
		, screen{s}
		, cur_page{Page::PatchOverview}
	{}

	void init()
	{
		cur_page = Page::PatchOverview;
		display_current_page();
	}

	void next_page()
	{
		cur_page = static_cast<Page>(static_cast<unsigned>(cur_page) + 1);
		if (cur_page >= LAST_PAGE)
			cur_page = PatchOverview;
	}
	void prev_page()
	{
		if (static_cast<unsigned>(cur_page) == 0)
			cur_page = static_cast<Page>(static_cast<unsigned>(LAST_PAGE) - 1);
		else
			cur_page = static_cast<Page>(static_cast<unsigned>(cur_page) - 1);
	}

	void jump_to_page(Page p)
	{
		cur_page = p;
	}

	void display_current_page();
};
} // namespace MetaModule
