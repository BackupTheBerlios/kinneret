open(FILES, ">>/home/r2d2/kthemes/karamba_light/scripts/weatherpics/yahoo/files");
for($x = 1; $x <= 100; $x++) {
	print FILES "http://us.yimg.com/i/us/we/intl/$x.gif\n";
}
