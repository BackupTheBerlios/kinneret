#!/usr/bin/perl
#Script for karamba updating weather from the net every 30 minutes
#Copyright (C) 2003 Gai Shaked (costello).
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

#this file is used just for counting 900 * 2 secondes
$filename = $ENV{HOME}."/.weather/update";
#just checking in what seconed are we?
open Source,"<".$filename;
$num=<Source>;
close Source;
#ok, 2 seconds passed since last time :)
$num += 1;
#Do we have to update again?
if ($num >= 900) {
	$num=1;
	`/opt/kinneret/karamba/scripts/weather.pl`;
}
#just write where we are now...
open Dest,">".$filename;
print Dest $num;
close Dest;
#and now tell karamba what's the weather...
$filename = $ENV{HOME}."/.weather/karamba";
open Source,"<".$filename;
print <Source>;
print <Source>;
print <Source>;
print <Source>;
print <Source>;
print <Source>;
close Source;

