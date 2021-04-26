#include "patch.hh"
static const Patch test_14switchCore_cv = { 
    .patch_name = "test_14switchCore_cv",
    .modules_used = {
        "PANEL_8",
        "SWITCH1TO4",
        "LFOSINE",
        "VOLTAGESOURCE",
    },
    .num_modules = 4,

    .module_nodes = {{
        // PANEL_8
        {1, 2, 3, 4, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // SWITCH1TO4
        {3, 4, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {245, 244, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // VOLTAGESOURCE
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 1, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 1, .jack_id = 3},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 1},
                {.module_id = 0, .jack_id = 3},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 2},
                {.module_id = 0, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 3},
                {.module_id = 0, .jack_id = 1},
            }},
        },
    }},
    .num_nets = 6,

    .static_knobs = {{
        {.module_id = 2, .param_id = 0, .value = 0.105000f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 1.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.000000f},
        {.module_id = 3, .param_id = 1, .value = 0.000000f},
    }},
    .num_static_knobs = 5,

    .mapped_knobs = {{
        {.module_id = 3, .param_id = 0, .panel_knob_id = 0},
    }},
    .num_mapped_knobs = 1,

};
