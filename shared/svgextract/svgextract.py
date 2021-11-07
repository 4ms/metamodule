#!/usr/bin/env python3

import sys
import os
import re
# import json
import xml.etree.ElementTree


# Version check
f"Python 3.6+ is required"


class UserException(Exception):
    pass


# def find(f, array):
#     for a in array:
#         if f(a):
#             return f

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
    s = s[0].upper() + s[1:]
    # Replace special characters with underscore
    s = re.sub(r'\W', '_', s)
    return s


def remove_trailing_dash_number(name):
    #Chop off -\d$
    if name[-2:-1] == '-' and name[-1:].isdigit():
        name = name[:-2]
    return name


def format_for_display(comp_name):
    comp_name = remove_trailing_dash_number(comp_name)
    return comp_name.title().replace('_',' ')


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


def panel_to_components(tree):
    ns = {
        "svg": "http://www.w3.org/2000/svg",
        "inkscape": "http://www.inkscape.org/namespaces/inkscape",
    }

    components = {}

    #TODO: extract size
    #TODO: extract module name (full name)
    #TODO: extract slug
    #TODO: extract knob long name and description (or is that to be done manually?)
    #.... maybe SVG id = "ShortName#LongName" or "ShortName"
    #.... and description is in some help file
    components['HP'] = 16
    components['ModuleName'] = "Ensemble Oscillator"
    components['slug'] = "EnOsc"

    # Get components layer
    root = tree.getroot()
    groups = root.findall(".//svg:g[@inkscape:label='components']", ns)
    # Illustrator uses `id` for the group name.
    if len(groups) < 1:
        groups = root.findall(".//svg:g[@id='components']", ns)
    if len(groups) < 1:
        raise UserException("Could not find \"components\" layer on panel")

    # Get circles and rects
    components_group = groups[0]
    circles = components_group.findall(".//svg:circle", ns)
    rects = components_group.findall(".//svg:rect", ns)

    components['params'] = []
    components['inputs'] = []
    components['outputs'] = []
    components['lights'] = []
    components['widgets'] = []
    components['switches'] = []

    for el in circles + rects:
        c = {}
        # Get name
        name = el.get('{http://www.inkscape.org/namespaces/inkscape}label')
        if name is None:
            name = el.get('id')
        c['raw_name'] = name
        c['display_name'] = format_for_display(name)
        c['enum_name'] = str_to_identifier(remove_trailing_dash_number(name))

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

        # Get color
        style = el.get('style')
        color_match = re.search(r'fill:\s*(.*)', style)
        color = ''
        color = color_match.group(1).lower() if color_match is not None else ''
        c['color'] = color

        #Red: Default fully-CCW knob
        if color == '#ff0000' or color == '#f00' or color == 'red':
            c['default_value'] = "0.f"
            c['knob_style'] = get_knob_style_from_radius(el.get('r'))
            components['params'].append(c)

        #Light Red/Coral: Center Detent knob
        elif color == '#ff8080':
            c['default_value'] = "0.5f"
            c['knob_style'] = get_knob_style_from_radius(el.get('r'))
            components['params'].append(c)

        #Green: Input jack, analog (CV or audio): 
        elif color == '#00ff00' or color == '#0f0' or color == 'lime':
            c['signal_type'] = "Analog"
            components['inputs'].append(c)

        #Light Green: Input jack, digital (gate or trig):
        elif color == '#80ff80':
            c['signal_type'] = "Gate"
            components['inputs'].append(c)

        #Blue: Output jack, analog (CV or audio)
        elif color == '#0000ff' or color == '#00f' or color == 'blue':
            c['signal_type'] = "Analog"
            components['outputs'].append(c)

        #Light Blue: Output jack, digital (gate or trig):
        elif color == '#8080ff':
            c['signal_type'] = "Gate"
            components['outputs'].append(c)

        #Magenta: LED
        elif color == '#ff00ff' or color == '#f0f':
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
        elif color == '#ff0080':
            c['switch_type'] = "Toggle2pos"
            components['switches'].append(c)

        #Hot Pink: Switch - 3pos
        elif color == '#ff00c0':
            c['switch_type'] = "Toggle3pos"
            components['switches'].append(c)

        elif color == '#ffff00' or color == '#ff0' or color == 'yellow':
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
    source = f"""
    enum {enum_name} {{"""
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

    #TODO: embed knob description and long name vs short name in svg
    source = f"""
#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct {slug}Info : ModuleInfoBase {{
    static constexpr auto NameChars = CoreProcessor::NameChars;
    static constexpr auto LongNameChars = CoreProcessor::LongNameChars;

    static constexpr std::string_view slug{{"{slug}"}};
    static inline const StaticString<LongNameChars> description{{"{components['ModuleName']}"}};
    static constexpr uint32_t width_hp = {components['HP']};
    static constexpr std::string_view svg_filename{{"res/{slug}-artwork.svg"}};

    static constexpr int NumKnobs = {len(components['params'])};
    {make_enum("", "Knob", components['params'])}

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{{{"""
    for k in components['params']:
        source += f"""
        {{
            .id = Knob{k['enum_name']},
            .x_mm = px_to_mm<72>({k['cx']}f),
            .y_mm = px_to_mm<72>({k['cy']}f),
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
            .x_mm = px_to_mm<72>({k['cx']}f),
            .y_mm = px_to_mm<72>({k['cy']}f),
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
            .x_mm = px_to_mm<72>({k['cx']}f),
            .y_mm = px_to_mm<72>({k['cy']}f),
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
            .x_mm = px_to_mm<72>({k['cx']}f),
            .y_mm = px_to_mm<72>({k['cy']}f),
            .short_name = "{k['display_name']}",
            .long_name = "{k['display_name']}",
            .switch_type = SwitchDef::{k['switch_type']},
        }},""" 
    source += f"""
    }}}};

}};
"""
    return source


def createInfoFile(svgfilename, infofilename):
    tree = xml.etree.ElementTree.parse(svgfilename)
    components = panel_to_components(tree)
    infofiletext = components_to_infofile(components)
    with open(infofilename, "w") as f:
        f.write(infofiletext)
        print(f"Wrote info file: {infofilename}")


def extractArtwork(svgfilename, artworkFilename):
    #artworkFilename = resourceDir + "/" + slug + "_artwork.svg"
    tree = xml.etree.ElementTree.parse(svgfilename)
    #tree = extractSvgArtwork(tree)
    tree.write(artworkFilename)
    print(f"Wrote artwork file: {artworkFilename}")


def usage(script):
    text = f"""VCV Rack Plugin Helper Utility

Usage: {script} <command> ...
Commands:

createinfo [svg file name] [output ModuleInfo file name]
    Creates a ModuleInfo struct and saves it in a file

extractart [svg file name] [output SVG file name]
    Saves a new SVG file with the components layer removed

"""
    print(text)


def parse_args(args):
    script = args.pop(0)
    if len(args) == 0:
        usage(script)
        return

    cmd = args.pop(0)
    inputfile = args.pop(0)
    outputfile = args.pop(0)
    if cmd == 'createinfo':
        createInfoFile(inputfile, outputfile)
    if cmd == 'extractart':
        extractArtwork(inputfile, outputfile)



if __name__ == "__main__":
    try:
        parse_args(sys.argv)
    except KeyboardInterrupt:
        pass
    except UserException as e:
        print(e)
        sys.exit(1)
