### Instructions for adding a new module (WIP)

1) First step is add the module code as a git submodule:

```bash
git submodule https://github.com/<user>/<repo> firmware/vcv_ports/<Brand>
```

2) Create artwork folders:

```bash
mkdir -p firmware/src/gui/images/<Brand>/modules/
mkdir -p firmware/src/gui/images/<Brand>/components/
```

3) Create a modules.cmake file: `firmware/vcv_ports/glue/<Brand>/modules.cmake` 
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
    This allows developers to speed up build times and reduce binary sizes by specifying a white-list of
    modules to include in the build.

- Set a list called `<BRAND>_FACEPLATE_SVGS` (<BRAND> is all caps), which
  contains full paths to the faceplate .svg files. This is used when
  (re-)generating all artwork files (convering SVG files to PNG and LVGL
  format).


4) Create a brand CMakeLists.txt file:  `firmware/vcv_ports/glue/<Brand>/CMakeLists.txt`
This file tells CMake how to build your modules.

- Typically at the top of the CMakeLists file, you will `include()` the
  `modules.cmake` file, and use the list of module names to generate the
  list of source files needed to compile, but that's not a strict requirement.

- The CMakeLists.txt must create a CMake target OBJECT library named <Brand>Library, like this:
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


5) Add the plugin to the VCV whitelist (see `vcv/src/mapping/module_directory.hh`).

6) Generate faceplate artwork. 
   You can now run `make faceplate-image` to generate the faceplate artwork. This will 
   also re-generate all other brands artwork, so it's recommend that you a
   limit file (see [Firmware README.md](../firmware/README.md) ) to just
   specify your brands' modules, or perhaps even a subset of them just to
   start. This works by reading the cmake list you created `BRAND_FACEPLATE_SVGS`

7) Generate component artwork.
   Put all SVG files for components into a folder (from the repo root) `graphics/<Brand>/components/`.
   Then run `make comp-images` to generate the component images. This will regenerate all brand's component images.
   (TODO: allow limiting this). Please only commit actually changed images.

8) Connect VCV Widgets to MetaModule Elements and LVGL images.
(TODO). For an example, see [this commit](https://github.com/4ms/metamodule/pull/135/commits/3d5a721e7c9beea818e58401e82ba4faf5d52321)
Also, see issue #47
   


