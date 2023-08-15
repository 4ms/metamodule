#!/usr/bin/env bash

# Script to unmount an SD Card

[ "$#" -eq 1 ] || { 
	echo ""
	echo "Usage: "
	echo "unmount.sh /dev/XXX"  >&2; 
	echo ""
	echo "Where /dev/XXX is the sd card device, e.g. /dev/sdc or /dev/disk4"
	exit 1; 
}

if [ ! -b $1 ]; then
	echo "Device $1 does not exist";
	exit 1;
fi

echo ""
echo "Unmounting..."

case "$(uname -s)" in
	Darwin)
		diskutil unmountDisk $1
		;;
	Linux)
		sudo umount $1
		;;
	*)
		echo 'OS not supported'
		;;
esac

echo "Done"
