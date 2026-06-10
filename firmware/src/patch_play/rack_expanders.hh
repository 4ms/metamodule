#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

class CoreProcessor;

namespace rack::engine
{
struct Module;
}

namespace MetaModule
{

// Wires VCV-style expander connections between rack modules in the loaded
// patch, and flips their double-buffered expander messages once per sample.
// Non-rack modules (native CoreProcessors, NullModule) are skipped safely.
class RackExpanders {
public:
	// Attach modules[right_id] as the right-side expander of modules[left_id].
	// Returns false (and does nothing) unless both are live rack::Modules.
	bool connect(CoreProcessor *left, CoreProcessor *right, uint16_t left_id, uint16_t right_id);

	// Swap producer/consumer messages on all connected modules, if requested.
	// Call once per sample after all modules have been stepped (audio thread).
	void flip_messages();

	size_t num_connected() const {
		return modules.size();
	}

	void clear();

private:
	std::vector<rack::engine::Module *> modules;
};

} // namespace MetaModule
