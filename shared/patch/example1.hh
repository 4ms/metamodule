#include "patch.hh"
static const Patch Example1 = { 
    .modules_used = {
        "PANEL_8",
        "SEND_1TO4",
        "MIXER4",
        "REVERB",
        "FADEDELAY",
    },
    .num_modules = 5,

    .module_nodes = {{
        // PANEL_8
        {4, 255, 1, 254, 253, 252, 251, 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // SEND_1TO4
        {1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // MIXER4
        {1, 2, 3, 249, 248, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // REVERB
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // FADEDELAY
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 2, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 2, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 4, .jack_id = 0},
                {.module_id = 2, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 1},
                {.module_id = 3, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 2},
                {.module_id = 4, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 0},
                {.module_id = 1, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 1},
                {.module_id = 0, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 7,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 1.000000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 1, .param_id = 3, .value = 0.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.330000f},
        {.module_id = 2, .param_id = 1, .value = 0.330000f},
        {.module_id = 2, .param_id = 2, .value = 0.330000f},
        {.module_id = 2, .param_id = 3, .value = 0.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.562500f},
        {.module_id = 3, .param_id = 1, .value = 0.445500f},
        {.module_id = 3, .param_id = 2, .value = 1.000000f},
        {.module_id = 3, .param_id = 3, .value = 0.631500f},
        {.module_id = 3, .param_id = 4, .value = 0.415500f},
        {.module_id = 3, .param_id = 5, .value = 0.424500f},
        {.module_id = 4, .param_id = 0, .value = 0.190500f},
        {.module_id = 4, .param_id = 1, .value = 0.778500f},
        {.module_id = 4, .param_id = 2, .value = 0.261000f},
        {.module_id = 4, .param_id = 3, .value = 1.000000f},
        {.module_id = 4, .param_id = 4, .value = 0.000000f},
    }},
    .num_static_knobs = 19,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 1, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 1},
        {.module_id = 4, .param_id = 0, .panel_knob_id = 2},
        {.module_id = 4, .param_id = 1, .panel_knob_id = 3},
        {.module_id = 3, .param_id = 0, .panel_knob_id = 4},
        {.module_id = 3, .param_id = 3, .panel_knob_id = 5},
        {.module_id = 3, .param_id = 1, .panel_knob_id = 6},
        {.module_id = 3, .param_id = 4, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
