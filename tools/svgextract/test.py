from actions.infofile import panel_to_components
from helpers.util import format_for_display
from helpers.util import format_as_enum_item
from helpers.util import remove_trailing_dash_number

import xml.etree.ElementTree

def CHECK(check, desc):
    if check == True:
        print(f"[pass]: {desc}")
    else:
        print(f"****FAIL: {desc}")

def CHECK_EQ(actual, expected, desc):
    if actual == expected:
        print(f"[pass]: {desc}")
    else:
        print(f"****FAIL: {desc}. Actual: {actual} Expected: {expected}")

def test_circle_colors():
    # Create test data
    testdata = """<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 229.55 364.25">
      <g id="components">
        <circle id="Knob Red" cx="1.1" cy="11.11" r="11.34" style="fill: red"/>
        <circle id="knob-shorthex" cx="2.2" cy="22.22" r="11.34" style="fill: #f00"/>
        <circle id="knob-fullhex" cx="3.3" cy="33.33" r="11.34" style="fill: #ff0000"/>

        <circle id="knob-25" cx="4.4" cy="44.44" r="11.34" style="fill: #ff0020"/>
        <circle id="knob-center" cx="4.3" cy="44.44" r="11.34" style="fill: #ff0040"/>
        <circle id="knob-75" cx="4.2" cy="44.44" r="11.34" style="fill: #ff0060"/>
        <circle id="knob-100" cx="4.1" cy="44.44" r="11.34" style="fill: #ff0080"/>
        <circle id="knob-red-big" cx="5.1" cy="11.1" r="31.38" style="fill: red"/>
        <circle id="knob-red-small" cx="6.1" cy="11.1" r="9.01" style="fill: red"/>
        <circle id="knob-red-small" cx="7.1" cy="11.1" r="9.01" style="fill: red"/>

        <circle id="in-analog-lime" cx="8.1" cy="88.1" r="5.00" style="fill: lime"/>
        <circle id="in-analog-0f0" cx="9.1" cy="99.1" r="5.00" style="fill: #0f0"/>
        <circle id="in-analog-00ff00" cx="10.1" cy="101.1" r="5.00" style="fill: #00ff00"/>
        <circle id="in-digital" cx="11.1" cy="111.1" r="5.00" style="fill: #80ff80"/>

        <circle id="out-analog-blue" cx="12.1" cy="128.1" r="5.00" style="fill: blue"/>
        <circle id="out-analog-00f" cx="13.1" cy="139.1" r="5.00" style="fill: #00f"/>
        <circle id="out-analog-0000ff" cx="14.1" cy="141.1" r="5.00" style="fill: #0000ff"/>
        <circle id="out-digital" cx="15.1" cy="151.1" r="5.00" style="fill: #8080ff"/>

        <circle id="led" cx="16.1" cy="161.1" r="5.00" style="fill: #f0f"/>
        <circle id="led" cx="16.1" cy="161.1" r="5.00" style="fill: #ff00ff"/>
        <circle cx="10" cy="10" r="5.00" style="fill: #f0f"/>
            
        <circle id="button-latch" cx="17.1" cy="161.1" r="5.00" style="fill: #ff8000"/>
        <circle id="button-momentary" cx="18.1" cy="161.1" r="5.00" style="fill: #ffc000"/>
        <circle id="switch-2pos" cx="19.1" cy="161.1" r="5.00" style="fill: #ff8080"/>
        <circle id="switch-1pos" cx="20.1" cy="161.1" r="5.00" style="fill: #ffc080"/>

        <circle id="widget-yellow" cx="16.1" cy="161.1" r="5.00" style="fill: yellow"/>
        <circle id="widget-ff0" cx="16.1" cy="161.1" r="5.00" style="fill: #ff0"/>
        <circle id="widget-ffff00" cx="16.1" cy="161.1" r="5.00" style="fill: #ffff00"/>

        <circle id="unknown-color" cx="16.1" cy="161.1" r="5.00" style="fill: #123456"/>

        <circle id="rotary-med" cx="96.1" cy="161.1" r="11.34" style="fill: #C000C0"/>
        <circle id="rotary-sm" cx="96.1" cy="161.1" r="9.0" style="fill: #C000C0"/>
        <circle id="rotary-large" cx="96.1" cy="161.1" r="31" style="fill: #C000C0"/>

        <path id="ignore-paths" cx="99.1" cy="11.1" r="9.01" style="fill: red"/>

        <text id="slug">TestModule</text>
        <text id="modulename">Test Module</text>
      </g>
    </svg>"""

    #Write data to a file
    testfilename = "test_circle_colors_data.xml"
    with open(testfilename, "w") as f:
        f.write(testdata)

    tree = xml.etree.ElementTree.parse(testfilename)
    components = panel_to_components(tree)
    CHECK_EQ(len(components['params']) , 10, "Found 10 knobs")
    CHECK_EQ(sum(k['knob_style']=='Small' for k in components['params']), 2, "... 2 small knobs")
    CHECK_EQ(sum(k['knob_style']=='Medium' for k in components['params']), 7, "... 7 medium knobs")
    CHECK_EQ(sum(k['knob_style']=='Large' for k in components['params']), 1, "... 1 large knob")
    CHECK_EQ(sum(k['default_value']=="0.25f" for k in components['params']), 1, "... 1 default 25% knob")
    CHECK_EQ(sum(k['default_value']=="0.5f" for k in components['params']), 1, "... 1 default 50% knob")
    CHECK_EQ(sum(k['default_value']=="0.75f" for k in components['params']), 1, "... 1 default 75% knob")
    CHECK_EQ(sum(k['default_value']=="1.0f" for k in components['params']), 1, "... 1 default 100% knob")
    CHECK_EQ(sum(k['default_value']=="0.0f" for k in components['params']), 6, "... 6 default=0% knobs")

    CHECK_EQ(sum(k['enum_name']=='Knob_Red' for k in components['params']), 1, "... 1 named 'Knob_Red'")
    CHECK_EQ(sum(k['display_name']=='Knob Red' for k in components['params']), 1, "... 1 display named 'Knob Red'")
    CHECK_EQ(sum(k['cx']==1.1 and k['cy']==11.11 for k in components['params']), 1, "... 1 knob at x=1.1, y=11.11")

    CHECK_EQ(len(components['inputs']) , 4, "Found 4 input jacks")
    CHECK_EQ(sum(k['signal_type']=='Analog' for k in components['inputs']), 3, "... 3 analog inputs")
    CHECK_EQ(sum(k['signal_type']=='Gate' for k in components['inputs']), 1, "... 1 digital input")

    CHECK_EQ(len(components['outputs']) , 4, "Found 4 output jacks")
    CHECK_EQ(sum(k['signal_type']=='Analog' for k in components['outputs']), 3, "... 3 analog outputs")
    CHECK_EQ(sum(k['signal_type']=='Gate' for k in components['outputs']), 1, "... 1 digital output")

    CHECK_EQ(len(components['lights']) , 3, "Found 3 lights")
    CHECK_EQ(len(components['switches']) , 7, "Found 7 switches/buttons/encoders")
    CHECK_EQ(sum(k['switch_type']=='LatchingButton' for k in components['switches']), 1, "... 1 latching button")
    CHECK_EQ(sum(k['switch_type']=='MomentaryButton' for k in components['switches']), 1, "... 1 momentary button")
    CHECK_EQ(sum(k['switch_type']=='Toggle2pos' for k in components['switches']), 1, "... 1 2pos switch")
    CHECK_EQ(sum(k['switch_type']=='Toggle3pos' for k in components['switches']), 1, "... 1 3pos switch")
    CHECK_EQ(sum(k['switch_type']=='Encoder' for k in components['switches']), 3, "... 3 encoders")
    CHECK_EQ(len(components['widgets']) , 3, "Found 3 custom widgets")

    CHECK_EQ(sum((k['cx']==10 and k['cy']==10) for k in components['lights']), 1, "... 1 (random named) light at 10, 10")

    CHECK_EQ(components['slug'], "TestModule", "Slug is TestModule")
    CHECK_EQ(components['ModuleName'], "Test Module", "ModuleName is Test Module")

