from helper import panel_to_components
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

        <circle id="knob-center" cx="4.4" cy="44.44" r="11.34" style="fill: #ff8080"/>
        <circle id="knob-red-big" cx="5.1" cy="11.1" r="15.34" style="fill: red"/>
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
            
        <circle id="button-latch" cx="17.1" cy="161.1" r="5.00" style="fill: #ff8000"/>
        <circle id="button-momentary" cx="18.1" cy="161.1" r="5.00" style="fill: #ffc000"/>
        <circle id="switch-2pos" cx="19.1" cy="161.1" r="5.00" style="fill: #ff0080"/>
        <circle id="switch-1pos" cx="20.1" cy="161.1" r="5.00" style="fill: #ff00c0"/>

        <circle id="widget-yellow" cx="16.1" cy="161.1" r="5.00" style="fill: yellow"/>
        <circle id="widget-ff0" cx="16.1" cy="161.1" r="5.00" style="fill: #ff0"/>
        <circle id="widget-ffff00" cx="16.1" cy="161.1" r="5.00" style="fill: #ffff00"/>

        <circle id="unknown" cx="16.1" cy="161.1" r="5.00" style="fill: #123456"/>

        <path id="ignore-paths" cx="99.1" cy="11.1" r="9.01" style="fill: red"/>
      </g>
    </svg>"""

    #Write data to a file
    testfilename = "test_circle_colors_data.xml"
    with open(testfilename, "w") as f:
        f.write(testdata)

    tree = xml.etree.ElementTree.parse(testfilename)
    components = panel_to_components(tree)
    CHECK_EQ(len(components['params']) , 7, "Found 7 knobs")
    CHECK_EQ(sum(k['knob_style']=='small' for k in components['params']), 2, "... 2 small knobs")
    CHECK_EQ(sum(k['knob_style']=='medium' for k in components['params']), 4, "... 4 medium knobs")
    CHECK_EQ(sum(k['knob_style']=='large' for k in components['params']), 1, "... 1 large knob")
    CHECK_EQ(sum(k['default_value']==0.5 for k in components['params']), 1, "... 1 center-det knob")
    CHECK_EQ(sum(k['default_value']==0.0 for k in components['params']), 6, "... 6 default=0 knobs")

    CHECK_EQ(sum(k['name']=='KNOB_RED' for k in components['params']), 1, "... 1 named 'KNOB_RED'")
    CHECK_EQ(sum(k['display_name']=='Knob Red' for k in components['params']), 1, "... 1 display named 'Knob Red'")
    CHECK_EQ(sum(k['cx']==1.1 and k['cy']==11.11 for k in components['params']), 1, "... 1 knob at x=1.1, y=11.11")

    CHECK_EQ(len(components['inputs']) , 4, "Found 4 input jacks")
    CHECK_EQ(sum(k['signal_type']=='analog' for k in components['inputs']), 3, "... 3 analog inputs")
    CHECK_EQ(sum(k['signal_type']=='gate' for k in components['inputs']), 1, "... 1 digital input")

    CHECK_EQ(len(components['outputs']) , 4, "Found 4 output jacks")
    CHECK_EQ(sum(k['signal_type']=='analog' for k in components['outputs']), 3, "... 3 analog outputs")
    CHECK_EQ(sum(k['signal_type']=='gate' for k in components['outputs']), 1, "... 1 digital output")

    CHECK_EQ(len(components['lights']) , 2, "Found 2 lights")
    CHECK_EQ(len(components['switches']) , 4, "Found 4 switches/buttons")
    CHECK_EQ(sum(k['switch_type']=='latching button' for k in components['switches']), 1, "... 1 latching button")
    CHECK_EQ(sum(k['switch_type']=='momentary button' for k in components['switches']), 1, "... 1 momentary button")
    CHECK_EQ(sum(k['switch_type']=='2-position toggle' for k in components['switches']), 1, "... 1 2pos switch")
    CHECK_EQ(sum(k['switch_type']=='3-position toggle' for k in components['switches']), 1, "... 1 3pos switch")
    CHECK_EQ(len(components['widgets']) , 3, "Found 3 custom widgets")

if __name__ == "__main__":
    test_circle_colors()

