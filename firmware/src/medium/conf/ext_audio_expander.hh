#include <array>
#include <cstdint>

namespace MetaModule::AudioExpander
{

static constexpr std::array<uint32_t, 6> in_order{0, 1, 2, 3, 4, 5};
// static constexpr std::array<uint32_t, 8> out_order{0, 7, 8, 5, 1, 4, 2, 3};
static constexpr std::array<uint32_t, 8> out_order{0, 6, 7, 5, 1, 4, 2, 3};
// static constexpr std::array<uint32_t, 8> out_order{0, 4, 6, 7, 5, 3, 1, 2};

//Patching into jack 1 (0), hear panel jack 8 -> 0
//Patching into jack 2 (1), hear Enosc 3 Out A (panel jack 14 -> 6)
//Patching into jack 3 (2), hear Enosc 3 Out B (panel jack 15 -> 7)
//Patching into jack 4 (3), hear Enosc 2 Out B (panel jack 13 -> 5)
//Patching into jack 5 (4), hear panel jack 9 -> 1
//Patching into jack 6 (5), hear Enosc 2 Out A (panel jack 12 -> 4)
//Patching into jack 7 (6), hear Enosc 1 Out A (panel jack 10 -> 2)
//Patching into jack 8 (7), hear Enosc 1 Out B (panel jack 11 -> 3)

} // namespace MetaModule::AudioExpander
