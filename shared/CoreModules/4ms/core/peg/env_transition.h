#pragma once
#include "pingable_env.h"
#include <stdint.h>

void reset_transition_counter();
void force_transition();
bool check_to_start_transition();

void do_start_transition(struct PingableEnvelope *e);
void start_transition(struct PingableEnvelope *e, uint32_t elapsed_time);
