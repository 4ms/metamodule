/*
 * envelope_calcs.h
 */

#pragma once

#include "pingable_env.h"
#include <stdint.h>

namespace MetaModule::PEG
{

enum ShapeRegions {
	RAMPUP_EXP2LIN,
	RAMPUP2SYM_LIN2EXP,
	SYM_EXP2LOG,
	SYM2RAMPDOWN_LOG2LIN,
	RAMPDOWN_EXP2LIN,

	NUM_SHAPE_REGIONS
};
enum PureSkews { RAMPUP = 0, SYM = 127, RAMPDOWN = 255 };
enum PureCurves { EXPO = 0, LIN = 127, LOG = 255 };

} // namespace MetaModule::PEG
