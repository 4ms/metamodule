#include "../ryml/ryml_serial.hh"
#include "../yaml_to_patch.hh"
#include "doctest.h"
#include <iostream>

TEST_CASE("Correct header and data produced from yaml") {
	std::string yamlhdr =
		// clang-format off
R"(
PatchData:
  patch_name: 'Test Patch 99'
  description: "This is a patch
  without a newline

  and then with"
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
    - alias_name: MappedInJ1
      panel_jack_id: 1
      ins:
        - module_id: 3
          jack_id: 4
    - panel_jack_id: 2
      ins:
        - module_id: 5
          jack_id: 6
        - module_id: 33
          jack_id: 44
      alias_name: MappedInJ2
    - panel_jack_id: 3
      ins:
        - module_id: 77
          jack_id: 88
  mapped_outs:
    - panel_jack_id: 4
      out:
        module_id: 1
        jack_id: 2
    - alias_name: MOut5
      panel_jack_id: 5
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
    - name: Osc Control
      set:
      - alias_name: Knob1 #comment
        panel_knob_id: 1
        module_id: 2
        param_id: 3
        curve_type: 1
        min: 0.1
        max: 0.95
      - panel_knob_id: 2
        alias_name: Knob2
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
    - name: LFO Controls
      set:
      - panel_knob_id: 4
        module_id: 5
        param_id: 6
        curve_type: 4
        min: 0.4
        max: 0.65
  vcvModuleStates:
    - module_id: 2
      data: !!binary |-
        AQJ/gP7/
    - module_id: 3
      data: !!binary |-
        AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/wABAgMEBQYHCAkKCwwNDg8QERITFBUWFxgZGhscHR4fICEiIyQlJicoKSorLC0uLzAxMjM0NTY3ODk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVpbXF1eX2BhYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ent8fX5/gIGCg4SFhoeIiYqLjI2Oj5CRkpOUlZaXmJmam5ydnp+goaKjpKWmp6ipqqusra6vsLGys7S1tre4ubq7vL2+v8DBwsPExcbHyMnKy8zNzs/Q0dLT1NXW19jZ2tvc3d7f4OHi4+Tl5ufo6err7O3u7/Dx8vP09fb3+Pn6+/z9/v8AAQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vv8/f7/AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/w==
)";
	// clang-format on

	PatchData pd;
	CHECK(yaml_string_to_patch(yamlhdr, pd));

	CHECK(pd.patch_name.is_equal("Test Patch 99"));

	CHECK(pd.description.is_equal("This is a patch without a newline\nand then with"));

	CHECK(pd.module_slugs.size() == 4);
	CHECK(pd.module_slugs[0].is_equal("PanelMedium"));
	CHECK(pd.module_slugs[1].is_equal("Module1"));
	CHECK(pd.module_slugs[2].is_equal("Module2"));
	CHECK(pd.module_slugs[3].is_equal("Module3"));

	CHECK(pd.int_cables.size() == 2);
	CHECK(pd.int_cables[0].out == Jack{1, 2});
	CHECK(pd.int_cables[0].ins[0] == Jack{3, 4});
	CHECK(pd.int_cables[0].ins[1] == Jack{5, 6});
	CHECK(pd.int_cables[0].color.has_value() == false);
	CHECK(pd.int_cables[1].out == Jack{11, 22});
	CHECK(pd.int_cables[1].ins[0] == Jack{33, 44});
	CHECK(pd.int_cables[1].ins[1] == Jack{55, 66});
	CHECK(pd.int_cables[1].ins[2] == Jack{77, 88});
	CHECK(pd.int_cables[1].color.value() == 1);

	CHECK(pd.mapped_ins.size() == 3);
	CHECK(pd.mapped_ins[0].alias_name.is_equal("MappedInJ1"));
	CHECK(pd.mapped_ins[0].panel_jack_id == 1);
	CHECK(pd.mapped_ins[0].ins[0] == Jack{3, 4});
	CHECK(pd.mapped_ins[1].alias_name.is_equal("MappedInJ2"));
	CHECK(pd.mapped_ins[1].panel_jack_id == 2);
	CHECK(pd.mapped_ins[1].ins[0] == Jack{5, 6});
	CHECK(pd.mapped_ins[1].ins[1] == Jack{33, 44});
	CHECK(pd.mapped_ins[2].alias_name.is_equal(""));
	CHECK(pd.mapped_ins[2].panel_jack_id == 3);
	CHECK(pd.mapped_ins[2].ins[0] == Jack{77, 88});

	CHECK(pd.mapped_outs.size() == 2);
	CHECK(pd.mapped_outs[0].alias_name.is_equal(""));
	CHECK(pd.mapped_outs[0].panel_jack_id == 4);
	CHECK(pd.mapped_outs[0].out == Jack{1, 2});
	CHECK(pd.mapped_outs[1].alias_name.is_equal("MOut5"));
	CHECK(pd.mapped_outs[1].panel_jack_id == 5);
	CHECK(pd.mapped_outs[1].out == Jack{11, 22});

	CHECK(pd.static_knobs.size() == 5);
	CHECK(pd.static_knobs[0].module_id == 1);
	CHECK(pd.static_knobs[0].param_id == 2);
	CHECK(pd.static_knobs[0].value == 0.3f);
	CHECK(pd.static_knobs[1].module_id == 2);
	CHECK(pd.static_knobs[1].param_id == 3);
	CHECK(pd.static_knobs[1].value == 0.4f);
	CHECK(pd.static_knobs[2].module_id == 3);
	CHECK(pd.static_knobs[2].param_id == 4);
	CHECK(pd.static_knobs[2].value == 0.5f);
	CHECK(pd.static_knobs[3].module_id == 4);
	CHECK(pd.static_knobs[3].param_id == 5);
	CHECK(pd.static_knobs[3].value == 0.6f);
	CHECK(pd.static_knobs[4].module_id == 5);
	CHECK(pd.static_knobs[4].param_id == 6);
	CHECK(pd.static_knobs[4].value == 0.7f);

	CHECK(pd.knob_sets.size() == 2);
	CHECK(pd.knob_sets[0].name.is_equal("Osc Control"));

	CHECK(pd.knob_sets[0].set[0].panel_knob_id == 1);
	CHECK(pd.knob_sets[0].set[0].alias_name.is_equal("Knob1"));
	CHECK(pd.knob_sets[0].set[0].module_id == 2);
	CHECK(pd.knob_sets[0].set[0].param_id == 3);
	CHECK(pd.knob_sets[0].set[0].curve_type == 1);
	CHECK(pd.knob_sets[0].set[0].min == 0.1f);
	CHECK(pd.knob_sets[0].set[0].max == 0.95f);

	CHECK(pd.knob_sets[0].set[1].panel_knob_id == 2);
	CHECK(pd.knob_sets[0].set[1].alias_name.is_equal("Knob2"));
	CHECK(pd.knob_sets[0].set[1].module_id == 3);
	CHECK(pd.knob_sets[0].set[1].param_id == 4);
	CHECK(pd.knob_sets[0].set[1].curve_type == 2);
	CHECK(pd.knob_sets[0].set[1].min == 0.2f);
	CHECK(pd.knob_sets[0].set[1].max == 0.85f);

	CHECK(pd.knob_sets[0].set[2].panel_knob_id == 3);
	CHECK(pd.knob_sets[0].set[2].module_id == 4);
	CHECK(pd.knob_sets[0].set[2].param_id == 5);
	CHECK(pd.knob_sets[0].set[2].curve_type == 3);
	CHECK(pd.knob_sets[0].set[2].min == 0.3f);
	CHECK(pd.knob_sets[0].set[2].max == 0.75f);

	CHECK(pd.knob_sets[1].name.is_equal("LFO Controls"));

	CHECK(pd.knob_sets[1].set[0].panel_knob_id == 4);
	CHECK(pd.knob_sets[1].set[0].module_id == 5);
	CHECK(pd.knob_sets[1].set[0].param_id == 6);
	CHECK(pd.knob_sets[1].set[0].curve_type == 4);
	CHECK(pd.knob_sets[1].set[0].min == 0.4f);
	CHECK(pd.knob_sets[1].set[0].max == 0.65f);

	CHECK(pd.module_states.size() == 2);

	CHECK(pd.module_states[0].module_id == 2);
	CHECK(pd.module_states[0].state_data.size() == 6);
	CHECK(pd.module_states[0].state_data[0] == 0x01);
	CHECK(pd.module_states[0].state_data[1] == 0x02);
	CHECK(pd.module_states[0].state_data[2] == 0x7F);
	CHECK(pd.module_states[0].state_data[3] == 0x80);
	CHECK(pd.module_states[0].state_data[4] == 0xFE);
	CHECK(pd.module_states[0].state_data[5] == 0xFF);

	CHECK(pd.module_states[1].module_id == 3);
	CHECK(pd.module_states[1].state_data.size() == 1024);
	for (unsigned i = 0; auto c : pd.module_states[1].state_data)
		CHECK(c == (i++ & 0xFF));
}
