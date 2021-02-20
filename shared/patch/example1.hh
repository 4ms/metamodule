#include "patch.hh"
static const Patch Example1 = { 
    .modules_used = {
        "PANEL_8",
        "FMOSC",
        "LFOSINE",
    },
    .num_modules = 3,

    .module_nodes = {{
        // PANEL_8
        {1, 2, 3, 255, 4, 1, 5, 254, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // FMOSC
        {1, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {3, 253, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 0},
                {.module_id = 2, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 2},
                {.module_id = 1, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 3},
                {.module_id = 1, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 4},
                {.module_id = 1, .jack_id = 2},
            }},
        },
    }},
    .num_nets = 6,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.000000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 1, .param_id = 3, .value = 0.000000f},
        {.module_id = 1, .param_id = 4, .value = 0.000000f},
        {.module_id = 1, .param_id = 5, .value = 1.000000f},
        {.module_id = 1, .param_id = 6, .value = 1.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.393000f},
        {.module_id = 2, .param_id = 1, .value = 0.531000f},
        {.module_id = 2, .param_id = 2, .value = 1.000000f},
    }},
    .num_static_knobs = 10,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 2},
        {.module_id = 1, .param_id = 3, .panel_knob_id = 3},
        {.module_id = 1, .param_id = 4, .panel_knob_id = 4},
        {.module_id = 2, .param_id = 2, .panel_knob_id = 7},
        {.module_id = 2, .param_id = 1, .panel_knob_id = 6},
        {.module_id = 2, .param_id = 0, .panel_knob_id = 5},
    }},
    .num_mapped_knobs = 8,

};
