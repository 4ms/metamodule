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

 - `sudo apt-get install cmake g++-12 jq ninja-build pkg-config`
 - Set gcc-12 and g++-12 to be the default. E.g. on Ubuntu 22.04: 
   - `sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 120`
   - `sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 120`

 - To use the simulator GUI, you need to also install:
   - `sudo apt-get install libsdl2-dev`

 
### Windows

To get started, you will want to follow the development environment guide for
VCV Rack [here](https://vcvrack.com/manual/Building#Windows). This will help
you set up an MSYS2/MinGW development environment along with most packages
required for MetaModule development. In short, install [MSYS](http://www.msys2.org/)
and then open the MinGW 64-bit shell and run:

```
pacman -Syu git wget make tar unzip zip mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb mingw-w64-x86_64-cmake autoconf automake libtool mingw-w64-x86_64-jq python zstd mingw-w64-x86_64-pkgconf
```

The only additional packages that you will need to install are ninja (which is
a build system), and SDL2 (which is only required for the simulator). Similar
to the VCV arguments, you will want to open a MinGW 64-bit shell and type the
following:

```
pacman -Syu mingw-w64-x86_64-ninja mingw-w64-x86_64-SDL2

```

To build the firmware, be sure that you've installed the `arm-none-eabi`
package listed at the top of this document. You will need to add this to your
MinGW PATH. If you haven't used MinGW before, this isn't the most
straightforward. Close all terminal prompts, and open
C:\msys64\home\\(USERNAME)\\.bashrc in a text editor of your choice. If you
used the .exe installer from ARM, then you need
to add the following line (you might need to change this depending on if
`arm-none-eabi` has a different version number since this document was
written):

```
export PATH=$PATH:"/c/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/12.3 rel1/bin"
```

If you downloaded the zip file from ARM, then change the above path to the 
location of the unzipped folder with `bin/` at the end. For example, if you
unzipped it in your MinGW home directory, use this:

```
export PATH=$PATH:/home/USERNAME/arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi/bin
```

To test this, open a new MinGW 64-bit shell and type:

```
arm-none-eabi-gcc --version
```

You should see the version number and some copyright info. If not, check where
the arm-none-eabi package was installed and adjust your PATH setting.

*Tip*: When building anything for MetaModule, be sure to launch the MinGW 64-Bit
shell! If you have Windows Terminal installed, it is worth setting up a profile
so that you can easily launch MinGW 64-Bit shells as Terminal tabs. If you have
Windows Terminal installed, you can open the Settings menu and create a
profile. For the Command Line option, if you installed MSYS2/MINGW64 to the
default location, the command that you want is 

```
C:/msys64/msys2_shell.cmd -defterm -here -no-start -mingw64
```

To help distinguish this tab from a regular `cmd` or `Windows Powershell` tab,
you should set the Icon option. Again, with default paths, this path is

```
C:/msys64/mingw64.ico
```

*Tip*: Many elements of the MetaModule code require C++20, so if you previously setup
a VCV environment (or an MSYS2 environment), you might need to update `gcc` to
`gcc-12` or higher. To find out which version you are using, you need to open
up a MinGW 64-Bit shell. Type the following command:

```
gcc -v
```

A large number of diagnostics will pop up, but the last line should show which
version of `gcc` you are running. If you are running anything below version
12.0, you will need to update `gcc`. Type the following in a MinGW prompt to
update `gcc` via the package manager:

```
pacman -Syu mingw-w64-x86_64-gcc
```

