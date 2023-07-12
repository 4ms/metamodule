#pragma once
#include "VCV-adaptor/common.hpp"
#include <cstddef>

namespace rack
{

namespace history
{
struct State;
} // namespace history

namespace window
{
struct Window;
} // namespace window

namespace patch
{
struct Manager;
} // namespace patch

namespace widget
{
struct EventState;
} // namespace widget

namespace app
{
struct Scene;
} // namespace app

namespace midiloopback
{
struct Context;
} // namespace midiloopback

struct Context {
	widget::EventState *event = nullptr;
	app::Scene *scene = nullptr;
	engine::Engine *engine = nullptr;
	window::Window *window = nullptr;
	history::State *history = nullptr;
	patch::Manager *patch = nullptr;
	midiloopback::Context *midiLoopbackContext = nullptr;
};

Context *contextGet() {
	static Context context;
	return &context;
}
// void contextSet(Context* context);

DEPRECATED inline Context *appGet() {
	return contextGet();
}

#define APP rack::contextGet()

} // namespace rack
