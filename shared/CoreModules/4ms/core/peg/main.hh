#pragma once

#include <cstdint>

#include "pingable_env.h"
#include "flash_user.hh"
#include "analog_conditioning.h"
#include "dig_inout_pins.hh"
#include "pwm.h"
#include "dac.h"

namespace MetaModule::PEG
{

struct MiniPEG
{
public:
    MiniPEG();

    void update();

private:
    void read_ping_button();
    void read_trigjacks();
    void read_cycle_button();
    void check_reset_envelopes();
    void update_tap_clock();
    void update_trigout();
    void read_ping_clock();
    void ping_led_off();
    void ping_led_on();
    void handle_qnt_trig(PingableEnvelope*);
    void handle_async_trig(PingableEnvelope*);

private:
    PingableEnvelope m;

    uint32_t ping_irq_timestamp = 0;
    uint32_t trig_irq_timestamp = 0;

    uint32_t last_tapin_time = 0;
    uint32_t tapout_clk_time = 0;

    uint32_t clk_time = 0;

    uint8_t cycle_but_on = 0;

    uint8_t using_tap_clock = 0;
    uint8_t do_toggle_cycle = 0;

    uint8_t force_params_update = 0;

    char div_ping_led = 0;
    char got_tap_clock = 0;

    uint32_t entering_system_mode = 0;
    uint8_t system_mode_cur = 0;
    uint8_t initial_cycle_button_state = 0;
    char update_cycle_button_now = 0;

    bool adjusting_shift_mode = false;
    bool toggled_sync_mode = false;
    int16_t cycle_latched_offset;

private:
    struct SystemSettings settings;

    analog_t analog[NUM_ADCS];
    uint32_t systmr;
    uint32_t tapouttmr;
    uint32_t tapintmr;
    uint32_t pingtmr;
    uint32_t trigouttmr;

private:
    // from trigout.hh
    void eor_on();
    void eor_off();
    void eof_on();
    void eof_off();
    void hr_on();
    void hr_off();
    void tapclkout_off();
    void tapclkout_on();
    void handle_trigout_trigfall();
    void clockbus_on();
    void clockbus_off();

    void trigout_on();
    void trigout_off();

    uint8_t trigout_high = 0;

public:
    // for sideloading
    DigIO digio;

private:
    void condition_analog(void);
    void init_analog_conditioning(void);
    void setup_fir_lpf(void);

public:
    // for sideloading
    uint16_t adc_dma_buffer[NUM_ADCS];

private:
    void init_pwm();
    void update_pwm(uint32_t pwmval, enum PwmOutputs channel);

public:
    // for sideloading
    uint32_t pwm_vals[NUM_PWMS];

private:
    void dac_out(enum DACs dac, uint16_t val);

public:
    // for sideloading
    uint16_t dac_vals[2];

public:
    // call this with dac sample rate
    static const uint32_t kDacSampleRate = 40000;
    void update_all_envelopes();

private:
    void update_envelope(PingableEnvelope *e);
    void stop_envelope(struct PingableEnvelope *e);
    void start_envelope(struct PingableEnvelope *e);
    void check_restart_async_env(struct PingableEnvelope *e);
    void sync_env_to_clk(struct PingableEnvelope *e);
    uint8_t resync_on_ping(struct PingableEnvelope *e);

    void do_reset_envelope(PingableEnvelope *e);
    void output_env_val(uint16_t rawA);
    void handle_env_segment_end(PingableEnvelope *e, envelopeStates end_segment_flag);
    void handle_env_end(PingableEnvelope *e, uint8_t end_env_flag);
    void start_envelope_in_sync(PingableEnvelope *e);
    void start_envelope_immediate(PingableEnvelope *e);
    int32_t scale_shift_offset_env(uint16_t raw_env_val);

    bool system_mode_active;
    int32_t scale;
    int32_t offset;
    int32_t shift;

private:
    int8_t get_clk_div_nominal(uint16_t adc_val);
    uint32_t get_clk_div_time(int8_t clock_divide_amount, uint32_t clk_time);
    uint32_t get_fall_time(uint8_t skew, uint32_t div_clk_time);
    int16_t calc_curve(int16_t t_dacout, uint8_t cur_curve);
    void calc_skew_and_curves(uint16_t shape, uint8_t *skew, uint8_t *next_curve_rise, uint8_t *next_curve_fall);
    void calc_rise_fall_incs(struct PingableEnvelope *e);
    void calc_div_clk_time(struct PingableEnvelope *e, uint32_t new_clk_time);

};

}