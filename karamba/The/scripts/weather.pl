#!/usr/bin/perl
#Script for karamba to retrieve weather from weather.yahoo.com
#Copyright (C) 2003 Robert Paskowitz, Gai Shaked (costello).
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

# The country's ID from weather.yahoo.com
# Just visit thje city for which you want information,
# can take the 4 letters of the 1st sub-directory.
# It normally ends with XX.
my $country = "ISXX";

# The city's ID from weather.yahoo.com
# This can be found immediately following the second
# occurance of the Country Code
$filename = $ENV{HOME}."/.weather/city";
open Source,"<".$filename;
$num=<Source>;
close Source;
if ($num==0) {$num=32}
while (length($num)<4) {
	$num="0".$num;
}

my $city = $num;

# The path to the images.
my $path = "pics/weatherpics";


my $URL="http://ca.weather.yahoo.com/$country/$country$city/index_c.html";
my $page=get($URL);

$filename = $ENV{HOME}."/.weather/karamba";
open Dest,">".$filename;
$page2 = $page;
$page =~ s/face=Arial><b>(\d{1,2})/$1/;
print Dest "$1C\n";
$page =~ s/http:\/\/us.yimg.com\/i\/us\/we\/intl\/(\d{1,2}).gif/$1/;
print Dest "$path/$1.gif\n";
for ($x=1;$x<=4;$x++) {
	$page =~ s/http:\/\/us.yimg.com\/i\/us\/we\/intl\/(\d{1,2}).gif/$1/;
	print Dest "$path/small/$1.gif\n";
}
close Dest;
