#!/bin/sh

# Gnu/Linux Kinneret
# Script to build the guided tour
# (C) 2003 http///www.linux-kinneret.org
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License at
# http///www.gnu.org/copyleft/gpl.html for more details.

# clear
xsltproc -o ../doc/he/tour_office.html ../etc/l2swim.xsl ../src/he/tour_office.xml
xsltproc -o ../doc/he/tour_edu.html ../etc/l2swim.xsl ../src/he/tour_edu.xml
xsltproc -o ../doc/he/tour_net.html ../etc/l2swim.xsl ../src/he/tour_net.xml
xsltproc -o ../doc/he/tour_media.html ../etc/l2swim.xsl ../src/he/tour_media.xml
xsltproc -o ../doc/he/tour_games.html ../etc/l2swim.xsl ../src/he/tour_games.xml
xsltproc -o ../doc/he/tour_admin.html ../etc/l2swim.xsl ../src/he/tour_admin.xml
xsltproc -o ../doc/he/desktop_ready.html ../etc/l2swim.xsl ../src/he/desktop_ready.xml
xsltproc -o ../doc/he/faq_kinneret.html ../etc/l2swim.xsl ../src/he/faq_kinneret.xml
xsltproc -o ../doc/he/fonts_license.html ../etc/l2swim.xsl ../src/he/fonts_license.xml
xsltproc -o ../doc/he/free_essay.html ../etc/l2swim.xsl ../src/he/free_essay.xml
xsltproc -o ../doc/he/gfdl_license.html ../etc/l2swim.xsl ../src/he/gfdl_license.xml
xsltproc -o ../doc/he/rachel_kinneret.html ../etc/l2swim.xsl ../src/he/rachel_kinneret.xml
xsltproc -o ../doc/he/gpl_license.html ../etc/l2swim.xsl ../src/he/gpl_license.xml
xsltproc -o ../doc/he/howto_help.html ../etc/l2swim.xsl ../src/he/howto_help.xml
xsltproc -o ../doc/he/kinneret_license.html ../etc/l2swim.xsl ../src/he/kinneret_license.xml
xsltproc -o ../doc/he/non_gpl.html ../etc/l2swim.xsl ../src/he/non_gpl.xml
xsltproc -o ../doc/he/why_linux.html ../etc/l2swim.xsl ../src/he/why_linux.xml
xsltproc -o ../doc/he/user_interface.html ../etc/l2swim.xsl ../src/he/user_interface.xml
xsltproc -o ../doc/he/linux_history.html ../etc/l2swim.xsl ../src/he/linux_history.xml
xsltproc -o ../doc/he/kinneret_credits.html ../etc/l2swim.xsl ../src/he/kinneret_credits.xml
xsltproc -o ../doc/he/thoughts_1.html ../etc/l2swim.xsl ../src/he/thoughts_1.xml
xsltproc -o ../doc/he/thoughts_2.html ../etc/l2swim.xsl ../src/he/thoughts_2.xml
xsltproc -o ../doc/he/thoughts_3.html ../etc/l2swim.xsl ../src/he/thoughts_3.xml
xsltproc -o ../doc/he/thoughts_4.html ../etc/l2swim.xsl ../src/he/thoughts_4.xml
xsltproc -o ../doc/he/thoughts_5.html ../etc/l2swim.xsl ../src/he/thoughts_5.xml
xsltproc -o ../doc/he/first_time.html ../etc/l2swim.xsl ../src/he/first_time.xml
#xsltproc -o ../doc/he/apps_list.html ../etc/l2swim.xsl ../src/he/apps_list.xml
xsltproc -o ../doc/he/social_contract.html ../etc/l2swim.xsl ../src/he/social_contract.xml
xsltproc -o ../doc/he/about_kinneret.html ../etc/l2swim.xsl ../src/he/about_kinneret.xml
xsltproc -o ../doc/he/man_enigma.html ../etc/l2swim.xsl ../src/he/man_enigma.xml

echo "if all files were compiles successfuly, then:"
echo "- enter root mode : su"
echo "- copy the files: cp ../doc/he/*.html /opt/kinneret/l2swim/doc/he/ -f"
