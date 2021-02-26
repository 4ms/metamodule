#include "patch.hh"
static const Patch Example1 = { 
    .modules_used = {
        "PANEL_8",
        "REVERB",
        "REVERB",
    },
    .num_modules = 3,

    .module_nodes = {{
        // PANEL_8
        {1, 2, 1, 2, 255, 254, 253, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // REVERB
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // REVERB
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
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
                {.module_id = 0, .jack_id = 1},
                {.module_id = 1, .jack_id = 0},
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
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 1},
            }},
        },
    }},
    .num_nets = 4,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.315000f},
        {.module_id = 1, .param_id = 1, .value = 0.346500f},
        {.module_id = 1, .param_id = 2, .value = 0.472500f},
        {.module_id = 1, .param_id = 3, .value = 0.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.201000f},
        {.module_id = 2, .param_id = 1, .value = 0.184500f},
        {.module_id = 2, .param_id = 2, .value = 0.168000f},
        {.module_id = 2, .param_id = 3, .value = 0.000000f},
    }},
    .num_static_knobs = 8,

    .mapped_knobs = {{
        {.module_id = 2, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 2, .param_id = 3, .panel_knob_id = 1},
        {.module_id = 2, .param_id = 1, .panel_knob_id = 2},
        {.module_id = 2, .param_id = 2, .panel_knob_id = 3},
        {.module_id = 1, .param_id = 0, .panel_knob_id = 4},
        {.module_id = 1, .param_id = 3, .panel_knob_id = 5},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 6},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
