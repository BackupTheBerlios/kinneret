#!/bin/bash
# Kinneret's home boot script v0.1b (C) Itay 'z9u2K' Duvdevani <z9u2k@bezeqint.net>
# Based on Persistent home boot script v0.4 (C) Matthias Schwarze <m_schwarze@t-online.de>
# that is based on knoppix-autoconfig (C) Klaus Knopper <knopper@knopper.net> 2001

# Get root
[ "`id -u`" != "0" ] && exec sudo "$0" "$@"

# ANSI COLORS
NORMAL="[0;39m"
# RED: Failure or error message
RED="[1;31m"
# GREEN: Success message
GREEN="[1;32m"
# BLUE: System messages
BLUE="[1;34m"
# MAGENTA: Found devices or drivers
MAGENTA="[1;35m"
#
maphome()
{
	d=$1
	echo "${BLUE}Checking integrity of Kinneret's Home files...${NORMAL}"
	e2fsck -y $d/kinneret/.config 2>&1 > /dev/null

	# Find a swap file
	if [ -e $d/kinneret/.swap ]
	then
		echo "${BLUE}Found swap file, activating.${NORMAL}"
		swapon $d/kinneret/.swap
	fi

	mount "${d}/kinneret/.config" /home/knoppix -t ext3 -o rw,loop 2>&1 > /dev/null
	chown -R knoppix:knoppix /home/knoppix
	HOMEFOUND="yes"
}

checkdir()
{
	d=$1
	if [ -e /mnt/$d/kinneret/.config ]
	then
		echo "${BLUE}Kinneret's Home found on directory: ${MAGENTA}${d}${BLUE}."
		maphome /mnt/$d
	fi
}

HOMEFOUND=""
echo "${BLUE}Searching for Kinneret's Home...${NORMAL}"

# mount all NTFS directories RO
for dir in `cat /etc/fstab | grep ntfs | cut -b 6-9`
do
	mount -t ntfs -o defaults,ro,user,uid=1000,codepage=cp1255,iocharset=cp1255,utf8 /dev/$dir /mnt/$dir 2>&1
done

# mount all vfat directories RW
for dir in `cat /etc/fstab | grep vfat | cut -b 6-9`
do
	mount -t vfat -o defaults,rw,user,uid=1000,codepage=cp1255,iocharset=cp1255,utf8 /dev/$dir /mnt/$dir 2>&1
done

# Scan directories
for dir in `cat /etc/fstab | grep vfat | cut -b 6-9`
do
	if [ -z "${HOMEFOUND}" ]
	then
		checkdir $dir
	fi
done

if [ -z "${HOMEFOUND}" ]
then
	echo "${BLUE}Cannot find Kinneret's Home partition, will run wizard at startup.${NORMAL}"
	echo "0" > /tmp/foundhome
	chown knoppix:knoppix /tmp/foundhome
fi

exit 0
