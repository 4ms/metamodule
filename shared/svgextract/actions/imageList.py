from helpers.util import *

def appendImageList(artwork_array_prefix, image_list_file):
    parts = artwork_array_prefix.split("_")
    slug = parts[0]
    artwork_prefix = parts[0] + "_" + parts[1]
    artwork_Carray_240 = artwork_prefix + "_240"
    artwork_Carray_120 = artwork_prefix + "_120"
    newText = f'''LV_IMG_DECLARE({artwork_Carray_240});
LV_IMG_DECLARE({artwork_Carray_120});
'''
    appendToFileAfterMarker(image_list_file, "// DECLARE HERE\n", newText)

    newText = f'''
\t\tif (slug == "{slug}")
\t\t\treturn (height == 240) ? &{artwork_Carray_240} : &{artwork_Carray_120};
'''
    appendToFileAfterMarker(image_list_file, "// SLUG TO IMAGE HERE\n", newText)


