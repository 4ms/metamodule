#!/usr/bin/env python3
import sys
import os
import re
import xml.etree.ElementTree
import random
import string
from xml_helper import register_all_namespaces

# Version check
f"Python 3.6+ is required"

ns = {
    "svg": "http://www.w3.org/2000/svg",
    "inkscape": "http://www.inkscape.org/namespaces/inkscape",
}

class UserException(Exception):
    pass


def input_default(prompt, default=""):
    str = input(f"{prompt} [{default}]: ")
    if str == "":
        return default
    return str


def is_valid_slug(slug):
    return re.match(r'^[a-zA-Z0-9_\-]+$', slug) != None


def str_to_identifier(s):
    if not s:
        return "_"
    # Identifiers can't start with a number
    if s[0].isdigit():
        s = "_" + s
    # Capitalize first letter
    s = s.title()
    # Replace special characters with underscore
    s = re.sub(r'\W', '_', s)
    return s


def remove_trailing_dash_number(name):
    #Chop off -[\d\d] or -[\d]
    if name[-3:-2] == '-' and name[-2:].isdigit() and name[-1:].isdigit():
        name = name[:-3]
    if name[-2:-1] == '-' and name[-1:].isdigit():
        name = name[:-2]
    return name


def format_for_display(comp_name):
    return comp_name.replace('_',' ')


def format_as_enum_item(comp_name):
    return str_to_identifier(comp_name)


def get_knob_style_from_radius(radius):
    r = float(radius)
    if r < 10 and r > 3:
        return "Small" #<10: 8.5 typical
    if r < 20:
        return "Medium" #10-20: 17.01 typical
    if r < 40:
        return "Large" #15-40: 31.18 typical
    return "Medium" #under 3 or over 40 is not a known knob


def get_button_style_from_radius(radius):
    r = float(radius)
    if r < 10 and r > 3:
        return "small" #<10: 7.09 typical?
    if r < 40:
        return "medium" #10-40: 11.34 typical
    return "unknown" #under 3 or over 40 is not a known style


def expand_color_synonyms(color):
    if color == 'red' or color == '#f00': color = '#ff0000'
    if color == 'lime' or color == '#0f0': color = '#00ff00'
    if color == 'blue' or color == '#00f': color = '#0000ff'
    if color == 'yellow' or color == '#ff0': color = '#ffff00'
    if color == 'magenta' or color == '#f0f': color = '#ff00ff'
    if color == 'cyan' or color == '#0ff': color = '#00ffff'
    if color == 'black' or color == '#000': color = '#000000'
    if color == 'white' or color == '#fff': color = '#ffffff'
    return color


def deduce_dpi(root):
    widthInches = get_dim_inches(root.get('width'))
    heightInches = get_dim_inches(root.get('height'))
    viewBox = root.get('viewBox')
    if widthInches == 0 or heightInches == 0 or viewBox is None:
        print("WARNING: DPI cannot be deduced, width, height, or viewBox is missing or 0 in root node. Using 72dpi")
        return 72

    viewBoxDims = viewBox.split(" ")
    viewWidth = float(viewBoxDims[2]) - float(viewBoxDims[0])
    viewHeight = float(viewBoxDims[3]) - float(viewBoxDims[1])
    hDPI = round(viewWidth / widthInches)
    vDPI = round(viewHeight / heightInches)
    if vDPI is not hDPI:
        print(f"WARNING: Horizontal DPI is {hDPI} and Vertical DPI is {vDPI}, which are not equal. Using horizontal value")
    else:
        print(f"DPI deduced as {hDPI}")

    return hDPI


def get_dim_inches(dimString):
    if dimString is None:
        return 0
    dimInches = float(re.sub("[^0-9.-]","", dimString))
    if dimInches is None:
        return 0
    if re.sub("[0-9.-]","", dimString) == "mm":
        dimInches /= 25.4
    return dimInches


