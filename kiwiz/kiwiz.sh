#!/bin/bash
#
# kiwiz version 0.32.0
# (C) 2004 by Dovix, dovix@linux-kinneret.org
# released under the terms of the GNU General Public License, version 2
# http://www.fsf.org/copyleft/gpl.txt
#
# dependencies: kdialog, internet (part of iwiz)

##########################################################
# Prepare welcome message, according to time of day
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

# Display welcome message
kdialog --title $"Kinneret's Internet WIZard" --yesno $"$welcome.\nWelcome to Kiwiz - Kinneret's Internet WIZard.\nThis wizard will help you connect to the Internet.\nDo you want to continue?"

# Check if user wants to continue
if [ $? -ne 0 ] ; then
	exit 1
fi

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
# Check if previous account exists, and if not then define one
##########################################################
# Check how many connections are defined
lines=$(internet --listcons | wc -l) && lines=$(echo $lines -1 | bc)

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
		lines=$(internet --listcons | wc -l) && lines=$(echo $lines -1 | bc)
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
