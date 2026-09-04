#pragma once
#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

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

// Detach the pair (left <-> right) if they are connected that way, then notify both.
template<typename M>
bool disconnect_pair(M *left, M *right) {
	if (!left || !right)
		return false;

	if (left->rightExpander.module != right || right->leftExpander.module != left)
		return false;

	left->rightExpander.module = nullptr;
	left->rightExpander.moduleId = -1;
	right->leftExpander.module = nullptr;
	right->leftExpander.moduleId = -1;
	left->onExpanderChange({.side = 1});
	right->onExpanderChange({.side = 0});
	return true;
}

// Detach `m` from its neighbors on both sides, then notify every module
// whose connection changed. Safe to call on unconnected or null modules.
template<typename M>
void disconnect(M *m) {
	if (!m)
		return;

	disconnect_pair(m->leftExpander.module, m);
	disconnect_pair(m, m->rightExpander.module);
}

// Swap producer/consumer messages on one side, if a flip was requested.
template<typename Expander>
bool flip_side(Expander &side) {
	if (!side.messageFlipRequested)
		return false;

	std::swap(side.producerMessage, side.consumerMessage);
	side.messageFlipRequested = false;
	return true;
}

// Swap producer/consumer messages if a flip was requested.
// VCV Rack runs this for every module after all modules have processed a frame.
template<typename M>
void flip_messages(M *m) {
	flip_side(m->leftExpander);
	flip_side(m->rightExpander);
}

// Tracks live expander pairs by pointer, so connections survive the
// re-numbering of module indices when unrelated modules are added or removed.
// Only the pairs that actually change are connected/disconnected (and notified).
template<typename M>
class Connections {
public:
	struct Pair {
		M *left{};
		M *right{};
		// Set once a message flip has been requested across this pair,
		// i.e. the two modules recognized each other and are exchanging data.
		// Written on the audio thread, read on the GUI thread: a bool is
		// atomic on all targets we build for.
		bool active{};
	};

	void reserve(size_t max_pairs) {
		pairs.reserve(max_pairs);
	}

	bool connect(M *left, M *right) {
		if (find(left, right) != pairs.end())
			return false;

		if (!ExpanderHookup::connect(left, right))
			return false;

		pairs.push_back({left, right, false});
		return true;
	}

	bool disconnect_pair(M *left, M *right) {
		auto p = find(left, right);
		if (p == pairs.end())
			return false;

		pairs.erase(p);
		return ExpanderHookup::disconnect_pair(left, right);
	}

	// Disconnect every pair that `m` belongs to
	void disconnect(M *m) {
		if (!m)
			return;
		disconnect_pair(m->leftExpander.module, m);
		disconnect_pair(m, m->rightExpander.module);
	}

	void disconnect_all() {
		for (auto &p : pairs)
			ExpanderHookup::disconnect_pair(p.left, p.right);
		pairs.clear();
	}

	// Forget all pairs without touching the modules (e.g. when they are already destroyed)
	void clear() {
		pairs.clear();
	}

	// Call once per sample after all modules have been stepped
	void flip_messages() {
		for (auto &p : pairs) {
			// Messages from right->left land in left->rightExpander, and vice-versa
			bool flipped = flip_side(p.left->rightExpander);
			flipped |= flip_side(p.right->leftExpander);
			if (flipped)
				p.active = true;
		}
	}

	bool is_connected(M const *left, M const *right) const {
		return find(left, right) != pairs.end();
	}

	bool is_active(M const *left, M const *right) const {
		auto p = find(left, right);
		return p != pairs.end() && p->active;
	}

	size_t num_connections() const {
		return pairs.size();
	}

private:
	auto find(M const *left, M const *right) {
		return std::ranges::find_if(pairs, [=](Pair const &p) { return p.left == left && p.right == right; });
	}
	auto find(M const *left, M const *right) const {
		return std::ranges::find_if(pairs, [=](Pair const &p) { return p.left == left && p.right == right; });
	}

	std::vector<Pair> pairs;
};

} // namespace MetaModule::ExpanderHookup
