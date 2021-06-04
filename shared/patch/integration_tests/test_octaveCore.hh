#include "patch.hh"
static const Patch test_octaveCore = { 
    .patch_name = "test_octaveCore",
    .modules_used = {
        "PANEL_8",
        "OCTAVE",
        "VOLTAGESOURCE",
    },
    .num_modules = 3,

    .module_nodes = {{
        // PANEL_8
        {255, 254, 1, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // OCTAVE
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // VOLTAGESOURCE
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 1, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 1},
                {.module_id = 1, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 2},
            }},
        },
    }},
    .num_nets = 3,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.004500f},
        {.module_id = 2, .param_id = 0, .value = 0.000000f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
    }},
    .num_static_knobs = 3,

    .mapped_knobs = {{
        {.module_id = 2, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 0, .panel_knob_id = 1},
        {.module_id = 2, .param_id = 1, .panel_knob_id = 2},
    }},
    .num_mapped_knobs = 3,

};
