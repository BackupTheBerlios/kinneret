#!/bin/bash
#
# Swimming Guide Compilation Script, Written by Yuval "Q" Brik, Sep 2003.
# Copyright (C) 2003  Yuval Brik
#
# CVS Connection Script is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# CVS Connection Script is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with CVS Connection Script; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

# For information about the hwo to use this script,
# Please read the README file.

VERSION="0.1" #The version of this script.

#`date +%D\ %T%n\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\->> log.mkdoc`
if [ "`id -u`" = "0" ]; then
	echo "Error: Do not run this script as root"
	#`echo "Error: Do not run this script as root\n" >> log.mkdoc`
	exit 0
fi

if [ ! -n "$1" ]; then
	echo "Usage: mkdoc.sh [options ...]"
	echo "Swimming Guide Compilation Script"
	echo "by Yuval 'Q' Brik (C) Licensed under GPL"
	echo
	echo "  -d                  Compile all languages (do not use with specific tags)"
	echo "  -h                  Compile Hebrew doc"
	echo "  -a                  Compile Arabic doc"
	echo "  -e                  Compile English doc"
	echo "  -r                  Compile Russian doc"
	echo
	echo "  -c                  Copy files to /opt/kinneret"
	echo "  -n                  Clean old files before copy"
	echo
	echo "  -f                  Force: Do not abort if there was a problem"
	# echo "  -i                 Interactive (all other arguments will be ignored)"
	exit 65
fi
FORCE="Error parsing %s into %s for language %s. Abort.\n"
QUIT="exit"
while getopts ":iheradcnf" Option
do
	case $Option in
	i ) INTERACTIVE=1;;
	a ) if [ -d ../src/ar ]; then
		LANG[3]=ar
	     fi;;
	d )	if [ -d ../src/he ]; then
		LANG[0]=he
		fi
		if [ -d ../src/en ]; then
		LANG[1]=en
		fi
		if [ -d ../src/ru ]; then
		LANG[2]=ru
		fi
		if [ -d ../src/ar ]; then
		LANG[3]=ar
		fi;;
	h ) if [ -d ../src/he ]; then
		LANG[0]=he
	     fi;;
	e ) if [ -d ../src/en ]; then
		LANG[1]=en
	     fi;;
	r ) if [ -d ../src/ru ]; then
		LANG[2]=ru
	     fi;;
	f ) FORCE="Error parsing %s into %s for language %s. Continue.\n"
		QUIT="";;
	n ) CLEAN=1;;
	c ) CP=1;;
	esac
done
shift $(($OPTIND - 1))

if [ "$CLEAN" == "1" ] && [ "$CP" == "0" ]; then
	echo "-n will work only if -c is on"
	exit
fi

#if [ INTERACTIVE=1 ]; then
#	LANG[0]=""; LANG[1]=""; LANG[2]=""; LANG[3]=""
#	CLEAN=""; CP=""
#	FORCE="Error parsing %s into %s for language %s. Abort.\n"
#	QUIT="exit"
#fi

for index in 0 1 2 3  # hebrew=0 english=1 russian=2 arabic=3
do
if [ "${LANG[$index]}" = "he" ] || [ "${LANG[$index]}" = "en" ] || [ "${LANG[$index]}" = "ru" ] || [ "${LANG[$index]}" = "ar" ]; then 
	LSXMLS=`ls ../src/${LANG[$index]}/*.xml`
	for XMLIF in $LSXMLS
	do
		BASIC=`basename $XMLIF | awk -F".xml" '{print $1}'`
		HTMLOF="../doc/${LANG[$index]}/$BASIC.html"
		XSL="../etc/l2swim.xsl"
		OPTHTML="/opt/kinneret/l2swim/doc/${LANG[$index]}/$BASIC.html"
		if [ `find ${XMLIF} -newer ${OPTHTML}` ]; then
			if [ `xsltproc -o $HTMLOF $XSL $XMLIF 2> /dev/null` ]; then
				echo "$XMLIF parsed into $HTMLOF for language ${LANG[$index]}. Success."
				#`echo "$XMLIF parsed into $HTMLOF for language ${LANG[$index]}. Success." >> log.mkdoc`
			else
				printf "$FORCE" `basename $XMLIF` ` basename $HTMLOF` ${LANG[$index]}
				#`xsltproc -o $HTMLOF $XSL $XMLIF 2>> log.mkdoc`
				${QUIT}
			fi
		fi
	done
	if [ "$CP" == "1" ]; then
		echo "In order to copy the files to Kinneret's directory we need to change to root."
		TARGET="`dirname $HTMLOF`/*.html"
		COPY="cp -f $TARGET /opt/kinneret/l2swim/doc/${LANG[$index]}"
		if [ "$CLEAN" == "1" ]; then
			COPY="rm -Rf /opt/kinneret/l2swim/doc/* ; cp -f $TARGET /opt/kinneret/l2swim/doc/${LANG[$index]}"
		fi
		ch_to_root()
		{
			COPY=`su root -c "$COPY"`
			 if [ "${COPY}" = "Sorry." ]; then
				echo "Bad password or target does not exist."
				ch_to_root
			else
				echo "Files copied to $TARGET for language ${LANG[$index]}. Success"
				#echo "Files copied to $TARGET for language ${LANG[$index]}. Success" >> log.mkdoc
			fi
			wait
		}
		ch_to_root
	fi
fi
done



