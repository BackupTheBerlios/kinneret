#!/usr/bin/perl
#Script for karamba to retrieve weather from weather.yahoo.com
#Copyright (C) 2003 Robert Paskowitz
#
#This program is free software; you can redistribute it and/or
#modify it under the terms of the GNU General Public License
#as published by the Free Software Foundation; either version 2
#of the License, or (at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program; if not, write to the Free Software
#Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#!-----------------------------------------!
#Make sure to change country and city codes
#!-----------------------------------------!


use LWP::Simple;
use utf8;

# The country's ID from weather.yahoo.com
# Just visit thje city for which you want information,
# can take the 4 letters of the 1st sub-directory.
# It normally ends with XX.
my $country = "ISXX";

# The city's ID from weather.yahoo.com
# This can be found immediately following the second
# occurance of the Country Code
@city[1]="אקר";
@city[2]="בת-ים";
@city[3]="בית-לחם";
@city[4]="בני ברק";
@city[5]="אילת";
@city[6]="חדרה";
@city[7]="חיפה";
@city[8]="הרצליה";
@city[9]="חולון";
@city[10]="ירושליים";
@city[11]="לוד בן-גוריון";
@city[12]="נהריה";
@city[13]="נצרת";
@city[14]="נשר";
@city[15]="נתניה";
@city[16]="עבדה";
@city[17]="פתח-תקווה";
@city[18]="קריית אתא";
@city[19]="קריית ביאליק";
@city[20]="קריית מוצקין";
@city[21]="קריית ים";
@city[22]="רמת גן";
@city[23]="רמלה";
@city[24]="רחובות";
@city[25]="ראשון לציון";
@city[26]="תל-אביב";
@city[27]="יוטבתה";
@city[28]="צובה";
@city[29]="אריאל";
@city[30]="באר-שבע";
@city[31]="קריית שמונה";
@city[32]="טבריה";
$filename = $ENV{HOME}."/.weather/city";
open Source,"<".$filename;
$num=<Source>;
close Source;

print @city[$num]."\n";
