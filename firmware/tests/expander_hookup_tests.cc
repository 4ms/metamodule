#include "doctest.h"
#include "patch_play/expander_hookup.hh"
#include <vector>

namespace
{

// Mirrors the expander-related shape of rack::engine::Module
struct FakeRackModule {
	struct Expander {
		int64_t moduleId = -1;
		FakeRackModule *module = nullptr;
		void *producerMessage = nullptr;
		void *consumerMessage = nullptr;
		bool messageFlipRequested = false;
	};
	struct ExpanderChangeEvent {
		uint8_t side;
	};

	int64_t id = -1;
	Expander leftExpander;
	Expander rightExpander;

	std::vector<uint8_t> change_events;
	void onExpanderChange(const ExpanderChangeEvent &e) {
		change_events.push_back(e.side);
	}
};

} // namespace

using namespace MetaModule;

TEST_CASE("expander connect: sets pointers and ids on both sides") {
	FakeRackModule a, b;
	a.id = 1;
	b.id = 2;

	bool ok = ExpanderHookup::connect(&a, &b);

	CHECK(ok);
	CHECK(a.rightExpander.module == &b);
	CHECK(a.rightExpander.moduleId == 2);
	CHECK(b.leftExpander.module == &a);
	CHECK(b.leftExpander.moduleId == 1);
	// Unrelated sides untouched
	CHECK(a.leftExpander.module == nullptr);
	CHECK(b.rightExpander.module == nullptr);
}

TEST_CASE("expander connect: fires onExpanderChange with correct sides") {
	FakeRackModule a, b;
	a.id = 1;
	b.id = 2;

	ExpanderHookup::connect(&a, &b);

	// a's right side changed (side=1), b's left side changed (side=0)
	REQUIRE(a.change_events.size() == 1);
	CHECK(a.change_events[0] == 1);
	REQUIRE(b.change_events.size() == 1);
	CHECK(b.change_events[0] == 0);
}

TEST_CASE("expander connect: rejects null and self-connections") {
	FakeRackModule a;
	a.id = 1;

	CHECK_FALSE(ExpanderHookup::connect<FakeRackModule>(nullptr, &a));
	CHECK_FALSE(ExpanderHookup::connect<FakeRackModule>(&a, nullptr));
	CHECK_FALSE(ExpanderHookup::connect(&a, &a));
	CHECK(a.change_events.empty());
}

TEST_CASE("expander connect: rejects duplicate side connections") {
	FakeRackModule a, b, c;
	a.id = 1;
	b.id = 2;
	c.id = 3;

	CHECK(ExpanderHookup::connect(&a, &b));
	// a already has a right expander:
	CHECK_FALSE(ExpanderHookup::connect(&a, &c));
	// b already has a left expander:
	CHECK_FALSE(ExpanderHookup::connect(&c, &b));

	CHECK(a.rightExpander.module == &b);
	CHECK(b.leftExpander.module == &a);
	CHECK(c.leftExpander.module == nullptr);
	CHECK(c.rightExpander.module == nullptr);
}

TEST_CASE("expander connect: daisy chain") {
	FakeRackModule a, b, c;
	a.id = 1;
	b.id = 2;
	c.id = 3;

	CHECK(ExpanderHookup::connect(&a, &b));
	CHECK(ExpanderHookup::connect(&b, &c));

	CHECK(b.leftExpander.module == &a);
	CHECK(b.rightExpander.module == &c);
	CHECK(a.rightExpander.module == &b);
	CHECK(c.leftExpander.module == &b);
}

TEST_CASE("expander disconnect: detaches from both neighbors and notifies all") {
	FakeRackModule a, b, c;
	a.id = 1;
	b.id = 2;
	c.id = 3;
	ExpanderHookup::connect(&a, &b);
	ExpanderHookup::connect(&b, &c);
	a.change_events.clear();
	b.change_events.clear();
	c.change_events.clear();

	ExpanderHookup::disconnect(&b);

	CHECK(a.rightExpander.module == nullptr);
	CHECK(a.rightExpander.moduleId == -1);
	CHECK(c.leftExpander.module == nullptr);
	CHECK(c.leftExpander.moduleId == -1);
	CHECK(b.leftExpander.module == nullptr);
	CHECK(b.rightExpander.module == nullptr);

	// a's right side changed, c's left side changed, b lost both sides
	REQUIRE(a.change_events.size() == 1);
	CHECK(a.change_events[0] == 1);
	REQUIRE(c.change_events.size() == 1);
	CHECK(c.change_events[0] == 0);
	CHECK(b.change_events.size() == 2);
}

TEST_CASE("expander disconnect: safe on null and unconnected modules") {
	FakeRackModule a;
	a.id = 1;

	ExpanderHookup::disconnect<FakeRackModule>(nullptr);
	ExpanderHookup::disconnect(&a);

	CHECK(a.change_events.empty());
	CHECK(a.leftExpander.module == nullptr);
	CHECK(a.rightExpander.module == nullptr);
}

TEST_CASE("flip_messages: swaps producer/consumer when requested and clears flag") {
	FakeRackModule a;
	int buf0 = 0, buf1 = 1;
	a.leftExpander.producerMessage = &buf0;
	a.leftExpander.consumerMessage = &buf1;
	a.leftExpander.messageFlipRequested = true;

	ExpanderHookup::flip_messages(&a);

	CHECK(a.leftExpander.producerMessage == &buf1);
	CHECK(a.leftExpander.consumerMessage == &buf0);
	CHECK_FALSE(a.leftExpander.messageFlipRequested);
}

TEST_CASE("flip_messages: does nothing when not requested") {
	FakeRackModule a;
	int buf0 = 0, buf1 = 1;
	a.rightExpander.producerMessage = &buf0;
	a.rightExpander.consumerMessage = &buf1;

	ExpanderHookup::flip_messages(&a);

	CHECK(a.rightExpander.producerMessage == &buf0);
	CHECK(a.rightExpander.consumerMessage == &buf1);
}

TEST_CASE("flip_messages: handles both sides independently") {
	FakeRackModule a;
	int lbuf0 = 0, lbuf1 = 1, rbuf0 = 2, rbuf1 = 3;
	a.leftExpander.producerMessage = &lbuf0;
	a.leftExpander.consumerMessage = &lbuf1;
	a.leftExpander.messageFlipRequested = true;
	a.rightExpander.producerMessage = &rbuf0;
	a.rightExpander.consumerMessage = &rbuf1;
	a.rightExpander.messageFlipRequested = false;

	ExpanderHookup::flip_messages(&a);

	CHECK(a.leftExpander.producerMessage == &lbuf1);
	CHECK(a.rightExpander.producerMessage == &rbuf0);
}
