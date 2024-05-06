#pragma once

#include <cstdint>

#include "pingable_env.h"
#include "flash_user.hh"
#include "analog_conditioning.h"
#include "dig_inout_pins.hh"

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

private:
    DigIO digio;

private:
    void condition_analog(void);
    void init_analog_conditioning(void);
    void setup_fir_lpf(void);

    uint16_t adc_dma_buffer[NUM_ADCS];

};

    void main();
}