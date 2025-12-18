### Instructions for adding a new module

For creating a plugin, see [Plugins.md](Plugins.md)

-----

Below are instructions for adding a new built-in module, statically compiled 
into the main firmware. 

1) **Add the module code to `firmware/modules`. 

See `firmware/modules/blank.hh` for an example structure. Notice there are two classes or structs:
the `Info` struct (`BlankInfo` in this case) and the `CoreProcessor` or
`SmartCoreProcessor` class (called `Blank` in this case, which derives from
`SmartCoreProcessor<BlankInfo>`)

For larger modules, you might want to put the `Info` struct and the
`CoreProcessor` class in different files, but it's up to you how to organize it.

You also might want to make a `.hh` file for the module class declaration
(interface), and a `.cpp` or `.cc` file that actually defines the methods
(implementation). If you do this, make sure to add the `.cpp` file to 
`firmware/src/CMakeLists.txt`. Like this:

```cmake
# Find this part of the cmake file:
add_executable(
  main.elf
  # ....
  # add your module anywhere in this list:
  ${FWDIR}/modules/my_new_module.cpp
  # ...
)
```

2) **Add modules to `internal_plugin_manager.hh`**

In the `load_internal_plugins()` function, add a call to `register_module`. Follow the example
given for the Blank module:

```c++
void load_internal_plugins() {
    //...
    // Add this line:
    register_module<MyNewModule, MyNewModuleInfo>("MyBrandSlug");
```

3) **Optional: Add the module to the json files**

If you want support for using module metadata in the firmware, then you need to add the metadata to both .json files.

This gives you the ability to search/filter modules by tag, list module names by their
display name (instread of just their slug), list brand aliases (display names).

Add an entry for your new module into the "modules" section of `firmware/assets/plugin.json` and into the "MetaModuleIncludedModules" section of `firmware/assets/plugin-mm.json`.

```json

  "modules": [
    # add this (make sure to avoid trailing commas!)
    {
      "slug": "MyModule",
      "name": "My Module Name",
      "description": "An example module",
      "tags": [
        "Utility"
      ]
    },
    # more modules follow...
  ]
```


4) **Optional: add any supporting files to `firmware/assets/built-ins`**

This is optional, but if you have any files that your modules will open 
(like a .wav file perhaps), then put it in the assets dir.
It be accessed from your module with `fopen`, using the path `ram:/filename.wav`

