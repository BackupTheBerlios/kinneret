<?xml version="1.0" encoding="UTF-8"?>

<!-- ********************************************************************
     Gnu/Linux Kinneret
     'Learn to Swim' Interactive Guide - stylesheet
     (C) 2003 http://www.linux-kinneret.org
     Some code segments (C) gentoo.org (tables, drop down toc)

     This program is free software; you can redistribute it and/or modify it under
     the terms of the GNU General Public License as published by the Free Software
     Foundation; either version 2 of the License, or (at your option) any later
     version.

     This program is distributed in the hope that it will be useful, but WITHOUT
     ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
     FOR A PARTICULAR PURPOSE.  See the GNU General Public License at
     http://www.gnu.org/copyleft/gpl.html for more details.

     Filename: l2swim.xsl
     Version: 1.99b (2nd edition) 18-September-2003
     Encoding: [UTF8]
     Language support: Hebrew, Arabic, English, Russian

     Authored by: dovix, dovix@linux-kinneret.org
     ******************************************************************** -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output encoding="UTF-8" method="html" indent="yes" doctype-public="-//W3C//DTD HTML 4.01 Transitional//EN"/>

<xsl:preserve-space elements="pre"/>

<xsl:template match="/article">
	<html>
		<head>
			<!-- apply stylesheet -->
 			<link title="StyleSheet" rel="stylesheet"  href="../../etc/l2swim.css" type="text/css"/>
			<!-- set the title to the value of the 'title' element of the current node -->
			<title><xsl:value-of select="./title"/></title>
			<!-- -->
		</head>

		<!-- define a variable with the document direction -->
		<xsl:variable name="_dir">
			<xsl:choose>
				<xsl:when test="@lang = 'hebrew'">rtl</xsl:when>
				<xsl:when test="@lang = 'arabic'">rtl</xsl:when>
				<xsl:when test="@lang = 'russian'">ltr</xsl:when>
				<xsl:when test="@lang = 'english'">ltr</xsl:when>
				<xsl:otherwise>ltr</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<!-- main document body and footer -->
		<!-- apply the direction to the document body -->
		<body dir="{$_dir}">

			<!-- is there a 'title' segment? if so apply 'title' template -->
			<xsl:if test="title">
				<xsl:apply-templates select="title" />
			</xsl:if>

			<!-- is there a 'copy' segment? if so apply 'copy' template -->
			<xsl:if test="copy">
				<xsl:apply-templates select="copy" />
			</xsl:if>

			<!-- is there a 'toc' segment? if so apply 'toc' template -->
			<xsl:if test="toc">
				<xsl:apply-templates select="toc" />
			</xsl:if>

			<!-- is there a mandatory 'main' segment? if so apply 'main' template -->
			<xsl:choose>
				<xsl:when test="main">
					<xsl:apply-templates select="main" />
				</xsl:when>
				<xsl:otherwise>
					Error: No 'main' section found around body tags
				</xsl:otherwise>
			</xsl:choose>

			<!-- print the footer text -->
			<table bgcolor="#99ccff" width="100%" cellpadding="5" cellspacing="0" border="0"><tr><td align="center">
				<xsl:choose>
<!-- TO DO: needs translation -->
					<xsl:when test="@lang = 'hebrew'">
מסמך זה עובד ונערך עבור <a href="http://www.linux-kinneret.org">גנו/לינוקס כנרת</a>, תוך שימוש בתוכנה חופשית בלבד.
					</xsl:when>
					<xsl:when test="@lang = 'arabic'">
מסמך זה עובד ונערך עבור <a href="http://www.linux-kinneret.org">גנו/לינוקס כנרת</a>, תוך שימוש בתוכנה חופשית בלבד.
					</xsl:when>
					<xsl:when test="@lang = 'russian'">
This document was edited and formatted for <a href="http://www.linux-kinneret.org">GNU/Linux Kinneret</a> using only free software
					</xsl:when>
					<xsl:when test="@lang = 'english'">
This document was edited and formatted for <a href="http://www.linux-kinneret.org">GNU/Linux Kinneret</a> using only free software
					</xsl:when>
					<xsl:otherwise>ltr</xsl:otherwise>
				</xsl:choose>
			</td></tr></table>

			<table bgcolor="#bbffbb" width="100%" cellpadding="5" cellspacing="0" border="0"><tr><td align="center">
				<xsl:choose>
<!-- TO DO: needs translation -->
					<xsl:when test="@lang = 'hebrew'">
Linux הוא שם רשום של Linus Torvalds; Unix הוא שם רשום של ה Open Group בארה"ב ובמדינות נוספות, Windows הוא שם רשום של Microsoft Corporation. כל שאר השמות הרשומים וזכויות היוצרים שייכים לבעליהם.
					</xsl:when>
					<xsl:when test="@lang = 'arabic'">
