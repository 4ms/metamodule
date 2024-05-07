#include "main.hh"
#include "envelope_calcs.h"
#include "log4096.h"
#include "util/math.hh"
#include "settings.h"
#include <array>

namespace MetaModule::PEG
{


struct PEGEnvelopeCalcs
{

static constexpr unsigned NUM_DIVMULTS = 15;
static constexpr int8_t P_array[NUM_DIVMULTS] = {8, 7, 6, 5, 4, 3, 2, 1, -2, -3, -4, -5, -6, -7, -8};
static constexpr int16_t midpt_array[NUM_DIVMULTS] = {273, 546, 819, 1092, 1365, 1638, 1911,
												2184, 2457, 2730, 3003, 3276, 3549, 3822, 4095};

// shape: 0..4095 (adc value)
// returns skew: 0..255
// returns next_curve_rise and _fall: 0..255: expo/linear/log
void calc_skew_and_curves(uint16_t shape, uint8_t *skew, uint8_t *next_curve_rise, uint8_t *next_curve_fall) {
	//TODO (copy from PEG)
	*skew = 127;
	*next_curve_rise = 127;
	*next_curve_fall = 127;
}

};

}
