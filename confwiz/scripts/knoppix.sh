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
mounthome()
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

	mount "$d/kinneret/.config" /home/knoppix -t ext3 -o rw,loop 2>&1 > /dev/null
	chown -R knoppix:knoppix /home/knoppix
	HOMEFOUND="yes"
}

checkdir()
{
	d=$1
	mount -o defaults,rw,user,uid=1000 /dev/$d /mnt/$d 2>&1
	if [ -e /mnt/$d/kinneret/.config ]
	then
		echo "${BLUE}Kinneret's Home found on directory: ${MAGENTA}${d}${BLUE}."
		mounthome /mnt/$d
	fi
}

HOMEFOUND=""
echo "${BLUE}Searching for Kinneret's Home...${NORMAL}"

# Scan directories
for dir in `cat /etc/fstab | grep vfat | cut -b 6-9`
do
	if [ -z "$HOMEFOUND" ]
	then
		checkdir $dir
	fi
done

# load fonts
#if [ -e "/home/knoppix/.fontsdirs" ]
#then
#	mkdir -p /home/knoppix/.fonts
#	rm -fr /home/knoppix/.fonts/*.ttf
#	for dir in `cat /home/knoppix/.fontsdirs`
#	do
#		if [ -e "${dir}" ]
#		then
#			ln -s "${dir}/*.ttf" /home/knoppix/.fonts
#		else
#			sudo mount `echo $dir | cut -b 1-9` -o rw,user
#			if [ -e "${dir}" ]
#			then
#				ln -s "${dir}/*.ttf" /home/knoppix/.fonts
#			else
#				echo "${RED}Invalid fonts directory, skipping.${NORMAL}"
#			fi
#		fi
#	done

#	cd /home/knoppix/.fonts
#	ttmkfdir -o fonts.scale > /dev/null

	# Make the drectory a fonts directory
#	mkfontdir > /dev/null

	# Update the X server's fonts search path
#	xset fp+ /home/knoppix/.fonts > /dev/null

	# Reload the font server
#	/etc/init.d/xfs start > /dev/null		# start it if it wasn't
#	/etc/init.d/xfs reload > /dev/null	# reload it
#fi

if [ -z "$HOMEFOUND" ]
then
	echo "${BLUE}Cannot find Kinneret's Home partition, will run wizard at startup.${NORMAL}"
	echo "0" > /tmp/foundhome
	chown knoppix:knoppix /tmp/foundhome
fi

exit 0
