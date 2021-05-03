#include "patch.hh"
static const Patch test_eightstepCore = { 
    .patch_name = "test_eightstepCore",
    .modules_used = {
        "PANEL_8",
        "LFOSINE",
        "EIGHTSTEP",
    },
    .num_modules = 3,

    .module_nodes = {{
        // PANEL_8
        {255, 254, 2, 1, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {243, 242, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // EIGHTSTEP
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
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
                {.module_id = 2, .jack_id = 1},
                {.module_id = 0, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 3},
            }},
        },
    }},
    .num_nets = 3,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.306000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 1.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.000000f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 0.000000f},
        {.module_id = 2, .param_id = 3, .value = 0.000000f},
        {.module_id = 2, .param_id = 4, .value = 0.000000f},
        {.module_id = 2, .param_id = 5, .value = 0.000000f},
        {.module_id = 2, .param_id = 6, .value = 0.000000f},
        {.module_id = 2, .param_id = 7, .value = 0.000000f},
        {.module_id = 2, .param_id = 8, .value = 1.000000f},
    }},
    .num_static_knobs = 12,

    .mapped_knobs = {{
        {.module_id = 2, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 2, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 2, .param_id = 2, .panel_knob_id = 2},
        {.module_id = 2, .param_id = 3, .panel_knob_id = 3},
        {.module_id = 2, .param_id = 4, .panel_knob_id = 4},
        {.module_id = 2, .param_id = 5, .panel_knob_id = 5},
        {.module_id = 2, .param_id = 6, .panel_knob_id = 6},
        {.module_id = 2, .param_id = 7, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
