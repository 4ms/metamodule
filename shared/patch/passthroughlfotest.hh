#include "patch.hh"
static const Patch passthroughlfotest = { 
    .patch_name = "passthrough-lfo-test",
    .modules_used = {
        "PANEL_8",
        "LFOSINE",
        "MIXER4",
    },
    .num_modules = 3,

    .module_nodes = {{
        // PANEL_8
        {1, 3, 5, 255, 254, 253, 252, 251, 250, 2, 4, 249, 248, 247, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {246, 245, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // MIXER4
        {2, 4, 244, 243, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
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
                {.module_id = 2, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 1},
                {.module_id = 0, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 1},
                {.module_id = 2, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 2},
            }},
        },
    }},
    .num_nets = 5,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.450000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 1.000000f},
        {.module_id = 2, .param_id = 0, .value = 1.000000f},
        {.module_id = 2, .param_id = 1, .value = 1.000000f},
        {.module_id = 2, .param_id = 2, .value = 0.000000f},
        {.module_id = 2, .param_id = 3, .value = 0.000000f},
    }},
    .num_static_knobs = 7,

    .mapped_knobs = {{
    }},
    .num_mapped_knobs = 0,

};
