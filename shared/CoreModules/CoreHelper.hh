#pragma once
#include "CoreModules/elements/element_counter.hh"

namespace MetaModule
{

template<typename INFO>
struct CoreHelper {
	using Elem = typename INFO::Elem;

	constexpr static auto indices = ElementCount::get_indices<INFO>();

	constexpr static auto element_index(Elem el) {
		return static_cast<std::underlying_type_t<Elem>>(el);
	}

	constexpr static ElementCount::Counts count(Elem el) {
		auto element_idx = element_index(el);
		return ElementCount::count(INFO::Elements[element_idx]);
	}

	constexpr static ElementCount::Indices index(Elem el) {
		return indices[element_index(el)];
	}
	template<Elem EL>
	static constexpr uint8_t param_index() requires(count(EL).num_params > 0)
	{
		return indices[element_index(EL)].param_idx;
	}

	template<Elem EL>
	static constexpr uint8_t input_index() requires(count(EL).num_inputs > 0)
	{
		return indices[element_index(EL)].input_idx;
	}

	template<Elem EL>
	static constexpr uint8_t output_index() requires(count(EL).num_outputs > 0)
	{
		return indices[element_index(EL)].output_idx;
	}

	template<Elem EL>
	static constexpr uint8_t first_light_index() requires(count(EL).num_lights > 0)
	{
		return indices[element_index(EL)].light_idx;
	}
};

} // namespace MetaModule
