#!/usr/bin/env bash

# dev_drive.sh: install a plugin onto a MetaModule over the developer drive.
#
# It mounts the drive, copies the plugin to the drive, unmounts it
# sends the INSTALL command via the console, and waits for the
# drive to come back.
# 
# Requires Developer Mode to be enabled in Preferences > USB.
#
# It boils down to essentially these basic commands:
#
# MacOS:
# diskutil mount DEV_MM 
# cp plugin.mmplugin /Volumes/DEV_MM
# diskutil unmount /Volumes/DEV_MM 
# echo "INSTALL" > /dev/console-device
#
# Linux:
# mount -L "DEV_MM"
# cp plugin.mmplugin `findmnt -rn -S "LABEL=DEV_MM" -o TARGET`
# umount `findmnt -rn -S "LABEL=DEV_MM" -o TARGET`
# echo "INSTALL" > /dev/console-device


set -u

DEFAULT_LABEL=DEV_MM
TIMEOUT_SEC=30

usage() {
	cat <<EOF
Usage:
  dev_drive.sh plugin.mmplugin /dev/console-device [volume-label]

Where: plugin.mmplugin is the plugin file to install.

       /dev/console-device is the MetaModule's USB console, typically
       /dev/cu.usbmodemXXXXXX on macOS, or /dev/ttyACM0 on Linux

       volume-label is the developer drive's label (default: $DEFAULT_LABEL)
       On Linux this assumes the drive can be mounted by label, either via
       an /etc/fstab entry for LABEL=$DEFAULT_LABEL or with udisksctl.
EOF
	exit 1
}

if [[ $# -lt 2 || $# -gt 3 ]]; then
	usage
fi

plugin=$1
console=$2
label=${3:-$DEFAULT_LABEL}

if [[ ! -f $plugin ]]; then
	echo "Plugin file '$plugin' does not exist" >&2
	exit 1
fi

if [[ ! -e $console ]]; then
	echo "Console device '$console' does not exist" >&2
	echo "Is the USB cable connected, and Developer Mode enabled?" >&2
	exit 1
fi

# Where the drive is mounted right now, or empty if it is not mounted.
mountpoint_of() {
	case "$(uname -s)" in
		Darwin) [[ -d "/Volumes/$label" ]] && echo "/Volumes/$label" ;;
		*) findmnt -rn -S "LABEL=$label" -o TARGET 2>/dev/null | head -1 ;;
	esac
}

mount_drive() {
	case "$(uname -s)" in
		Darwin)
			# The host does not mount the drive by itself when the medium comes
			# back, so ask. By name first; if the volume is not resolvable by
			# name while unmounted, find its device identifier.
			diskutil mount "$label" >/dev/null 2>&1 && return 0
			local dev
			dev=$(diskutil list | awk -v L="$label" '$0 ~ ("[[:space:]]" L "[[:space:]]") {print $NF}' | head -1)
			[[ -n $dev ]] && diskutil mount "$dev" >/dev/null 2>&1
			;;
		*)
			mount -L "$label" >/dev/null 2>&1 ||
				udisksctl mount -b "/dev/disk/by-label/$label" >/dev/null 2>&1
			;;
	esac
}

unmount_drive() {
	local mnt=$1
	case "$(uname -s)" in
		Darwin) diskutil unmount "$mnt" >/dev/null ;;
		*)
			umount "$mnt" 2>/dev/null ||
				udisksctl unmount -b "/dev/disk/by-label/$label" >/dev/null 2>&1
			;;
	esac
}

# Wait for the drive to be mounted again, mounting it ourselves if the OS does
# not. The MetaModule only restores the medium once the install has finished,
# so this doubles as waiting for the install.
wait_for_drive() {
	local deadline=$((SECONDS + TIMEOUT_SEC))

	while ((SECONDS < deadline)); do
		local mnt
		mnt=$(mountpoint_of)
		if [[ -n $mnt ]]; then
			echo "$mnt"
			return 0
		fi
		mount_drive
		sleep 1
	done

	return 1
}

mnt=$(mountpoint_of)
if [[ -z $mnt ]]; then
	echo "Developer drive '$label' is not mounted, trying to mount it..."
	mnt=$(wait_for_drive) || {
		echo "Could not find the developer drive '$label'" >&2
		echo "Is Developer Mode enabled, and the USB cable re-plugged since?" >&2
		exit 1
	}
fi

echo "Copying $(basename "$plugin") to $mnt"
cp "$plugin" "$mnt/" || exit 1
sync

# The host caches the filesystem, so it has to let go before the MetaModule
# reads the drive -- otherwise it can write its stale copy back over the
# install. Unmounting (not ejecting) leaves the device attached, so the drive
# can come back without re-plugging the cable.
unmount_drive "$mnt"

echo "Installing..."
echo "INSTALL" >"$console" || {
	echo "Could not write to the console device '$console'" >&2
	exit 1
}

if mnt=$(wait_for_drive); then
	echo "Done. Developer drive is back at $mnt"
else
	echo "Timed out waiting for the developer drive to come back." >&2
	echo "Check the MetaModule's console output for what happened." >&2
	exit 1
fi
