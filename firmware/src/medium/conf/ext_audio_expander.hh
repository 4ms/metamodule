#include <array>
#include <cstdint>

namespace MetaModule::AudioExpander
{

static constexpr std::array<uint32_t, 6> in_order{0, 1, 2, 3, 4, 5};
static constexpr std::array<uint32_t, 8> out_order{0, 2, 3, 4, 1, 5, 6, 7};

} // namespace MetaModule::AudioExpander