def panel_to_components(tree):

    components = {}
    #TODO: extract knob long name and description (or is that to be done manually?)
    #.... maybe SVG id = "ShortName#LongName" or "ShortName"
    #.... and description is in some help file

    # Get components layer/group
    root = tree.getroot()
    groups = root.findall(".//svg:g[@inkscape:label='components']", ns)
    # Illustrator uses `id` for the group name.
    if len(groups) < 1:
        groups = root.findall(".//svg:g[@id='components']", ns)
    if len(groups) < 1:
        raise UserException("ERROR: Could not find \"components\" layer on panel")
    components_group = groups[0]

    # Deduce DPI and HP:
    components['dpi'] = deduce_dpi(root)
    components['HP'] = round(get_dim_inches(root.get('width')) / 0.2)
    print(f"HP deduced as {components['HP']}")

    # Set default slug and ModuleName
    components['slug'] = "UNNAMED"
    components['ModuleName'] = "Unnamed"

    # Scan all text elements: look for slug and ModuleName
    texts = components_group.findall(".//svg:text", ns)
    for t in texts:
        name = t.get('{http://www.inkscape.org/namespaces/inkscape}label')
        if name is None:
            name = t.get('id')
        if name is None:
            name = t.get('data-name')
        if name is None:
            continue

        if name == "slug":
            components['slug'] = ""
            for m in t.itertext():
                components['slug'] += m

        if name == "modulename":
            components['ModuleName'] = ""
            for m in t.itertext():
                components['ModuleName'] += m

    if components['slug'] == "UNNAMED":
        print("WARNING: No text element with name or id 'slug' was found in the 'components' layer/group. Setting slug to 'UNNAMED'.")
    else:
        print(f"Slug found: \"{components['slug']}\"")

    if components['ModuleName'] is None:
        print("WARNING: No text element with name or id 'modulename' was found in the 'components' layer/group. Setting ModuleName to 'Unnamed'")
    else:
        print(f"Module Name found: \"{components['ModuleName']}\"")


    # Scan all circles and rects for components
    components['params'] = []
    components['inputs'] = []
    components['outputs'] = []
    components['lights'] = []
    components['widgets'] = []
    components['switches'] = []

    circles = components_group.findall(".//svg:circle", ns)
    rects = components_group.findall(".//svg:rect", ns)

    for el in circles + rects:
        c = {}
        # Get name
        name = el.get('{http://www.inkscape.org/namespaces/inkscape}label')
        if name is None:
            name = el.get('data-name')
        if name is None:
            name = el.get('id')
            if name is not None:
                name = remove_trailing_dash_number(name)
        if name is None:
            name = ''.join(random.choices(string.ascii_uppercase, k=6))
            print("Unnamed component found: generating random name: " + name)
        c['raw_name'] = name
        c['display_name'] = format_for_display(name)
        c['enum_name'] = format_as_enum_item(name)

        # Get position
        if el.tag == "{http://www.w3.org/2000/svg}rect":
            x = float(el.get('x'))
            y = float(el.get('y'))
            width = float(el.get('width'))
            height = float(el.get('height'))
            c['x'] = round(x, 3)
            c['y'] = round(y, 3)
            c['width'] = round(width, 3)
            c['height'] = round(height, 3)
            c['cx'] = round(x + width / 2, 3)
            c['cy'] = round(y + height / 2, 3)
        elif el.tag == "{http://www.w3.org/2000/svg}circle":
            cx = float(el.get('cx'))
            cy = float(el.get('cy'))
            c['cx'] = round(cx, 3)
            c['cy'] = round(cy, 3)

        # Get color --> component type
        style = el.get('style')
        color_match = re.search(r'fill:\s*(.*)', style)
        color = ''
        color = color_match.group(1).lower() if color_match is not None else ''
        color = expand_color_synonyms(color)
        c['color'] = color

        #Red: Default fully-CCW knob
        if color.startswith("#ff00") and color!="#ff00ff":
            def_val_int = int(color[-2:], 16)
            if def_val_int <= 128:
                c['encoder'] = False
                c['default_value'] = str(def_val_int / 128) + "f"
                c['knob_style'] = get_knob_style_from_radius(el.get('r'))
                components['params'].append(c)

        #Deep Purple: Encodeer
        elif color == '#c000c0':
            c['encoder'] = True
            c['default_value'] = "0.0f"
            c['knob_style'] = get_knob_style_from_radius(el.get('r'))
            components['params'].append(c)

        #Green: Input jack, analog (CV or audio): 
        elif color == '#00ff00':
            c['signal_type'] = "Analog"
            components['inputs'].append(c)

        #Light Green: Input jack, digital (gate or trig):
        elif color == '#80ff80':
            c['signal_type'] = "Gate"
            components['inputs'].append(c)

        #Blue: Output jack, analog (CV or audio)
        elif color == '#0000ff':
            c['signal_type'] = "Analog"
            components['outputs'].append(c)

        #Light Blue: Output jack, digital (gate or trig):
        elif color == '#8080ff':
            c['signal_type'] = "Gate"
            components['outputs'].append(c)

        #Magenta: LED
        elif color == '#ff00ff':
            #TODO: led color is in the name in parenthesis
            c['led_color'] = "Red"
            components['lights'].append(c)

        #Orange: Button - Latching
        elif color == '#ff8000':
            c['switch_type'] = "LatchingButton"
            components['switches'].append(c)

        #Light Orange: Button - Momentary
        elif color == '#ffc000':
            c['switch_type'] = "MomentaryButton"
            components['switches'].append(c)

        #Deep Pink: Switch - 2pos
        elif color == '#ff8080':
            c['switch_type'] = "Toggle2pos"
            components['switches'].append(c)

        #Hot Pink: Switch - 3pos
        elif color == '#ffc080':
            c['switch_type'] = "Toggle3pos"
            components['switches'].append(c)

        elif color == '#ffff00':
            components['widgets'].append(c)
        else:
            print(f"Unknown color: {color} found at {cx},{cy}. Skipping.")

    # Sort components
    top_left_sort = lambda w: (w['cy'], w['cx'])
    components['params'] = sorted(components['params'], key=top_left_sort)
    components['inputs'] = sorted(components['inputs'], key=top_left_sort)
    components['outputs'] = sorted(components['outputs'], key=top_left_sort)
    components['lights'] = sorted(components['lights'], key=top_left_sort)
    components['widgets'] = sorted(components['widgets'], key=top_left_sort)
    components['switches'] = sorted(components['switches'], key=top_left_sort)

    print(f"Found {len(components['params'])} params, {len(components['inputs'])} inputs, {len(components['outputs'])} outputs, {len(components['lights'])} lights, and {len(components['widgets'])} custom widgets.")
    return components


