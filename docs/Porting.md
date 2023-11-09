### Instructions for adding a new module (WIP)

1) **Add the module code as a git submodule**

```bash
git submodule add https://github.com/<user>/<repo> firmware/vcv_ports/<Brand>
```

2) **Create artwork folders**

```bash
mkdir -p firmware/src/gui/images/<Brand>/modules/
mkdir -p firmware/src/gui/images/<Brand>/components/
```

3) **Create a modules.cmake file**
   Make a new file: `firmware/vcv_ports/glue/<Brand>/modules.cmake` 
   Look at other brands examples and copy what's done there.

   `modules.cmake` must do a few things:

   - Create a list of module names call `<Brand>Modules`.
     These names should be the VCV Rack module slugs. Ideally, these names are
     also the names of the SVG faceplate files (without the .svg extension) and
     also the names of the C++ source files (without the .cpp or .cc extension),
     but if that's not the case you will just need to manually specify the SVGs
     and source file names manually.
   
   - Invoke the module list filtering function on the list, like this:
       ```cmake
       include(${CMAKE_CURRENT_LIST_DIR}/../filter.cmake)
       limit_modules_built("<Brand>" <Brand>Modules)
       ```
       This allows developers to speed up build times and reduce binary sizes
       by specifying a white-list of modules to include in the build.
   
   - Set a list called `<BRAND>_FACEPLATE_SVGS` (<BRAND> is all caps), which
     contains full paths to the faceplate .svg files. This is used when
     (re-)generating all artwork files (convering SVG files to PNG and LVGL
     format).


4) *Create a brand `CMakeLists.txt` file*
   Make a new file: `firmware/vcv_ports/glue/<Brand>/CMakeLists.txt`
   This file tells CMake how to build your modules. Look at other brands do it,
   it's a fairly simple CMake file.

   - Typically at the top of the CMakeLists file, you will `include()` the
     `modules.cmake` file, and use the list of module names to generate the
     list of source files needed to compile, but that's not a strict requirement.
   
   - The CMakeLists.txt must create a CMake target OBJECT library named
     <Brand>Library, like this: 
```cmake
     add_library(
       <Brand>Library OBJECT
       ${BRAND_SOURCE_PATHS}
       ${OTHER_SOURCES}
       more_source_files.cpp
     )
 ```
   You can then use normal CMake commands like `target_include_directories`,
   `target_compile_options`, etc to specify how your modules should be built.


5) Add the brand name to `firmware/vcv_ports/brands.cmake`

```cmake
# List of brands
set(brands
  ...
  <Brand>
)
```


6) **Add the plugin to the VCV whitelist** 
   Add an entry for your brand in `vcv/src/mapping/module_directory.hh`. 

7) **Generate faceplate artwork. **
   Run `make faceplate-image-<Brand>` to generate the faceplate artwork. This
   will (re-)generate a faceplate for all the images in the
   `BRAND_FACEPLATE_SVGS` cmake list you made earlier. If you only want to
   regenerate a few images, use limit file -- see [Firmware Building](./firmware-building.md).



###Widgets, Artwork and Elements 

8) **Convert Component artwork to PNG (LVGL)**
   Most Rack components are already ported, but if you use one that isn't
   ported yet or you have your own components, then you'll need to do two
   things:
   - Convert the SVG artwork files to LVGL files (which is a PNG, encoded as a
     C-struct)
   - Tell MetaModule how to make a MetaModule-native Element when it sees this
     VCV Rack Widget 

   An example is probably the best way to outline this process and hopefully
   explain a bit how MetaModule works. Let's say have something like this in
   your code:

```c++
// Your existing ModuleWidget constructor...
addParam(createParam<MyBrandNewWidget>(Vec(1.2, 3.4), module, MyModule::MYPARAM));
```

   And `MyBrandNewWidget` is defined elsewhere like this:

