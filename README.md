## MetaModule

### Start

After cloning this repo, init and update the submodules recursively:

```
git submodule update --init --recursive
```

### Building VCV Rack Plugin

You must have the Rack-SDK on your computer already. Version 2.2.3 is known to work. Set the environment variable `RACK_DIR` equal to the patch to the location of Rack-SDK:

```
export RACK_DIR=/Users/MyName/projects/Rack-SDK
```

Enter the vcv directory. All VCV Rack plugin code is in here, as well as in `shared/`

```
cd vcv
```

Create a `src/local_path.hh` file by copying the template. This file is required to build, even if the next step is skipped.

```
cp src/local_path_template.hh src/local_path.hh
```

SKIP THIS STEP IF YOU ARE NOT CREATING PATCH FILES TO TRANSFER TO HARDWARE.
Change to paths in src/local_path.hh to valid paths on your system.
Once we incorporate OS filesystem tools into the plugin, this won't be necessary.

```
vi src/local_path.hh  # Open with your preferred editor and edit the paths
```

SKIP THIS STEP IF YOU ARE NOT ADDING OR MODIFYING SVG FILES
Next, create/update the module artwork and info headers:

```
make modules
```

To build the plugin, run:

```
make -j16 install
```

This will create the plugin file and install it in your local VCV Rack plugin directory. The next time you start VCV Rack, it will load the modified plugin.


### Building Firmware

To create the artwork files from the SVGs, you must have Inkscape and Imagemagick installed an on your PATH

...To Be Continued...
