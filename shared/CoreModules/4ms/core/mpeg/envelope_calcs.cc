#include "main.hh"
#include "envelope_calcs.h"
#include "log4096.h"
#include "util/math.hh"
#include "settings.h"
#include <array>

namespace MetaModule::PEG
{

struct MiniPEGEnvelopeCalcs
{

static constexpr unsigned NUM_DIVMULTS = 19;
static constexpr int8_t P_array[NUM_DIVMULTS] = {32, 16, 8, 7, 6, 5, 4, 3, 2, 1, -2, -3, -4, -5, -6, -7, -8, -12, -16};
static constexpr int16_t midpt_array[NUM_DIVMULTS] = {68, 262, 509, 743, 973, 1202, 1427, 1657, 1882, 
												2107, 2341, 2574, 2802, 3026, 3262, 3500, 3734, 3942, 4095};
// shape: 0..4095 (adc value)
// returns skew: 0..255
// returns next_curve_rise and _fall: 0..255: expo/linear/log
void calc_skew_and_curves(uint16_t shape, uint8_t *skew, uint8_t *next_curve_rise, uint8_t *next_curve_fall) {
	if (shape > region_starts.back())
		shape = region_starts.back();
	int i = 1;
	while (shape >= region_starts[i])
		i++;
	uint16_t shape_region = i - 1;

	uint16_t shape_variation = shape - region_starts[shape_region];
	uint32_t var_127 = (shape_variation << 7) / region_sizes[shape_region];

	switch (shape_region) {
		case RAMPUP_EXP2LIN:
			*skew = RAMPUP;
			*next_curve_rise = morph_exp2lin(var_127);
			*next_curve_fall = LIN;
			break;

		case RAMPUP2SYM_LIN2EXP:
			*skew = var_127;
			*next_curve_rise = morph_lin2exp(var_127);
			*next_curve_fall = morph_lin2exp(var_127); //was EXPO
			break;

		case SYM_EXP2LOG:
			*skew = SYM;
			*next_curve_rise = morph_exp2log(var_127);
			*next_curve_fall = morph_exp2log(var_127);
			break;

		case SYM2RAMPDOWN_LOG2LIN:
			*skew = var_127 + 128;
			*next_curve_rise = morph_log2lin(var_127); //255 - var_127 * 2;
			*next_curve_fall = morph_log2lin(var_127);
			break;

		default:
		case RAMPDOWN_EXP2LIN:
			*skew = RAMPDOWN;
			*next_curve_rise = LIN;
			*next_curve_fall = morph_lin2exp(var_127);
			break;
	}
}

constexpr uint32_t morph_exp2lin(uint32_t x) {
	//0..127 => 0..127
	return x;
}
constexpr uint32_t morph_lin2exp(uint32_t x) {
	//0..127 => 127..0
	return 127 - x;
}
constexpr uint32_t morph_exp2log(uint32_t x) {
	//0..127 => 0..255
	return x * 2;
}
constexpr uint32_t morph_log2exp(uint32_t x) {
	//0..127 => 255..0
	return 255 - x * 2;
}
constexpr uint32_t morph_log2lin(uint32_t x) {
	//0..127 => 255..128
	return 255 - x;
}

static constexpr std::array region_starts = {0, 900, 1450, 2645, 3195, 4096};
static constexpr std::array region_sizes = MathTools::array_adj_diff(region_starts);
//{900, 550,...}


};
}
