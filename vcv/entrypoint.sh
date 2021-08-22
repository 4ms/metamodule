#!/bin/sh

set -eu

export RACK_DIR=$(PWD)/Rack-SDK
#export RACK_USER_DIR=./
export RACK_SDK_VERSION=1.1.6

curl -L https://vcvrack.com/downloads/Rack-SDK-${RACK_SDK_VERSION}.zip -o rack-sdk.zip
unzip -o rack-sdk.zip
rm rack-sdk.zip

#export CC=x86_64-w64-mingw32-gcc-posix
#export CXX=x86_64-w64-mingw32-g++-posix
export CC=x86_64-w64-mingw32-gcc
export CXX=x86_64-w64-mingw32-g++
export STRIP=x86_64-w64-mingw32-strip

cd /plugin
cd vcv
make clean
make dist

