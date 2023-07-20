#pragma once
#include "VCV_adaptor/app/Scene.hpp"
#include "VCV_adaptor/common.hpp"
#include "VCV_adaptor/engine/Engine.hpp"
#include "VCV_adaptor/window.hpp"
#include <cstddef>

namespace rack
{

namespace history
{
struct State;
} // namespace history

namespace patch
{
struct Manager;
} // namespace patch

namespace widget
{
struct EventState;
} // namespace widget

namespace midiloopback
{
struct Context;
} // namespace midiloopback

struct Context {
	app::Scene *scene = &_scene;
	engine::Engine *engine = &_engine;
	window::Window *window = &_window;

	widget::EventState *event = nullptr;
	history::State *history = nullptr;
	patch::Manager *patch = nullptr;
	midiloopback::Context *midiLoopbackContext = nullptr;

private:
	app::Scene _scene;
	window::Window _window;
	engine::Engine _engine;
};

inline Context *contextGet() {
	// static Context context;
	// return &context;
	return nullptr;
}
// void contextSet(Context* context);

DEPRECATED inline Context *appGet() {
	return contextGet();
}

#define APP rack::contextGet()

} // namespace rack
