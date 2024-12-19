#include "console/pr_dbg.hh"
#include "engine/Engine.hpp"
#include "window/Window.hpp"
#include <app/Scene.hpp>
#include <context.hpp>

namespace rack
{

static app::Scene _scene;
static window::Window _window;
static engine::Engine _engine;
static app::RackScrollWidget rackScroll;
static widget::ZoomWidget zoomWidget;

static Context rack_context{
	.scene = &_scene, .engine = &_engine, .window = &_window,
	//event
	//history
	//patch
	//midiLoopbackContext
};

Context *contextGet() {
	return &rack_context;
}

void contextSet(Context *context) {
	rack_context.scene->rackScroll = &rackScroll;
	rack_context.scene->rackScroll->zoomWidget = &zoomWidget;

	if (context != nullptr) {
		pr_warn("rack context changed!\n");
		rack_context = *context;
	}
}

} // namespace rack
