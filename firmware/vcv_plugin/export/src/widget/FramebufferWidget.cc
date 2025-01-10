#include "widget/FramebufferWidget.hpp"

namespace rack::widget
{

struct FramebufferWidget::Internal {
	NVGLUframebuffer *fb = NULL;

	/** Pixel dimensions of the allocated framebuffer */
	math::Vec fbSize;
	/** Bounding box in world coordinates of where the framebuffer should be painted.
	Always has integer coordinates so that blitting framebuffers is pixel-perfect.
	*/
	math::Rect fbBox;
	/** Framebuffer's scale relative to the world */
	math::Vec fbScale;
	/** Framebuffer's subpixel offset relative to fbBox in world coordinates */
	math::Vec fbOffsetF;
	/** Local box where framebuffer content is valid.
	*/
	math::Rect fbClipBox = math::Rect::inf();
};

FramebufferWidget::FramebufferWidget() {
	internal = new Internal;
}

FramebufferWidget::~FramebufferWidget() {
	deleteFramebuffer();
	delete internal;
}

void FramebufferWidget::setDirty(bool dirty) {
	this->dirty = dirty;
}

int FramebufferWidget::getImageHandle() {
	if (!internal->fb)
		return -1;
	return internal->fb->image;
}

NVGLUframebuffer *FramebufferWidget::getFramebuffer() {
	return internal->fb;
}

math::Vec FramebufferWidget::getFramebufferSize() {
	return internal->fbSize;
}

void FramebufferWidget::deleteFramebuffer() {
	if (!internal->fb)
		return;

	// If the framebuffer exists, the Window should exist.
	// assert(APP->window);

	// nvgluDeleteFramebuffer(internal->fb);
	internal->fb = nullptr;
}

void FramebufferWidget::step() {
	Widget::step();
}

void FramebufferWidget::draw(const DrawArgs &args) {
}

void FramebufferWidget::render(math::Vec scale, math::Vec offsetF, math::Rect clipBox) {};

void FramebufferWidget::drawFramebuffer() {
}

void FramebufferWidget::onDirty(const DirtyEvent &e) {
	setDirty();
	Widget::onDirty(e);
}

void FramebufferWidget::onContextCreate(const ContextCreateEvent &e) {
	setDirty();
	Widget::onContextCreate(e);
}

void FramebufferWidget::onContextDestroy(const ContextDestroyEvent &e) {
	deleteFramebuffer();
	setDirty();
	Widget::onContextDestroy(e);
}

} // namespace rack::widget
