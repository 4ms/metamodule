#include "doctest.h"
#include "gui/helpers/selected_display.hh"
#include <array>

using namespace MetaModule;

namespace
{

constexpr auto NoIdx = ElementCount::Indices::NoElementMarker;

Element display(std::string_view name, float x, float y, float w, float h, Coords coords = Coords::TopLeft) {
	DynamicGraphicDisplay el{};
	el.short_name = name;
	el.x_mm = x;
	el.y_mm = y;
	el.width_mm = w;
	el.height_mm = h;
	el.coords = coords;
	return el;
}

ElementCount::Indices light(uint16_t idx) {
	return {.param_idx = NoIdx, .light_idx = idx, .input_idx = NoIdx, .output_idx = NoIdx};
}

// Display 0 at (2,10), a tiny display at (20,10), Display 1 at (2,40) given by its center
const std::array<Element, 4> elements{
	display("Display 0", 2, 10, 30, 20),
	Knob{},
	display("Tiny", 20, 10, 2, 2),
	display("Display 1", 17, 50, 30, 20, Coords::Center),
};
const std::array<ElementCount::Indices, 4> indices{light(1024), ElementCount::Indices{}, light(1025), light(1026)};

ModuleInfoView info() {
	return {.width_hp = 10, .elements = elements, .indices = indices};
}

} // namespace

TEST_CASE("find_selected_display_element by light id") {
	CHECK(find_selected_display_element(info(), {.module_id = 1, .light_id = 1026}) == 3u);
	CHECK(find_selected_display_element(info(), {.module_id = 1, .light_id = 1024}) == 0u);

	// Not full-screen capable
	CHECK_FALSE(find_selected_display_element(info(), {.module_id = 1, .light_id = 1025}));
	// Unknown
	CHECK_FALSE(find_selected_display_element(info(), {.module_id = 1, .light_id = 7}));
}

TEST_CASE("find_selected_display_element by position") {
	auto at = [](float x, float y) {
		return SelectedDisplay{.module_id = 1, .position_mm = std::pair{x, y}};
	};

	CHECK(find_selected_display_element(info(), at(2, 10)) == 0u);
	CHECK(find_selected_display_element(info(), at(2.6f, 9.4f)) == 0u);

	// Center coords are compared by their top-left corner (17-15, 50-10)
	CHECK(find_selected_display_element(info(), at(2, 40)) == 3u);

	// More than 1mm away
	CHECK_FALSE(find_selected_display_element(info(), at(3.5f, 10)));

	// A tiny display at that spot is not a candidate
	CHECK_FALSE(find_selected_display_element(info(), at(20, 10)));
}
