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

clear
xsltproc -o ../doc/he/tour1office_kcalc.html ../etc/l2swim.xsl ../src/he/tour1office_kcalc.xml
xsltproc -o ../doc/he/tour1office_kpresenter.html ../etc/l2swim.xsl ../src/he/tour1office_kpresenter.xml
xsltproc -o ../doc/he/tour1office_kspread.html ../etc/l2swim.xsl ../src/he/tour1office_kspread.xml
xsltproc -o ../doc/he/tour1office_kword.html ../etc/l2swim.xsl ../src/he/tour1office_kword.xml
xsltproc -o ../doc/he/tour2edu_kbabel.html ../etc/l2swim.xsl ../src/he/tour2edu_kbabel.xml
xsltproc -o ../doc/he/tour2edu_kformula.html ../etc/l2swim.xsl ../src/he/tour2edu_kformula.xml
xsltproc -o ../doc/he/tour2edu_kgeo.html ../etc/l2swim.xsl ../src/he/tour2edu_kgeo.xml
xsltproc -o ../doc/he/tour3net_kmail.html ../etc/l2swim.xsl ../src/he/tour3net_kmail.xml
xsltproc -o ../doc/he/tour3net_konqueror.html ../etc/l2swim.xsl ../src/he/tour3net_konqueror.xml
xsltproc -o ../doc/he/tour4media_tuxpaint.html ../etc/l2swim.xsl ../src/he/tour4media_tuxpaint.xml
xsltproc -o ../doc/he/tour4media_xine.html ../etc/l2swim.xsl ../src/he/tour4media_xine.xml
xsltproc -o ../doc/he/tour4media_xmms.html ../etc/l2swim.xsl ../src/he/tour4media_xmms.xml
xsltproc -o ../doc/he/tour5games_frozenbubble.html ../etc/l2swim.xsl ../src/he/tour5games_frozenbubble.xml
xsltproc -o ../doc/he/tour5games_lbreakout2.html ../etc/l2swim.xsl ../src/he/tour5games_lbreakout2.xml
xsltproc -o ../doc/he/tour5games_powermanga.html ../etc/l2swim.xsl ../src/he/tour5games_powermanga.xml
xsltproc -o ../doc/he/tour6admin_kcontrol.html ../etc/l2swim.xsl ../src/he/tour6admin_kcontrol.xml
xsltproc -o ../doc/he/tour6admin_kdiskfree.html ../etc/l2swim.xsl ../src/he/tour6admin_kdiskfree.xml
xsltproc -o ../doc/he/tour6admin_kfloppy.html ../etc/l2swim.xsl ../src/he/tour6admin_kfloppy.xml
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

echo "if all files were compiles successfuly, then:"
echo "- enter toot mode : su"
echo "- copy the files: cp ../doc/he/*.html /opt/kinneret/l2swim/doc/he/ -f"
