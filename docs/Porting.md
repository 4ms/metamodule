### Instructions for adding a new module

For creating a plugin, see [Plugins.md](Plugins.md)

-----

Below are instructions for adding a new built-in brand from an existing VCV Rack plugin, statically compiled 
into the main firmware. This is not a common thing, typically you will use plugins (see above).

1) **Add the module code as a git submodule into vcv_ports/**

```bash
git submodule add https://github.com/<user>/<repo> firmware/vcv_ports/<Brand>
```

2) **Copy artwork PNG files**

```bash
mkdir -p firmware/assets/<Brand>/
```

Convert all your artwork SVG files (faceplates and components) into PNG files,
and put them into this new directory.
Make sure the faceplate PNG files are 240px high, and component PNG files are 
scaled similarly.

Keep the same file names and directory structure as your original VCV Rack plugin.
Just change the `.svg` suffixes to `.png`.
The `<Brand>` directory replaces the `res/` directory that VCV plugins use.


3) **Create a brand `CMakeLists.txt` file**

   Make a new file called `firmware/vcv_ports/glue/<Brand>/CMakeLists.txt`.
   This file tells CMake how to build your modules. It's a fairly simple CMake
   file, the only thing it must do is create a new target named <Brand>Library.

   Here's an example:

```cmake

cmake_minimum_required(VERSION 3.22)

# Define your project name, vesion, etc
project(MyBrandMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "MyBrand Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(MyBrandLibrary STATIC)

target_sources(MyBrandLibrary
    PRIVATE
    #Put all source files here
)

# Put whatever dirs you need to include here:
target_include_directories(MyBrandLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../MyBrand/src)

# Put whatever compile options you need here
target_compile_options(MyBrandLibrary PRIVATE -Wno-double-promotion)

# Set properites here (at least c++20 is required)
set_property(TARGET MyBrandLibrary PROPERTY CXX_STANDARD 23)

```


4) Add the brand name to `firmware/vcv_ports/brands.cmake`

```cmake
# List of brands
set(brands
  ...
  <Brand>
)
```


5) **Add modules to internal_plugin_manager.hh**

TODO

```c++
// glue/Brand/plugin.hh
#include "plugin/Plugin.hpp"

extern rack::plugin::Model *modelSomeModule;
extern rack::plugin::Model *modelSomeOtherModule;

```


```c++
// add this to internal_plugin_manager.hh:
#include "glue/Brand/plugin.hh"

// add this to the end of load_internal_plugins()
    auto &MyBrand_plugin = internal_plugins.emplace_back("MyBrand");
    pluginInstance = &MyBrand_plugin;
    MyBrand_plugin.addModel(modelSomeModule);
    MyBrand_plugin.addModel(modelSomeOtherModule);

```

6) Run `make configure` to refresh the build with the new brand.

Then build and update firmware as normal.
