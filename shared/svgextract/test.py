from helper import panel_to_components
import xml.etree.ElementTree

def CHECK(check, desc):
    if check == True:
        print(f"[pass]: {desc}")
    else:
        print(f"!FAIL!: {desc}")

def test_circle_colors():
    # Create test data
    testdata = """<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 229.55 364.25">
      <g id="components">
        <circle cx="175.8" cy="77.47" r="11.34" style="fill: red"/>
        <circle cx="114.45" cy="61.09" r="11.34" style="fill: red"/>
        <circle cx="31.7" cy="144.09" r="11.34" style="fill: red"/>
        <circle cx="52.85" cy="77.47" r="11.34" style="fill: #ff8080"/>
        <circle cx="61.02" cy="207.97" r="11.34" style="fill: #ff8080"/>
        <circle cx="167.9" cy="208.04" r="11.34" style="fill: #ff8080"/>
        <circle cx="197.21" cy="144.09" r="11.34" style="fill: #ff8080"/>
        <circle cx="114.63" cy="140.8" r="17.01" style="fill: #ff8080"/>
        <circle cx="114.46" cy="207.68" r="7.09" style="fill: red"/>
        <circle cx="213.27" cy="102.85" r="8.5" style="fill: #ff0"/>
        <circle cx="213.27" cy="201.64" r="8.5" style="fill: #ff0"/>
        <circle cx="15.99" cy="214.89" r="8.5" style="fill: #ff0"/>
        <circle cx="15.99" cy="102.85" r="8.5" style="fill: #ff0"/>
        <circle cx="208.59" cy="42.37" r="11.34" style="fill: #ff0"/>
        <circle cx="20.67" cy="42.37" r="11.34" style="fill: #ff0"/>
        <circle cx="133.35" cy="262.62" r="11.34" style="fill: lime"/>
        <circle cx="95.91" cy="262.62" r="11.34" style="fill: lime"/>
        <circle cx="21.03" cy="262.62" r="11.34" style="fill: lime"/>
        <circle cx="21.03" cy="305.82" r="11.34" style="fill: lime"/>
        <circle cx="58.47" cy="275.72" r="11.34" style="fill: lime"/>
        <circle cx="58.47" cy="318.92" r="11.34" style="fill: lime"/>
        <circle cx="95.91" cy="305.82" r="11.34" style="fill: lime"/>
        <circle cx="133.35" cy="305.82" r="11.34" style="fill: lime"/>
        <circle cx="170.79" cy="275.72" r="7.09" style="fill: lime"/>
        <circle cx="170.79" cy="318.92" r="7.09" style="fill: lime"/>
        <circle cx="207.81" cy="262.62" r="11.34" style="fill: blue"/>
        <circle cx="208.19" cy="305.82" r="11.34" style="fill: blue"/>
      </g>
    </svg>"""

    #Write data to a file
    testfilename = "test_circle_colors_data.xml"
    with open(testfilename, "w") as f:
        f.write(testdata)

    tree = xml.etree.ElementTree.parse(testfilename)
    components = panel_to_components(tree)

test_circle_colors()

