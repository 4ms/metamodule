import os
import random
import string
import xml.etree.ElementTree
from helpers.xml_helper import register_all_namespaces
from helpers.util import *
from helpers.svg_parse_helpers import *

def createInfoFile(svgFilename, infoFilePath = None):
    if infoFilePath == None:
        infoFilePath = os.getenv('METAMODULE_INFO_DIR')
        if infoFilePath is None:
            infoFilePath = input_default("Directory to save ModuleInfo file", pathFromHere("../CoreModules/info"))

    if os.path.isdir(infoFilePath) == False:
        Log(f"Not a directory: {infoFilePath}. Aborting without creating an info file.")
        return

    if os.path.isfile(svgFilename) == False:
        Log(f"Not a file: {svgFilename}. Aborting without creating an info file.")
        return

    register_all_namespaces(svgFilename)
    tree = xml.etree.ElementTree.parse(svgFilename)
    components = panel_to_components(tree)
    infoFileText = components_to_infofile(components)
    infoFileName = os.path.join(infoFilePath, components['slug']+"_info.hh")
    with open(infoFileName, "w") as f:
        f.write(infoFileText)
        Log(f"Wrote info file: {infoFileName}")
    
    return components['slug']


def panel_to_components(tree):

    components = {}
    #TODO: extract knob long name and description (or is that to be done manually?)
    #.... maybe SVG id = "ShortName#LongName" or "ShortName"
    #.... and description is in some help file

    root = tree.getroot()

    # Deduce DPI and HP:
    components['dpi'] = deduce_dpi(root)
    components['HP'] = round(get_dim_inches(root.get('width')) / 0.2)
    Log(f"HP deduced as {components['HP']}")

    components_group = get_components_group(root)
    components['slug'], components['ModuleName'] = find_slug_and_modulename(components_group)

    if components['slug'] == "Unnamed":
        Log("WARNING: No text element with name or id 'slug' was found in the 'components' layer/group. Setting slug to 'UNNAMED'.")
    else:
        Log(f"Slug found: \"{components['slug']}\"")

    if components['ModuleName'] == "Unnamed":
        Log("WARNING: No text element with name or id 'modulename' was found in the 'components' layer/group. Setting ModuleName to 'Unnamed'")
    else:
        Log(f"Module Name found: \"{components['ModuleName']}\"")

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
            Log("Unnamed component found: generating random name: " + name)
        c['raw_name'] = name
        c['display_name'] = format_for_display(name)
        c['enum_name'] = format_as_enum_item(name)

        # Get position
        if el.tag == "{http://www.w3.org/2000/svg}rect":
            shape = "rect"
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
            tr = el.get('transform') 
            if tr and ("rotate(90)" in tr or "rotate(270)" in tr or "rotate(-90)" in tr):
                tmp = c['width']
                c['width'] = c['height']
                c['height'] = tmp
            if c['width'] > c['height']:
                c['orientation'] = "Horizontal"
            else:
                c['orientation'] = "Vertical"

        elif el.tag == "{http://www.w3.org/2000/svg}circle":
            shape = "circle"
            cx = float(el.get('cx'))
            cy = float(el.get('cy'))
            c['cx'] = round(cx, 3)
            c['cy'] = round(cy, 3)
            c['orientation'] = "Round"

        else:
            shape = "unknown"

        # Get color --> component type
        style = el.get('style')
        if style is None:
            print(f"Error: {shape} shape with no style found at {c['cx']}, {c['cy']}")
            continue
        color_match = re.search(r'fill:\s*(.*)', style)
        color = ''
        color = color_match.group(1).lower() if color_match is not None else ''
        color = color.strip(";")
        color = expand_color_synonyms(color)
        c['color'] = color

        #Red: Knob or slider
        if color.startswith("#ff00") and color!="#ff00ff":
            def_val_int = int(color[-2:], 16)
            if def_val_int <= 128:
                c['default_value'] = str(def_val_int / 128) + "f"
                if shape == "circle":
                    c['knob_style'] = get_knob_style_from_radius(el.get('r'))
                else:
                    c['knob_style'] = "Slider25mm"
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

        #Deep Purple: Encodeer
        elif color == '#c000c0':
            c['switch_type'] = "Encoder"
            c['encoder_knob_style'] = get_knob_style_from_radius(el.get('r'))
            components['switches'].append(c)

        #Orange: Button - Latching
        elif color == '#ff8000':
            c['encoder_knob_style'] = "None"
            c['switch_type'] = "LatchingButton"
            components['switches'].append(c)

        #Light Orange: Button - Momentary
        elif color == '#ffc000':
            c['encoder_knob_style'] = "None"
            c['switch_type'] = "MomentaryButton"
            components['switches'].append(c)

        #Deep Pink rectangle: Switch - 2pos
        elif color == '#ff8080':
            c['encoder_knob_style'] = "None"
            c['switch_type'] = "Toggle2pos"
            if c['orientation'] == "Round":
                c['orientation'] = "Vertical"
            components['switches'].append(c)

        #Hot Pink rectangle: Switch - 3pos
        elif color == '#ffc080':
            c['encoder_knob_style'] = "None"
            c['switch_type'] = "Toggle3pos"
            if c['orientation'] == "Round":
                c['orientation'] = "Vertical"
            components['switches'].append(c)

        elif color == '#ffff00':
            components['widgets'].append(c)
        else:
            Log(f"Unknown color: {color} found at {c['cx']},{c['cy']}. Skipping.")

    # Sort components
    components['params'].reverse()
    components['inputs'].reverse()
    components['outputs'].reverse()
    components['lights'].reverse()
    components['widgets'].reverse()
    components['switches'].reverse()

    # top_left_sort = lambda w: (w['cy'], w['cx'])
    # components['params'] = sorted(components['params'], key=top_left_sort)
    # components['inputs'] = sorted(components['inputs'], key=top_left_sort)
    # components['outputs'] = sorted(components['outputs'], key=top_left_sort)
    # components['lights'] = sorted(components['lights'], key=top_left_sort)
    # components['widgets'] = sorted(components['widgets'], key=top_left_sort)
    # components['switches'] = sorted(components['switches'], key=top_left_sort)

    # Log(f"Found {len(components['params'])} params, {len(components['inputs'])} inputs, {len(components['outputs'])} outputs, {len(components['lights'])} lights, and {len(components['widgets'])} custom widgets.")
    return components

def components_to_infofile(components):
    slug = components['slug']
    DPI = components['dpi']

    #TODO: embed knob long name vs short name in svg
    source = f"""#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct {slug}Info : ModuleInfoBase {{
    static constexpr std::string_view slug{{"{slug}"}};
    static constexpr std::string_view description{{"{components['ModuleName']}"}};
    static constexpr uint32_t width_hp = {components['HP']};
    static constexpr std::string_view svg_filename{{"res/modules/{slug}-artwork.svg"}};

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
            .orientation = KnobDef::{k['orientation']},
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
            .orientation = SwitchDef::{k['orientation']},
            .encoder_knob_style = SwitchDef::{k['encoder_knob_style']},
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

