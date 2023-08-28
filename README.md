## Meta Module

[![Build Simulator](https://github.com/4ms/metamodule/actions/workflows/build_simulator.yml/badge.svg)](https://github.com/4ms/metamodule/actions/workflows/build_simulator.yml)
[![Build VCV Rack Plugin](https://github.com/4ms/metamodule/actions/workflows/build_vcv_plugin.yml/badge.svg)](https://github.com/4ms/metamodule/actions/workflows/build_vcv_plugin.yml)
[![Run VCV unit tests](https://github.com/4ms/metamodule/actions/workflows/run_vcv_tests.yml/badge.svg)](https://github.com/4ms/metamodule/actions/workflows/run_vcv_tests.yml)
[![Build Firmware](https://github.com/4ms/metamodule/actions/workflows/build_test_firmware.yml/badge.svg)](https://github.com/4ms/metamodule/actions/workflows/build_test_firmware.yml)

### Start

First, clone this repo and `cd` into the new directory.

```
git clone https://github.com/4ms/metamodule
cd metamodule
```

If you would like to use a different branch than `main`, switch to this branch before submodules are updated:

```
git checkout BRANCHNAME
```

Initialize and update the submodules recursively:

```
git submodule update --init --recursive
```

Next, setup your development environment by [following the instructions on this page](Setup.md).

### Next Steps

The Meta Module environment is built using three separate components: The VCV Rack Plugin (which includes the Meta Module patch exporter module), the Firmware for the Meta Module hardware, and the Firmware Simulator that allows you to run the firmware locally to test changes.

To build these components, please follow the separate build guides:
- [VCV Rack Plugin](./vcv/README.md)
- [Firmware Simulator](./simulator/Setup.md)
- [Firmware](./firmware/README.md)


### Contributing

If you would like to port your own VCV modules to the Meta Module platform, please see the [Porting Guide](./Porting.md).

