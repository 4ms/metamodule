#include "patch.hh"
static const Patch test_bitcrushCore = { 
    .patch_name = "test_bitcrushCore",
    .modules_used = {
        "PANEL_8",
        "BITCRUSH",
        "LFOSINE",
        "ATTENVERT2",
        "LFOSINE",
    },
    .num_modules = 5,

    .module_nodes = {{
        // PANEL_8
        {1, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // BITCRUSH
        {1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {242, 241, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // ATTENVERT2
        {2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {240, 239, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
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
                {.module_id = 3, .jack_id = 0},
                {.module_id = 1, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 1},
                {.module_id = 1, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 3,
            .jacks = {{
                {.module_id = 4, .jack_id = 0},
                {.module_id = 3, .jack_id = 0},
                {.module_id = 3, .jack_id = 1},
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
    .num_nets = 5,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 1.000000f},
        {.module_id = 1, .param_id = 1, .value = 1.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.000000f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 1.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.500000f},
        {.module_id = 3, .param_id = 1, .value = 0.500000f},
        {.module_id = 4, .param_id = 0, .value = 0.000000f},
        {.module_id = 4, .param_id = 1, .value = 0.000000f},
        {.module_id = 4, .param_id = 2, .value = 1.000000f},
    }},
    .num_static_knobs = 10,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 3, .param_id = 0, .panel_knob_id = 2},
        {.module_id = 3, .param_id = 1, .panel_knob_id = 3},
    }},
    .num_mapped_knobs = 4,

};
