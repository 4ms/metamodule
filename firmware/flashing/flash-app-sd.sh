#!/usr/bin/env bash

if [[ $# -lt 1 || $# -ge 3 ]]; then 
	echo "Usage:"
	echo "flash-app-sd.sh main.uimg [/dev/diskXX]"
	echo ""
	echo "Where /dev/diskXX is the partition stem of the sd card"
	echo "Appending a '4' to this stem must be a valid partition."
	echo "If this argument is omitted, you will be prompted to enter it"
	echo ""
	exit 1
fi

if [ ! -f $1 ]; then
	echo "File $1 does not exist";
	exit 1;
fi

if [ $# -lt 2 ]; then
	read -p "What is the disk partition stem to copy to: " DISKPART
else
	DISKPART=$2
fi

DISKPART=${DISKPART}4

if [ ! -b $DISKPART ]; then
	echo "Device $DISKPART does not exist";
	exit 1;
fi

echo "Copying $1 to $DISKPART"

sudo dd if=$1 of=$DISKPART

