#!/bin/bash
#
# kiwiz-radio version 0.0.1
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
# 2a. add error handling for all commands, especially Internet
# 2b. add check that necessary commands exist (e.g. kdialog)
# 3. translation

##########################################################
# Main menu
##########################################################

MyStation=`kdialog --title $"Radio" --menu $"Please select a station:" 1 $"Radius 100FM" 2 $"Glz" 3 $"GGlz"`

# Check if user wants to continue
if [ $? -ne 0 ] ; then
	exit 1
fi

case "$MyStation" in
  1)
  xterm -iconic -title Radius100 -e mplayer http://213.8.143.164/audiomedia &;;
  2)
  xterm -iconic -title Glz -e mplayer http://213.8.138.13/glz-stream &;;
  3)
  xterm -iconic -title GGlz -e mplayer http://213.8.138.13/gglz &;;
  *)
  echo "bad choice";; 
esac
