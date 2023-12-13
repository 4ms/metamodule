#!/usr/bin/env bash
# Script to format and partition an SD card to prepare for mp1-boot and an app

if [ $# -lt 2 ]; then
	read -p "What is the disk device to format (e.g. /dev/disk4): " DISK
	read -p "What is the disk partition stem (e.g. /dev/disk4s): " DISKSTEM
else
	DISK=$1
	DISKSTEM=$2
fi

if [ ! -b $DISK ]; then
	echo "Error: Device $DISK does not exist";
	exit 1;
fi

if [[ "$DISKSTEM" != *"$DISK"* ]]; then
	echo "Error: Disk device name $DISK must be a substring of the disk partition stem $DISKSTEM";
	exit 1;
fi

echo ""
echo "Device $DISK found"

echo ""
case "$(uname -s)" in
	Darwin)
		echo "Formatting"
		set -x
		diskutil eraseDisk FAT32 TMPDISK $DISK
		set +x
		;;
	*)
		;;
esac

echo ""
echo "Clearing partition table and converting MBR to GPT if present..."
echo ""

set -x
sudo sgdisk -go $DISK || exit
set +x

echo ""
echo "Partitioning..."
set -x
sudo sgdisk --resize-table=128 -a 1 \
	-n 1:34:545 -c 1:fsbl1 \
	-n 2:546:1057 -c 2:fsbl2 \
	-n 3:1058:17441 -c 3:ssbl \
	-n 4:17442:33825 -c 4:prog \
	-N 5 -c 5:fatfs \
	-p $DISK || exit
set +x

echo ""
echo "Formatting partition 5 as FAT32 (for patch storage)"

echo ""
case "$(uname -s)" in
	Darwin)
		set -x
		diskutil eraseVolume FAT32 METAMOD ${DISKSTEM}5 || exit
		sleep 1
		echo "Unmounting so macOS sees the new partitions"
		diskutil unmountDisk $DISK || exit
		set +x
		;;
	Linux)
		read -p "You must eject and re-insert the SD Card now. Press enter when ready." READY
		set -x
		sudo umount ${DISKSTEM}5
		sudo mkfs.fat -F 32 -n METAMOD ${DISKSTEM}5 || exit
		set +x
		;;
	*)
		echo 'OS not supported: please format $DISK partition 5 as FAT32'
		;;
esac

echo "Success!"

