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

   Make a new file called `firmware/vcv_ports/glue/<Brand>/modules.cmake`.
   It'll be helpful look at other brands examples and copy what's done there.
   Here's an example where the <Brand> is "MyBrand"

```cmake
# MyBrandModules is a list of VCV Rack module slugs
# This cmake variable must be spelled exactly like that because it's used
# in the MetaModule build system
set(MyBrandModules
    SomeModule
    AnotherModule
    #... more modules
)

# Invoke the module list filtering function on the list.
# This allows devs to filter out modules when building (faster, smaller binaries)
include(${CMAKE_CURRENT_LIST_DIR}/../filter.cmake)
limit_modules_built("MyBrand" MyBrandModules)

# Just a helper variable, this is optional
set(MYBRAND_DIR ${CMAKE_CURRENT_LIST_DIR}/../../MyBrand)

# Create a list of faceplate SVGs to convert
# Typically the SVG file for a module has the same name as the slug, with .svg appended 
# (which is what this cmake code is assuming)
# This variable MYBRAND_FACEPLATE_SVGS must be named exactly that, since it's used
# in the MetaModule build system
list(TRANSFORM MyBrandModules PREPEND ${MYBRAND_DIR}/res/panels/ OUTPUT_VARIABLE MYBRAND_FACEPLATE_SVGS)
list(TRANSFORM MYBRAND_FACEPLATE_SVGS APPEND .svg)

# Create a list of c++ files to compile for your brand
# Typically the .cpp files have the same name as the module slug, which this cmake code assumes.
# This variable will be used in your brand's CMakeLists.txt file, but is not used
# anywhere else, so you are free to name it however you like.
list(TRANSFORM MyBrandModules PREPEND ${MYBRAND_DIR}/src/ OUTPUT_VARIABLE MYBRAND_SOURCE_PATHS)
list(TRANSFORM MYBRAND_SOURCE_PATHS APPEND .cpp)
```

   `modules.cmake` must do three things:

   - Create a list of module names call `<Brand>Modules`.
     These names should be the VCV Rack module slugs. Ideally, these names are
     also the names of the SVG faceplate files (without the .svg extension) and
     also the names of the C++ source files (without the .cpp or .cc extension),
     but if that's not the case you will just need to manually specify the SVGs
     and source file names (and filtering won't work, so avoid this if possible).
   
   - Set a list called `<BRAND>_FACEPLATE_SVGS` (<BRAND> is all caps), which
     contains full paths to the faceplate .svg files. This is used when
     (re-)generating all artwork files (convering SVG files to PNG and LVGL
     format).

   - Invoke the module list filtering function on the list.
     This allows developers to speed up build times and reduce binary sizes
     by specifying a white-list of modules to include in the build.


4) **Create a brand `CMakeLists.txt` file**

   Make a new file called `firmware/vcv_ports/glue/<Brand>/CMakeLists.txt`.
   This file tells CMake how to build your modules. It's a fairly simple CMake
   file, the only thing it must do is create a new target named <Brand>Library.

   Here's an example:

```cmake
include(modules.cmake)

# ${MYBRAND_SOURCE_PATHS} was defined in modules.cmake
add_library(MyBrandLibrary OBJECT ${MYBRAND_SOURCE_PATHS}
            # Add any other sources you need here (3rd party libs, etc)
)

# Put whatever dirs you need to include here:
target_include_directories(MyBrandLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../MyBrand/src)

# Put whatever compile options you need here
target_compile_options(MyBrandLibrary PRIVATE -Wno-double-promotion)

# Set properites here (at least c++20 is required)
set_property(TARGET MyBrandLibrary PROPERTY CXX_STANDARD 20)
```


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
   Hopefully this is self-explanatory: just make sure the function returns
   true for modules with your plugin's slug.

7) **Generate faceplate artwork.**

   Run `make faceplate-image-<Brand>` to generate the faceplate artwork for
   your brand only. This will (re-)generate a faceplate for **all** the images in
   the `BRAND_FACEPLATE_SVGS` cmake list you made earlier (even if nothing changed).
   If you only want to regenerate a few images, use limit file -- see [Firmware
   Building](./firmware-building.md), or edit `BRAND_FACEPLATE_SVGS` in your cmake files,
   or use the `svgextract` script directly (again, see the Firmware Building page)


8) **Convert Component artwork to PNG (LVGL)**

   Most Rack components are already ported, but if you use one that isn't
   ported yet or you have your own components, then you'll need to do two
   things:
   - Convert the SVG artwork files to LVGL files (which is a PNG encoded as a
     C-struct)
   - Tell MetaModule how to make a MetaModule-native Element when it sees this
     VCV Rack component widget 

   An example is probably the best way to outline this process and hopefully
   explain a bit how MetaModule works. 

   Let's say you have something like this in your VCV plugin code:

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
   For knobs, VCV uses two images (fg and bg) but MetaModule only uses one.
   So, we need to edit these two SVG files (`NewWidget.svg` and
   `NewWidget_bg.svg`) and combine them into one image. 
   Note that other types of elements like sliders work the same in VCV and MetaModule
   (both use a bg and a fg/handle), so if this was a slider we would not need to 
   combine the images.

   Create a new folder `(repo root)/graphics/<Brand>/components/`. Open those
   two SVG files in Inkscape or your favorite program.
   Combine the two images so that you have a single "knob" image that will look
   good when rotated. Remember, these will be displayed on a 16-bit 320x240
   screen, so avoid gradients and small details.
   Save the SVG file into the `graphics/<Brand>/components/` folder, as an SVG.

   Next, use the svgextract python script to convert the SVG to a PNG/LVGL
   image file:

```bash
shared/svgextract/svgextract.py convertSvgToLvgl graphics/<Brand>/components/NewWidget.svg  \
                                  firmware/src/gui/images/<Brand>/components/NewWidget.c
```

   For sanity, use the same filename for the .svg and the .c files.
   You should now have a new .c file and .png file in the
   `firmware/src/gui/images/<Brand>/components` dir. Open the PNG file to make
   sure it looks OK.

   For more details on svgextract usage, see [Firmware Building](./firmware-building.md). 


9) **Connect any new components to the MetaModule Element**

   Skip this if you didn't add any components in step 8.

   The final step is to create a function that takes your VCV Rack Widget type
   as a template parameter and returns a MetaModule Element constructed with 
   the image you converted.

   Create a new file in `firmware/VCV_adaptor/widget_convert/<Brand>.hh`
   (or just append to the file if it already exists).

   To convert the `MyBrandNewWidget` which uses the image `NewWidget.svg`, 
   we would need a file like this:

```c++
#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

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
   XY position of the element, and other things) and the image filename to
   constuct an Element. Note that we chose the `Knob` element. If we were doing
   a slider, we would choose the Slider element. See
   `shared/CoreModules/elements/elements.hh` for all the possible elements.
   Also see `shared/CoreModules/elements/base_element.hh` for the fields each Element requires.

   Note that `make_element` is in the MetaModule namespace, and your brand's
   widget type is not. Also note that `make_element` is an inline function.

   For another example, if you also need to add a new switch with three positions and an image for each position,
   you could just add this function below the other one in the same file:

```c++
template<>
inline Element make_element<::Cool3PosSwitch>(BaseElement b) {
	return FlipSwitch{{b}, 3, {"CoolSwitch_0.png", "CoolSwitch_1.png", "CoolSwitch_2.png"}};
};
```

   Take a look at the other brand files in `firmware/VCV_adaptor/widget_convert/` for more examples.

