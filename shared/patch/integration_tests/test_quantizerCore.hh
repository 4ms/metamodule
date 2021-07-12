#include "patch.hh"
static const Patch test_quantizerCore = { 
    .patch_name = "test_quantizerCore",
    .modules_used = {
        "PANEL_8",
        "QUANTIZER",
        "VOLTAGESOURCE",
        "QUANTIZER",
    },
    .num_modules = 4,

    .module_nodes = {{
        // PANEL_8
        {1, 255, 2, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // QUANTIZER
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // VOLTAGESOURCE
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // QUANTIZER
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
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
                {.module_id = 3, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 0, .jack_id = 2},
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
    .num_nets = 4,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 1.000000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 1, .param_id = 3, .value = 0.000000f},
        {.module_id = 1, .param_id = 4, .value = 1.000000f},
        {.module_id = 1, .param_id = 5, .value = 0.000000f},
        {.module_id = 1, .param_id = 6, .value = 0.000000f},
        {.module_id = 1, .param_id = 7, .value = 0.000000f},
        {.module_id = 1, .param_id = 8, .value = 0.000000f},
        {.module_id = 1, .param_id = 9, .value = 1.000000f},
        {.module_id = 1, .param_id = 10, .value = 0.000000f},
        {.module_id = 1, .param_id = 11, .value = 0.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.000000f},
        {.module_id = 2, .param_id = 1, .value = 0.183000f},
        {.module_id = 3, .param_id = 0, .value = 1.000000f},
        {.module_id = 3, .param_id = 1, .value = 0.000000f},
        {.module_id = 3, .param_id = 2, .value = 0.000000f},
        {.module_id = 3, .param_id = 3, .value = 0.000000f},
        {.module_id = 3, .param_id = 4, .value = 1.000000f},
        {.module_id = 3, .param_id = 5, .value = 0.000000f},
        {.module_id = 3, .param_id = 6, .value = 0.000000f},
        {.module_id = 3, .param_id = 7, .value = 0.000000f},
        {.module_id = 3, .param_id = 8, .value = 0.000000f},
        {.module_id = 3, .param_id = 9, .value = 1.000000f},
        {.module_id = 3, .param_id = 10, .value = 0.000000f},
        {.module_id = 3, .param_id = 11, .value = 0.000000f},
    }},
    .num_static_knobs = 26,

    .mapped_knobs = {{
        {.module_id = 2, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 2, .param_id = 1, .panel_knob_id = 1},
    }},
    .num_mapped_knobs = 2,

};
