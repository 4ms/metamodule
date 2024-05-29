#pragma once
#include "CoreModules/elements/elements.hh"
#include <optional>

namespace MetaModule
{

// Returns default value of param, normalized to 0..1
std::optional<float> get_normalized_default_value(Element const &element);

} // namespace MetaModule
