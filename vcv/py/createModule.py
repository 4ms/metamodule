import os
import sys

# Version check
f"Python 3.6+ is required"

class UserException(Exception):
    pass

def input_default(prompt, default=""):
    str = input(f"{prompt} [{default}]: ")
    if str == "":
        return default
    return str


def appendToFileAfterMarker(filename, marker, newText):
    with open(filename, 'r') as file :
      filedata = file.read()

    prettyNewText = newText.replace('\n',' ').replace('\t', ' ')
    if filedata.find(newText) == -1:
        filedata = filedata.replace(marker, marker + newText)
        print(f"Updated {filename} with {prettyNewText}")
        with open(filename, 'w') as file:
            file.write(filedata)
    else:
        print(f"Didn't update {filename} with {prettyNewText}, already exists in file")


def appendPluginFiles(slug, pluginDir, description=""):
    plugincpp = os.path.join(pluginDir, 'src/plugin.cpp')
    pluginhpp = os.path.join(pluginDir, 'src/plugin.hpp')
    pluginjson = os.path.join(pluginDir, 'plugin.json')
    if description=="":
        description = slug
    modelName = 'model' + slug

    # Append to plugins.cpp file
    marker = '// Add models below here'
    newText = f'''
    p->addModel({modelName});
    '''
    appendToFileAfterMarker(plugincpp, marker, newText)

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
    newText=f'''
    {{
      "slug": "{slug}",
      "name": "{slug}",
      "description": "{description}",
      "tags": []
    }},'''
    marker = '"modules": ['
    appendToFileAfterMarker(pluginjson, marker, newText)


def usage(script):
    text = f"""CoreModule creation helper

Usage: {script} command ... 
Commands:

addtoplugin [SlugName] ["optional description in quotes"]
    adds the given slug (and optional description) to the VCV plugin registry
    only modifies src/plugin.cpp, src/plugin.hpp, and plugin.json

"""
    print(text)

def parse_args(args):
    script = args.pop(0)
    if len(args) == 0:
        usage(script)
        return

    cmd = args.pop(0)
    if cmd == 'createcore':
        if len(args) < 1:
            usage(script)
            return
        slug = args.pop(0)
        coreModuleDir = os.getenv('METAMODULE_COREMODULE_DIR')
        if coreModuleDir is None:
            coreModuleDir = input_default("CoreModule dir", os.path.realpath(os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../shared/CoreModules/")))
        createCoreModule(slug, coreModuleDir)
        return

    elif cmd == 'addtoplugin':
        if len(args) < 2:
            usage(script)
            return
        slug = args.pop(0)
        desc = args.pop(0)
        vcvDir = os.getenv('METAMODULE_COREMODULE_DIR')
        if vcvDir is None:
            vcvDir = input_default("VCV Plugin dir", os.path.realpath(os.path.join(os.path.dirname(os.path.realpath(__file__)),"../")))
        appendPluginFiles(slug, vcvDir, desc)
        return

    else:
        usage(script)


if __name__ == "__main__":
    try:
        parse_args(sys.argv)
    except KeyboardInterrupt:
        pass
    except UserException as e:
        print(e)
        sys.exit(1)
