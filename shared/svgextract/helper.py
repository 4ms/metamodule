#!/usr/bin/env python3

import sys
import os
import re
import json
import xml.etree.ElementTree


# Version check
f"Python 3.6+ is required"


class UserException(Exception):
    pass


def find(f, array):
    for a in array:
        if f(a):
            return f

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


def get_knob_style_from_radius(radius):
    r = float(radius)
    if r < 10 and r > 3:
        return "small" #<10
    if r < 15:
        return "medium" #10-15
    if r < 30:
        return "large" #15-30
    return "unknown" #under 3 or over 30 is not a known knob

def panel_to_components(tree):
    ns = {
        "svg": "http://www.w3.org/2000/svg",
        "inkscape": "http://www.inkscape.org/namespaces/inkscape",
    }

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

    components = {}
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
        c['name'] = str_to_identifier(name).upper()
        c['display_name'] = name

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
        #color_match = re.search(r'fill:\S*#(.{6});', style)
        color_match = re.search(r'fill:\s*(.*)', style)
        color = ''
        color = color_match.group(1).lower() if color_match is not None else ''
        c['color'] = color

        #Red: Default fully-CCW knob
        if color == '#ff0000' or color == '#f00' or color == 'red':
            c['default_value'] = 0.0
            c['knob_style'] = get_knob_style_from_radius(el.get('r'))
            components['params'].append(c)

        #Light Red/Coral: Center Detent knob
        elif color == '#ff8080':
            c['default_value'] = 0.5
            c['knob_style'] = get_knob_style_from_radius(el.get('r'))
            components['params'].append(c)

        #Green: Input jack, analog (CV or audio): 
        elif color == '#00ff00' or color == '#0f0' or color == 'lime':
            c['signal_type'] = "analog"
            components['inputs'].append(c)

        #Light Green: Input jack, digital (gate or trig):
        elif color == '#80ff80':
            c['signal_type'] = "gate"
            components['inputs'].append(c)

        #Blue: Output jack, analog (CV or audio)
        elif color == '#0000ff' or color == '#00f' or color == 'blue':
            c['signal_type'] = "analog"
            components['outputs'].append(c)

        #Light Blue: Output jack, digital (gate or trig):
        elif color == '#8080ff':
            c['signal_type'] = "gate"
            components['outputs'].append(c)

        #Magenta: LED
        elif color == '#ff00ff' or color == '#f0f':
            components['lights'].append(c)

        #Orange: Button - Latching
        elif color == '#ff8000':
            c['switch_type'] = "latching button"
            components['switches'].append(c)

        #Light Orange: Button - Momentary
        elif color == '#ffc000':
            c['switch_type'] = "momentary button"
            components['switches'].append(c)

        #Deep Pink: Switch - 2pos
        elif color == '#ff0080':
            c['switch_type'] = "2-position toggle"
            components['switches'].append(c)

        #Hot Pink: Switch - 3pos
        elif color == '#ff00c0':
            c['switch_type'] = "3-position toggle"
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