def make_enum(enum_name, item_prefix, list):
    if len(list) == 0:
        return ""
    if len(enum_name) > 0:
        enum_name = enum_name + " "
    source = f"""
    enum {enum_name}{{"""
    i = 0
    for k in list:
        source += f"""
        {item_prefix}{k['enum_name']} = {str(i)},"""
        i = i + 1
    source += f"""
    }};"""
    return source


def components_to_infofile(components):
    slug = components['slug']
    DPI = components['dpi']

    #TODO: embed knob long name vs short name in svg
    source = f"""#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct {slug}Info : ModuleInfoBase {{
    static constexpr auto NameChars = CoreProcessor::NameChars;
    static constexpr auto LongNameChars = CoreProcessor::LongNameChars;

    static constexpr std::string_view slug{{"{slug}"}};
    static inline const StaticString<LongNameChars> description{{"{components['ModuleName']}"}};
    static constexpr uint32_t width_hp = {components['HP']};
    static constexpr std::string_view svg_filename{{"res/{slug.lower()}-artwork.svg"}};

    static constexpr int NumKnobs = {len(components['params'])};
    {make_enum("", "Knob", components['params'])}

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{{{"""
    for k in components['params']:
        source += f"""
        {{
            .id = Knob{k['enum_name']},
            .x_mm = px_to_mm<{DPI}>({k['cx']}f),
            .y_mm = px_to_mm<{DPI}>({k['cy']}f),
            .short_name = "{k['display_name']}",
            .long_name = "{k['display_name']}",
            .default_val = {k['default_value']},
            .knob_style = KnobDef::{k['knob_style']},
        }},""" 
    source += f"""
    }}}};

    static constexpr int NumInJacks = {len(components['inputs'])};
    {make_enum("", "Input", components['inputs'])}

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{{{"""
    for k in components['inputs']:
        source += f"""
        {{
            .id = Input{k['enum_name']},
            .x_mm = px_to_mm<{DPI}>({k['cx']}f),
            .y_mm = px_to_mm<{DPI}>({k['cy']}f),
            .short_name = "{k['display_name']}",
            .long_name = "{k['display_name']}",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::{"Gate" if k['signal_type']=='gate' else 'Analog'},
        }},""" 
    source += f"""
    }}}};

    static constexpr int NumOutJacks = {len(components['outputs'])};
    {make_enum("", "Output", components['outputs'])}

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{{{"""
    for k in components['outputs']:
        source += f"""
        {{
            .id = Output{k['enum_name']},
            .x_mm = px_to_mm<{DPI}>({k['cx']}f),
            .y_mm = px_to_mm<{DPI}>({k['cy']}f),
            .short_name = "{k['display_name']}",
            .long_name = "{k['display_name']}",
            .signal_type = OutJackDef::{"Gate" if k['signal_type']=='gate' else 'Analog'},
        }},""" 
    source += f"""
    }}}};

    static constexpr int NumSwitches = {len(components['switches'])};
    {make_enum("", "Switch", components['switches'])}

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{{{"""
    for k in components['switches']:
        source += f"""
        {{
            .id = Switch{k['enum_name']},
            .x_mm = px_to_mm<{DPI}>({k['cx']}f),
            .y_mm = px_to_mm<{DPI}>({k['cy']}f),
            .short_name = "{k['display_name']}",
            .long_name = "{k['display_name']}",
            .switch_type = SwitchDef::{k['switch_type']},
        }},""" 
    source += f"""
    }}}};

    static constexpr int NumDiscreteLeds = {len(components['lights'])};
    {make_enum("", "Led", components['lights'])}

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{{{"""
    for k in components['lights']:
        source += f"""
        {{
            .id = Led{k['enum_name']},
            .x_mm = px_to_mm<{DPI}>({k['cx']}f),
            .y_mm = px_to_mm<{DPI}>({k['cy']}f),
            .led_color = LedDef::{k['led_color']},
        }},""" 
    source += f"""
    }}}};

}};
"""
    return source


