#pragma once
#include <stdint.h>

enum envelopeStates {
	WAIT = 0,
	RISE = 1,
	SUSTAIN = 2,
	FALL = 3,
	TRANSITION = 4,
};

struct PingableEnvelope {
	volatile uint32_t divpingtmr;
	int8_t ping_div_ctr;
	int8_t clock_divider_amount;
	volatile uint8_t reset_nextping_flag;

	uint32_t div_clk_time;
	uint32_t rise_time;
	uint32_t fall_time;
	uint32_t rise_inc;
	uint32_t fall_inc;

	uint8_t skew;
	uint8_t curve_rise;
	uint8_t curve_fall;
	uint8_t cur_curve;
	uint8_t next_curve_rise;
	uint8_t next_curve_fall;

	//env state
	char envelope_running;
	envelopeStates env_state;
	envelopeStates next_env_state;

	//envelope phase
	uint32_t accum;
	uint16_t segphase;
	uint16_t cur_val;

	//syncing/async to ping
	volatile uint8_t sync_to_ping_mode;
	char reset_now_flag;
	char ready_to_start_async;
	uint32_t async_phase_diff;
	uint8_t async_env_changed_shape;

	//transitioning
	char tracking_changedrisefalls;
	int32_t transition_inc;
	int32_t transition_ctr;
	uint32_t accum_endpoint;
	char outta_sync;

	uint8_t trigq_down;
	uint8_t triga_down;
};

void init_pingable_env(struct PingableEnvelope *e);
void copy_rise_fall_incs(struct PingableEnvelope *dst, struct PingableEnvelope *src);
void copy_skew_and_curves(struct PingableEnvelope *dst, struct PingableEnvelope *src);
