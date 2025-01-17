## Building the Simulator

The simulator uses SDL2, which must be installed on your host machine. It 
simulates graphics and audio output. 
Install the requirements as described in [Setup](../docs/Setup.md)

Make sure you are in the right branch and you already updated the submodules.

Go to the simulator directory:

```
cd simulator
```

Generate the build system:

```
cmake -B build -GNinja      #Or whatever build system you want
```

Build it:

```
cmake --build build
```

Run it:

```
build/simulator

# To see the possible command-line arguments:
build/simulator --help
```

See the [Simulator Usage guide](simulator-usage.md) for arguments details.

As a shortcut, there is a Makefile wrapping the above cmake commands. 
You can just do:

```
# Generate build system (if needed) and build:
make

# Run the simulator:
make run

# Clean:
make clean
```

Note that `make run` doesn't allow you to pass arguments.

### Adding/removing PNG images from assets directory

When adding/removing images in the `firmware/assets` dir, you must re-build the assets tar image before the simulator will 
show the updated image assets. This is done automatically whenever you build the firmware normally, or you can build the `asset-image` cmake target:

```
# edit/add/remove some graphical asset in the firmware/assets dir

cd ../firmware
cmake --build build -- asset-image
cd ../simulator

# now running the simulator will use the updated assets
```

The reason is that the simulator does not access the `firmware/assets` dir on the host filesystem
directly, instead it does the same thing that the firmware does: untar the assets tarball into a virtual FatFS ram disk. 

### Running external plugins

You cannot load .mmplugin files into the simulator (the GUI for loading/unloading works, but the plugin is not actually loaded).

Instead, there is a crude but simple way to run a plugin in the simulator.

1. Add the path to the external plugin directory, and the name of the cmake
   target library to ext-plugins.cmake. For example, to run Venom in the
   simulator, you could add this to the top of ext-plugins.cmake (assuming the
   path is correct):

```cmake
    list(APPEND ext_builtin_brand_paths "${CMAKE_CURRENT_LIST_DIR}/../../metamodule-plugin-examples/Venom")
    list(APPEND ext_builtin_brand_libname "Venom")
```

    Make sure the libname ("Venom") exactly matches the brand slug.

2. Inside the plugin source code, rename the `init(rack::Plugin *plugin)` function to
   `init_Brand(rack::Plugin *plugin)`. So for Venom, for example, it would be
   `init_Venom(rack::Plugin *plugin)`. 

3. Inside the plugin source code, usually in the same file where the `init`
   function is, make the `Plugin *pluginInstance` global extern. So, change
   this: 

```
Plugin *pluginInstance;
```

to this:

```
extern Plugin *pluginInstance;
```

Then you should be able to build and run the simulator. You DO NOT need to
build the plugin separately -- the simulator will build and link it into the
simulator binary. The new brand will show up as a built-in brand, it's no
longer a plugin so it'll just be in the list of brands as soon as you run the
simulator.


If you go back and forth between building as a simulator external brand, and as a hardware plugin, 
and you don't want to keep changing the source code, then you can do something like this:

```c++
#if defined(METAMODULE_BUILTIN)
extern Plugin *pluginInstance;
#else
Plugin *pluginInstance;
#endif

//...

#if defined(METAMODULE_BUILTIN)
void init_Venom(rack::Plugin *p) {
#else 
void init(rack::Plugin *p) {
#endif
```

