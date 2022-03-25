#!/usr/bin/env python3
import sys
import os
import re
import xml.etree.ElementTree
import random
import string
from xml_helper import register_all_namespaces
from shutil import which
import subprocess

# Version check
f"Python 3.6+ is required"

def Log(x):
    TAG = "    svgextract: "
    print(TAG+x)

ns = {
    "svg": "http://www.w3.org/2000/svg",
    "inkscape": "http://www.inkscape.org/namespaces/inkscape",
}

class UserException(Exception):
    pass


def appendToFileAfterMarker(filename, marker, newText, matchText=None):
    if matchText == None:
        matchText = newText

    with open(filename, 'r') as file :
      filedata = file.read()

    prettyNewText = newText.replace('\n',' ').replace('\t', ' ')
    if filedata.find(matchText) == -1:
        filedata = filedata.replace(marker, marker + newText)
        Log(f"Updated {filename} with {prettyNewText}")
        with open(filename, 'w') as file:
            file.write(filedata)
    else:
        Log(f"Didn't update {filename} with {prettyNewText}, already exists in file")


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
    # Replace + with P
    s = re.sub(r'\+', 'P', s)
    # Replace - with N
    s = re.sub(r'\-', 'N', s)
    # Replace | with OR 
    s = re.sub(r'\|', '_OR_', s)
    # Replace other special characters with underscore
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
        Log("WARNING: DPI cannot be deduced, width, height, or viewBox is missing or 0 in root node. Using 72dpi")
        return 72

    viewBoxDims = viewBox.split(" ")
    viewWidth = float(viewBoxDims[2]) - float(viewBoxDims[0])
    viewHeight = float(viewBoxDims[3]) - float(viewBoxDims[1])
    hDPI = round(viewWidth / widthInches)
    vDPI = round(viewHeight / heightInches)
    if vDPI is not hDPI:
        Log(f"WARNING: Horizontal DPI is {hDPI} and Vertical DPI is {vDPI}, which are not equal. Using horizontal value")
        vDPI = hDPI

    if hDPI == 1:
        Log(f"File is possibly already in 72DPI pixels for the root object units. Using 72 for DPI")
        hDPI = 72

    Log(f"DPI deduced as {hDPI}")

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

def get_components_group(root):
    groups = root.findall(".//svg:g[@inkscape:label='components']", ns)
    # Illustrator uses `id` for the group name.
    if len(groups) < 1:
        groups = root.findall(".//svg:g[@id='components']", ns)
    if len(groups) < 1:
        raise UserException("ERROR: Could not find \"components\" layer on panel")
    return groups[0]


def find_slug_and_modulename(components_group):
    texts = components_group.findall(".//svg:text", ns)
    slug = "Unnamed"
    moduleName = "Unnamed"
    for t in texts:
        name = t.get('{http://www.inkscape.org/namespaces/inkscape}label')
        if name is None:
            name = t.get('id')
        if name is None:
            name = t.get('data-name')
        if name is None:
            continue

        if name == "slug":
            slug = ""
            for m in t.itertext():
                slug += m

        if name == "modulename":
            moduleName = ""
            for m in t.itertext():
                moduleName += m

    subgroups = components_group.findall(".//svg:g", ns)
    if slug == "Unnamed":
        for t in subgroups:
            name = t.get('{http://www.inkscape.org/namespaces/inkscape}label')
            if name is None:
                name = t.get('id')
            if name is None:
                name = t.get('data-name')
            if name is None:
                continue
            if name == "slug":
                slug = ""
                for m in t.itertext():
                    slug += m
                slug = re.sub(r'\W+', '', slug).strip()

    if moduleName == "Unnamed":
        for t in subgroups:
            name = t.get('{http://www.inkscape.org/namespaces/inkscape}label')
            if name is None:
                name = t.get('id')
            if name is None:
                name = t.get('data-name')
            if name is None:
                continue
            if name == "modulename":
                moduleName = ""
                for m in t.itertext():
                    moduleName += m
                moduleName = re.sub(r'[\W]+', ' ', moduleName).strip()

    return slug, moduleName


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


def pathFromHere(path):
    return os.path.join(os.path.dirname(os.path.realpath(__file__)),path)


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
    
    if components['slug']:
        createCoreModule(components['slug'])
    return components['slug']


