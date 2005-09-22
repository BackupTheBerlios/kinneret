<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
  <html>
  <body>
  <center>
  <font color="blue">
  <h2>טבלת היישומים הכלולים בגנו/לינוקס כנרת</h2>
  </font>
    <table border="1">
      <tr bgcolor="#99ccff">
        <th align="center">הערות</th>
        <th align="center">תרגום</th>
         <th align="center">גרסה</th>
        <th align="center">תיאור</th>
	<th align="center">אתר הבית</th>
	<th align="center">שם היישום</th>
	<th align="right">משנה</th>
	<th align="right">קטגוריה</th>
      </tr>
      <xsl:for-each select="catalog/app">
      <tr>
	<td align="right"><xsl:value-of select="extra"/></td>
	<td align="right"><xsl:value-of select="hebrew"/></td>

        <td align="center"><xsl:value-of select="version"/></td>


        <td align="right" dir="rtl"><xsl:value-of select="class"/></td>


	<td align="left"><xsl:value-of select="home"/></td>
	<td align="left"><xsl:value-of select="title"/></td>
	<td align="right"><b><xsl:value-of select="sub"/></b></td>
	<td align="right"><font size="+1"><b><xsl:value-of select="cat"/></b></font></td>
      </tr>
      </xsl:for-each>
    </table>
  </center>
  <hr></hr>
<p dir="rtl">
 הערות:
 <p>* הרשימה כוללת יישומים לגרסא 0.8
 </p>
 <p>* גרסא 0.8 תכלול אך ורק יישומים הנמצאים ברשימה או תלויות שלהם</p>
  <p>* חלק מהיישומים ברשימה טרם שוחררו בגרסתם הסופית, אך הם אמורים להשתחרר עד תאריך היעד לגרסא 1.0
  <br></br>
  במידה ולא שוחררה גרסא יציבה עד תאריך ביניים, יבחר המערצב אם להשתמש בגרסא ישנה יותר או בגרסאת פיתוח של התוכנה.
</p>
 </p>
  </body>
  </html>
</xsl:template>
</xsl:stylesheet>
