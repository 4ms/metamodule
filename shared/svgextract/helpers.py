import os
import re

def Log(x):
    TAG = "    svgextract: "
    print(TAG+x)

ns = {
    "svg": "http://www.w3.org/2000/svg",
    "inkscape": "http://www.inkscape.org/namespaces/inkscape",
}


class UserException(Exception):
    pass


def pathFromHere(path):
    return os.path.join(os.path.dirname(os.path.realpath(__file__)),path)


def input_default(prompt, default=""):
    return default
    # str = input(f"{prompt} [{default}]: ")
    # if str == "":
    #     return default
    # return str


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


