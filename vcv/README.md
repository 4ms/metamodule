This folder contains emulations of [4ms Company's](https://4mscompany.com/) Eurorack modules for the [VCV Rack](https://vcvrack.com/) platform.

If you have not previously built plugins for VCV Rack before, you will want to setup a build environment by following the instructions [here](https://vcvrack.com/manual/Building).

### Building VCV Rack Plugin

You must have the Rack-SDK on your computer already. Version 2.2.3 is known to
work. Set the environment variable `RACK_DIR` equal to the path to the
location of Rack-SDK. For instance, add this to your .bashrc or .zshrc:

```
export RACK_DIR=/Users/MyName/projects/Rack-SDK
```

Enter the vcv directory. All VCV Rack plugin code is in here, as well as in
`shared/`

```
cd vcv
```

You will need a recent c++ compiler such as gcc-12 or later, or clang-14 or later.

To run the unit tests:

```
make tests
```

To build the plugin, run:

```
make -j16 install
```

This will create the plugin file and install it in your local VCV Rack plugin
directory. The next time you start VCV Rack, it will load the modified plugin.