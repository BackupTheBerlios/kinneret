#!/bin/bash

# load fonts
if [ -e "/home/knoppix/.fontsdirs" ]
then
	cd /home/knoppix/
	mkdir -p /home/knoppix/.fonts/
	rm -fr /home/knoppix/.fonts/*.ttf
	for dir in `cat /home/knoppix/.fontsdirs`
	do
		if [ -e "${dir}" ]
		then
			cd "${dir}"
			for font in `ls | grep .ttf`
			do
				ln -s "${dir}/${font}" "/home/knoppix/.fonts/${font}"
			done
		else
			# mount
			mnt=`echo $dir | cut -b 6-9`
			sudo mount /dev/$mnt /mnt/$mnt -o defaults,rw,user,uid=1000 2>&1
			if [ -e "${dir}" ]
			then
				cd "${dir}"
				for font in `ls | grep .ttf`
				do
					ln -s "${dir}/${font}" "/home/knoppix/.fonts/${font}"
				done
			else
				echo "${RED}Invalid fonts directory, skipping.${NORMAL}"
			fi
		fi
	done

	cd /home/knoppix/.fonts/
	ttmkfdir -o fonts.scale > /dev/null

	# Make the drectory a fonts directory
	mkfontdir > /dev/null

	# Update the X server's fonts search path
	xset fp+ /home/knoppix/.fonts > /dev/null

	# Reload the font server
	/etc/init.d/xfs start > /dev/null		# start xfs, if it wasn't
	/etc/init.d/xfs reload > /dev/null		# reload xfs
fi

exit 0
