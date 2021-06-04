#include "patch.hh"
static const Patch simple_lfo_passthrru = { 
    .patch_name = "simple_lfo_passthrru",
    .modules_used = {
        "PANEL_8",
        "LFOSINE",
        "MIXER4",
        "LFOSINE",
    },
    .num_modules = 4,

    .module_nodes = {{
        // PANEL_8
        {9, 2, 3, 4, 255, 254, 253, 252, 251, 1, 10, 5, 6, 250, 0, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {6, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // MIXER4
        {1, 10, 249, 248, 9, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {5, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
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
                {.module_id = 3, .jack_id = 0},
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
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 2},
                {.module_id = 3, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 3},
                {.module_id = 1, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 6},
                {.module_id = 3, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 7},
                {.module_id = 1, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 1},
                {.module_id = 2, .jack_id = 1},
            }},
        },
    }},
    .num_nets = 10,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.000000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 2, .param_id = 0, .value = 1.000000f},
        {.module_id = 2, .param_id = 1, .value = 1.000000f},
        {.module_id = 2, .param_id = 2, .value = 0.000000f},
        {.module_id = 2, .param_id = 3, .value = 0.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.000000f},
        {.module_id = 3, .param_id = 1, .value = 0.000000f},
        {.module_id = 3, .param_id = 2, .value = 0.000000f},
    }},
    .num_static_knobs = 10,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 2},
        {.module_id = 3, .param_id = 0, .panel_knob_id = 4},
        {.module_id = 3, .param_id = 1, .panel_knob_id = 5},
        {.module_id = 3, .param_id = 2, .panel_knob_id = 6},
        {.module_id = 2, .param_id = 0, .panel_knob_id = 3},
        {.module_id = 2, .param_id = 1, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
