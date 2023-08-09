from helpers.util import *

def appendImageList(artwork_array_prefix, image_list_file):
    #artwork_array_prefix = artwork_array_prefix.replace("-artwork","")
    parts = artwork_array_prefix.split("_")
    slug = parts[0]
    #artwork_prefix = parts[0] + "_" + parts[1]
    artwork_Carray_240 = artwork_array_prefix.rstrip("_240") + "_240"
    newText = f'''LV_IMG_DECLARE({artwork_Carray_240});
'''
    appendToFileAfterMarker(image_list_file, "// DECLARE HERE\n", newText)

    newText = f'''
\t\tif (slug == "{slug}")
\t\t\treturn &{artwork_Carray_240};
'''
    appendToFileAfterMarker(image_list_file, "// SLUG TO IMAGE HERE\n", newText)


