#pragma once
#include <common.hpp>

namespace rack
{

namespace history
{
struct State;
} // namespace history

namespace engine
{
struct Engine;
} // namespace engine

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

/** Rack instance state
*/
struct Context {
	widget::EventState *event = nullptr;
	app::Scene *scene = nullptr;
	engine::Engine *engine = nullptr;
	window::Window *window = nullptr;
	history::State *history = nullptr;
	patch::Manager *patch = nullptr;
	midiloopback::Context *midiLoopbackContext = nullptr;
};

/** Returns the global Context pointer */
Context *contextGet();
/** Sets the context for this thread.
You must set the context when preparing each thread if the code uses the APP macro in that thread.
*/
void contextSet(Context *context);

/** Deprecated. Use contextGet() or the APP macro to get the current Context. */
DEPRECATED inline Context *appGet() {
	return contextGet();
}

/** Accesses the global Context pointer. Just an alias for contextGet(). */
#define APP rack::contextGet()

} // namespace rack
