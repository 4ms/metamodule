#pragma once
#include <widget/Widget.hpp>

//MM:
#include <widget/SvgWidget.hpp>

namespace rack::widget
{

/** Caches its children's draw() result to a framebuffer image.
When dirty, its children will be re-rendered on the next call to step().
*/
struct FramebufferWidget : Widget {
	//MM:
	widget::SvgWidget *_bg = nullptr;

	bool dirty = true;
	bool bypassed = false;
	float oversample = 1.0;
	bool dirtyOnSubpixelChange = true;
	math::Vec viewportMargin = math::Vec(INFINITY, INFINITY);

	void setDirty(bool dirty = true) {
	}
	int getImageHandle() {
		return 0;
	}
	NVGLUframebuffer *getFramebuffer() {
		return nullptr;
	}
	math::Vec getFramebufferSize() {
		return {0, 0};
	}
	void deleteFramebuffer() {
	}
	void render(math::Vec scale = math::Vec(1, 1),
				math::Vec offsetF = math::Vec(0, 0),
				math::Rect clipBox = math::Rect::inf()) {
	}
	virtual void drawFramebuffer() {
	}

	void addChildBelow(SvgWidget *child, Widget *sibling);

	~FramebufferWidget() override;
};

} // namespace rack::widget
