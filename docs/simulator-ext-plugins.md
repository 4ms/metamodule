## External Plugins

The Simulator cannot load plugins in the same way the firmware can. But, there is a hack that allows you to build plugins
into the simulator (as a "built-in") in order to test a plugin without needing hardware.

### Requirements

The plugin project should live in a separate directory, outside of the
metamodule repo. 
The project must contain a CMakeLists.txt file that builds a .mmplugin file.
See the
[metamodule-plugins-examples](https://github.com/4ms/metamodule-plugins-examples)
repo for examples. 
Within the plugin, there must be an `init()` function (or `init(rack::Plugin
*)`).

### Building

You must make a few changes to the code to make this hack work:

1. In your plugin, find the `init()` function and change it to `init_PluginSlug()`, 
   where PluginSlug is the brand slug of your plugin (check your plugin.json file to 
   find your brand slug). This is needed because we can't have multiple
   functions with the name `init()`.

2. If you have a global variable in your plugin called `pluginInstance`, you need
   to make it `extern`. So find this:

```c++
   Plugin* pluginInstance;
```

   and change it to this:
```c++
   extern Plugin* pluginInstance;
```

   This is needed because there already is a global variable called pluginInstance, and 
   we can't have two.

3. In your plugin's CMakeLists.txt file, make sure something like this is at the top:

```cmake
if(NOT "${METAMODULE_SDK_DIR}" STREQUAL "")
	message("METAMODULE_SDK_DIR set by CMake variable ${METAMODULE_SDK_DIR}")
elseif (DEFINED ENV{METAMODULE_SDK_DIR})
    set(METAMODULE_SDK_DIR "$ENV{METAMODULE_SDK_DIR}")
	message("METAMODULE_SDK_DIR set by environment variable ${METAMODULE_SDK_DIR}")
else()
    set(METAMODULE_SDK_DIR "${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk")
	message("METAMODULE_SDK_DIR set to default: ${METAMODULE_SDK_DIR}")
endif()

include(${METAMODULE_SDK_DIR}/plugin.cmake)
```

This block will look for a cmake variable called METAMODULE_SDK_DIR, and use
that to find the SDK. If that doesn't exist, it looks for a shell environment
variable with the same name. Failing that, it looks for the SDK in the parent
directory. It also will print the dir it's going to use. The reason this is
needed is because in order for the simulator to build the plugin as a
built-in, it tells the plugin to use a fake SDK.

If you get an error like:

```
  add_library cannot create target "metamodule-rack-interface" because  another target with the same name already exists. 
```

then your plugin is trying to build with the normal SDK instead of the
simulator's fake SDK. Something is wrong with the block of cmake code above, or
else METAMODULE_SDK_DIR is not being set properly.


4. Finally, in the simulator project, open the file `simulator/ext-plugins.cmake`
   and add these two lines at the top:

```cmake
list(APPEND ext_builtin_brand_paths "${CMAKE_CURRENT_LIST_DIR}/../../metamodule-plugin-examples/PluginSlug")
list(APPEND ext_builtin_brand_libname "PluginSlug")
```

Replace PluginSlug with your brand slug.

5. Now, you can build the simulator from within the simulator directory (not the firmware dir!) and your plugin should show up as a built-in brand.

```bash
cd metamodule/simulator
make clean
make
make run
```

### Limitations

Since this is a bit of a hack, there are some limitations:

- Plugins cannot use POSIX filesystem calls to access files in their assets/ dir.
  Plugins *can* access .ttf fonts and .png files for widgets loaded by the
  rack interface or by the native plugin ModuleInfo interface. But calls to
  fopen(), fread(), etc. will not find the files in the assets/ dir. The reason
  is that on hardware the assets are loaded as a FatFS RAM disk. The simulator
  simulates mounting the FatFS RAM Disk and accesses the files via that instead
  of directly from the host computer. (One goal of the simulator is to closely
  imitate hardware, so doing it this way is intentional). It probably wouldn't
  be too difficult to make a workaround for this.

- Other filesystem calls might not work. I haven't explored every edge case,
  but in general since the simulator is simulating the filesystem of the
  MetaModule, there might be other things broken when trying to access files on
  the host computer.

If you are experiencing an issue along these lines with an external plugin on
the simulator, testing on actual hardware is the best way to determine if an
issue is due to one of these limitations or is an actual bug.

- Variable names, function names, and macros (`#define`) might collide. Since
  the plugin is being built and linked with the simulator code and all the
  normal built-in modules (Befaco, HetrickCV, 4ms, etc) there's a chance some
  function or global variable name your plugin uses will already be in use.
  Hopefully this will cause a compiler error, but in the worst case it could
  cause a runtime crash (especially with macros). Unfortunately there's not an
  easy way around this besides renaming your functions/variables, using
  namespacing, and/or avoiding macros. Searching the metamodule repo for the
  offending text should tell you if this is happening, or you can try building
  the plugin normally and see if you get the same error.


  I would not be surprised if there are other limiations, so please report it
  (via email, the forum, or open a github issue) if you find something.


