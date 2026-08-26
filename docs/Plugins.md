## Plugins


Plugins are dynamically-loaded binaries that add modules to the MetaModule. 

The [MetaModule Plugin SDK](https://github.com/4ms/metamodule-plugin-sdk) is used to create plugins.

For examples, see [metamodule-plugin-examples](https://github.com/4ms/metamodule-plugin-examples)

When doing plugin development, use the `Developer Mode` to transfer plugins from your computer to the MetaModule. See [Developer Drive](../firmware/metamodule-plugin-sdk/docs/developer-drive.md).

### VCV Rack plugins

Most plugins are VCV Rack modules re-compiled for the MetaModule. The `rack-interface` directory of the plugin SDK provides a similar API as the Rack SDK. The API functions are implemented as wrappers and adaptors for the `core-interface`.

Most VCV plugins can be build as-is. Many of the limitations in v1.x SDK and early v2.x SDKs are now lifted.

### Native plugins

Plugins do not need to be based on VCV Rack. For an example, see Airwindows in
[metamodule-plugin-examples](https://github.com/4ms/metamodule-plugin-examples)


### What happens when a plugin is loaded
At minimum, a plugin must define an `init()` function, but there is nothing else required.

When a plugin is loaded, first all the assets are copied to the internal RAM drive into a subdirectory.

Next, the `.so` file is parsed (as an elf file) and all dynamic relocations are performed. If there are unresolved symbols, they are reported and it aborts.

Next, the global static constructors are called

Finally, the `init()` function is called. 

A plugin's job is to initialize plugin-wide data (if any) and register its
modules. This is usually done in `init()` but also can be done in the global
constructors.

In a typical VCV Rack plugin, modules are registered with calls to
`p->addModel(modelName)` in `init()`. 

In native plugins, modules can be
registered using one of the `register_module()` functions, defined in
`core-interface/CoreModules/register_module.hh`

For example:

```c++
class MyModule : public CoreProcessor {
    //...
};

struct MyModuleInfo : ModuleInfoBase {
    //...
};

extern "C" void init() {
    register_module<MyModule, MyModuleInfo>("MyBrandName");
}

```

For a complete simple example of a working plugin, see the Native Example plugin README in [metamodule-plugin-examples](https://github.com/4ms/metamodule-plugin-examples/blob/main/NativeExample/README.md)

Also see the [MetaModule Plugin SDK README](https://github.com/4ms/metamodule-plugin-sdk/blob/main/README.md) for an in-depth discussion.
