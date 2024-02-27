import os
import xml.etree.ElementTree
from helpers.util import *
from helpers.xml_helper import register_all_namespaces
from helpers.svg_parse_helpers import *

def extractForVcv(svgFilename, artworkFilename = None, slug = ""):
    if artworkFilename == None:
        outputpath = os.getenv('METAMODULE_ARTWORK_DIR')
        if outputpath is None:
            outputpath = input_default("Directory to save SVG artwork file", pathFromHere("../../vcv/res/modules"))
        artworkFilename = os.path.join(outputpath, slug + "_artwork.svg")

    Log(f"reading from {svgFilename}, writing to {artworkFilename}")
    register_all_namespaces(svgFilename)

    tree = xml.etree.ElementTree.parse(svgFilename)
    root = tree.getroot()
    components_group = get_components_group(root)

    # slug, _ = find_slug_and_modulename(components_group)
    # appendPluginFiles(slug)

    components_group.clear()
    Log("Removed components layer")
    tree.write(artworkFilename)
    Log(f"Wrote artwork svg file for vcv: {artworkFilename}")


def appendPluginFiles(slug, brand, pluginDir = None, description=""):
    if pluginDir == None:
        pluginDir = os.getenv('METAMODULE_VCV_DIR')
        if pluginDir is None:
            pluginDir = input_default("Metamodule/VCV dir", pathFromHere("../../vcv/"))
    plugincc = os.path.join(pluginDir, 'src/plugin.cc')
    private_plugin_cc = os.path.join(pluginDir, f'src/models/{slug}.cc')
    pluginhh = os.path.join(pluginDir, 'src/plugin.hh')
    pluginjson = os.path.join(pluginDir, 'plugin.json')
    if description=="":
        description = slug
    modelName = 'model' + slug

    module_file_content = f"""#include "generic_module.hh"
#include "CoreModules/{brand}/info/{slug}_info.hh"
using namespace MetaModule;

rack::Model* {modelName} = GenericModule<{slug}Info>::create();
"""

    overwriteOrCreateFile(private_plugin_cc, module_file_content)

    # Append to plugin.cc file
    marker = '// Add models below here'
    newText = f'p->addModel({modelName});'
    appendToFileAfterMarker(plugincc, marker, "\n\t" + newText, newText)
    marker = "// include and define models below here\n"

    # Append to plugin.hh file
    marker = '// Add models below here\n'
    newText = f'extern rack::Model *{modelName};\n'
    appendToFileAfterMarker(pluginhh, marker, newText)

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


