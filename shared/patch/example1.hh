#include "patch.hh"
static const Patch Example1 = { 
    .modules_used = {
        "PANEL_8",
        "PITCHSHIFT",
        "PITCHSHIFT",
        "LFOSINE",
        "LFOSINE",
    },
    .num_modules = 5,

    .module_nodes = {{
        // PANEL_8
        {4, 6, 3, 5, 255, 254, 253, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // PITCHSHIFT
        {3, 1, 251, 250, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // PITCHSHIFT
        {5, 2, 249, 248, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {247, 246, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {245, 244, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 4, .jack_id = 0},
                {.module_id = 1, .jack_id = 1},
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
                {.module_id = 0, .jack_id = 0},
                {.module_id = 1, .jack_id = 0},
            }},
        },
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
                {.module_id = 0, .jack_id = 1},
                {.module_id = 2, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 1},
            }},
        },
    }},
    .num_nets = 6,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.500000f},
        {.module_id = 1, .param_id = 1, .value = 0.200000f},
        {.module_id = 1, .param_id = 2, .value = 0.645000f},
        {.module_id = 1, .param_id = 3, .value = 0.420000f},
        {.module_id = 2, .param_id = 0, .value = 0.500000f},
        {.module_id = 2, .param_id = 1, .value = 0.200000f},
        {.module_id = 2, .param_id = 2, .value = 0.295500f},
        {.module_id = 2, .param_id = 3, .value = 0.540000f},
        {.module_id = 3, .param_id = 0, .value = 0.000000f},
        {.module_id = 3, .param_id = 1, .value = 0.000000f},
        {.module_id = 3, .param_id = 2, .value = 1.000000f},
        {.module_id = 4, .param_id = 0, .value = 0.000000f},
        {.module_id = 4, .param_id = 1, .value = 0.523000f},
        {.module_id = 4, .param_id = 2, .value = 0.723000f},
    }},
    .num_static_knobs = 14,

    .mapped_knobs = {{
    }},
    .num_mapped_knobs = 0,

};
