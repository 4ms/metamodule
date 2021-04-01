#include "patch.hh"
static const Patch Unnamed51 = { 
    .patch_name = "Unnamed51",
    .modules_used = {
        "PANEL_8",
        "DRUM",
        "DRUM",
        "DRUM",
        "DRUM",
        "STEREOMIXER",
        "LOWPASSFILTER",
        "HIGHPASSFILTER",
        "LFOSINE",
    },
    .num_modules = 9,

    .module_nodes = {{
        // PANEL_8
        {6, 5, 255, 254, 253, 252, 7, 8, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // DRUM
        {4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // STEREOMIXER
        {6, 5, 3, 4, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LOWPASSFILTER
        {1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // HIGHPASSFILTER
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        // LFOSINE
        {251, 250, 249, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    }},

    .nets = {{
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 1, .jack_id = 0},
                {.module_id = 6, .jack_id = 0},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 2, .jack_id = 0},
                {.module_id = 7, .jack_id = 0},
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
                {.module_id = 6, .jack_id = 0},
                {.module_id = 5, .jack_id = 4},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 7, .jack_id = 0},
                {.module_id = 5, .jack_id = 5},
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
                {.module_id = 0, .jack_id = 5},
                {.module_id = 4, .jack_id = 0},
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
                {.module_id = 0, .jack_id = 0},
                {.module_id = 6, .jack_id = 1},
            }},
        },
        {
            .num_jacks = 2,
            .jacks = {{
                {.module_id = 0, .jack_id = 1},
                {.module_id = 4, .jack_id = 1},
            }},
        },
    }},
    .num_nets = 14,

    .static_knobs = {{
        {.module_id = 6, .param_id = 0, .value = 0.380500f},
        {.module_id = 6, .param_id = 1, .value = 0.240000f},
        {.module_id = 6, .param_id = 2, .value = 0.000000f},
        {.module_id = 6, .param_id = 3, .value = 0.000000f},
        {.module_id = 7, .param_id = 0, .value = 0.235000f},
        {.module_id = 7, .param_id = 1, .value = 0.594000f},
        {.module_id = 7, .param_id = 2, .value = 0.000000f},
        {.module_id = 8, .param_id = 0, .value = 0.000000f},
        {.module_id = 8, .param_id = 1, .value = 0.000000f},
        {.module_id = 8, .param_id = 2, .value = 1.000000f},
        {.module_id = 1, .param_id = 0, .value = 0.043500f},
        {.module_id = 1, .param_id = 1, .value = 0.000000f},
        {.module_id = 1, .param_id = 2, .value = 0.496500f},
        {.module_id = 1, .param_id = 3, .value = 0.129000f},
        {.module_id = 1, .param_id = 4, .value = 0.250500f},
        {.module_id = 1, .param_id = 5, .value = 0.264000f},
        {.module_id = 1, .param_id = 6, .value = 0.264000f},
        {.module_id = 1, .param_id = 7, .value = 0.000000f},
        {.module_id = 1, .param_id = 8, .value = 0.000000f},
        {.module_id = 2, .param_id = 0, .value = 0.286500f},
        {.module_id = 2, .param_id = 1, .value = 0.102000f},
        {.module_id = 2, .param_id = 2, .value = 0.253500f},
        {.module_id = 2, .param_id = 3, .value = 0.283500f},
        {.module_id = 2, .param_id = 4, .value = 0.090000f},
        {.module_id = 2, .param_id = 5, .value = 0.684000f},
        {.module_id = 2, .param_id = 6, .value = 0.088500f},
        {.module_id = 2, .param_id = 7, .value = 0.210000f},
        {.module_id = 2, .param_id = 8, .value = 0.507000f},
        {.module_id = 3, .param_id = 0, .value = 0.426000f},
        {.module_id = 3, .param_id = 1, .value = 0.106500f},
        {.module_id = 3, .param_id = 2, .value = 0.237000f},
        {.module_id = 3, .param_id = 3, .value = 0.244500f},
        {.module_id = 3, .param_id = 4, .value = 0.436500f},
        {.module_id = 3, .param_id = 5, .value = 0.316500f},
        {.module_id = 3, .param_id = 6, .value = 0.306000f},
        {.module_id = 3, .param_id = 7, .value = 0.000000f},
        {.module_id = 3, .param_id = 8, .value = 0.000000f},
        {.module_id = 4, .param_id = 0, .value = 0.127500f},
        {.module_id = 4, .param_id = 1, .value = 0.522000f},
        {.module_id = 4, .param_id = 2, .value = 0.000000f},
        {.module_id = 4, .param_id = 3, .value = 0.155500f},
        {.module_id = 4, .param_id = 4, .value = 0.376500f},
        {.module_id = 4, .param_id = 5, .value = 0.628500f},
        {.module_id = 4, .param_id = 6, .value = 0.150000f},
        {.module_id = 4, .param_id = 7, .value = 0.037500f},
        {.module_id = 4, .param_id = 8, .value = 0.138000f},
        {.module_id = 5, .param_id = 0, .value = 0.990000f},
        {.module_id = 5, .param_id = 1, .value = 1.000000f},
        {.module_id = 5, .param_id = 2, .value = 1.000000f},
        {.module_id = 5, .param_id = 3, .value = 1.000000f},
        {.module_id = 5, .param_id = 4, .value = 0.340500f},
        {.module_id = 5, .param_id = 5, .value = 0.645000f},
        {.module_id = 5, .param_id = 6, .value = 0.348000f},
        {.module_id = 5, .param_id = 7, .value = 0.322000f},
    }},
    .num_static_knobs = 54,

    .mapped_knobs = {{
        {.module_id = 2, .param_id = 7, .panel_knob_id = 1},
        {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
        {.module_id = 6, .param_id = 0, .panel_knob_id = 4},
        {.module_id = 3, .param_id = 0, .panel_knob_id = 2},
        {.module_id = 4, .param_id = 3, .panel_knob_id = 3},
        {.module_id = 7, .param_id = 0, .panel_knob_id = 5},
        {.module_id = 4, .param_id = 6, .panel_knob_id = 7},
        {.module_id = 3, .param_id = 6, .panel_knob_id = 6},
    }},
    .num_mapped_knobs = 8,

};
