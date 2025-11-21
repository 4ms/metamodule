#pragma once
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "sketch/sketch.hh"
#include "sketch/test2.hh"

namespace MetaModule
{

struct FullscreenGraphicPage : PageBase {

	std::unique_ptr<Handheld::Sketch> sketch;

	FullscreenGraphicPage(PatchContext info)
		: PageBase{info, PageId::FullscreenGraphic} {
		sketch = std::make_unique<Handheld::Test2>();
	}

	void prepare_focus() final {
		sketch->setup();
	}

	void update() final {
		sketch->draw();
	}

	void blur() final {
	}
};

} // namespace MetaModule
