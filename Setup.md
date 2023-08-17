## Setting up your environment

All platforms:
- A c++ toolchain that has partial support for c++20 (gcc-12 or later, clang 14 or later)
- To build firmware, you need the gcc arm toolchain, version 12.2 or later.
  - Download here: https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
    - Make sure you get the package for your host computer that ends in `arm-none-eabi`
  - Or xpack versions are OK: https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/tag/v12.2.1-1.2
  - Make sure arm-none-eabi-gcc is on your PATH
  - For MacOS, sometimes the OS security system flags the executables the first
    time they are run. Just keep running "make clean" and then "make" and then
    clicking "Allow" until you get no more security pop-ups (might be 6-10
    pop-ups). It only happens the first time after installation.

### MacOS

A recent-ish macOS version is required, though I do not know exactly how old will still work.
Ventura 13.4 and 13.5 have been tested.

 - Install [brew](https://brew.sh) and follow the "Next Steps" instructions to add Homebrew to your PATH.

 - For the simulator this is needed (ninja is not required if you use a different -G option when invoking cmake):
   - `brew install cmake ninja sdl2`

 - For the VCV plugin, this is needed:
   - `brew install jq rsync`

### Linux

TODO: check this, and notes for different distros

 - sudo apt-get install bison flex gcc-12

 
### Windows

TODO: Help wanted!

