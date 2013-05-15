(:
    XLST Test
    
Ref
    http://en.wikipedia.org/wiki/Xpath
    http://en.wikipedia.org/wiki/Xslt
    http://en.wikibooks.org/wiki/XQuery
    http://www.zorba-xquery.com/html/modules/zorba/programming/xslt
 :)
 
module namespace shu = 'http://www.microstrategy.com/xquery/test/shu';
 
declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

import module namespace xslt = "http://www.zorba-xquery.com/modules/languages/xslt";

declare function shu:xslt-example-run() as item()+
{
    let $source :=
    <catalog>
        <cd>
            <title>Empire Burlesque</title>
            <artist>Bob Dylan</artist>
            <country>USA</country>
            <company>Columbia</company>
            <price>10.90</price>
            <year>1985</year>
        </cd>
        <cd>
            <title>Hide your heart</title>
            <artist>Bonnie Tyler</artist>
            <country>UK</country>
            <company>CBS Records</company>
            <price>9.90</price>
            <year>1988</year>
        </cd>
    </catalog>
    
    let $stylesheet :=
    <xsl:stylesheet version="1.0"
        xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
        <xsl:template match="/">
            <html>
                <body>
                    <h2>Music Collection</h2>
                    <table border="1">
                        <tr bgcolor="lightblue">
                            <th>Title</th>
                            <th>Artist</th>
                        </tr>
                        <xsl:for-each select="catalog/cd">
                            <tr>
                                <td>
                                    <xsl:value-of select="title" />
                                </td>
                                <td>
                                    <xsl:value-of select="artist" />
                                </td>
                            </tr>
                        </xsl:for-each>
                    </table>
                </body>
            </html>
        </xsl:template>
    </xsl:stylesheet>
    return xslt:transform( $source, $stylesheet)
};
