#include "CoreModules/elements/base_element.hh"
#include "CoreModules/elements/units.hh"
#include <string_view>
#include <widget/Widget.hpp>

namespace MetaModule
{

void assign_element_fields(rack::widget::Widget *widget, std::string_view name) {
	std::visit(
		[&name, &widget](BaseElement &el) {
			el.x_mm = to_mm(widget->box.pos.x);
			el.y_mm = to_mm(widget->box.pos.y);
			el.width_mm = to_mm(widget->box.size.x);
			el.height_mm = to_mm(widget->box.size.y);
			el.coords = Coords::TopLeft;
			el.short_name = name;
			el.long_name = name;
		},
		widget->element);
}

} // namespace MetaModule
