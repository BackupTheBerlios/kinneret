<?xml version='1.0'?>

<!-- ********************************************************************
     Gnu/Linux Kinneret
     'Learn to Swim' Interactive Guide - stylesheet
     (C) 2003 http://www.linux-kinneret.org

     This program is free software; you can redistribute it and/or modify it under
     the terms of the GNU General Public License as published by the Free Software
     Foundation; either version 2 of the License, or (at your option) any later
     version.

     This program is distributed in the hope that it will be useful, but WITHOUT
     ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
     FOR A PARTICULAR PURPOSE.  See the GNU General Public License at
     http://www.gnu.org/copyleft/gpl.html for more details.

     Filename: l2swim.xsl
     Version: 0.3b 17-June-2003
     Encoding: [UTF8]
     Language: Hebrew

     Authored by: dovix, dovix@linux-kinneret.org
     ******************************************************************** -->

<xsl:stylesheet
          xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="html" encoding="utf-8"/>

<xsl:template match="document | hebrew | arabic | article">
  <html>
    <head><title>
      <xsl:value-of select="./title"/>
    </title></head>
    <body dir="rtl">
      <xsl:apply-templates/>
    </body>
  </html>
</xsl:template>

<xsl:template match="english | russian">
  <html>
    <head><title>
      <xsl:value-of select="./title"/>
    </title></head>
    <body>
      <xsl:apply-templates/>
    </body>
  </html>
</xsl:template>

<!-- document title, blue, centered and barred -->
<!-- use only once, at the top of the document -->
<xsl:template match="title">
  <CENTER>
  <IMG SRC="/opt/kinneret/images/blue_bar.png" />
  <FONT COLOR="BLUE">
  <H1><xsl:apply-templates/></H1>
  </FONT>
  <IMG SRC="/opt/kinneret/images/blue_bar.png" />
  </CENTER>
  <BR/>
</xsl:template>

<!-- document subtitle, underlined, blue and right justified -->
<!-- use to designate sections within the document, usually followed by some text -->
<xsl:template match="subtitle | chapter">
  <p>
  <U>
  <FONT COLOR="BLUE">
  <B><xsl:apply-templates/></B>
  </FONT>
  </U>
  </p>
</xsl:template>

<!-- document level 2 subtitle, bold, italics, blue and right justified -->
<!-- use to designate sections within the document, usually followed by some text -->
<xsl:template match="subtitle2 | section">
  <p>
  <B>
  <I>
  <FONT COLOR="BLUE">
  <B><xsl:apply-templates/></B>
  </FONT>
  </I>
  </B>
  </p>
</xsl:template>

<!-- document level 3 subtitle, underlined, italics, blue and right justified -->
<!-- use to designate sections within the document, usually followed by some text -->
<xsl:template match="subtitle3 | subsect">
  <p>
  <U>
  <I>
  <FONT COLOR="BLUE" SIZE="-1">
  <B><xsl:apply-templates/></B>
  </FONT>
  </I>
  </U>
  </p>
</xsl:template>

<!-- A paragraph of text terminated with a new line -->
<xsl:template match="para">
  <p>
<!--   <blockquote> -->
    <xsl:apply-templates/>
<!--   </blockquote> -->
  </p>
</xsl:template>

<!-- A quote, centered, italicized and within "" -->
<xsl:template match="quote">
   <blockquote><p>
      <xsl:text>"</xsl:text>
      <em>
        <xsl:apply-templates/>
      </em>
      <xsl:text>"</xsl:text>
   </p></blockquote>
   <br/>
</xsl:template>

<!-- The quote source, bold and left justified "" -->
<xsl:template match="by">
   <blockquote dir="ltr"><p>
      <xsl:text>(</xsl:text>
      <b>
        <xsl:apply-templates/>
      </b>
      <xsl:text>)</xsl:text>
   </p></blockquote>
   <br/>
</xsl:template>


<!-- Left justified text within a aqua framed box. Use for english code samples -->
<xsl:template match="code">
  <table bgcolor="#99ccff" width="100%" cellpadding="5" cellspacing="0" border="1" dir="ltr"><tr><td><pre><code>
    <xsl:apply-templates/>
  </code></pre></td></tr></table>
</xsl:template>

<!-- Copyright box -->
<xsl:template match="copy">
<center>
  <table bgcolor="#99ccff" width="90%" cellpadding="5" cellspacing="0" border="1"><tr><td align="center">
    <xsl:apply-templates/>
  </td></tr></table>
</center>
<br/>
</xsl:template>

<!-- Box -->
<xsl:template match="box">
<p>
<center>
  <table bgcolor="#99ccff" width="90%" cellpadding="5" cellspacing="0" border="1"><tr><td>
    <xsl:apply-templates/>
  </td></tr></table>
</center>
</p>
</xsl:template>

<!-- List of items (using bullets) -->
<xsl:template match="bullets">
  <ul>
    <xsl:for-each select="item">
     <li>
      <xsl:apply-templates/>
    </li>
  </xsl:for-each>
 </ul>
</xsl:template>
  
<!-- List of items (using numbers) -->  
 <xsl:template match="numbers">
   <ol type="1">
     <xsl:for-each select="item">
      <li>
       <xsl:apply-templates/>
     </li>
    </xsl:for-each>
  </ol>
</xsl:template>

<!-- List of items (using capital letters) -->  
 <xsl:template match="letters">
   <ol type="A">
     <xsl:for-each select="item">
      <li>
       <xsl:apply-templates  mode='text'/>
     </li>
    </xsl:for-each>
  </ol>
</xsl:template>

<!-- A web link, can be used in midle of text -->
<xsl:template match="link">
  <a target="_blank">
    <xsl:attribute name="href">
      <xsl:value-of select="@href"/>
    </xsl:attribute>
    <xsl:value-of select="."/>
  </a>
</xsl:template>

<!-- ensures a new line after a line of text -->
<xsl:template match="newl">
  <BR/>
</xsl:template>

<!-- displays a centered image -->
<xsl:template match="image">
  <CENTER>
  <IMG>
    <xsl:attribute name = "SRC">
      <xsl:value-of select="file" />
    </xsl:attribute>
  </IMG>
  </CENTER>
</xsl:template>

<!-- sets the style of text to bold -->
<xsl:template match="bold">
  <b>
    <xsl:apply-templates/>
  </b>
</xsl:template>

</xsl:stylesheet>

<!-- ********************************************************************
	Tips:

	For hexadecimalm color codes please refer to http://www.utexas.edu/learn/html/colors.html
	For HTML quick reference please refer to http://www.cc.ukans.edu/~acs/docs/other/HTML_quick.shtml 
	Additional HTML references can be found at: http://www.utexas.edu/learn/html/

     ******************************************************************** -->

