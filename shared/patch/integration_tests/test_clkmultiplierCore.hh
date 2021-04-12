#include "patch.hh"
static const Patch test_clkmultiplierCore = { 
    .patch_name = "test_clkmultiplierCore",
    .modules_used = {
        "PANEL_8",
        "LFOSINE",
        "LFOSINE",
        "CLKMULTIPLIER",
    },
    .num_modules = 4,

    .module_nodes = {{
        // PANEL_8
        {1, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {242, 241, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {240, 239, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // CLKMULTIPLIER
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 3, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 3, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 3,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.226500f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 1.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.774000f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 0.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.000000f},
    }},
    .num_static_knobs = 7,

    .mapped_knobs = {{
        {.module_id = 2, .param_id = 2, .panel_knob_id = 1},
        {.module_id = 3, .param_id = 0, .panel_knob_id = 0},
    }},
    .num_mapped_knobs = 2,

};