def components_to_source(components, slug):
    identifier = str_to_identifier(slug)
    source = ""

    source += f"""#include "plugin.hpp"


struct {identifier} : Module {{"""

    # Params
    source += """
    enum ParamIds {"""
    for c in components['params']:
        source += f"""
        {c['name']}_PARAM,"""
    source += """
        NUM_PARAMS
    };"""

    # Inputs
    source += """
    enum InputIds {"""
    for c in components['inputs']:
        source += f"""
        {c['name']}_INPUT,"""
    source += """
        NUM_INPUTS
    };"""

    # Outputs
    source += """
    enum OutputIds {"""
    for c in components['outputs']:
        source += f"""
        {c['name']}_OUTPUT,"""
    source += """
        NUM_OUTPUTS
    };"""

    # Lights
    source += """
    enum LightIds {"""
    for c in components['lights']:
        source += f"""
        {c['name']}_LIGHT,"""
    source += """
        NUM_LIGHTS
    };"""


    source += f"""

    {identifier}() {{
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);"""

    for c in components['params']:
        source += f"""
        configParam({c['name']}_PARAM, 0.f, 1.f, 0.f, "");"""

    source += """
    }

    void process(const ProcessArgs& args) override {
    }
};"""

    source += f"""


struct {identifier}Widget : ModuleWidget {{
    {identifier}Widget({identifier}* module) {{
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/{slug}.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));"""


    # Params
    if len(components['params']) > 0:
        source += "\n"
    for c in components['params']:
        if 'x' in c:
            source += f"""
        addParam(createParam<RoundBlackKnob>(mm2px(Vec({c['x']}, {c['y']})), module, {identifier}::{c['name']}_PARAM));"""
        else:
            source += f"""
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec({c['cx']}, {c['cy']})), module, {identifier}::{c['name']}_PARAM));"""

    # Inputs
    if len(components['inputs']) > 0:
        source += "\n"
    for c in components['inputs']:
        if 'x' in c:
            source += f"""
        addInput(createInput<PJ301MPort>(mm2px(Vec({c['x']}, {c['y']})), module, {identifier}::{c['name']}_INPUT));"""
        else:
            source += f"""
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec({c['cx']}, {c['cy']})), module, {identifier}::{c['name']}_INPUT));"""

    # Outputs
    if len(components['outputs']) > 0:
        source += "\n"
    for c in components['outputs']:
        if 'x' in c:
            source += f"""
        addOutput(createOutput<PJ301MPort>(mm2px(Vec({c['x']}, {c['y']})), module, {identifier}::{c['name']}_OUTPUT));"""
        else:
            source += f"""
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec({c['cx']}, {c['cy']})), module, {identifier}::{c['name']}_OUTPUT));"""

    # Lights
    if len(components['lights']) > 0:
        source += "\n"
    for c in components['lights']:
        if 'x' in c:
            source += f"""
        addChild(createLight<MediumLight<RedLight>>(mm2px(Vec({c['x']}, {c['y']})), module, {identifier}::{c['name']}_LIGHT));"""
        else:
            source += f"""
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec({c['cx']}, {c['cy']})), module, {identifier}::{c['name']}_LIGHT));"""

    # Widgets
    if len(components['widgets']) > 0:
        source += "\n"
    for c in components['widgets']:
        if 'x' in c:
            source += f"""
        // mm2px(Vec({c['width']}, {c['height']}))
        addChild(createWidget<Widget>(mm2px(Vec({c['x']}, {c['y']}))));"""
        else:
            source += f"""
        addChild(createWidgetCentered<Widget>(mm2px(Vec({c['cx']}, {c['cy']}))));"""

    source += f"""
    }}
}};


Model* model{identifier} = createModel<{identifier}, {identifier}Widget>("{slug}");"""

    return source


def usage(script):
    text = f"""VCV Rack Plugin Helper Utility

Usage: {script} <command> ...
Commands:

createplugin <slug> [plugin dir]

    A directory will be created and initialized with a minimal plugin template.
    If no plugin directory is given, the slug is used.

createmanifest <slug> [plugin dir]

    Creates a `plugin.json` manifest file in an existing plugin directory.
    If no plugin directory is given, the current directory is used.

createmodule <module slug> [panel file] [source file]

    Adds a new module to the plugin manifest in the current directory.
    If a panel and source file are given, generates a template source file initialized with components from a panel file.
    Example:
        {script} createmodule MyModule res/MyModule.svg src/MyModule.cpp

    See https://vcvrack.com/manual/PanelTutorial.html for creating SVG panel files.
"""
    print(text)


def parse_args(args):
    script = args.pop(0)
    if len(args) == 0:
        usage(script)
        return

    # cmd = args.pop(0)
    # if cmd == 'createplugin':
    #     create_plugin(*args)
    # elif cmd == 'createmodule':
    #     create_module(*args)
    # elif cmd == 'createmanifest':
    #     create_manifest(*args)
    # else:
    #     print(f"Command not found: {cmd}")


if __name__ == "__main__":
    try:
        parse_args(sys.argv)
    except KeyboardInterrupt:
        pass
    except UserException as e:
        print(e)
        sys.exit(1)
