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
        <th align="center">תרגום</th>
        <th align="center">גרסת כנרת</th>
        <th align="center">גרסה</th>
        <th align="center">אתר הבית</th>
        <th align="center">קבוצת גיל</th>
        <th align="center">סיווג</th>
	<th align="center">שם היישום</th>
        <th align="center">קבוצה</th>
        <th align="center">הערות</th>
      </tr>
      <xsl:for-each select="catalog/app">
      <tr>
        <td align="right"><xsl:value-of select="hebrew"/></td>
        <td align="center"><xsl:value-of select="kinneret"/></td>
        <td align="center"><xsl:value-of select="version"/></td>
        <td align="left"><xsl:value-of select="home"/></td>
        <td align="center"><xsl:value-of select="age"/></td>
        <td align="right"><xsl:value-of select="class"/></td>
        <td align="left"><xsl:value-of select="title"/></td>
        <td align="right"><xsl:value-of select="group"/></td>
        <td align="right"><xsl:value-of select="extra"/></td>
      </tr>
      </xsl:for-each>
    </table>
  </center>
  </body>
  </html>
</xsl:template>
</xsl:stylesheet>
