#include "patch.hh"
static const Patch Example1 = { 
    .modules_used = {
        "PANEL_8",
        "REVERB",
    },
    .num_modules = 2,

    .module_nodes = {{
        // PANEL_8
        {1, 255, 1, 254, 253, 252, 251, 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // REVERB
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
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
                {.module_id = 0, .jack_id = 0},
                {.module_id = 1, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 2,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.315000f},
        {.module_id = 1, .param_id = 1, .value = 0.346500f},
        {.module_id = 1, .param_id = 2, .value = 0.472500f},
    }},
    .num_static_knobs = 3,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 2},
    }},
    .num_mapped_knobs = 3,

};