```c++
// Your existing widget definitions ...
struct MyBrandNewWidget : app::SvgKnob {
	MyBrandNewWidget() {
		setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/NewWidget.svg")));
		bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/NewWidget_bg.svg")));
	}
};
```
   First, we need to edit these two SVG files (`NewWidget.svg` and
   `NewWidget_bg.svg`) and combine them into one image. For knobs, VCV uses two
   images (fg and bg) but MetaModule only uses one. Other types of elements
   like sliders work the same in VCV and MetaModule (both use a bg and a
   fg/handle), so this step isn't always necessary.

   Create a new folder `(repo root)/graphics/<Brand>/components/`. Open those
   two SVG files in Inkscape or your favorite program.
   Combine the two images so that you have a single "knob" image that will look
   good when rotated. Remember, these will be displayed on a 16-bit 320x240
   screen, so avoid gradients and small details. 
   Save the SVG file into the `graphics/<Brand>/components/` folder, as an SVG.

   Next, use the svgextract python script to convert the SVG to a PNG/LVGL
   image file:

```bash
shared/svgextract/svgextract.py convertSvgToLvgl \
                                graphics/<Brand>/components/NewWidget.svg  \
                                firmware/src/gui/images/<Brand>/components/NewWidget.c
```

   You should now have the .c file and a .png file in your
   `firmware/src/gui/images/<Brand>/components` dir. Open the PNG file to make sure it looks
   OK.

   For more details on svgextract usage, see [Firmware Building](./firmware-building.md). 

9) **Add new component artwork files to "filesystem".**
   Skip this if you didn't add any components in step 8.

   We need to add the new artwork to the mock read-only "filesystem". This is 
   just a std::map in `firmware/src/gui/images/image_fs.hh`. Eventually we
   will use a real filesystem, but for now this lets the rest of the code use
   a filesystem-like interface. To add an image, just add a line in 
   the map like this:

```c++
    {"NewWidget.png", &NewWidget},
```
   The first element is a string which is the "filename". You'll use this later
   in the next step. Best practice is to use the actual PNG filename. The second
   element is a pointer to the generated LVGL .c file.  It's 
   most likely going to be the same as the filename without the ".png", but 
   if the file contains characters that C++ doesn't like, then it may be different.
   You can double-check by looking for the `lv_img_dsc_t` struct that's defined
   at the bottom of the .c file you generated in 
   `firmware/src/gui/images/<Brand>/components/`.

   You need to extern declare that struct, so add a line at the top like this:

```c++
    extern const lv_img_dsc_t NewWidget;
```

10) **Connect any new components to the MetaModule Element**
    Skip this if you didn't add any components in step 8.

   The final step is to create a function that takes your VCV Rack Widget type
   as a template parameter and returns a MetaModule Element constructed with 
   the image you converted.

   So to convert the `MyBrandNewWidget` which uses the image `NewWidget.svg`, 
   we would need this function:

```c++
struct MyBrandNewWidget; //foward declare

namespace MetaModule {

template<>
inline Element make_element<::MyBrandNewWidget>(BaseElement b) {
	return Knob{{b}, "NewWidget.png"};
};

}
```

   We forward declare `MyBrandNewWidget` so you don't have to #include your
   plugin files here, but you can do it how you like.
   The `make_element` function takes a BaseElement type (which contains the 
   XY position of the element, among other things) and uses that plus the
   image filename to constuct an Element. Note that we chose the `Knob` element.
   If we were doing a slider, we would choose the Slider element. See
   `shared/CoreModules/elements/elements.hh` for all the possible elements.

   Note that `make_element` is in the MetaModule namespace, and your brand's
   widget type is not. Also note that `make_element` is an inline function.

   OK, so that's the function we need, but where do we put it?
   Create a new file in `firmware/VCV_adaptor/widget_convert/<Brand>.hh`
   (or just append to the file if it already exists).
   Put this function (and the forward declaration) in it.
   You also need some lines at the top:

```c++
#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"
```
   Take a look at the other files in `firmware/VCV_adaptor/widget_convert/` for examples.

   That's it!

