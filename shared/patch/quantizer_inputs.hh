#include "patch.hh"
static const Patch quantizer_inputs = { 
    .patch_name = "quantizer_inputs",
    .modules_used = {
        "PANEL_8",
        "QUANTIZER",
        "QUANTIZER",
    },
    .num_modules = 3,

    .module_nodes = {{
        // PANEL_8
        {2, 255, 1, 254, 253, 252, 251, 250, 249, 2, 248, 1, 247, 246, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // QUANTIZER
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // QUANTIZER
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 2},
                {.module_id = 1, .jack_id = 0},
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
                {.module_id = 0, .jack_id = 0},
                {.module_id = 2, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 4,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 1.000000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 1, .param_id = 3, .value = 0.000000f},
        {.module_id = 1, .param_id = 4, .value = 0.000000f},
        {.module_id = 1, .param_id = 5, .value = 0.000000f},
        {.module_id = 1, .param_id = 6, .value = 0.000000f},
        {.module_id = 1, .param_id = 7, .value = 1.000000f},
        {.module_id = 1, .param_id = 8, .value = 0.000000f},
        {.module_id = 1, .param_id = 9, .value = 0.000000f},
        {.module_id = 1, .param_id = 10, .value = 0.000000f},
        {.module_id = 1, .param_id = 11, .value = 0.000000f},
        {.module_id = 2, .param_id = 0, .value = 1.000000f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 0.000000f},
        {.module_id = 2, .param_id = 3, .value = 0.000000f},
        {.module_id = 2, .param_id = 4, .value = 0.000000f},
        {.module_id = 2, .param_id = 5, .value = 0.000000f},
        {.module_id = 2, .param_id = 6, .value = 0.000000f},
        {.module_id = 2, .param_id = 7, .value = 1.000000f},
        {.module_id = 2, .param_id = 8, .value = 0.000000f},
        {.module_id = 2, .param_id = 9, .value = 0.000000f},
        {.module_id = 2, .param_id = 10, .value = 0.000000f},
        {.module_id = 2, .param_id = 11, .value = 0.000000f},
    }},
    .num_static_knobs = 24,

    .mapped_knobs = {{
    }},
    .num_mapped_knobs = 0,

};
