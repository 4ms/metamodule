#include "patch.hh"
static const Patch test_comparatorCore = { 
    .patch_name = "test_comparatorCore",
    .modules_used = {
        "PANEL_8",
        "COMPARATOR",
        "LFOSINE",
        "LFOSINE",
    },
    .num_modules = 4,

    .module_nodes = {{
        // PANEL_8
        {1, 1, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // COMPARATOR
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {243, 242, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {241, 240, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 3,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 1, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 3,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.500000f},
        {.module_id = 1, .param_id = 1, .value = 1.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.175500f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 1.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.000000f},
        {.module_id = 3, .param_id = 1, .value = 0.000000f},
        {.module_id = 3, .param_id = 2, .value = 0.000000f},
    }},
    .num_static_knobs = 8,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 2, .param_id = 0, .panel_knob_id = 1},
        {.module_id = 3, .param_id = 2, .panel_knob_id = 2},
    }},
    .num_mapped_knobs = 3,

};
