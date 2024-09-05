# MetaModule

[![Build Simulator](https://github.com/4ms/metamodule/actions/workflows/build_simulator.yml/badge.svg)](https://github.com/4ms/metamodule/actions/workflows/build_simulator.yml)
[![Build Firmware](https://github.com/4ms/metamodule/actions/workflows/build_test_firmware.yml/badge.svg)](https://github.com/4ms/metamodule/actions/workflows/build_test_firmware.yml)

## Start

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

Next, setup your development environment by [following the instructions on this page](./docs/Setup.md).

## Next Steps

The MetaModule environment is built using three separate components: The VCV Rack Plugin (which includes the MetaModule patch exporter module), the Firmware for the MetaModule hardware, and the Firmware Simulator that allows you to run the firmware locally to test changes.

For information about building and using these components, please follow the separate guides:

- [VCV Rack Plugin](./vcv/README.md)
- [Simulator](./simulator/README.md)
- [Firmware](./firmware/README.md)

## Usage

- [Creating MetaModule Patches With VCV](./docs/BasicVCVPatching.md)
- [Updating Firmware](./docs/user-firmware-update.md)


## Contributing

If you would like to create plugins of your own VCV modules for the MetaModule platform, please see the [Plugin Guide](./docs/Plugins.md).

