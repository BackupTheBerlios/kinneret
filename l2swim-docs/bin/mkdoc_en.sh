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
xsltproc -o ../doc/en/gfdl_license.html ../etc/l2swim.xsl ../src/en/gfdl_license.xml
xsltproc -o ../doc/en/gpl_license.html ../etc/l2swim.xsl ../src/en/gpl_license.xml
xsltproc -o ../doc/en/user_interface.html ../etc/l2swim.xsl ../src/en/user_interface.xml
echo "if all files were compiles successfuly, then:"
echo "- enter toot mode : su"
echo "- copy the files: cp ../doc/en/*.html /opt/kinneret/l2swim/doc/en/ -f"
echo "... and same for other languages."
