#!/usr/bin/perl

######################################################
#100 Musagim - Randomaly pick musag                  #
#Wrriten by Gai Shaked (shaked.gai@gmail.com)        #
#Licence: GPL                                        #
######################################################

$lng=125;

srand time;
open Source1,"</opt/kinneret/karamba/100musagim/ctl";
$num=<Source1>;
close Source1;
$randtip=int(rand $num)+1;
open Source2,"</opt/kinneret/karamba/100musagim/musag-".$randtip;
$line=<Source2>;
print $line;
$url="http://he.wikipedia.org/wiki/".$line;
$line=<Source2>;
while (length($line) > $lng) {
	$i=$lng;
	while ((substr($line,$i,1) ne " ") && ($i > 0)) {$i--}
	if ($i==0) {$i=$lng}
	print substr($line,0,$i);
	print "\n";
	$line=substr($line,$i+1,length($line));
}
print $line;
close Source2;
print "\n";

open Dest,">/opt/kinneret/karamba/100musagim/url";
print Dest $url;
close Dest;