def extractArtworkLayer(svgFilename, artworkFilename = None, slug = None):
    if artworkFilename == None:
        outputpath = os.getenv('METAMODULE_ARTWORK_DIR')
        if outputpath is None:
            outputpath = input_default("Directory to save SVG artwork file", pathFromHere("../../vcv/res/modules"))
        artworkFilename = os.path.join(outputpath, slug + "-artwork.svg")

    Log(f"reading from {svgFilename}, writing to {artworkFilename}")
    register_all_namespaces(svgFilename)

    tree = xml.etree.ElementTree.parse(svgFilename)
    root = tree.getroot()
    components_group = get_components_group(root)

    slug, _ = find_slug_and_modulename(components_group)
    appendPluginFiles(slug)

    components_group.clear()
    Log("Removed components layer")
    tree.write(artworkFilename)
    Log(f"Wrote artwork svg file for vcv: {artworkFilename}")


# def createComponentImageCompositeCmd(svgFilename, pngFilename):
#     PXSCALE = 240/(5.059*72)
#     JACKSIZE_X = 20
#     JACKSIZE_Y = 18
#     OFFX = -JACKSIZE_X / 2
#     OFFY = -JACKSIZE_Y / 2
#     register_all_namespaces(svgFilename)
#     tree = xml.etree.ElementTree.parse(svgFilename)
#     components = panel_to_components(tree)
#     cmd = f"{pngFilename}"
#     for c in components['outputs'] + components['inputs']:
#         cmd += f" src/pages/images/jack-black.png -geometry +{PXSCALE*c['cx'] + OFFX}+{PXSCALE*c['cy'] + OFFY} -composite"
    
#     cmd += " " + pngFilename.strip(".png") + "_comps.png"
#     # magick EnOsc_artwork_240.png jack-black.png -geometry +5+10 -composite jack-black.png -geometry +40+20 -composite tt.png
#     return cmd

   
def createlvimg(artworkSvgFilename, pngFilename):
    # Find programs needed
    inkscapeBin = which('inkscape') or os.getenv('INKSCAPE_BIN_PATH')
    if inkscapeBin is None:
        Log("inkscape is not found. Please put it in your shell PATH, or set INKSCAPE_BIN_PATH to the path to the binary")
        Log("Aborting")
        return
    convertBin = which('convert') or which('magick') or os.getenv('IMAGEMAGICK_BIN_PATH')
    if convertBin is None:
        Log("convert or magick is not found. Please put it in your shell PATH, or set IMAGEMAGICK_BIN_PATH to the path to the binary")
        Log("Aborting")
        return

    # SVG ==> PNG
    Log(f"converting {artworkSvgFilename} to {pngFilename} with inkscape and convert.")
    try:
        subprocess.run(f'{inkscapeBin} --export-type="png" --export-id="faceplate" --export-id-only --export-filename=- {artworkSvgFilename} | {convertBin} -resize x240 - {pngFilename}', shell=True, check=True)
    except:
        Log(f"Failed running {inkscapeBin} and {convertBin}. Aborting")
        return

    # cmd = createComponentImageCompositeCmd(artworkSvgFilename, pngFilename)
    # Log("Going to run "+ cmd)
    # subprocess.run(f'{convertBin} {cmd}', shell=True, check=True)
    # Log(f"Created {pngFilename} from {artworkSvgFilename}")

    # PNG ==> LVGL image (C file with array)
    lv_img_conv = os.path.dirname(os.path.realpath(__file__)) + "/lv_img_conv/lv_img_conv.js"
    try:
        subprocess.run([lv_img_conv, '-c', 'CF_TRUE_COLOR', '-t', 'c', '--force', pngFilename], check=True)
    except subprocess.CalledProcessError:
        Log("lv_img_conv.js failed. Try 1) `git submodule update --init` and/or 2) `cd shared/svgextract/lv_img_conv && npm install`")
        return
    Log(f"Created {pngFilename.strip('.png')}.c file from {pngFilename}")


def appendImageList(slug, artwork_Carray, image_list_file):
    newText = f'''LV_IMG_DECLARE({artwork_Carray});
'''
    appendToFileAfterMarker(image_list_file, "// DECLARE HERE\n", newText)

    newText = f'''
\t\tif (slug == "{slug}")
\t\t\treturn &{artwork_Carray};
'''
    appendToFileAfterMarker(image_list_file, "// SLUG TO IMAGE HERE\n", newText)


def processSvg(svgFilename):
    slug = createInfoFile(svgFilename)

    if slug is None:
        Log("No slug found, aborting")
        return

    extractArtworkLayer(svgFilename, None, slug)
    

