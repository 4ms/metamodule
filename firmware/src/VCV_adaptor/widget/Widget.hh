#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/engine/ParamQuantity.hpp"
#include "VCV_adaptor/events.hh"
#include "VCV_adaptor/math.hpp"
#include "VCV_adaptor/nanovg.h"
#include "VCV_adaptor/window.hpp"

namespace rack
{

struct DrawArgs {
	NVGcontext *vg;
	math::Rect clipBox;
	NVGLUframebuffer *fb;
};

namespace widget
{
struct Widget {
	math::Rect box{0, 0, 0, 0};
	MetaModule::Element element;

	virtual ~Widget() = default;

	virtual void onDragStart(const event::DragStart &e) {
	}
	virtual void onDragMove(const event::DragMove &e) {
	}
	virtual void onDragEnd(const event::DragEnd &e) {
	}
	virtual void onDoubleClick(const event::DoubleClick &e) {
	}
	virtual void onAction(const event::ActionEvent &e) {
	}
	virtual void onHover(const HoverEvent &e) {
	}
	virtual void onHoverKey(const HoverKeyEvent &e) {
	}
	virtual void onButton(const ButtonEvent &e) {
	}
	virtual void onDragHover(const DragHoverEvent &e) {
	}
	virtual void step() {
	}
	virtual void draw(const DrawArgs &) {
	}
	virtual void drawLayer(const DrawArgs &, int) {
	}
	virtual void onDoubleClick(const DoubleClickEvent &e) {
	}
	bool hasChild(Widget *child) {
		return false;
	}
	void addChild(Widget *child) {
		//TODO: take ownership of the pointer, and delete it in ~Widget()
	}
	void addChildBottom(Widget *child) {
		//TODO: take ownership of the pointer, and delete it in ~Widget()
	}
	void addChildBelow(Widget *child, Widget *sibling) {
		//TODO: take ownership of the pointer, and delete it in ~Widget()
	}
	void addChildAbove(Widget *child, Widget *sibling) {
		//TODO: take ownership of the pointer, and delete it in ~Widget()
	}
	void removeChild(Widget *child) {
	}
	void clearChildren() {
	}
	void hide() {
	}
};

struct OpaqueWidget : Widget {};
struct TransparentWidget : Widget {
	float opacity = 0.f;
};
struct FramebufferWidget : Widget {
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
};

// Should be called SvgParamWidget
struct SvgWidget : Widget {
	NVGcolor bgColor{};
	bool visible = true;

	std::string svg_filename;

	void setSvg(std::shared_ptr<window::Svg> svg) {
		svg_filename = svg->filename;
		// printf("SvgWidget::setSvg(): svg_filename = %s\n", svg_filename.c_str());
	}

	void setSVG(std::shared_ptr<window::Svg> svg) {
		setSvg(svg);
	}
};

struct TransformWidget : Widget {};

} // namespace widget
} // namespace rack
