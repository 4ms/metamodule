#pragma once
#include <utility>

namespace MetaModule::ExpanderHookup
{

// Wiring and message-flipping for VCV-style expander modules.
// M is any type with the expander shape of rack::engine::Module:
// id, leftExpander/rightExpander (module, moduleId, producerMessage,
// consumerMessage, messageFlipRequested), and onExpanderChange(ExpanderChangeEvent).
// Templated so the logic can be unit-tested without constructing rack modules.

// Attach `right` as the right-side expander of `left` (and vice versa),
// then notify both modules. Each side of a module can only have one expander.
template<typename M>
bool connect(M *left, M *right) {
	if (!left || !right || left == right)
		return false;

	if (left->rightExpander.module || right->leftExpander.module)
		return false;

	left->rightExpander.module = right;
	left->rightExpander.moduleId = right->id;
	right->leftExpander.module = left;
	right->leftExpander.moduleId = left->id;

	left->onExpanderChange({.side = 1});
	right->onExpanderChange({.side = 0});
	return true;
}

// Swap producer/consumer messages if a flip was requested.
// VCV Rack runs this for every module after all modules have processed a frame.
template<typename M>
void flip_messages(M *m) {
	if (m->leftExpander.messageFlipRequested) {
		std::swap(m->leftExpander.producerMessage, m->leftExpander.consumerMessage);
		m->leftExpander.messageFlipRequested = false;
	}
	if (m->rightExpander.messageFlipRequested) {
		std::swap(m->rightExpander.producerMessage, m->rightExpander.consumerMessage);
		m->rightExpander.messageFlipRequested = false;
	}
}

} // namespace MetaModule::ExpanderHookup
