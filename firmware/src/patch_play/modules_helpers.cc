#include "modules_helpers.hh"
#include "util/overloaded.hh"

namespace MetaModule
{

std::optional<float> get_normalized_default_value(Element const &element) {
	// clang-format off
	return std::visit(overloaded{
			[](BaseElement const &el) { 
				return std::optional<float>{}; 
			},

			[&]<typename T>(T const &el)
				requires(std::derived_from<T, AltParamChoice> || std::derived_from<T, Switch>)
			{ 
				return std::optional<float>{el.num_pos > 0 ? (float)el.default_value / (float)el.num_pos : 0};
			},

			[&]<typename T>(T const &el)
			// If it's AltParamContinuous or regular Param that's not an AltParamChoice or Switch
				requires(std::derived_from<T, AltParamContinuous> ||
						 (std::derived_from<T, ParamElement> && !std::derived_from<T, Switch> && !std::derived_from<T, AltParamChoice>))
			{ 
				return std::optional<float>((float)el.default_value); 
			},
		},
		element);
	// clang-format on
}

} // namespace MetaModule
