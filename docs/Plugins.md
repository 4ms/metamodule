## Plugins


Plugins are dynamically-loaded binaries that add modules to the MetaModule. 

The [MetaModule Plugin SDK](https://github.com/4ms/metamodule-plugin-sdk) is used to help create plugins.

For examples, see [metamodule-plugin-examples](https://github.com/4ms/metamodule-plugin-examples)


### VCV Rack plugins

Most plugins are VCV Rack modules re-compiled for the MetaModule. The `metamodule-rack-interface` submodule of the plugin SDK provides a similar API as the Rack SDK. The API functions are implemented as wrappers and adaptors for the `metamodule-core-interface`.

TODO: 
Describe system:
- How faceplate is assigned
- Rack components
- ModuleWidget's widget tree -> element conversion
- How images work and limitations


### Native plugins

Plugins do not need to be based on VCV Rack. For an example, see Airwindows in
[metamodule-plugin-examples](https://github.com/4ms/metamodule-plugin-examples)

At minimum, a plugin must define an init() function, but there is nothing else required.

- When a plugin is loaded, first all the assets are copied to the internal RAM drive into a subdirectory.

- Next, the `.so` file is parsed (as an elf file) and all dynamic relocations are performed. If there are unresolved symbols, they are reported and it aborts.

- Next, the global static constructors are called

- Finally, the init() function is called. 

A plugin's job is to intialize plugin-wide data (if any) and register its
modules. This is usually done in init() but also can be done in the global
constructors.

In a typical VCV Rack plugin, modules are registered with calls to
`p->addModel(modelName)` in init(). In the more general case, modules can be
registered using the function `register_module()`, defined in
`metamodule-core-interface` in `CoreModules/register_module.hh`:

```c++
using CreateModuleFunc = std::function<std::unique_ptr<CoreProcessor>()>;

bool register_module(std::string_view brand_name,
					 std::string_view typeslug,
					 CreateModuleFunc funcCreate,
					 ModuleInfoView const &info,
					 std::string_view faceplate_filename);
```

`ModuleInfoView` is a view into the module's elements (knobs, jacks, etc). Since only a view is passed to the MetaModule core interface,
the actual data must live statically for the entire duration of the plugin. VCV plugins achieve this using global `Model` variables,
but you also could put them on the heap and then free them in the global destructors.

`funcCreate` is a factory function that returns a unique_ptr to a `CoreProcessor` module.
The `CoreProcessor` class is a virtual base class which is the base of all MetaModule modules:

```c++
class CoreProcessor {
public:
	virtual void update() = 0;
	virtual void set_samplerate(float sr) = 0;
	virtual void set_param(int param_id, float val) = 0;
	virtual void set_input(int input_id, float val) = 0;
	virtual float get_output(int output_id) const = 0;
	virtual float get_led_brightness(int led_id) { return 0; }
	virtual void mark_all_inputs_unpatched() {}
	virtual void mark_input_unpatched(int input_id) {}
	virtual void mark_input_patched(int input_id) {}
	virtual void mark_all_outputs_unpatched() {}
	virtual void mark_output_unpatched(int output_id) {}
	virtual void mark_output_patched(int output_id) {}
	virtual void load_state(std::string_view state_data) {}
	virtual std::string save_state() { return ""; }
};
```

Putting it all together, here is a simple native plugin to provide gain to an
audio signal (with an LED to show the gain):

```c++
// simple_gain.hh

#include "CoreModules/CoreProcessor.hh"

enum { GainKnobID };
enum { InputJackID };
enum { OutputJackID };
enum { GainLightID };

class SimpleGain : public CoreProcessor {
public:
    void update() override;
    void set_param(int param_id, float val) override;
    void set_samplerate(float sr) override;
    void set_input(int input_id, float val) override;
    float get_output(int output_id) const override;
    float get_led_brightness(int led_id) const override;

private:
    float in = 0;
    float out = 0;
    float gain = 1.f;
};

```

```c++
// simple_gain.cc

#include "simple_gain.hh"

void SimpleGain::update() {
    out = in * gain;
}

void SimpleGain::set_param(int param_id, float val) {
    if (param_id == GainKnobID)
        gain = val;
}

void SimpleGain::set_samplerate(float sr) {
}

void SimpleGain::set_input(int input_id, float val) {
    if (input_id == InputJackID)
        in = val;
}

float SimpleGain::get_output(int output_id) const {
    if (output_id == OutputJackID)
        return out;
    else
        return 0;
}

float SimpleGain::get_led_brightness(int led_id) const {
    if (led_id == GainLightID)
        return gain;
    else
        return 0;
}

```

Then we will define the module's elements (jacks, knob, light) and register it in the init() function:

```c++
// plugin.cc
    
#include "simple_gain.hh"
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "CoreModules/register_module.hh"
#include "CoreModules/CoreProcessor.hh"

void init() {
    static std::array<MetaModule::Element, 4> elements; 
    static std::array<ElementCount::Indices, 4> indices;

    MetaModule::Knob gain;
    gain.x_mm = 10;
    gain.y_mm = 20;
    gain.image = "Brandname/comps/knob.png";
    gain.short_name = "Gain";
    elements[0] = gain;
    indices[0] = {.param_idx = GainKnobID}; 

    MetaModule::JackInput injack;
    injack.x_mm = 10;
    injack.y_mm = 60;
    injack.image = "Brandname/comps/jack.png";
    injack.short_name = "Input";
    elements[1] = injack;
    indices[1] = {.input_idx = InputJackID}; 

    MetaModule::JackOutput outjack;
    outjack.x_mm = 10;
    outjack.y_mm = 80;
    outjack.image = "Brandname/comps/jack.png";
    outjack.short_name = "Output";
    elements[2] = outjack;
    indices[2] = {.output_idx = OutputJackID}; 

    MetaModule::MonoLight light;
    light.x_mm = 10;
    light.y_mm = 30;
    light.image = "Brandname/comps/led.png";
    light.short_name = "Gain LED";
    elements[3] = light;
    indices[3] = {.light_idx = GainLightID}; 

    MetaModule::ModuleInfoView info {
        .description = "A simple gain module",
        .width_hp = 10,
        .elements = elements,
        .indices = indices,
    };

    MetaModule::register_module("Brandname", "SimpleGain", [](){ return std::make_unique<SimpleGain>(); }, info, "Brandname/simple_gain.png");
}

```

Of course this method of defining the elements one by one does not scale well
if you have lots of modules, but you are free to use any method. For the 4ms
modules, we use a python script to parse SVGs and generate a c++ header file
with a constexpr array of elements. You also could generate the table at
runtime, as is done with the Airwindows modules.

One "gotcha" is that if the strings are not backed by static storage,
then you will need to provide the strings in some sort of static container.
The reason is that Element type only contains string_views, and likewise
the module registry contains string_views. See the Airwindows `module_creator.cc`
for an example.

Then to build it, put this CMakeLists.txt in the same directory:

```cmake
cmake_minimum_required(VERSION 3.22)
include(../metamodule-plugin-sdk/plugin.cmake)

project(SimpleModules 
    VERSION 0.1 
    DESCRIPTION "Example Native Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(SimpleModules STATIC)
target_include_directories(SimpleModules PRIVATE . )

target_sources(SimpleModules PRIVATE
	simple_modules.cc
    plugin.cc
)

# Call this to link and create the plugin file
create_plugin(
    SOURCE_LIB      SimpleModules
    PLUGIN_NAME     SimpleModules
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/SimpleModules
)

```

Finally, put the png files referenced in `plugin.cc` into a dir called `assets/`.

