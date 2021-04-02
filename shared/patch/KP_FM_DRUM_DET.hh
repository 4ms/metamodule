#include "patch.hh"
static const Patch KP_FM_DRUM_DET = { 
    .patch_name = "KP_FM_DRUM_DET",
    .modules_used = {
        "PANEL_8",
        "FMOSC",
        "DRUM",
        "KARPLUS",
        "DETUNE",
    },
    .num_modules = 5,

    .module_nodes = {{
        // PANEL_8
        {1, 3, 4, 5, 255, 254, 1, 5, 2, 7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // FMOSC
        {3, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // KARPLUS
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DETUNE
        {5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 0},
                {.module_id = 3, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 2},
                {.module_id = 3, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 0, .jack_id = 1},
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
                {.module_id = 4, .jack_id = 0},
                {.module_id = 0, .jack_id = 3},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 1},
                {.module_id = 4, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 5},
                {.module_id = 4, .jack_id = 1},
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
                {.module_id = 0, .jack_id = 3},
                {.module_id = 1, .jack_id = 4},
            }},
        },
    }},
    .num_nets = 10,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.546000f},
        {.module_id = 1, .param_id = 1, .value = 0.462000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 1, .param_id = 3, .value = 0.000000f},
        {.module_id = 1, .param_id = 4, .value = 0.249000f},
        {.module_id = 1, .param_id = 5, .value = 0.000000f},
        {.module_id = 1, .param_id = 6, .value = 0.000000f},
        {.module_id = 1, .param_id = 7, .value = 0.534000f},
        {.module_id = 2, .param_id = 0, .value = 0.198000f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 0.000000f},
        {.module_id = 2, .param_id = 3, .value = 0.640500f},
        {.module_id = 2, .param_id = 4, .value = 0.000000f},
        {.module_id = 2, .param_id = 5, .value = 0.000000f},
        {.module_id = 2, .param_id = 6, .value = 0.075000f},
        {.module_id = 2, .param_id = 7, .value = 0.093000f},
        {.module_id = 2, .param_id = 8, .value = 0.445500f},
        {.module_id = 3, .param_id = 0, .value = 0.165000f},
        {.module_id = 3, .param_id = 1, .value = 0.250500f},
        {.module_id = 3, .param_id = 2, .value = 0.112500f},
        {.module_id = 4, .param_id = 0, .value = 0.256500f},
        {.module_id = 4, .param_id = 1, .value = 0.988000f},
        {.module_id = 4, .param_id = 2, .value = 0.000000f},
        {.module_id = 4, .param_id = 3, .value = 1.000000f},
    }},
    .num_static_knobs = 24,

    .mapped_knobs = {{
        {.module_id = 3, .param_id = 1, .panel_knob_id = 0},
        {.module_id = 3, .param_id = 2, .panel_knob_id = 4},
        {.module_id = 1, .param_id = 0, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 5},
        {.module_id = 2, .param_id = 0, .panel_knob_id = 2},
        {.module_id = 2, .param_id = 8, .panel_knob_id = 6},
        {.module_id = 4, .param_id = 0, .panel_knob_id = 3},
        {.module_id = 4, .param_id = 2, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
