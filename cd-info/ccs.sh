#!/bin/sh
#
# CVS Connection Script, Written by Yuval "Q" Brik, May 6th 2003.
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

NORMAL="[0;39m"
RED="[1;31m"
GREEN="[1;32m"
DARKGRAY="[1;30m"
BLUE="[1;34m"
PURPLE="[1;35m"
DARKPURPLE="[35m"
DARKRED="[31m"
BLACK="[30m"
DARKBLUE="[34m"
DARKGREEN="[32m"
WHITE="[1;37m"
LIGHTGRAY="[37m"

export CVS_RSH=ssh

exp_vars()
{
CVSROOT="$PREFIX:$USER@cvs.kinneret.berlios.de:/cvsroot/kinneret"
export CVSROOT
}

set_work_dir()
{
echo "Enter your working directory (if you don't know what it is, read the README):"
read WRK_DIR
if [ ! -d $WRK_DIR ]; then
echo "${RED}The working dir you entered does not exist.${NORMAL}"
set_work_dir
elif [ ! -w $WRK_DIR ]; then
echo "${RED}You don't have writing premision on the dir you've chosen.${NORMAL}"
set_work_dir
fi
}

main_menu()
{
MAINOPT="Checkout Update Commit Version Exit"
select opt in $MAINOPT; do
	if [ "$opt" = "Checkout" ]; then
	echo "Check out which module?"
	read co_mdl
	echo "Checking out ${PURPLE}$co_mdl ${NORMAL}into working directory."
	cd $WRK_DIR
	cvs -z3 co $co_mdl
	main_menu
	exit
	
	
	elif [ "$opt" = "Update" ]; then
	echo "Updating the whole working directory."
	cd $WRK_DIR
	cvs -z3 update
	main_menu
	exit
	
	
	elif [ "$opt" = "Commit" ]; then
	
	commit_ques()
	{
		echo "Which directory/file from working directory to commit?"
		read $ci_file
		if [ ! -e $WRK_DIR/$ci_file ]; then
		echo "${RED}This directory or file doesn't exist.${NORMAL}"
		commit_ques
		fi
	}
	echo "Commiting ${BLUE}$ci_file${NORMAL}"
	echo "Enter a message that will describe the changes:"
	read $des_msg
	cvs -z3 commit -m "$des_msg" $ci_file
	main_menu
	exit
	
	elif [ "$opt" = "Version" ]; then
	echo "CVS Connection Script, Written by Yuval "Q" Brik, May 6th 2003."
	echo "Copyright (C) 2003  Yuval Brik"
	echo
	echo "CVS Connection Script V. $VERSION"
	echo
	main_menu
	exit
	
	elif [ "$opt" = "Exit" ]; then
	
	exit
	
	else
	echo "${RED}ERROR! Please enter a valid option.${NORMAL}"
	exit
	fi
done
}
echo "CVS Connection Script, Copyright (C) 2003  Yuval Brik"
echo "Welcome to ${BLUE}Kinneret ${PURPLE}CVS Connection Script${NORMAL}"
echo
echo "For information about the how to use this script,"
echo "Please read the README file."
echo "This script is distributed under the GNU GPL license."
echo "It can be found at: http://www.gnu.org/licenses/gpl.html "
echo
echo
echo
echo "Choose, ${GREEN}developer${NORMAL} or ${LIGHTGREY}Anonymous${NORMAL} access."
ANDEV="Anonymous Developer Exit"
select access in $ANDEV; do
	if [ "$access" = "Anonymous" ]; then
	USER="anonymous"
	PREFIX=":pserver"
	exp_vars
	echo "For ${LIGHTGREY}anonymous${NORMAL} password, simply press enter. The login may take few seconds."
	cvs login
	set_work_dir
	main_menu
	
	
	elif [ "$access" = "Developer" ]; then
	echo "Please enter your username:"
	read USER
	echo "Your username is ${GREEN}$USER${NORMAL}"
	PREFIX=":ext"
	exp_vars
	set_work_dir
	main_menu
	else
	exit
	fi
done
