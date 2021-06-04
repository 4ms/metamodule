#include "patch.hh"
static const Patch test_sense_pins_CV = { 
    .patch_name = "test_sense_pins_CV",
    .modules_used = {
        "PANEL_8",
        "ATTENVERT2",
        "ATTENVERT2",
    },
    .num_modules = 3,

    .module_nodes = {{
        // PANEL_8
        {1, 2, 3, 4, 255, 254, 253, 252, 251, 250, 249, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // ATTENVERT2
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // ATTENVERT2
        {3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
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
                {.module_id = 1, .jack_id = 1},
                {.module_id = 0, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 3},
                {.module_id = 1, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 1},
                {.module_id = 0, .jack_id = 3},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 4},
                {.module_id = 2, .jack_id = 0},
            }},
        },
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
                {.module_id = 0, .jack_id = 5},
                {.module_id = 2, .jack_id = 1},
            }},
        },
    }},
    .num_nets = 8,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.484500f},
        {.module_id = 1, .param_id = 1, .value = 0.502500f},
        {.module_id = 2, .param_id = 0, .value = 0.484500f},
        {.module_id = 2, .param_id = 1, .value = 0.502500f},
    }},
    .num_static_knobs = 4,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 2, .param_id = 0, .panel_knob_id = 2},
        {.module_id = 2, .param_id = 1, .panel_knob_id = 3},
    }},
    .num_mapped_knobs = 4,

};
