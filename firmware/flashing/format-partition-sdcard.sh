#!/usr/bin/env bash

# Script to format and partition an SD card to prepare for mp1-boot and an app

[ "$#" -eq 1 ] || { 
	echo ""
	echo "Usage: "
	echo "scripts/format-partition-sdcard.sh /dev/XXX"  >&2; 
	echo ""
	echo "Where /dev/XXX is the sd card device, e.g. /dev/sdc or /dev/disk4"
	exit 1; 
}

if [ ! -b $1 ]; then
	echo "Device $1 does not exist";
	exit 1;
fi

echo ""
echo "Device $1 found"
echo "Formatting..."

echo ""
case "$(uname -s)" in
	Darwin)
		set -x
		diskutil eraseDisk FAT32 BAREMETA $1
		set +x
		;;
	Linux)
		set -x
		mkfs.fat -F 32 $1
		set +x
		;;
	*)
		echo 'OS not supported: please format $1 as FAT32'
		;;
esac

echo ""
set -x
sudo sgdisk -o $1 
set +x

echo ""
echo "Partitioning..."
set -x
sudo sgdisk --resize-table=128 -a 1 -n 1:34:545 -c 1:fsbl1 -n 2:546:1057 -c 2:fsbl2 -n 3:1058:17441 -c 3:ssbl -N 4 -c 4:prog -p $1
set +x

echo ""
echo "Unmounting"

echo ""
case "$(uname -s)" in
	Darwin)
		set -x
		diskutil unmountDisk $1
		set +x
		;;
	Linux)
		set -x
		sudo umount $1
		set +x
		;;
	*)
		echo 'OS not supported'
		;;
esac

echo "Done!"

