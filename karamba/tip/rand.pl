#!/usr/bin/perl
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




