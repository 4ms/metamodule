#include "patch.hh"
static const Patch test_vcaCore = { 
    .patch_name = "test_vcaCore",
    .modules_used = {
        "PANEL_8",
        "VCA",
        "LFOSINE",
        "ADENV",
    },
    .num_modules = 4,

    .module_nodes = {{
        // PANEL_8
        {1, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // VCA
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {242, 241, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // ADENV
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 3,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 1, .jack_id = 0},
                {.module_id = 3, .jack_id = 0},
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
        {.module_id = 1, .param_id = 0, .value = 0.000000f},
        {.module_id = 1, .param_id = 1, .value = 1.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 1, .param_id = 3, .value = 1.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.000000f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 1.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.000000f},
        {.module_id = 3, .param_id = 1, .value = 0.252000f},
        {.module_id = 3, .param_id = 2, .value = 0.462000f},
        {.module_id = 3, .param_id = 3, .value = 1.000000f},
    }},
    .num_static_knobs = 11,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 2},
        {.module_id = 1, .param_id = 3, .panel_knob_id = 3},
    }},
    .num_mapped_knobs = 4,

};
