/*
 * system_mode.h
 */

#pragma once

#include <stdint.h>

enum SystemModeParams {
	SET_TRIGIN_FUNCTION,
	SET_CYCLEJACK_FUNCTION,
	SET_TRIGOUT_FUNC,
	SET_TRIGOUT_IS_TRIG,
	SET_FREE_RUNNING_PING,
	SET_LIMIT_SKEW,

	NUM_SYSMODE_PARAMS
};

void handle_system_mode(bool sync_to_ping_mode);
