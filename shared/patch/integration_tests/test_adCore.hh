#include "patch.hh"
static const Patch test_adCore = { 
    .patch_name = "test_adCore",
    .modules_used = {
        "PANEL_8",
        "ADENV",
        "LFOSINE",
        "LFOSINE",
        "SEND_1TO4",
    },
    .num_modules = 5,

    .module_nodes = {{
        // PANEL_8
        {1, 255, 2, 3, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // ADENV
        {1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {244, 243, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {242, 241, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // SEND_1TO4
        {2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
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
                {.module_id = 4, .jack_id = 0},
                {.module_id = 1, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 4, .jack_id = 1},
                {.module_id = 1, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 4, .jack_id = 2},
                {.module_id = 1, .jack_id = 3},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 4, .jack_id = 3},
                {.module_id = 1, .jack_id = 4},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 4, .jack_id = 0},
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
                {.module_id = 0, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 2},
                {.module_id = 0, .jack_id = 3},
            }},
        },
    }},
    .num_nets = 9,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.000000f},
        {.module_id = 1, .param_id = 1, .value = 0.163500f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 1, .param_id = 3, .value = 0.512500f},
        {.module_id = 2, .param_id = 0, .value = 0.183000f},
        {.module_id = 2, .param_id = 1, .value = 0.000000f},
        {.module_id = 2, .param_id = 2, .value = 1.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.000000f},
        {.module_id = 3, .param_id = 1, .value = 0.000000f},
        {.module_id = 3, .param_id = 2, .value = 1.000000f},
        {.module_id = 4, .param_id = 0, .value = 0.000000f},
        {.module_id = 4, .param_id = 1, .value = 0.000000f},
        {.module_id = 4, .param_id = 2, .value = 0.000000f},
        {.module_id = 4, .param_id = 3, .value = 0.000000f},
    }},
    .num_static_knobs = 14,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 2},
        {.module_id = 1, .param_id = 3, .panel_knob_id = 3},
        {.module_id = 4, .param_id = 0, .panel_knob_id = 4},
        {.module_id = 4, .param_id = 1, .panel_knob_id = 5},
        {.module_id = 4, .param_id = 2, .panel_knob_id = 6},
        {.module_id = 4, .param_id = 3, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
