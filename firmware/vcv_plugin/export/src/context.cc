#include "console/pr_dbg.hh"
#include "engine/Engine.hpp"
#include "vcv_plugin/export/nanovg/fontstash-wrapper.h"
#include "window/Window.hpp"
#include <app/Scene.hpp>
#include <context.hpp>

namespace rack
{

namespace midiloopback
{
struct Context {};
} // namespace midiloopback

namespace patch
{
struct Manager {};
} // namespace patch

static app::Scene _scene;
static window::Window _window;
static engine::Engine _engine;
static app::RackScrollWidget _rackScroll;
static widget::ZoomWidget _zoomWidget;
static widget::EventState _event;
static history::State _history;
static patch::Manager _patch;
static midiloopback::Context _midiLoopbackContext;
static app::RackWidget _rackWidget;

static widget::Widget _menuBar;
static widget::Widget _browser;

static Context rack_context{
	.event = &_event,
	.scene = &_scene,
	.engine = &_engine,
	.window = &_window,
	.history = &_history,
	.patch = &_patch,
	.midiLoopbackContext = &_midiLoopbackContext,
};

Context *contextGet() {
	return &rack_context;
}

Context::~Context() = default;

void contextSet(Context *context) {
	rack_context.scene->rack = &_rackWidget;
	rack_context.scene->rackScroll = &_rackScroll;
	rack_context.scene->rackScroll->zoomWidget = &_zoomWidget;
	rack_context.scene->menuBar = &_menuBar;
	rack_context.scene->browser = &_browser;

	auto fonsctx = fonsCreateInternal();
	auto handle = fonsAddFont(fonsctx, "DejaVuSans", asset::system("res/fonts/DejaVuSans.ttf").c_str(), 0);
	rack_context.window->uiFont->handle = handle;

	if (context != nullptr) {
		pr_warn("rack context changed!\n");
		rack_context = *context;
	}
}

math::Vec widget::ZoomWidget::getRelativeOffset(math::Vec v, Widget *ancestor) {
	return {};
}
float widget::ZoomWidget::getRelativeZoom(Widget *ancestor) {
	return {};
}
math::Rect widget::ZoomWidget::getViewport(math::Rect r) {
	return {};
}
float widget::ZoomWidget::getZoom() {
	return {};
}
void widget::ZoomWidget::setZoom(float zoom) {
}
void widget::ZoomWidget::draw(const DrawArgs &args) {
}
void widget::ZoomWidget::drawLayer(const DrawArgs &args, int layer) {
}

} // namespace rack
