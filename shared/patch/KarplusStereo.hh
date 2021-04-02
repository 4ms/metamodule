#include "patch.hh"
static const Patch KarplusStereo = { 
    .patch_name = "Karplus Stereo",
    .modules_used = {
        "PANEL_8",
        "KARPLUS",
        "KARPLUS",
    },
    .num_modules = 3,

    .module_nodes = {{
        // PANEL_8
        {1, 4, 255, 254, 253, 252, 251, 250, 2, 1, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // KARPLUS
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // KARPLUS
        {4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
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
                {.module_id = 0, .jack_id = 2},
                {.module_id = 1, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 4},
                {.module_id = 2, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 5},
                {.module_id = 2, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 3},
                {.module_id = 1, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 6,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.165000f},
        {.module_id = 1, .param_id = 1, .value = 0.250500f},
        {.module_id = 1, .param_id = 2, .value = 0.112500f},
        {.module_id = 2, .param_id = 0, .value = 0.165000f},
        {.module_id = 2, .param_id = 1, .value = 0.250500f},
        {.module_id = 2, .param_id = 2, .value = 0.112500f},
    }},
    .num_static_knobs = 6,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 2},
        {.module_id = 2, .param_id = 0, .panel_knob_id = 4},
        {.module_id = 2, .param_id = 1, .panel_knob_id = 5},
        {.module_id = 2, .param_id = 2, .panel_knob_id = 6},
    }},
    .num_mapped_knobs = 6,

};
