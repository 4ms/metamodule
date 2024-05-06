#include "engine/Engine.hpp"
#include "window/Window.hpp"
#include <app/Scene.hpp>
#include <context.hpp>

namespace rack
{

static app::Scene _scene;
static window::Window _window;
static engine::Engine _engine;
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
	rack_context = *context;
}

} // namespace rack
