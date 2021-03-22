#include "patch.hh"
static const Patch Example1 = { 
    .modules_used = {
        "PANEL_8",
        "REVERB",
        "DRUM",
        "FADEDELAY",
        "LFOSINE",
        "KARPLUS",
    },
    .num_modules = 6,

    .module_nodes = {{
        // PANEL_8
        {2, 255, 254, 253, 252, 251, 250, 249, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // REVERB
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // FADEDELAY
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {248, 247, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // KARPLUS
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 4, .jack_id = 0},
                {.module_id = 2, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 3, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 5, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 3,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 1.000000f},
        {.module_id = 1, .param_id = 1, .value = 0.260000f},
        {.module_id = 1, .param_id = 2, .value = 0.491500f},
        {.module_id = 1, .param_id = 3, .value = 0.178500f},
        {.module_id = 1, .param_id = 4, .value = 0.256500f},
        {.module_id = 1, .param_id = 5, .value = 0.243000f},
        {.module_id = 2, .param_id = 0, .value = 0.121500f},
        {.module_id = 2, .param_id = 1, .value = 0.346500f},
        {.module_id = 2, .param_id = 2, .value = 0.294000f},
        {.module_id = 2, .param_id = 3, .value = 0.117000f},
        {.module_id = 2, .param_id = 4, .value = 0.133500f},
        {.module_id = 2, .param_id = 5, .value = 0.232500f},
        {.module_id = 2, .param_id = 6, .value = 0.193500f},
        {.module_id = 2, .param_id = 7, .value = 0.165000f},
        {.module_id = 2, .param_id = 8, .value = 0.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.351000f},
        {.module_id = 3, .param_id = 1, .value = 0.879000f},
        {.module_id = 3, .param_id = 2, .value = 0.149999f},
        {.module_id = 3, .param_id = 3, .value = 0.540000f},
        {.module_id = 3, .param_id = 4, .value = 0.000000f},
        {.module_id = 4, .param_id = 0, .value = 0.000000f},
        {.module_id = 4, .param_id = 1, .value = 0.000000f},
        {.module_id = 4, .param_id = 2, .value = 1.000000f},
        {.module_id = 5, .param_id = 0, .value = 0.000000f},
        {.module_id = 5, .param_id = 1, .value = 0.000000f},
        {.module_id = 5, .param_id = 2, .value = 0.000000f},
    }},
    .num_static_knobs = 26,

    .mapped_knobs = {{
    }},
    .num_mapped_knobs = 0,

};
