#!/bin/bash
#
# kiwiz version 0.3.1-92
# (C) 2004 by Dovix, dovix@linux-kinneret.org
# released under the terms of the GNU General Public License, version 2
# http://www.fsf.org/copyleft/gpl.txt
#
# dependencies: kdialog, internet (part of iwiz)
#
# THIS IS DEVELOPMENT VERSION; USE AT YOUR OWN RISK
#
# TODO:
#
# 1. basic flow - IN PROGRESS
# 2a. create log file
# 2b. send all output and error messages to log file
# 2c. create step messages to log file
# 3. create modular functions
# 4a. add error handling for all commands, especially Internet
# 4b. add check that necessary commands exist (e.g. kdialog)
# 5. translation
# 6. add option to skip certain messages (future)
# 7. add display of command line options
# 8a. Display debugging information to log file in case of fatal errors
# 8b. Add option to save log in a user-specified location
# 9. other, as noted inside the script

##########################################################
# Check if have root privilages
##########################################################
# TEMP commented just for testing
#if [ `id -u` != "0" ]; then
#	kdialog --title $"Kiwiz fatal error" --error $"Sorry, you do not have the necessary privilages to run this wizard. The wizard will exit when you press 'OK'. Please contact the system administrator to grant you acess.\nAdvanced users notice:\nIf you run this from a shell or a menu, try to precede the command with 'kdesu' or with 'sudo' (if you defined /etc/sudoers to the user to execute the wizard)."
#	exit 1
#fi
# TODO: check if this works when user is in /etc/sudoers

##########################################################
# Prepare welcome message parameters, according to time of day
##########################################################
# Retrive current hour
hour=`date | cut -c12-13`

# Morning
if [ $hour -ge 4 -a $hour -le 11 ] ; then
	welcome=$"Good morning $LOGNAME"
fi

# Afternoon
if [ $hour -ge 12 -a $hour -le 16 ] ; then
	welcome=$"Good afternoon $LOGNAME"
fi

# Evening
if [ $hour -ge 17 -a $hour -le 20 ]
then
	welcome=$"Good evening $LOGNAME"
fi

#Night
if [ $hour -ge 21 -a $hour -le 3 ] ; then
	welcome=$"Good night $LOGNAME"
fi

##########################################################
# Determine operation mode
##########################################################
#
# There are 4 operation modes:
#
# Mode#		Connected-to-Internet		iwiz-connection-found	Behavior
# 	0				no						no			Offer to connect to the Internet using iwiz
#	1				no						yes			Must have been disconnected, offer to re-connect
#	2				yes						no			Connected but not with iwiz, exit
#	3				yes						yes			Offer to disconnect from the Internet	

mode=0

# Check if connected to the Internet (try 2 different destinations)
ping -c 1 iwiz.linux-kinneret.org > /dev/null 2> /dev/null
if [ "$?" -eq 0 ]; then
	mode=$($mode + 2)
else
	ping -c 1 kinneret.berlios.de > /dev/null 2> /dev/null
	if [ "$?" -eq 0 ]; then
		mode=$($mode + 2)
	fi
fi

# check if iwiz connection found
internet --currentshow > /dev/null 2> /dev/null
if [ "$?" -eq 1 ]; then
	mode=$($mode + 0)
fi

# now check the value of mode:
case $mode in
  	0)	# proceed to connect
		;;
	1)	kdialog --title $"Kiwiz warning" --yesno $"You are no longer connected to the Internet.\n\nDo you want to re-connect?."
		if [ $? -ne 0 ] ; then
			internet --clearcurr
			exit 1
		fi
		internet --connect
		ping -c 1 iwiz.linux-kinneret.org > /dev/null 2> /dev/null
		if [ "$?" -eq 0 ]; then
			kdialog --title $"Kiwiz goodbye" --msgbox $"You are now connected to the Internet.\n\nThank you for using the Internet Wizard"
			exit 1
		else
			ping -c 1 kinneret.berlios.de > /dev/null 2> /dev/null
			if [ "$?" -eq 0 ]; then
				kdialog --title $"Kiwiz goodbye" --msgbox $"You are now connected to the Internet.\n\nThank you for using the Internet Wizard"
			fi
		fi
		kdialog --title $"Kiwiz fatal error" --error $"Sorry, can not establish connection to the Internet.\n\nThere might be a problem with your network or connection parameters."
		exit 1
		;;
	2)	kdialog --title $"Kiwiz warning" --sorry $"You are connected to the Internet.\n\nIt looks that you are not using the Internet Wizard. This may happen when you have an always-on connection and do not need to dial a connection\n\nThe Internet Wizard will exit now."
		exit 1
		;;
	3)	kdialog --title $"Kiwiz warning" --yesno $"You are connected to the Internet.\n\nDo you want to disconnect?."
		if [ $? -ne 0 ] ; then
			exit 1
		fi
		internet --kill
		kdialog --title $"Kiwiz goodbye" --msgbox $"You are now disconnected to the Internet.\n\nThank you for using the Internet Wizard"
		exit 1
		;;
	*)	# TODO: report script error
		exit
esac

##########################################################
# Display welcome message
##########################################################
kdialog --title $"Kinneret's Internet WIZard" --yesno $"$welcome.\nWelcome to Kiwiz - Kinneret's Internet WIZard.\nThis wizard will help you connect to the Internet.\nDo you want to continue?"

# Check if user wants to continue
if [ $? -ne 0 ] ; then
	exit 1
fi

##########################################################
# Check if previous account exists, and if not then define one
##########################################################
# Check how many connections are defined
lines=$(internet --listcons 2> /dev/null| wc -l) && lines=$(echo $lines -1 | bc) 

# In case there are no connections...
if [ $lines -eq 0 ] ; then
# Ask the user if to create new connection
	kdialog --warningcontinuecancel $"Since no previous account was found,  you will be asked a few questions, to setup your dialup account.\nIf you do not want to set up your account at this time, please select 'cancel'"
	if [ $? -ne 0 ] ; then
		exit 1
	else
# Launch wizard to create new connection
		konsole --nomenubar --notoolbar -T "Kinneret's Internet Wizard" -e /bin/bash -c "internet -w"
# Check how many connections we have after the wizard
		lines=$(internet --listcons 2> /dev/null| wc -l) && lines=$(echo $lines -1 | bc)
		echo $lines
# Still no connections: this must be an error
		if [ $lines -eq 0 ] ; then
			kdialog --title $"Kiwiz fatal error" --error $"Sorry, but I still can't find any connections. There may be a problem in the program or you closed the connection definition window abrutly.\nPlease consult the system administrator."
			exit 1
		fi
	fi
fi

##########################################################
# Select connection to dial
##########################################################

lines=$(internet --listcons | wc -l) && lines=$(echo $lines -1 | bc)
cons=`(internet --listcons | tail -n $lines)`
opts=`for name in $cons; do
    echo -n "\"$name\" \"$name\" "
done`
echo $opts
kdialog --title $"Kinneret's Internet WIZard" --menu $"Select a connection to dial:" $opts