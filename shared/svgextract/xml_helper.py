import xml.etree.ElementTree

def register_all_namespaces(filename):
    namespaces = dict([node for _, node in xml.etree.ElementTree.iterparse(filename, events=['start-ns'])])
    for ns in namespaces:
        xml.etree.ElementTree.register_namespace(ns, namespaces[ns])
