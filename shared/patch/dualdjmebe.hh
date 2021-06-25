#include "patch.hh"
static const Patch dualdjmebe = { 
    .patch_name = "dual-djmebe",
    .modules_used = {
        "PANEL_8",
        "DJEMBE",
        "DJEMBE",
        "CLKMULTIPLIER",
        "MULTILFO",
    },
    .num_modules = 5,

    .module_nodes = {{
        // PANEL_8
        {3, 4, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DJEMBE
        {3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DJEMBE
        {4, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // CLKMULTIPLIER
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // MULTILFO
        {0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 1, .jack_id = 4},
            }},
        },
        {
            .num_jacks = 3,
            .jacks = {{
                {.module_id = 4, .jack_id = 3},
                {.module_id = 2, .jack_id = 4},
                {.module_id = 3, .jack_id = 0},
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
                {.module_id = 2, .jack_id = 0},
                {.module_id = 0, .jack_id = 1},
            }},
        },
    }},
    .num_nets = 4,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.000000f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.000000f},
        {.module_id = 1, .param_id = 3, .value = 0.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.000000f},
        {.module_id = 2, .param_id = 1, .value = 0.466500f},
        {.module_id = 2, .param_id = 2, .value = 0.000000f},
        {.module_id = 2, .param_id = 3, .value = 0.000000f},
        {.module_id = 3, .param_id = 0, .value = 0.000000f},
        {.module_id = 4, .param_id = 0, .value = 0.000000f},
        {.module_id = 4, .param_id = 1, .value = 0.000000f},
        {.module_id = 4, .param_id = 2, .value = 0.222000f},
    }},
    .num_static_knobs = 12,

    .mapped_knobs = {{
        {.module_id = 4, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 1, .param_id = 0, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 2, .panel_knob_id = 2},
        {.module_id = 1, .param_id = 1, .panel_knob_id = 3},
        {.module_id = 3, .param_id = 0, .panel_knob_id = 4},
        {.module_id = 2, .param_id = 0, .panel_knob_id = 5},
        {.module_id = 2, .param_id = 2, .panel_knob_id = 6},
        {.module_id = 2, .param_id = 3, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
