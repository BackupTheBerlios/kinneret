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

maphome()
{
	d=$1
	echo "${BLUE}Checking integrity of Kinneret's Home files...${NORMAL}"
	e2fsck -y $d/kinneret/.config 2>&1 > /dev/null

	# Find a swap file
	if [ -e $d/kinneret/.swap ]
	then
		echo "${MAGENTA}Found swap file, activating.${NORMAL}"
		swapon $d/kinneret/.swap
	fi

	mount "${d}/kinneret/.config" /home/knoppix -t ext3 -o rw,loop 2>&1 > /dev/null

	chown -R knoppix:knoppix /home/knoppix/

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

# fix for "partial installation", need to remount the cdrom device with rw permissions, 
# before mounting the windows partitions. Nir Misgav.
mount -o remount,rw /cdrom

# mount all NTFS directories
if [ `grep ntfs /etc/fstab`]
then
	NTFSOK=1
	captive-install-acquire --scan-disks-quick
	if [ $? -ne 0 ]
	then
		echo "${RED}Unable to load NTFS driver, access to NTFS partition will not be possible${NORMAL}"
		NTFSOK=0
	fi

	if [ $NTFSOK ]
	then
		for dir in `cat /etc/fstab | grep ntfs | cut -b 6-9`
		do
			mount -t captive-ntfs -o defaults,rw,user,uid=1000,codepage=1255,iocharset=cp1255 /dev/$dir /mnt/$dir 2>&1
		done
	fi
fi

# mount all vfat directories RW
for dir in `cat /etc/fstab | grep vfat | cut -b 6-9`
do
	mount -t vfat -o defaults,rw,user,uid=1000,codepage=1255,iocharset=cp1255 /dev/$dir /mnt/$dir 2>&1
done

# mount all ext2 directories RW
for dir in `cat /etc/fstab | grep ext2 | cut -b 6-9`
do
	mount -t ext2 -o defaults,rw,user /dev/$dir /mnt/$dir 2>&1
done

# mount all ext3 directories RW
for dir in `cat /etc/fstab | grep ext3 | cut -b 6-9`
do
	mount -t ext3 -o defaults,rw,user /dev/$dir /mnt/$dir 2>&1
done

# mount all ReiserFS directories RW
#for dir in `cat /etc/fstab | grep reiserfs | cut -b 6-9`
#do
#	mount -t reiserfs -o defaults,rw,user /dev/$dir /mnt/$dir 2>&1
#done

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
fi

#make sure the partitions directory is present
[ ! -e "/home/knoppix/partitions" ] && cp -ua /etc/skel/partitions /home/knoppix/

echo "${BLUE}Linking partitions...${NORMAL}"
rm -fr /home/knoppix/partitions/*

letter="103"	# C in octal
#for mntpt in `cat /etc/fstab | grep -F "`echo -e "vfat\nntfs"`" | cut -b 6-9`
for mntpt in `cat /etc/fstab | grep vfat | cut -b 6-9`
do
	echo -e "${BLUE}Linking /mnt/${mntpt} to \\${letter}...${NORMAL}"
	slash=\\
	to=`echo -e "${slash}${letter}"`
	ln -s /mnt/$mntpt/ "/home/knoppix/partitions/λεπο ${to}"

	let letter++
done

chown -R knoppix:knoppix /home/knoppix/partitions/

#partial installation fix
	chmod a+w /cdrom
	chmod a+w /dev/hda

exit 0
