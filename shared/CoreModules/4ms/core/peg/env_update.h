/*
 * env_update.h
 */
#pragma once
#include "pingable_env.h"

void update_all_envelopes();
void update_envelope(PingableEnvelope *e);
void stop_envelope(struct PingableEnvelope *e);
void start_envelope(struct PingableEnvelope *e);
void check_restart_async_env(struct PingableEnvelope *e);
void sync_env_to_clk(struct PingableEnvelope *e);
uint8_t resync_on_ping(struct PingableEnvelope *e);
