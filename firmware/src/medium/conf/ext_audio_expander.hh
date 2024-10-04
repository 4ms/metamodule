#include <array>
#include <cstdint>
#include <string_view>

namespace MetaModule::AudioExpander
{
static constexpr uint32_t NumInJacks = 8;
static constexpr uint32_t NumUserFacingInJacks = NumInJacks;

static constexpr std::array<uint32_t, 6> in_order{0, 1, 2, 3, 4, 5};

static constexpr std::array<std::string_view, NumUserFacingInJacks> InJackNames{
	"Out9", "Out10", "Out11", "Out12", "Out13", "Out14"};

static constexpr std::array<std::string_view, NumUserFacingInJacks> InJackAbbrevs{"9", "10", "11", "12", "13", "14"};

static constexpr std::string_view get_map_injack_name(uint32_t id) {
	if (id < InJackNames.size())
		return InJackNames[id];
	return "?";
}

static constexpr std::array<uint32_t, 8> out_order{0, 4, 6, 7, 5, 3, 1, 2};

static constexpr uint32_t NumOutJacks = 8;
static constexpr uint32_t NumUserFacingOutJacks = NumOutJacks;

static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackNames{
	"Out9", "Out10", "Out11", "Out12", "Out13", "Out14", "Out15", "Out16"};

static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackAbbrevs{
	"9", "10", "11", "12", "13", "14", "15", "16"};

static constexpr std::string_view get_map_outjack_name(uint32_t id) {
	if (id < OutJackNames.size())
		return OutJackNames[id];
	return "?";
}

} // namespace MetaModule::AudioExpander
