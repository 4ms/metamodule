#include "../patch_to_yaml.hh"
#include "doctest.h"
#include "ryml_serial.hh"
#include <iostream>

TEST_CASE("Correct yaml output produced") {
	PatchHeader ph{
		.header_version = 1,
		.patch_name = "test123",
		.num_modules = 4,
		.num_int_cables = 2,
		.num_mapped_ins = 3,
		.num_mapped_outs = 2,
		.num_static_knobs = 5,
		.num_mapped_knobs = 4,
	};

	PatchData pd{
		.module_slugs{"PanelMedium", "Module1", "Module2", "Module3"},
	};
	Jack out1{1, 2};
	Jack out2{11, 22};
	Jack in1{3, 4};
	Jack in2{5, 6};
	Jack in3{33, 44};
	Jack in4{55, 66};
	Jack in5{77, 88};
	Jack END{-1, -1};
	pd.int_cables.push_back({out1, {{in1, in2, END}}});

	CHECK(MAX_CONNECTIONS_PER_NODE == 4);
	// if MAX_CONNECTIONS_PER_NODE > 4, then we need a terminator at the end of this:
	pd.int_cables.push_back({out2, {{in3, in4, in5}}});

	pd.mapped_ins.push_back({1, {{in1, END}}});
	pd.mapped_ins.push_back({2, {{in2, in3, END}}});
	pd.mapped_ins.push_back({3, {{in5, END}}});

	pd.mapped_outs.push_back({4, out1});
	pd.mapped_outs.push_back({5, out2});

	pd.mapped_knobs.push_back(MappedKnob{
		.panel_knob_id = 1,
		.module_id = 2,
		.param_id = 3,
		.curve_type = 1,
		.min = 0.1f,
		.max = 0.95f,
	});

	pd.mapped_knobs.push_back(MappedKnob{
		.panel_knob_id = 2,
		.module_id = 3,
		.param_id = 4,
		.curve_type = 2,
		.min = 0.2f,
		.max = 0.85f,
	});

	pd.mapped_knobs.push_back(MappedKnob{
		.panel_knob_id = 3,
		.module_id = 4,
		.param_id = 5,
		.curve_type = 3,
		.min = 0.3f,
		.max = 0.75f,
	});

	pd.mapped_knobs.push_back(MappedKnob{
		.panel_knob_id = 4,
		.module_id = 5,
		.param_id = 6,
		.curve_type = 4,
		.min = 0.4f,
		.max = 0.65f,
	});

	pd.static_knobs.push_back({1, 2, 0.3f});
	pd.static_knobs.push_back({2, 3, 0.4f});
	pd.static_knobs.push_back({3, 4, 0.5f});
	pd.static_knobs.push_back({4, 5, 0.6f});
	pd.static_knobs.push_back({5, 6, 0.7f});

	auto yaml = patch_to_yaml_string(ph, pd);
	CHECK(yaml ==
		  // clang-format off
R"(PatchHeader:
  header_version: 1
  patch_name: test123
  num_modules: 4
  num_int_cables: 2
  num_mapped_ins: 3
  num_mapped_outs: 2
  num_static_knobs: 5
  num_mapped_knobs: 4
PatchData:
  module_slugs:
    0: PanelMedium
    1: Module1
    2: Module2
    3: Module3
  int_cables:
    - out:
        module_id: 1
        jack_id: 2
      ins:
        - module_id: 3
          jack_id: 4
        - module_id: 5
          jack_id: 6
    - out:
        module_id: 11
        jack_id: 22
      ins:
        - module_id: 33
          jack_id: 44
        - module_id: 55
          jack_id: 66
        - module_id: 77
          jack_id: 88
  mapped_ins:
    - panel_jack_id: 1
      ins:
        - module_id: 3
          jack_id: 4
    - panel_jack_id: 2
      ins:
        - module_id: 5
          jack_id: 6
        - module_id: 33
          jack_id: 44
    - panel_jack_id: 3
      ins:
        - module_id: 77
          jack_id: 88
  mapped_outs:
    - panel_jack_id: 4
      out:
        module_id: 1
        jack_id: 2
    - panel_jack_id: 5
      out:
        module_id: 11
        jack_id: 22
  static_knobs:
    - module_id: 1
      param_id: 2
      value: 0.3
    - module_id: 2
      param_id: 3
      value: 0.4
    - module_id: 3
      param_id: 4
      value: 0.5
    - module_id: 4
      param_id: 5
      value: 0.6
    - module_id: 5
      param_id: 6
      value: 0.7
  mapped_knobs:
    - module_id: 2
      param_id: 3
      curve_type: 1
      min: 0.1
      max: 0.95
    - module_id: 3
      param_id: 4
      curve_type: 2
      min: 0.2
      max: 0.85
    - module_id: 4
      param_id: 5
      curve_type: 3
      min: 0.3
      max: 0.75
    - module_id: 5
      param_id: 6
      curve_type: 4
      min: 0.4
      max: 0.65
)");
	// clang-format on
}
