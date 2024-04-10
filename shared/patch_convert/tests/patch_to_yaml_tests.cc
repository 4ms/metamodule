#include "../patch_to_yaml.hh"
#include "doctest.h"
#include "ryml_serial.hh"
#include <iostream>
#include <vector>

TEST_CASE("Correct yaml output produced") {
	PatchData pd{
		.module_slugs{"PanelMedium", "Module1", "Module2", "Module3"},
	};
	pd.patch_name = "test123";
	pd.description = "This is the description of the patch.";

	Jack out1{1, 2};
	Jack out2{11, 22};
	Jack in1{3, 4};
	Jack in2{5, 6};
	Jack in3{33, 44};
	Jack in4{55, 66};
	Jack in5{77, 88};

	pd.int_cables.push_back({out1, {{in1, in2}}, std::nullopt});
	pd.int_cables.push_back({out2, {{in3, in4, in5}}, 1});

	pd.mapped_ins.push_back({1, {{in1}}, "MapIn1"});
	pd.mapped_ins.push_back({2, {{in2, in3}}});
	pd.mapped_ins.push_back({3, {{in5}}});

	pd.mapped_outs.push_back({4, out1});
	pd.mapped_outs.push_back({5, out2, "MapOut2"});

	MappedKnobSet set0;
	set0.name = "MKSet0";

	set0.set.push_back(MappedKnob{
		.panel_knob_id = 1,
		.module_id = 2,
		.param_id = 3,
		.curve_type = 1,
		.min = 0.1f,
		.max = 0.95f,
		.alias_name = "MapKnob1",
	});

	set0.set.push_back(MappedKnob{
		.panel_knob_id = 2,
		.module_id = 3,
		.param_id = 4,
		.curve_type = 2,
		.min = 0.2f,
		.max = 0.85f,
	});

	set0.set.push_back(MappedKnob{
		.panel_knob_id = 3,
		.module_id = 4,
		.param_id = 5,
		.curve_type = 3,
		.min = 0.3f,
		.max = 0.75f,
	});

	pd.knob_sets.push_back(set0);

	MappedKnobSet set1;
	set1.name = "MKSet1";
	set1.set.push_back(MappedKnob{
		.panel_knob_id = 4,
		.module_id = 5,
		.param_id = 6,
		.curve_type = 4,
		.min = 0.4f,
		.max = 0.65f,
	});
	pd.knob_sets.push_back(set1);

	pd.static_knobs.push_back({1, 2, 0.3f});
	pd.static_knobs.push_back({2, 3, 0.4f});
	pd.static_knobs.push_back({3, 4, 0.5f});
	pd.static_knobs.push_back({4, 5, 0.6f});
	pd.static_knobs.push_back({5, 6, 0.7f});

	pd.midi_poly_num = 4;

	pd.module_states.push_back({2, "some string\nCan span lines\n\nNo problem"});

	std::string str;
	for (unsigned i = 0; i < 1000; i++)
		str.push_back(char((i++ % 0x5F) + 0x20));
	pd.module_states.push_back({3, str});

	auto yaml = patch_to_yaml_string(pd);
	CHECK(yaml ==
		  // clang-format off
R"(PatchData:
  patch_name: test123
  description: This is the description of the patch.
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
      color: 1
  mapped_ins:
    - panel_jack_id: 1
      ins:
        - module_id: 3
          jack_id: 4
      alias_name: MapIn1
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
      alias_name: MapOut2
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
    - name: MKSet0
      set:
        - panel_knob_id: 1
          module_id: 2
          param_id: 3
          curve_type: 1
          min: 0.1
          max: 0.95
          alias_name: MapKnob1
        - panel_knob_id: 2
          module_id: 3
          param_id: 4
          curve_type: 2
          min: 0.2
          max: 0.85
        - panel_knob_id: 3
          module_id: 4
          param_id: 5
          curve_type: 3
          min: 0.3
          max: 0.75
    - name: MKSet1
      set:
        - panel_knob_id: 4
          module_id: 5
          param_id: 6
          curve_type: 4
          min: 0.4
          max: 0.65
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 4
  vcvModuleStates:
    - module_id: 2
      data: |-
        some string
        Can span lines
        
        No problem
    - module_id: 3
      data: |-
         "$&(*,.02468:<>@BDFHJLNPRTVXZ\^`bdfhjlnprtvxz|~!#%')+-/13579;=?ACEGIKMOQSUWY[]_acegikmoqsuwy{} "$&(*,.02468:<>@BDFHJLNPRTVXZ\^`bdfhjlnprtvxz|~!#%')+-/13579;=?ACEGIKMOQSUWY[]_acegikmoqsuwy{} "$&(*,.02468:<>@BDFHJLNPRTVXZ\^`bdfhjlnprtvxz|~!#%')+-/13579;=?ACEGIKMOQSUWY[]_acegikmoqsuwy{} "$&(*,.02468:<>@BDFHJLNPRTVXZ\^`bdfhjlnprtvxz|~!#%')+-/13579;=?ACEGIKMOQSUWY[]_acegikmoqsuwy{} "$&(*,.02468:<>@BDFHJLNPRTVXZ\^`bdfhjlnprtvxz|~!#%')+-/13579;=?ACEGIKMOQSUWY[]_acegikmoqsuwy{} "$&(*,.02468:<>@BDFHJLNP
)");
	// clang-format on
}
