#!/usr/bin/perl
#Script for karamba to pick random tip.
#Copyright (C) 2003 Gai Shaked <costello@linux-kinneret.org>.
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
srand time;
@files=glob("/opt/kinneret/karamba/tip/*.tip");
$num=0;
while (@files[$num] ne "") {
	$num++
}
$tip=int(rand $num);
open Source,"<".@files[$tip];
$line=<Source>;
#title line
print $line;
$chomp=70;
#body
while ($line=<Source>) {
$line.=" ";
while (length($line) > $chomp) {
	$cut=true;
	$i=0;
	while (($i<$chomp) and $cut) {
		if (substr($line,$i,1) eq "\n") {
			$cut=false;
			print substr($line,0,$i);
			print "\n";
			$line=substr($line,$i+1,length($line)-$i);
		}
		$i++;
	}
	$i=$chomp;
	while ($cut and ($i>0)) {
		if (substr($line,$i,1) eq " ") {
			print substr($line,0,$i);
			print "\n";
			$line=substr($line,$i+1,length($line)-$i);
			$cut=false;
		}
		$i--;
	}
}
#print $line;
}
close Source;
print "\n";




