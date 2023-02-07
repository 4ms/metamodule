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

Create a `src/local_path.hh` file by copying the template and changing to paths to valid paths on your system.
If you're not creating patch files, it won't matter if the path is valid (i.e., they can be empty strings).
Once we incorporate OS filesystem tools into the plugin, this won't be necessary.

```
cp src/local_path_template.hh src/local_path.hh
vi src/local_path.hh  # Open with your preferred editor and edit the paths
```

Next, create/update the module artwork and info headers:

```
make modules
```

To build the plugin, run:

```
make install
```

This will create the plugin file and install it in the VCV Rack plugin directory. The next time you start VCV Rack, it will load the modified plugin.


### Building Firmware

To create the artwork files from the SVGs, you must have Inkscape and Imagemagick installed an on your PATH

...
