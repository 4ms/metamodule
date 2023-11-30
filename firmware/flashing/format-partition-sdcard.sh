#!/usr/bin/env bash
# Script to format and partition an SD card to prepare for mp1-boot and an app

if [ $# -lt 1 ]; then
	read -p "What is the disk device to format: " DISK
else
	DISK=$1
fi

if [ ! -b $DISK ]; then
	echo "Device $DISK does not exist";
	exit 1;
fi

echo ""
echo "Device $DISK found"
echo "Formatting..."

echo ""
case "$(uname -s)" in
	Darwin)
		set -x
		diskutil eraseDisk FAT32 BAREMETA $DISK
		set +x
		;;
	Linux)
		set -x
		mkfs.fat -F 32 $DISK
		set +x
		;;
	*)
		echo 'OS not supported: please format $DISK as FAT32'
		;;
esac

echo ""
set -x
sudo sgdisk -g $DISK || exit
sudo sgdisk -o $DISK || exit
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
	-p $DISK
set +x

echo ""
echo "Formatting partition 5 as FAT32"

echo ""
case "$(uname -s)" in
	Darwin)
		set -x
		diskutil eraseVolume FAT32 METAMOD ${DISK}s5
		sleep 3
		diskutil unmountDisk $DISK
		set +x
		;;
	Linux)
		set -x
		sudo mkfs.fat -F 32 ${DISK}p5
		sleep 3
		sudo umount ${DISK}
		set +x
		;;
	*)
		echo 'OS not supported: please format $DISK partition 5 as FAT32'
		;;
esac

echo "Done! Remove and re-insert the card now."

