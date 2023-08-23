#!/usr/bin/env bash

if [[ $# -lt 1 || $# -ge 3 ]]; then 
	echo "Usage:"
	echo "flash-app-sd.sh main.uimg [/dev/diskX]"
	echo ""
	echo "If the second argument is omitted, you will be prompted to enter it"
	echo ""
	exit 1
fi

if [ ! -f $1 ]; then
	echo "File $1 does not exist";
	exit 1;
fi

if [ $# -lt 2 ]; then
	read -p "What is the disk device and partition to copy to: " DISK
else
	DISK=$2
fi

if [ ! -b $DISK ]; then
	echo "Device $DISK does not exist";
	exit 1;
fi

case "$(uname -s)" in
	Darwin)
		DISKPART=${DISK}s4
		;;
	Linux)
		DISKPART=${DISK}4
		;;
	*)
		echo "OS not supported: please use dd to transfer $1 to partition 4 of ${DISK}"
		;;
esac

echo "Copying $1 to $DISKPART"

sudo dd if=$1 of=$DISKPART