לינוקס הוא שם רשום של Linus Torvalds; יוניקס הוא שם רשום של ה Open Group בארה"ב ובמדינות נוספות, Windows הוא שם רשום של Microsoft Corporation. כל שאר השמות הרשומים וזכויות היוצרים שייכים לבעליהם.
					</xsl:when>
					<xsl:when test="@lang = 'russian'">
Linux is a registered trademark by Linus Torvalds. Unix is a registered trademark by the Open Group is the US and other countries. Windows is a registered trademarks of Microsoft corp. All other trademarks and copyrights belong to the respective owners.
					</xsl:when>
					<xsl:when test="@lang = 'english'">
Linux is a registered trademark by Linus Torvalds. Unix is a registered trademark by the Open Group is the US and other countries. Windows is a registered trademarks of Microsoft corp. All other trademarks and copyrights belong to the respective owners.
					</xsl:when>
					<xsl:otherwise>ltr</xsl:otherwise>
				</xsl:choose>
			</td></tr></table>

			<table bgcolor="#ffffbb" width="100%" cellpadding="5" cellspacing="0" border="0"><tr><td align="center">
				<xsl:choose>
<!-- TO DO: needs translation -->
					<xsl:when test="@lang = 'hebrew'">
חשוב לדעת! גנו/לינוקס כנרת מסופקת "כפי שהיא", בלא אחריות מסוג כלשהו, בין אם מפורשת ובין אם משתמעת, לרבות, אך מבלי למעט מהאמור, האחריות המשתמעת למסחריות והתאמה למטרה מסוימת. בעלי זכויות היוצרים ו/או מפיצי התוכנה לא ישאו כלפיך באחריות לנזקים, לרבות נזקים כלליים, מיוחדים, משניים או תוצאתיים כלשהם, הנובעים מהשימוש או מאי-היכולת להשתמש בתוכנות המסופקות. עליך .לקרוא בעיון את רישיון השימוש המלא ולהסכים לנאמר בו לפני השימוש בהפצה זו.
					</xsl:when>
					<xsl:when test="@lang = 'arabic'">
חשוב לדעת! גנו/לינוקס כנרת מסופקת "כפי שהיא", בלא אחריות מסוג כלשהו, בין אם מפורשת ובין אם משתמעת, לרבות, אך מבלי למעט מהאמור, האחריות המשתמעת למסחריות והתאמה למטרה מסוימת. בעלי זכויות היוצרים ו/או מפיצי התוכנה לא ישאו כלפיך באחריות לנזקים, לרבות נזקים כלליים, מיוחדים, משניים או תוצאתיים כלשהם, הנובעים מהשימוש או מאי-היכולת להשתמש בתוכנות המסופקות. עליך .לקרוא בעיון את רישיון השימוש המלא ולהסכים לנאמר בו לפני השימוש בהפצה זו.
					</xsl:when>
					<xsl:when test="@lang = 'russian'">
Important! GNU/Linux Kinneret is provided "as is" without warranty of any kind, either expressed or implied, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose. You are requested to read and agree to the full end user license prior to using this distribution.
					</xsl:when>
					<xsl:when test="@lang = 'english'">
Important! GNU/Linux Kinneret is provided "as is" without warranty of any kind, either expressed or implied, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose. You are requested to read and agree to the full end user license prior to using this distribution.
					</xsl:when>
					<xsl:otherwise>ltr</xsl:otherwise>
				</xsl:choose>
				<IMG SRC="/opt/kinneret/images/exclamation.png" />
			</td></tr></table>


		</body>

	</html>
</xsl:template>

<xsl:template match="main">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="toc">
	<form name="contents">
	<b>	<xsl:choose>
		<xsl:when test="@lang = 'hebrew'">תוכן</xsl:when>
		<xsl:when test="@lang = 'arabic'">תוכן</xsl:when>
		<xsl:when test="@lang = 'russian'">Contents</xsl:when>
		<xsl:when test="@lang = 'english'">Contents</xsl:when>
		<xsl:otherwise>Contents</xsl:otherwise>
	</xsl:choose></b>:
	<select name="url" size="1" OnChange="location.href=form.url.options[form.url.selectedIndex].value" style="font-family:Arial,Helvetica,sans-serif; font-size:10">
		<xsl:for-each select="ancestor::article/main/chapter">
			<xsl:variable name="chapid">doc_chap
				<xsl:number/>
			</xsl:variable>
			<option value="#{$chapid}">
				<xsl:number/>.
				<xsl:value-of select="."/>
			</option>
		</xsl:for-each>
	</select>
	</form>

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

