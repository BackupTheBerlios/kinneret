#!/bin/bash
#
# kiwiz-radio version 0.0.1 July 2004
# (C) 2004 http://www.linux-kinneret.org
# by Dovix, dovix ~ linux-kinneret ~ org
# released under the terms of the GNU General Public License, version 2
# http://www.fsf.org/copyleft/gpl.txt
#
# dependencies: kdialog, xterm, mplayer
#
# THIS IS DEVELOPMENT VERSION; USE AT YOUR OWN RISK
#
# TODO:
#
# 1. basic flow - IN PROGRESS
# 2. check if radio is already on, and stop before playing new one
# 3a. add error handling for all commands, especially Internet
# 3b. add check that necessary commands exist (e.g. kdialog)
# 4. translation
# 5. add more stations

MyScript="kiwiz-radio"

echo "$MyScript (info): script started"

##########################################################
# Some basic checks
##########################################################

# Check if kdialog is installed
MyTest="`which kdialog`"
if [ -n "$MyTest" ]; then
  echo "$MyScript (info): kdialog found"                                  
else
  echo "$MyScript (error): kdialog not found"
  exit -1
fi
                                         
# Check if mplayer is installed
# TBD

# check if xterm is installed
# TBD

# check if connected to the internet
# TBD

##########################################################
# Station definitions
##########################################################

#MyPlayer='xterm -iconic -title $MyLabel -e mplayer -cache 4'

# Stations
# Note: do not use spaces inside station names!
MyStation[1]=$"Radius-100FM-Israel"
MyStation[2]=$"GGlz-Israel"
MyStation[3]=$"Glz-Israel"
MyStation[4]=$"Tlv-102FM-Israel"
MyStation[5]=$"103FM-Israel"
MyStation[6]=$"ClassicFM-UK"
MyStation[7]=$"ClassicGold-UK"
MyStation[8]=$"WXPK-Rock-NY"
MyStation[9]=$"WCWP-Variety-NY"

# Servers
MyServer[1]="http://213.8.143.164/audiomedia"
MyServer[2]="http://213.8.138.13/gglz"
MyServer[3]="http://213.8.138.13/glz-stream"
MyServer[4]="http://212.179.112.29/102fm"
MyServer[5]="http://live.103.fm/103fm-low/"
MyServer[6]="mms://audio1.musicradio.com/classicfm"
MyServer[7]="mms://audio2.musicradio.com/classicgold"
MyServer[8]="http://pamal.wm.llnwd.net/pamal_wxpk"
MyServer[9]="http://cwp-media.liu.edu/wcwpfm"

##########################################################
# Main menu
##########################################################

# Prepare the main menu string, that will be passed as a parameter to kdialog
let MyIndex=0
MyMenu=""
for MyLoop in ${MyStation[*]}
do
  let "MyIndex = $MyIndex + 1"
  MyMenu="$MyMenu "$MyIndex" "$MyLoop
done  
echo "$MyScript (info): main menu string is $MyMenu" 

# Display the main menu
MyOption=`kdialog --title $"Radio" --menu $"Please select a station:" $MyMenu`

# Check if user wants to continue
if [ $? -ne 0 ] ; then
  echo "$MyScript (info): selected option is Cancel; quitting"
  exit 1
fi

echo "$MyScript (info): selected option is $MyOption"
     
# Now launching mplayer to play audio stream
MyPlayer='xterm -iconic -title '${MyStation[$MyOption]}' -e mplayer -cache 4 '${MyServer[$MyOption]}
echo "$MyScript (info): play command is $MyPlayer"
$MyPlayer

echo "$MyScript (info): script ended"
exit 0
