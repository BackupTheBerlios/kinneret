#!/bin/bash

# Get root
[ "`id -u`" != "0" ] && exec sudo "$0" "$@"

HOME_DIR=$1
SWAP_SIZE=$2
MNT_PT=$3

HOME_SIZE=100

cd $MNT_PT
mkdir kinneret

# create swap
if [ $SWAP_SIZE -gt 0 ]
then
	dd if=/dev/zero of="$MNT_PT/kinneret/.swap" bs=1M count=$SWAP_SIZE;
	mkswap "$MNT_PT/kinneret/.swap"
	swapon "$MNT_PT/kinneret/.swap"
fi

# create the ext3 file (20megs)
dd if=/dev/zero of="$MNT_PT/kinneret/.config" bs=1M count=$HOME_SIZE
devnum=-1
while [[ $? -ne 0 && $devnum -lt 8 || $devnum -eq -1 ]]
do
	let devnum++
	losetup /dev/loop$devnum "$MNT_PT/kinneret/.config"
done

if [ $? -ne 0 ]
then
	exit 1
fi

mkfs -t ext3 /dev/loop$devnum
# tune2fs -L KINNERET /dev/loop$devnum		# causes a hang... why?

cd /mnt
mkdir tmpcfg
chown knoppix:knoppix /mnt/tmpcfg

# mount ext3 to /mnt/tmpcfg
mount /dev/loop$devnum /mnt/tmpcfg

# copy all file from home to /mnt/tmpcfg
cd /home/knoppix
cp -a -f --preserve=all . /mnt/tmpcfg 2>&1

# umount tmpcfg
umount /dev/loop$devnum
rmdir /mnt/tmpcfg
losetup -d /dev/loop$devnum

# mount ext3 to /home/knoppix
mount "$MNT_PT/kinneret/.config" /home/knoppix -t ext3 -o defaults,rw,loop 2>&1 > /dev/null

# change premissions
chown -R knoppix:knoppix /home/knoppix

# sym-link
ln -s "${HOME_DIR}" /home/knoppix/docs

exit 0
