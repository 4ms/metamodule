#include "patch.hh"
static const Patch gateintest = { 
    .patch_name = "gatein-test",
    .modules_used = {
        "PANEL_8",
        "DRUM",
        "FOURSTEP",
        "LFOSINE",
        "FMOSC",
        "FMOSC",
        "GATESEQ8",
    },
    .num_modules = 7,

    .module_nodes = {{
        // PANEL_8
        {3, 4, 2, 255, 5, 254, 253, 252, 251, 250, 0, 0, 3, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // FOURSTEP
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {249, 248, 247, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // FMOSC
        {4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // FMOSC
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // GATESEQ8
        {5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 4, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 6, .jack_id = 1},
                {.module_id = 5, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 6},
                {.module_id = 1, .jack_id = 0},
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
                {.module_id = 4, .jack_id = 0},
                {.module_id = 0, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 5, .jack_id = 0},
                {.module_id = 0, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 8},
                {.module_id = 6, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 6, .jack_id = 0},
                {.module_id = 0, .jack_id = 4},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 7},
                {.module_id = 2, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 9,

    .static_knobs = {{
        {.module_id = 2, .param_id = 0, .value = 0.142500f},
        {.module_id = 2, .param_id = 1, .value = 0.340500f},
        {.module_id = 2, .param_id = 2, .value = 0.607500f},
        {.module_id = 2, .param_id = 3, .value = 0.664500f},
        {.module_id = 3, .param_id = 0, .value = 0.121500f},
        {.module_id = 3, .param_id = 1, .value = 0.000000f},
        {.module_id = 3, .param_id = 2, .value = 1.000000f},
        {.module_id = 4, .param_id = 0, .value = 0.243000f},
        {.module_id = 4, .param_id = 1, .value = 0.082500f},
        {.module_id = 4, .param_id = 2, .value = 0.909000f},
        {.module_id = 4, .param_id = 3, .value = 0.000000f},
        {.module_id = 4, .param_id = 4, .value = 0.000000f},
        {.module_id = 4, .param_id = 5, .value = 0.000000f},
        {.module_id = 4, .param_id = 6, .value = 0.000000f},
        {.module_id = 4, .param_id = 7, .value = 0.483000f},
        {.module_id = 5, .param_id = 0, .value = 0.360000f},
        {.module_id = 5, .param_id = 1, .value = 0.000000f},
        {.module_id = 5, .param_id = 2, .value = 0.000000f},
        {.module_id = 5, .param_id = 3, .value = 0.000000f},
        {.module_id = 5, .param_id = 4, .value = 0.000000f},
        {.module_id = 5, .param_id = 5, .value = 0.000000f},
        {.module_id = 5, .param_id = 6, .value = 0.000000f},
        {.module_id = 5, .param_id = 7, .value = 0.000000f},
        {.module_id = 1, .param_id = 0, .value = 0.105000f},
        {.module_id = 1, .param_id = 1, .value = 0.183000f},
        {.module_id = 1, .param_id = 2, .value = 0.198000f},
        {.module_id = 1, .param_id = 3, .value = 0.240000f},
        {.module_id = 1, .param_id = 4, .value = 0.000000f},
        {.module_id = 1, .param_id = 5, .value = 0.000000f},
        {.module_id = 1, .param_id = 6, .value = 0.351000f},
        {.module_id = 1, .param_id = 7, .value = 0.105000f},
        {.module_id = 1, .param_id = 8, .value = 0.493500f},
        {.module_id = 6, .param_id = 0, .value = 1.000000f},
        {.module_id = 6, .param_id = 1, .value = 0.000000f},
        {.module_id = 6, .param_id = 2, .value = 1.000000f},
        {.module_id = 6, .param_id = 3, .value = 1.000000f},
        {.module_id = 6, .param_id = 4, .value = 0.000000f},
        {.module_id = 6, .param_id = 5, .value = 1.000000f},
        {.module_id = 6, .param_id = 6, .value = 1.000000f},
        {.module_id = 6, .param_id = 7, .value = 0.000000f},
    }},
    .num_static_knobs = 40,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 8, .panel_knob_id = 2},
        {.module_id = 1, .param_id = 3, .panel_knob_id = 3},
        {.module_id = 4, .param_id = 0, .panel_knob_id = 4},
        {.module_id = 4, .param_id = 2, .panel_knob_id = 5},
        {.module_id = 3, .param_id = 2, .panel_knob_id = 6},
        {.module_id = 3, .param_id = 0, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