def createCoreModule(slug, coreModuleDir = None):
    if coreModuleDir == None:
        coreModuleDir = os.getenv('METAMODULE_COREMODULE_DIR')
        if coreModuleDir is None:
            coreModuleDir = input_default("CoreModule dir", pathFromHere("../../shared/CoreModules/"))

    newCoreFileName = slug + 'Core.cc'
    if not os.path.exists(os.path.join(coreModuleDir, newCoreFileName)):
        # Replace 'Slug' in template file with our slug, then write to a new file
        coreTemplateFilename = 'template_core_cc.tmpl'
        with open(os.path.join(coreModuleDir, coreTemplateFilename), 'r') as file :
            filedata = file.read()
        filedata = filedata.replace('Slug', slug)
        with open(os.path.join(coreModuleDir, newCoreFileName), 'w') as file:
            file.write(filedata)
            Log(f"Created new file {newCoreFileName} in {coreModuleDir} because it didn't exist")


def appendPluginFiles(slug, pluginDir = None, description=""):
    if pluginDir == None:
        pluginDir = os.getenv('METAMODULE_VCV_DIR')
        if pluginDir is None:
            pluginDir = input_default("Metamodule/VCV dir", pathFromHere("../../vcv/"))
    plugincpp = os.path.join(pluginDir, 'src/plugin.cpp')
    pluginhpp = os.path.join(pluginDir, 'src/plugin.hpp')
    pluginjson = os.path.join(pluginDir, 'plugin.json')
    if description=="":
        description = slug
    modelName = 'model' + slug

    # Append to plugins.cpp file
    marker = '// Add models below here'
    newText = f'p->addModel({modelName});'
    appendToFileAfterMarker(plugincpp, marker, "\n\t" + newText, newText)

    # Append more to plugins.cpp
    marker = "// include and define models below here\n"
    newText = f'''
#include "CoreModules/info/{slug}_info.hh"
auto {modelName} = createModelFromInfo<{slug}Info>();
'''
    appendToFileAfterMarker(plugincpp, marker, newText)

    # Append to plugins.hpp file
    marker = '// Add models below here\n'
    newText = f'extern Model *{modelName};\n'
    appendToFileAfterMarker(pluginhpp, marker, newText)

    # Append plugin.json
    # TODO: Use a json library because appendToFileAfterMarker gets confused easily (whitespace, trailing comma...)
    newText=f'''
    {{
      "slug": "{slug}",
      "name": "{slug}",
      "description": "{description}",
      "tags": []
    }},'''
    matchText = f'"slug": "{slug}",'
    marker = '"modules": ['
    appendToFileAfterMarker(pluginjson, marker, newText, matchText)


def usage(script):
    print(f"""MetaModule SVG Helper Utility

Usage: {script} <command> ...
Commands:

processsvg [input svg file name]
    Runs createinfo, extractforvcv, and createcorefiles on the given file.
    Uses environmant variables METAMODULE_INFO_DIR, METAMODULE_ARTWORK_DIR, METAMODULE_COREMODULE_DIR if found,
    otherwise prompts user for the values

createinfo [input svg file name] {{optional output path for ModuleInfo file}}
    Creates a ModuleInfo struct and saves it to a file in the given path. The
    file will be named "slug_info.hh", where "slug" is the string of the text
    element with name/id "slug" found in the components layer/group of the SVG
    file. File will be overwritten if it exists.

extractforvcv [input SVG file name] [output artwork SVG file name]
    Saves a new VCV artwork SVG file with the components layer removed.
    Also makes sure the Slug (found in the SVG file) exists as a model in the VCV plugin, and adds it if not.

createlvimg [input artwork SVG file name] [output C file name]
    Converts the artwork SVG to a PNG, scales it to 240px high, and then
    converts it to a .c file using the LVGL image converter.

    Requires these commands to be present on $PATH, or else found at the associated env variable:
        inkscape            (INKSCAPE_BIN_PATH)
        convert             (IMAGEMAGICK_BIN_PATH)

appendimglist [C array name] [image_list.hh filename]
    C array name is the name of an image array (in c format, created by lv_img_conv).
    The second argument is the path to the image_list.hh file that should be updated with this new array.
    Does not update the image_list.hh file if the exact string to be inserted is already found.
    The slug is the first part of the C array name, up to the first underscore (EnOsc_artwork_240 => EnOsc)

""")


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

    if cmd == 'createinfo':
        output = args.pop(0) if len(args) > 0 else None
        createInfoFile(inputfile, output)
        return

    # Two args required for all other cmds:

    if len(args) == 0:
        usage(script)
        return

    output = args.pop(0)

    if cmd == 'extractforvcv':
        extractArtworkLayer(inputfile, output)
        return

    if cmd == 'createlvimg':
        createlvimg(inputfile, output)
        return

    if cmd == 'appendimglist':
        slug = inputfile.split('_')[0]
        appendImageList(slug, inputfile, output)

if __name__ == "__main__":
    try:
        parse_args(sys.argv)
    except KeyboardInterrupt:
        pass
    except UserException as e:
        print(e)
        sys.exit(1)
