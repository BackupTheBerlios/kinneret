#!/bin/bash
#
# A part of the GNU/Linux Kinneret project (http://kinneret.miloberi.com)
# Written by Itay Duvdevani, 01-March-2003
#
# Script Brief:
# This script scans all the mounted devices
# and looks for /<windows && winnt>/fonts (not everybody installs windows
# to C:\Windows || C:\Winnt, I know, but running `find ...` will be too slow).
# If the Windwos directory was found, the script will create a sym-link
# of the file in /home/knoppix/.fonts
#
# After the sym-links have been created and the scan was completed,
# the script makes /home/knoppix/.fonts a fonts directory, adds it
# to the fonts path of the X Server and re-loads the fonts server, thus making
# the new fonts available to the user.
#
# Script requirments:
# - /home/knoppix/ exists an writeable

rm -f /tmp/.fontsdirs

# list all the mounted devices
for CURDEV in `ls /mnt/hd?? -d`
do
	echo -n Scanning $CURDEV...

	# directory exists?
	# yes, add font path,
	# no, skip it.
	DIR95="${CURDEV}/windows/fonts"
	DIRNT="${CURDEV}/winnt/fonts"

	if [ -e "${DIR95}" ]
	then
		DIR="${DIR95}"
	elif [ -e "${DIRNT}" ]
	then
		DIR="${DIRNT}"
	else
		DIR=""
	fi

	if [ "${DIR}" != "" ]
	then
		echo "${DIR}" >> /tmp/.fontsdirs
	fi
done

exit 0