<!-- document chapter, underlined, blue and right justified - numbered & toc-ready -->
<!-- use to designate sections within the document, usually followed by some text -->
<xsl:template match="chapter">
	<xsl:variable name="chid"><xsl:number/></xsl:variable>
        <p>
		<U>
		<FONT COLOR="BLUE">
		<B>
		<span>
			<a name="doc_chap{$chid}"><xsl:number/>. </a>
		</span>
		<xsl:value-of select="."/>
		</B>
		</FONT>
		</U>
	</p>
</xsl:template>

<!-- document chapter, underlined, blue and right justified - not numbered & no toc -->
<!-- use to designate sections within the document, usually followed by some text -->
<xsl:template match="chapnotoc">
  <p>
  <U>
  <FONT COLOR="BLUE">
  <B><xsl:apply-templates/></B>
  </FONT>
  </U>
  </p>
</xsl:template>

<!-- document section, bold, italics, blue and right justified -->
<!-- use to designate sections within the document, usually followed by some text -->
<xsl:template match="section">
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

<!-- document sub-section, italics, blue and right justified -->
<!-- use to designate sections within the document, usually followed by some text -->
<xsl:template match="subsect">
  <p>
  <I>
  <FONT COLOR="BLUE" SIZE="-1">
  <xsl:apply-templates/>
  </FONT>
  </I>
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

<!-- A link or email, can be used in middle of text -->
<xsl:template match="link">
  <a target="_blank">
    <xsl:attribute name="href">
      <xsl:value-of select="@href"/>
    </xsl:attribute>
    <xsl:value-of select="."/>
  </a>
</xsl:template>

<!-- A globe used to designate an external (Internet) link, following <link> tag -->
<xsl:template match="web">
    <IMG SRC="/opt/kinneret/images/globe.png" />
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

<!-- displays a 4 images in a table -->
<xsl:template match="quatro">
  <CENTER>
  <table>
  <tr>
  <td>  
  <IMG>
    <xsl:attribute name = "SRC">
      <xsl:value-of select="one" />
    </xsl:attribute>
  </IMG>
  </td>
  <td>  
  <IMG>
    <xsl:attribute name = "SRC">
      <xsl:value-of select="two" />
    </xsl:attribute>
  </IMG>
  </td>
  </tr>
  <tr>
  <td>  
  <IMG>
    <xsl:attribute name = "SRC">
      <xsl:value-of select="three" />
    </xsl:attribute>
  </IMG>
  </td>
  <td>  
  <IMG>
    <xsl:attribute name = "SRC">
      <xsl:value-of select="four" />
    </xsl:attribute>
  </IMG>
  </td>
  </tr>
  </table>
  </CENTER>
</xsl:template>

<!-- sets the style of text to bold -->
<xsl:template match="bold">
  <b>
    <xsl:apply-templates/>
  </b>
</xsl:template>

<!--

The following tags allow to construct a table. Here is an example:

<table>
<tr><th>title1</th><th>title2</th></tr>
<tr><ti>item1.1</ti><ti>item1.2</ti></tr>
<tr><ti>item2.1</ti><ti>item2.2</ti></tr>
<tr><ti>item3.1</ti><ti>item3.2</ti></tr>
</table>
-->

<xsl:template match="table">
    <table class="ntable">
      <xsl:apply-templates/>
    </table>
  </xsl:template>


  <xsl:template match="tr">
    <tr>
      <xsl:apply-templates/>
    </tr>
  </xsl:template>


  <xsl:template match="ti">
    <td bgcolor="#ddddff" class="tableinfo">
      <xsl:apply-templates/>
    </td>
  </xsl:template>


  <xsl:template match="th">
    <td bgcolor="#99ccff" class="infohead">
      <b>
        <xsl:apply-templates/>
      </b>
    </td>
  </xsl:template>




<!-- report errors when obsolete tags are used -->

<xsl:template match="/document | /english | /hebrew | /arabic | /russian">
The old document tags are no longer in use. Please use 'article lang = "hebrew"|"arabic"|"russian"|"english"' instead.
</xsl:template>

<xsl:template match="subtitle | subtitle2 | subtitle3">
The old paragrapg tags are no longer in use. Please use "chapter"|"section"|"subsect""' instead of "subtitle" | "subtitle2" | "subtitle3".
</xsl:template>

</xsl:stylesheet>

<!-- ********************************************************************
	Tips:

	For hexadecimalm color codes please refer to http://www.utexas.edu/learn/html/colors.html
	For HTML quick reference please refer to http://www.cc.ukans.edu/~acs/docs/other/HTML_quick.shtml 
	Additional HTML references can be found at: http://www.utexas.edu/learn/html/

     ******************************************************************** -->
