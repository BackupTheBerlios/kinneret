#!/bin/bash

# Get root
[ "`id -u`" != "0" ] && exec sudo "$0" "$@"

HOME_DIR=$1
SWAP_SIZE=$2
MNT_PT=$3

HOME_SIZE=100

echo "DIR_CREATE" > /tmp/.progress
cd $MNT_PT
mkdir kinneret

# create swap
if [ $SWAP_SIZE -gt 0 ]
then
	echo "SWAP_FILE" > /tmp/.progress
	dd if=/dev/zero of="${MNT_PT}/kinneret/.swap" bs=1M count=$SWAP_SIZE;

	echo "CREATE_SWAP" > /tmp/.progress
	mkswap "${MNT_PT}/kinneret/.swap"

	echo "SWAP_ON" > /tmp/.progress
	swapon "${MNT_PT}/kinneret/.swap"
fi

# create the ext3 file
echo "HOME_FILE" > /tmp/.progress
dd if=/dev/zero of="${MNT_PT}/kinneret/.config" bs=1M count=$HOME_SIZE

echo "DEVICE_SEARCH" > /tmp/.progress
devnum=-1
while [[ $? -ne 0 && $devnum -lt 8 || $devnum -eq -1 ]]
do
	let devnum++
	losetup /dev/loop$devnum "${MNT_PT}/kinneret/.config"
done

if [ $? -ne 0 ]
then
	exit 1
fi

echo "CREATE_HOME" > /tmp/.progress
mkfs -t ext3 /dev/loop$devnum

echo "TUNE_HOME" > /tmp/.progress
# tune2fs -L KINNERET /dev/loop$devnum		# causes a hang... why?

echo "OWN_CHANGE" > /tmp/.progress
cd /mnt
mkdir tmpcfg
chown knoppix:knoppix /mnt/tmpcfg

echo "COPY_HOME" > /tmp/.progress
# mount ext3 to /mnt/tmpcfg
mount /dev/loop$devnum /mnt/tmpcfg

# copy all file from home to /mnt/tmpcfg
cd /home/knoppix
cp -a -f --preserve=all . /mnt/tmpcfg 2>&1

echo "RELEASE_HOME" > /tmp/.progress
# umount tmpcfg
umount /dev/loop$devnum
rmdir /mnt/tmpcfg
losetup -d /dev/loop$devnum

echo "ACTIVATE_HOME" > /tmp/.progress
# mount ext3 to /home/knoppix
mount "${MNT_PT}/kinneret/.config" /home/knoppix -t ext3 -o defaults,rw,loop 2>&1 > /dev/null

echo "FINISH" > /tmp/.progress
# change premissions
chown -R knoppix:knoppix /home/knoppix

# sym-link
ln -s "${HOME_DIR}" /home/knoppix/docs

exit 0
