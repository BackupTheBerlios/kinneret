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
xsltproc -o ../doc/ar/tour_kinneret.html ../etc/l2swim.xsl ../src/ar/tour_kinneret.xml
xsltproc -o ../doc/ar/desktop_ready.html ../etc/l2swim.xsl ../src/ar/desktop_ready.xml
xsltproc -o ../doc/ar/faq_kinneret.html ../etc/l2swim.xsl ../src/ar/faq_kinneret.xml
xsltproc -o ../doc/ar/fonts_license.html ../etc/l2swim.xsl ../src/ar/fonts_license.xml
xsltproc -o ../doc/ar/free_essay.html ../etc/l2swim.xsl ../src/ar/free_essay.xml
xsltproc -o ../doc/ar/gfdl_license.html ../etc/l2swim.xsl ../src/ar/gfdl_license.xml
xsltproc -o ../doc/ar/rachel_kinneret.html ../etc/l2swim.xsl ../src/ar/rachel_kinneret.xml
xsltproc -o ../doc/ar/gpl_license.html ../etc/l2swim.xsl ../src/ar/gpl_license.xml
xsltproc -o ../doc/ar/howto_help.html ../etc/l2swim.xsl ../src/ar/howto_help.xml
xsltproc -o ../doc/ar/kinneret_license.html ../etc/l2swim.xsl ../src/ar/kinneret_license.xml
xsltproc -o ../doc/ar/non_gpl.html ../etc/l2swim.xsl ../src/ar/non_gpl.xml
xsltproc -o ../doc/ar/why_linux.html ../etc/l2swim.xsl ../src/ar/why_linux.xml
xsltproc -o ../doc/ar/user_interface.html ../etc/l2swim.xsl ../src/ar/user_interface.xml
xsltproc -o ../doc/ar/linux_history.html ../etc/l2swim.xsl ../src/ar/linux_history.xml
xsltproc -o ../doc/ar/kinneret_credits.html ../etc/l2swim.xsl ../src/ar/kinneret_credits.xml
xsltproc -o ../doc/ar/thoughts_1.html ../etc/l2swim.xsl ../src/ar/thoughts_1.xml
xsltproc -o ../doc/ar/thoughts_2.html ../etc/l2swim.xsl ../src/ar/thoughts_2.xml
xsltproc -o ../doc/ar/thoughts_3.html ../etc/l2swim.xsl ../src/ar/thoughts_3.xml
xsltproc -o ../doc/ar/thoughts_4.html ../etc/l2swim.xsl ../src/ar/thoughts_4.xml
xsltproc -o ../doc/ar/thoughts_5.html ../etc/l2swim.xsl ../src/ar/thoughts_5.xml
xsltproc -o ../doc/ar/first_time.html ../etc/l2swim.xsl ../src/ar/first_time.xml
#xsltproc -o ../doc/ar/apps_list.html ../etc/l2swim.xsl ../src/ar/apps_list.xml
xsltproc -o ../doc/ar/social_contract.html ../etc/l2swim.xsl ../src/ar/social_contract.xml
xsltproc -o ../doc/ar/about_kinneret.html ../etc/l2swim.xsl ../src/ar/about_kinneret.xml
xsltproc -o ../doc/ar/man_games.html ../etc/l2swim.xsl ../src/ar/man_games.xml
xsltproc -o ../doc/ar/release_notes.html ../etc/l2swim.xsl ../src/ar/release_notes.xml
xsltproc -o ../doc/ar/apps_list.html ../etc/l2swim.xsl ../src/ar/apps_list.xml

echo "if all files were compiles successfuly, then:"
echo "- enter root mode : su"
echo "- copy the files: cp ../doc/ar/*.html /opt/kinneret/l2swim/doc/ar/ -f"
