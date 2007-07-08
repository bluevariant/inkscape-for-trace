<?xml version="1.0" encoding="utf-8"?> 

<xsl:stylesheet
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
   xmlns="http://www.w3.org/1999/xhtml"
   xmlns:k="http://www.inkscape.org/namespaces/keys"
   xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
   xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
   xmlns:xlink="http://www.w3.org/1999/xlink"
   exclude-result-prefixes="k #default inkscape sodipodi xlink"
>
<xsl:output method="html" encoding="utf-8" indent="no" doctype-public="-//W3C//DTD HTML 4.0 Transitional//EN"/>

<xsl:template match="k:root">
<xsl:comment>
Do not edit this file.
It is generated automatically from doc/keys.xml by doc/keys-html.xsl.
</xsl:comment>
<html>
<head>
<title>Inkscape keys and mouse reference</title>
<style type="text/css">
.key {font-weight: bold}
.action {}
.note {padding-left: 100px; font-size: 70%}
.contents {padding: 1em; padding-left: 50px; background-color: #eeeeee; font-size: small; line-height: 1.7em;}
.contents-title {font-size: large; font-weight: bold; letter-spacing: 0.4em;}
.contents-section {font-size: large; font-weight: bold;}
.contents-group {font-size: small; }
body {margin: 1em; background-color: #ffffff;}
h1 {margin-top: 0.5em; padding-left: 50px; padding-bottom: 0em; margin-bottom: 0em; letter-spacing: -0.02em}
h2 {margin-top: 0.0em; padding-left: 50px; padding-bottom: 0em; margin-bottom: 0em; font-size: small;}
h4 {font-weight: bold; font-style: italic; margin-top: 1em; padding-left: 50px; padding-bottom: 0em; margin-bottom: 0em}
</style>
</head>
<body>
<h1><xsl:value-of select="/k:root/@title"/></h1>
<h2>Version <xsl:value-of select="/k:root/@ver"/></h2>

<xsl:apply-templates select="k:p"/>

<p class="contents"><span class="contents-title">Contents:</span><xsl:text>   </xsl:text>
<xsl:for-each select="//k:section">
<a class="contents-section" href="#{generate-id()}"><xsl:value-of select="./@title"/></a>
<xsl:if test="./k:group[k:title]">
<span class="contents-section">: </span>
</xsl:if>
<xsl:for-each select="./k:group[k:title]">
<a class="contents-group" href="#{generate-id()}"><xsl:value-of select="./k:title"/></a>
<xsl:if test="following-sibling::k:group[k:title]"><xsl:text>&#160;&#183; </xsl:text></xsl:if>
</xsl:for-each>
<span class="contents-section"><xsl:if test="following::k:section"><xsl:text>&#160;| </xsl:text></xsl:if></span>
</xsl:for-each>
</p>

<center>
<table border="0" cellspacing="0" cellpadding="4" width="100%">
<xsl:apply-templates select="k:column"/>
</table>
</center>

    <p>
      <a href="http://validator.w3.org/check/referer"><img border="0"
          src="http://www.w3.org/Icons/valid-html40"
          alt="Valid HTML 4.0!" height="31" width="88" /></a>
    </p>

</body>
</html>
</xsl:template>

<xsl:template match="k:p">
<p><xsl:apply-templates/></p>
</xsl:template>

<xsl:template match="k:a">
<a href="{@href}"><xsl:apply-templates/></a>
</xsl:template>

<xsl:template match="k:root/text() | k:column/text()"/>

<xsl:template match="k:column">
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="k:section">
<tr><td colspan="3"><a name="{generate-id()}"/><h1><xsl:value-of select="@title"/></h1></td></tr>
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="k:group/k:title">
<tr bgcolor="{ancestor::k:section/@color}"><td colspan="3"><h4><a name="{generate-id(..)}"/><xsl:value-of select="text()"/></h4></td></tr>
</xsl:template>

<xsl:template match="k:note">
<tr bgcolor="{ancestor::k:section/@color}"><td colspan="3"><span class="note"><xsl:value-of select="text()"/></span></td></tr>
</xsl:template>

<xsl:template match="k:keys | k:mouse">
<tr bgcolor="{ancestor::k:section/@color}">
<td align="right" width="40%">
<xsl:choose>
<xsl:when test="count(k:key) = 2">
<span class="key"><xsl:apply-templates select="k:key[1]"/></span>,
<span class="key"><xsl:apply-templates select="k:key[2]"/></span>
</xsl:when>
<xsl:otherwise>
<span class="key"><xsl:apply-templates select="k:key[1]"/></span>
</xsl:otherwise>
</xsl:choose>
</td>
<td>
<span class="action">
<xsl:apply-templates select="k:action"/>
</span>
</td>
</tr>
</xsl:template>

<xsl:template match="k:action">
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="k:key">
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="k:shift">
<xsl:text>Shift+</xsl:text>
</xsl:template>

<xsl:template match="k:ctrl">
<xsl:text>Ctrl+</xsl:text>
</xsl:template>

<xsl:template match="k:alt">
<xsl:text>Alt+</xsl:text>
</xsl:template>

<xsl:template match="k:left">
<xsl:text>Left </xsl:text>
</xsl:template>

<xsl:template match="k:right">
<xsl:text>Right </xsl:text>
</xsl:template>

<xsl:template match="k:keyf | k:misc | k:misc-wide">
<xsl:value-of select="@f"/>
</xsl:template>

<xsl:template match="k:arrows">
<xsl:text>arrows</xsl:text>
</xsl:template>

<xsl:template match="k:up">
<xsl:text>Up arrow</xsl:text>
</xsl:template>

<xsl:template match="k:down">
<xsl:text>Down arrow</xsl:text>
</xsl:template>

<xsl:template match="k:left-arrow">
<xsl:text>Left arrow</xsl:text>
</xsl:template>

<xsl:template match="k:right-arrow">
<xsl:text>Right arrow</xsl:text>
</xsl:template>

<xsl:template match="k:up-arrow">
<xsl:text>Up arrow</xsl:text>
</xsl:template>

<xsl:template match="k:down-arrow">
<xsl:text>Down arrow</xsl:text>
</xsl:template>

<xsl:template match="k:wheel">
<xsl:text>mouse wheel</xsl:text>
</xsl:template>

<xsl:template match="k:left-drag">
<xsl:text>mouse drag</xsl:text>
</xsl:template>

<xsl:template match="k:left-click">
<xsl:text>click</xsl:text>
</xsl:template>

<xsl:template match="k:mid-drag">
<xsl:text>middle button drag</xsl:text>
</xsl:template>

<xsl:template match="k:mid-click">
<xsl:text>middle click</xsl:text>
</xsl:template>

<xsl:template match="k:right-drag">
<xsl:text>right button drag</xsl:text>
</xsl:template>

<xsl:template match="k:right-click">
<xsl:text>right click</xsl:text>
</xsl:template>

</xsl:stylesheet>