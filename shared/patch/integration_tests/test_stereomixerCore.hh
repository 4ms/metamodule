#include "patch.hh"
static const Patch test_stereomixerCore = { 
    .patch_name = "test_stereomixerCore",
    .modules_used = {
        "PANEL_8",
        "STEREOMIXER",
        "LFOSINE",
        "LFOSINE",
        "LFOSINE",
        "LFOSINE",
    },
    .num_modules = 6,

    .module_nodes = {{
        // PANEL_8
        {1, 2, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // STEREOMIXER
        {1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {243, 242, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {241, 240, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {239, 238, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {237, 236, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
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
                {.module_id = 4, .jack_id = 0},
                {.module_id = 1, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 5, .jack_id = 0},
                {.module_id = 1, .jack_id = 3},
            }},
        },
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
    }},
    .num_nets = 6,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 1.000000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 1, .param_id = 3, .value = 0.000000f},
        {.module_id = 1, .param_id = 4, .value = 0.496500f},
        {.module_id = 1, .param_id = 5, .value = 0.498000f},
        {.module_id = 1, .param_id = 6, .value = 0.522000f},
        {.module_id = 1, .param_id = 7, .value = 0.505500f},
        {.module_id = 2, .param_id = 0, .value = 0.250500f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 1.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.375000f},
        {.module_id = 3, .param_id = 1, .value = 0.000000f},
        {.module_id = 3, .param_id = 2, .value = 1.000000f},
        {.module_id = 4, .param_id = 0, .value = 0.520500f},
        {.module_id = 4, .param_id = 1, .value = 0.000000f},
        {.module_id = 4, .param_id = 2, .value = 1.000000f},
        {.module_id = 5, .param_id = 0, .value = 0.844500f},
        {.module_id = 5, .param_id = 1, .value = 0.000000f},
        {.module_id = 5, .param_id = 2, .value = 1.000000f},
    }},
    .num_static_knobs = 20,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 2},
        {.module_id = 1, .param_id = 3, .panel_knob_id = 3},
        {.module_id = 1, .param_id = 4, .panel_knob_id = 4},
        {.module_id = 1, .param_id = 5, .panel_knob_id = 5},
        {.module_id = 1, .param_id = 6, .panel_knob_id = 6},
        {.module_id = 1, .param_id = 7, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
