#pragma once
#include "patch_play/expander_hookup.hh"
#include <cstddef>
#include <cstdint>

class CoreProcessor;

namespace rack::engine
{
struct Module;
}

namespace MetaModule
{

// Wires VCV-style expander connections between rack modules in the loaded
// patch, and flips their double-buffered expander messages once per sample.
// Connections are tracked by module pointer, so they are unaffected by
// module index re-numbering. Non-rack modules (native CoreProcessors,
// NullModule) are skipped safely.
class RackExpanders {
public:
	RackExpanders();

	// Attach `right` as the right-side expander of `left`.
	// Returns false (and does nothing) unless both are live rack::Modules
	// with that side free.
	bool connect(CoreProcessor *left, CoreProcessor *right);

	// Detach the pair (if connected) and notify both modules.
	bool disconnect_pair(CoreProcessor *left, CoreProcessor *right);

	// Detach `m` from its neighbors on both sides, notifying only the modules involved.
	// Must be called before `m` is destroyed (with audio muted).
	void disconnect(CoreProcessor *m);

	// Detach all connected modules from each other (clearing their Expander
	// pointers and notifying them) and stop tracking them. Must be called
	// before any connected module is destroyed (with audio muted).
	void disconnect_all();

	// Swap producer/consumer messages on all connected modules, if requested.
	// Call once per sample after all modules have been stepped (audio thread).
	void flip_messages();

	bool is_connected(CoreProcessor *left, CoreProcessor *right) const;

	// True once the two modules have exchanged at least one expander message
	bool is_active(CoreProcessor *left, CoreProcessor *right) const;

	size_t num_connections() const {
		return conns.num_connections();
	}

	void clear();

private:
	ExpanderHookup::Connections<rack::engine::Module> conns;
};

} // namespace MetaModule
