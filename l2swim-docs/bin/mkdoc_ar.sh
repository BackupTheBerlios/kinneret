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
xsltproc -o ../doc/ar/howto_help.html ../etc/l2swim.xsl ../src/ar/howto_help.xml
xsltproc -o ../doc/ar/kinneret_license.html ../etc/l2swim.xsl ../src/ar/kinneret_license.xml
xsltproc -o ../doc/ar/about_kinneret.html ../etc/l2swim.xsl ../src/ar/about_kinneret.xml
xsltproc -o ../doc/ar/first_time.html ../etc/l2swim.xsl ../src/ar/first_time.xml

echo "if all files were compiles successfuly, then:"
echo "- enter root mode : su"
echo "- copy the files: cp ../doc/ar/*.html /opt/kinneret/l2swim/doc/ar/ -f"
