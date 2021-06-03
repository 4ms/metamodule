#include "patch.hh"
static const Patch test_envelopefollowerCore = { 
    .patch_name = "test_envelopefollowerCore",
    .modules_used = {
        "PANEL_8",
        "ENVELOPEFOLLOWER",
        "LFOSINE",
        "VCA",
        "FMOSC",
        "ADENV",
    },
    .num_modules = 6,

    .module_nodes = {{
        // PANEL_8
        {1, 255, 3, 1, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // ENVELOPEFOLLOWER
        {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {244, 243, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // VCA
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // FMOSC
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // ADENV
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 3,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 4, .jack_id = 0},
                {.module_id = 3, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 5, .jack_id = 0},
                {.module_id = 3, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 5, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 1},
                {.module_id = 0, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 3},
            }},
        },
    }},
    .num_nets = 6,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.540000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.514500f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 1.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.500000f},
        {.module_id = 3, .param_id = 1, .value = 1.000000f},
        {.module_id = 3, .param_id = 2, .value = 0.000000f},
        {.module_id = 3, .param_id = 3, .value = 1.000000f},
        {.module_id = 4, .param_id = 0, .value = 0.280500f},
        {.module_id = 4, .param_id = 1, .value = 0.627000f},
        {.module_id = 4, .param_id = 2, .value = 0.318000f},
        {.module_id = 4, .param_id = 3, .value = 0.303000f},
        {.module_id = 4, .param_id = 4, .value = 0.564000f},
        {.module_id = 4, .param_id = 5, .value = 0.000000f},
        {.module_id = 4, .param_id = 6, .value = 0.000000f},
        {.module_id = 4, .param_id = 7, .value = 0.548500f},
        {.module_id = 5, .param_id = 0, .value = 0.000000f},
        {.module_id = 5, .param_id = 1, .value = 0.145500f},
        {.module_id = 5, .param_id = 2, .value = 0.000000f},
        {.module_id = 5, .param_id = 3, .value = 0.000000f},
    }},
    .num_static_knobs = 22,

    .mapped_knobs = {{
    }},
    .num_mapped_knobs = 0,

};
