#include "patch.hh"
static const Patch Example1 = { 
    .modules_used = {
        "PANEL_8",
        "DETUNE",
        "FREQSHIFT",
    },
    .num_modules = 3,

    .module_nodes = {{
        // PANEL_8
        {2, 1, 2, 1, 255, 254, 253, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DETUNE
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // FREQSHIFT
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 1},
                {.module_id = 1, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 0},
                {.module_id = 2, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 4,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.346500f},
        {.module_id = 1, .param_id = 1, .value = 0.564000f},
        {.module_id = 1, .param_id = 2, .value = 0.261000f},
        {.module_id = 1, .param_id = 3, .value = 0.579000f},
        {.module_id = 2, .param_id = 0, .value = 0.285000f},
        {.module_id = 2, .param_id = 1, .value = 0.157500f},
        {.module_id = 2, .param_id = 2, .value = 0.291000f},
    }},
    .num_static_knobs = 7,

    .mapped_knobs = {{
        {.module_id = 2, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 2, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 2, .param_id = 2, .panel_knob_id = 2},
        {.module_id = 1, .param_id = 0, .panel_knob_id = 3},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 4},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 5},
        {.module_id = 1, .param_id = 3, .panel_knob_id = 6},
    }},
    .num_mapped_knobs = 7,

};