def createInfoFile(svgFilename, infoFilePath):
    if os.path.isdir(infoFilePath) == False:
        print(f"Not a directory: {infoFilePath}. Aborting without creating an info file.")
        return
    if os.path.isfile(svgFilename) == False:
        print(f"Not a file: {svgFilename}. Aborting without creating an info file.")
        return
    register_all_namespaces(svgFilename)
    tree = xml.etree.ElementTree.parse(svgFilename)
    components = panel_to_components(tree)
    infoFileText = components_to_infofile(components)
    infoFileName = os.path.join(infoFilePath, components['slug'].lower()+"_info.hh")
    with open(infoFileName, "w") as f:
        f.write(infoFileText)
        print(f"Wrote info file: {infoFileName}")
    return components['slug']


def extractArtwork(svgFilename, artworkFilename):
    print(f"reading from {svgFilename}, writing to {artworkFilename}")
    register_all_namespaces(svgFilename)

    tree = xml.etree.ElementTree.parse(svgFilename)
    root = tree.getroot()
    comps = root.findall(".//*[@id='components']",ns)
    if len(comps) == 0:
        print("No group (or any element) with id = 'components' found in svg file")
        return
    if len(comps) > 1:
        print("More than 1 group or element with id = 'components' found in svg file. Using the first one.")

    g = comps[0]
    g.clear()
    print("Removed components layer")
    tree.write(artworkFilename)
    print(f"Wrote artwork file: {artworkFilename}")

    #TODO: convert artwork file to PNG
    #resize to 240px height
    #save in METAMODULE_PNG_DIR
    #Run lvgl script


def processSvg(svgFilename):
    outputpath = os.getenv('METAMODULE_INFO_DIR')
    if outputpath is None:
        outputpath = input_default("Directory to save ModuleInfo file", os.path.join(os.path.dirname(os.path.realpath(__file__)),"../CoreModules/info"))
    slug = createInfoFile(svgFilename, outputpath)
    if slug is None:
        return

    outputpath = os.getenv('METAMODULE_ARTWORK_DIR')
    if outputpath is None:
        outputpath = input_default("Directory to save SVG artwork file", os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../vcv/res"))
    extractArtwork(svgFilename, os.path.join(outputpath, slug.lower() + "-artwork.svg"))


def usage(script):
    text = f"""VCV Rack Plugin Helper Utility

Usage: {script} <command> ...
Commands:

processsvg [input svg file name]
    Runs createinfo and extractart on the given file. 
    Uses environmant variables $METAMODULE_INFO_DIR and $METAMODULE_ARTWORK_DIR if found,
    otherwise prompts user for the values

createinfo [input svg file name] [output path for ModuleInfo file]
    Creates a ModuleInfo struct and saves it to a file in the given path.
    The file will be named "slug_info.hh", where "slug" is the lower-case
    string of the text element with name/id "slug" found in the components layer/group
    of the SVG file.
    File will be overwritten if it exists.

extractart [input svg file name] [output SVG file name]
    Saves a new SVG file with the components layer removed

"""
    print(text)


def parse_args(args):
    script = args.pop(0)
    if len(args) < 2:
        usage(script)
        return

    cmd = args.pop(0)
    inputfile = args.pop(0)

    if cmd == 'processsvg':
        processSvg(inputfile)
        return

    if len(args) == 0:
        usage(script)
        return

    output= args.pop(0)

    if cmd == 'createinfo':
        createInfoFile(inputfile, output)
        return

    if cmd == 'extractart':
        extractArtwork(inputfile, output)
        return



if __name__ == "__main__":
    try:
        parse_args(sys.argv)
    except KeyboardInterrupt:
        pass
    except UserException as e:
        print(e)
        sys.exit(1)
