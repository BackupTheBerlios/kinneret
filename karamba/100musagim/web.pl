#!/usr/bin/perl
######################################################
#100 Musagim - Open Konqueror with the musag         #
#Wrriten by Gai Shaked (shaked.gai@gmail.com)        #
#Licence: GPL                                        #
######################################################

@Gibrish[1]="%D7%90";
@Gibrish[2]="%D7%91";
@Gibrish[3]="%D7%92";
@Gibrish[4]="%D7%93";
@Gibrish[5]="%D7%94";
@Gibrish[6]="%D7%95";
@Gibrish[7]="%D7%96";
@Gibrish[8]="%D7%97";
@Gibrish[9]="%D7%98";
@Gibrish[10]="%D7%99";
@Gibrish[11]="%D7%9A";
@Gibrish[12]="%D7%9B";
@Gibrish[13]="%D7%9C";
@Gibrish[14]="%D7%9D";
@Gibrish[15]="%D7%9E";
@Gibrish[16]="%D7%9F";
@Gibrish[17]="%D7%A0";
@Gibrish[18]="%D7%A1";
@Gibrish[19]="%D7%A2";
@Gibrish[20]="%D7%A3";
@Gibrish[21]="%D7%A4";
@Gibrish[22]="%D7%A5";
@Gibrish[23]="%D7%A6";
@Gibrish[24]="%D7%A7";
@Gibrish[25]="%D7%A8";
@Gibrish[26]="%D7%A9";
@Gibrish[27]="%D7%AA";
@Gibrish[28]="_";

@Hebrew[1]="א";
@Hebrew[2]="ב";
@Hebrew[3]="ג";
@Hebrew[4]="ד";
@Hebrew[5]="ה";
@Hebrew[6]="ו";
@Hebrew[7]="ז";
@Hebrew[8]="ח";
@Hebrew[9]="ט";
@Hebrew[10]="י";
@Hebrew[11]="ך";
@Hebrew[12]="כ";
@Hebrew[13]="ל";
@Hebrew[14]="ם";
@Hebrew[15]="מ";
@Hebrew[16]="ן";
@Hebrew[17]="נ";
@Hebrew[18]="ס";
@Hebrew[19]="ע";
@Hebrew[20]="ף";
@Hebrew[21]="פ";
@Hebrew[22]="ץ";
@Hebrew[23]="צ";
@Hebrew[24]="ק";
@Hebrew[25]="ר";
@Hebrew[26]="ש";
@Hebrew[27]="ת";
@Hebrew[28]=" ";

open Source1,"</opt/kinneret/karamba/100musagim/url";
$url=<Source1>;
close Source1;

for ($i=1; $i<29; $i++) {
	$url =~ s/@Hebrew[$i]/@Gibrish[$i]/g;
}


`konqueror $url`;