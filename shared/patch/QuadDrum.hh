#include "patch.hh"
static const Patch QuadDrum = { 
    .patch_name = "QuadDrum",
    .modules_used = {
        "PANEL_8",
        "DRUM",
        "DRUM",
        "DRUM",
        "DRUM",
        "STEREOMIXER",
    },
    .num_modules = 6,

    .module_nodes = {{
        // PANEL_8
        {1, 2, 255, 254, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // STEREOMIXER
        {1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 5, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 5, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 3, .jack_id = 0},
                {.module_id = 5, .jack_id = 2},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 4, .jack_id = 0},
                {.module_id = 5, .jack_id = 3},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 5, .jack_id = 0},
                {.module_id = 0, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 5, .jack_id = 1},
                {.module_id = 0, .jack_id = 1},
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
                {.module_id = 0, .jack_id = 3},
                {.module_id = 2, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 4},
                {.module_id = 3, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 5},
                {.module_id = 4, .jack_id = 0},
            }},
        },
    }},
    .num_nets = 10,

    .static_knobs = {{
        {.module_id = 1, .param_id = 0, .value = 0.025500f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.496500f},
        {.module_id = 1, .param_id = 3, .value = 0.129000f},
        {.module_id = 1, .param_id = 4, .value = 0.250500f},
        {.module_id = 1, .param_id = 5, .value = 0.000000f},
        {.module_id = 1, .param_id = 6, .value = 0.264000f},
        {.module_id = 1, .param_id = 7, .value = 0.000000f},
        {.module_id = 1, .param_id = 8, .value = 0.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.286500f},
        {.module_id = 2, .param_id = 1, .value = 0.102000f},
        {.module_id = 2, .param_id = 2, .value = 0.253500f},
        {.module_id = 2, .param_id = 3, .value = 0.283500f},
        {.module_id = 2, .param_id = 4, .value = 0.090000f},
        {.module_id = 2, .param_id = 5, .value = 0.684000f},
        {.module_id = 2, .param_id = 6, .value = 0.000000f},
        {.module_id = 2, .param_id = 7, .value = 0.210000f},
        {.module_id = 2, .param_id = 8, .value = 0.508500f},
        {.module_id = 3, .param_id = 0, .value = 0.426000f},
        {.module_id = 3, .param_id = 1, .value = 0.106500f},
        {.module_id = 3, .param_id = 2, .value = 0.237000f},
        {.module_id = 3, .param_id = 3, .value = 0.244500f},
        {.module_id = 3, .param_id = 4, .value = 0.436500f},
        {.module_id = 3, .param_id = 5, .value = 0.316500f},
        {.module_id = 3, .param_id = 6, .value = 0.145500f},
        {.module_id = 3, .param_id = 7, .value = 0.000000f},
        {.module_id = 3, .param_id = 8, .value = 0.000000f},
        {.module_id = 4, .param_id = 0, .value = 0.102000f},
        {.module_id = 4, .param_id = 1, .value = 0.522000f},
        {.module_id = 4, .param_id = 2, .value = 0.000000f},
        {.module_id = 4, .param_id = 3, .value = 0.155500f},
        {.module_id = 4, .param_id = 4, .value = 0.376500f},
        {.module_id = 4, .param_id = 5, .value = 0.628500f},
        {.module_id = 4, .param_id = 6, .value = 0.151500f},
        {.module_id = 4, .param_id = 7, .value = 0.037500f},
        {.module_id = 4, .param_id = 8, .value = 0.138000f},
        {.module_id = 5, .param_id = 0, .value = 0.990000f},
        {.module_id = 5, .param_id = 1, .value = 1.000000f},
        {.module_id = 5, .param_id = 2, .value = 1.000000f},
        {.module_id = 5, .param_id = 3, .value = 1.000000f},
        {.module_id = 5, .param_id = 4, .value = 0.252000f},
        {.module_id = 5, .param_id = 5, .value = 0.385500f},
        {.module_id = 5, .param_id = 6, .value = 0.619500f},
        {.module_id = 5, .param_id = 7, .value = 0.781500f},
    }},
    .num_static_knobs = 44,

    .mapped_knobs = {{
        {.module_id = 1, .param_id = 1, .panel_knob_id = 0},
        {.module_id = 2, .param_id = 7, .panel_knob_id = 1},
        {.module_id = 3, .param_id = 0, .panel_knob_id = 2},
        {.module_id = 4, .param_id = 3, .panel_knob_id = 3},
        {.module_id = 1, .param_id = 5, .panel_knob_id = 4},
        {.module_id = 2, .param_id = 6, .panel_knob_id = 5},
        {.module_id = 3, .param_id = 6, .panel_knob_id = 6},
        {.module_id = 4, .param_id = 6, .panel_knob_id = 7},
    }},
    .num_mapped_knobs = 8,

};
