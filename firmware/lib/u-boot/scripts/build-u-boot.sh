#!/usr/bin/env bash

if [ "$#" -eq 0 ]; then
	UDIR="third-party/u-boot/u-boot-stm32mp1-baremetal"
	echo ""
	echo "Using $UDIR for u-boot source"
	echo ""
fi

if [ "$#" -eq 1 ]; then
	UDIR=$1
fi

if [ "$#" -ge 2 ]; then
	echo ""
	echo "Usage: "
	echo "scripts/build-u-boot.sh path/to/u-boot-stm32mp1-baremetal"
	echo ""
	echo "path defaults to third-party/u-boot/u-boot-stm32mp1-baremetal"
	echo ""
	exit 1
fi


echo "What board do you want to build for?"
echo "1) STM32MP157A-DK1"
echo "2) STM32MP157C-DK2"
echo "3) STM32MP157D-DK1"
echo "4) STM32MP157F-DK2"
echo "5) OSD32MP1-BRK"
echo "6) 4ms OSD32MP1-BRK clone"
echo "7) 4ms MM p7"
read -p "Enter a number 1-7: " boardnum

DT=""

case $boardnum in
	"1")
		DT="stm32mp157a-dk1"
		;;
	"2")
		DT="stm32mp157c-dk2"
		;;
	"3")
		DT="stm32mp157d-dk1"
		;;
	"4")
		DT="stm32mp157f-dk2"
		;;
	"5")
		DT="stm32mp157c-osd32mp1-brk"
		;;
	"6")
		DT="stm32mp157c-4ms-mp1-brk"
		;;
	"7")
		DT="stm32mp153dad-metamodule-p7"
		;;
	*)
		echo "Please enter a number 1-7"
		exit 0
esac

CURDIR=$(pwd)


echo ""
echo "Building with these commands:"
echo "cd $UDIR"
echo "make O=../build DEVICE_TREE=$DT CROSS_COMPILE=arm-none-eabi- stm32mp15x_baremetal_defconfig"
echo "make -j16 O=../build DEVICE_TREE=$DT CROSS_COMPILE=arm-none-eabi- all"
echo "cd $CURDIR"
echo ""

#rm -rf ../build
cd $UDIR
make O=../build DEVICE_TREE=$DT CROSS_COMPILE=arm-none-eabi- stm32mp15x_baremetal_defconfig
make -j16 O=../build DEVICE_TREE=$DT CROSS_COMPILE=arm-none-eabi- all
cd $CURDIR