def test_format_for_display():
    CHECK_EQ(remove_trailing_dash_number("Knob-1"), "Knob", "Strips trailing -#: Knob-1 => Knob")
    CHECK_EQ(remove_trailing_dash_number("Shift--1"), "Shift-", "...Can end in a '-': Shift--1 => Shift-")
    CHECK_EQ(remove_trailing_dash_number("Shift-"), "Shift-", "...Keeps dash if no number following: Shift- => Shift-")
    CHECK_EQ(remove_trailing_dash_number("Knob-12"), "Knob", "... Knob-12 => Knob")
    CHECK_EQ(format_for_display(remove_trailing_dash_number("Cross_FM-2")), "Cross FM", "format for display and strip dash: Cross_FM-2 ==> Cross FM")
    CHECK_EQ(format_for_display("Other_Knob"), "Other Knob", "... underscore => space: Other_Knob => Other Knob")
    CHECK_EQ(format_for_display("other_knob_Cap"), "other knob Cap", "... Does not change capitalization")
    CHECK_EQ(format_as_enum_item("On|Off"), "On_OR_Off", "... | => _OR_");
    CHECK_EQ(format_as_enum_item("+Env"), "PEnv", "... + => P");
    CHECK_EQ(format_as_enum_item("-Env"), "NEnv", "... - => N");


if __name__ == "__main__":
    test_circle_colors()
    test_format_for_display()

