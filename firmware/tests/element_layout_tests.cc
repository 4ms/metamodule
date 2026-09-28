#include "CoreModules/moduleFactory.hh"
#include "doctest.h"
#include "gui/pages/module_view/element_layout.hh"
#include <vector>

using namespace MetaModule;

namespace
{

constexpr auto NoIdx = ElementCount::Indices::NoElementMarker;

template<typename T>
Element named(std::string_view name) {
	T el{};
	el.short_name = name;
	return el;
}

// Red Speed (param 0), Red Size (param 1), Clock In (input 0), Out (output 0)
std::vector<Element> const elements{
	named<Knob>("Red Speed"),
	named<Knob>("Red Size"),
	named<JackInput>("Clock In"),
	named<JackOutput>("Out"),
};

std::vector<DrawnElement> drawn_elements() {
	std::vector<DrawnElement> drawn;
	auto add = [&](unsigned el, ElementCount::Indices idx) {
		GuiElement gui_el;
		gui_el.idx = idx;
		drawn.push_back({.gui_element = gui_el, .element = elements[el]});
	};
	add(0, {.param_idx = 0, .light_idx = NoIdx, .input_idx = NoIdx, .output_idx = NoIdx});
	add(1, {.param_idx = 1, .light_idx = NoIdx, .input_idx = NoIdx, .output_idx = NoIdx});
	add(2, {.param_idx = NoIdx, .light_idx = NoIdx, .input_idx = 0, .output_idx = NoIdx});
	add(3, {.param_idx = NoIdx, .light_idx = NoIdx, .input_idx = NoIdx, .output_idx = 0});
	return drawn;
}

// Each test case registers its own module, so they don't share groups/order/names
void register_module(std::string_view slug,
					 std::vector<ElementGroup> groups,
					 std::vector<ElementRef> order,
					 std::vector<ElementName> names) {
	ModuleFactory::registerModuleType("LayoutTest", slug, [] { return std::unique_ptr<CoreProcessor>{}; }, {}, "");
	ModuleFactory::setElementGroups("LayoutTest", slug, std::move(groups));
	ModuleFactory::setElementOrder("LayoutTest", slug, std::move(order));
	ModuleFactory::setElementNames("LayoutTest", slug, std::move(names));
}

ElementRef ref(std::string_view token) {
	return ElementRef::parse(token);
}

} // namespace

TEST_CASE("Element layout: valid groups, order, and names have no errors") {
	register_module("Valid",
					{{"Red", {ref("Red Speed"), ref("param:1")}}},
					{ref("Clock"), ref("Red")}, // "Clock" matches "Clock In"
					{{ref("Out"), "Main"}});

	ElementLayout layout;
	layout.build("LayoutTest:Valid", drawn_elements());

	CHECK(layout.errors.empty());

	REQUIRE(layout.group_names.size() == 1);
	CHECK(layout.group_names[0] == "Red");
	CHECK(layout.group_members[0] == std::vector<unsigned>{0, 1});

	// Order first (Clock In, then Red), then everything else in panel order
	REQUIRE(layout.top_level_entries.size() == 3);
	CHECK(!layout.top_level_entries[0].is_group);
	CHECK(layout.top_level_entries[0].idx == 2);
	CHECK(layout.top_level_entries[1].is_group);
	CHECK(layout.top_level_entries[1].idx == 0);
	CHECK(!layout.top_level_entries[2].is_group);
	CHECK(layout.top_level_entries[2].idx == 3);

	CHECK(layout.element_display_name[3] == "Main");
	CHECK(layout.element_display_name[0].empty());
}

TEST_CASE("Element layout: every kind of mistake is an error") {
	register_module("Mistakes",
					{{"Red", {ref("Red Speed"), ref("Missing")}}},
					{ref("in:5"), ref("Red Speed")},
					{{ref("Nope"), "X"}, {ref("Out"), "Main"}, {ref("out:0"), "Again"}});

	ElementLayout layout;
	layout.build("LayoutTest:Mistakes", drawn_elements());

	CHECK(layout.errors == std::vector<std::string>{
							   "group 'Red' has no element 'Missing'",
							   "names: 'Nope' is unknown",
							   "names: 'out:0' appears more than once",
							   "order: 'in:5' is unknown",
							   "order: Red Speed is already in group 'Red'",
						   });

	// The mistakes are skipped, and the rest still works
	CHECK(layout.group_members[0] == std::vector<unsigned>{0});
	CHECK(layout.element_display_name[3] == "Main");
}

TEST_CASE("Element layout: a module without groups, order, or names lists every element") {
	register_module("Plain", {}, {}, {});

	ElementLayout layout;
	layout.build("LayoutTest:Plain", drawn_elements());

	CHECK(layout.errors.empty());
	CHECK(layout.group_names.empty());
	CHECK(layout.top_level_entries.size() == 4);
}
