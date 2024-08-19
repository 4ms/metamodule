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
				return std::optional<float>{el.num_pos > 0 ? (float)el.DefaultValue / (float)el.num_pos : 0};
			},

			[&]<typename T>(T const &el)
				requires(std::derived_from<T, AltParamContinuous> ||
						 (std::derived_from<T, ParamElement> && !std::derived_from<T, Switch>))
			{ 
				return std::optional<float>((float)el.DefaultValue); 
			},
		},
		element);
// clang-format on
}

} // namespace MetaModule
