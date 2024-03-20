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

	pd.module_states.push_back({2, std::vector<uint8_t>{0x1, 0x2, 0x7F, 0x80, 0xFE, 0xFF}});

	std::vector<uint8_t> vec(1024);
	for (unsigned i = 0; auto &c : vec)
		c = i++;
	pd.module_states.push_back({3, vec});

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
      data: !!binary |-
        AQJ/gP7/
    - module_id: 3
      data: !!binary |-
        AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/wABAgMEBQYHCAkKCwwNDg8QERITFBUWFxgZGhscHR4fICEiIyQlJicoKSorLC0uLzAxMjM0NTY3ODk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVpbXF1eX2BhYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ent8fX5/gIGCg4SFhoeIiYqLjI2Oj5CRkpOUlZaXmJmam5ydnp+goaKjpKWmp6ipqqusra6vsLGys7S1tre4ubq7vL2+v8DBwsPExcbHyMnKy8zNzs/Q0dLT1NXW19jZ2tvc3d7f4OHi4+Tl5ufo6err7O3u7/Dx8vP09fb3+Pn6+/z9/v8AAQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vv8/f7/AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/w==
)");
	// clang-format on
}
