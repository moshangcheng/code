module namespace shu = 'http://shu.me/acc';
 
declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

declare function shu:manipuliate-xml-run() as item()+
{
    <html>
        <body>
            <h1>Bookstore</h1>
            <ul>
                {
                    for $x in doc("books.xml")/bookstore/book
                    order by $x/title
                    return
                    <li class="{data($x/@category)}">{data($x/title)}</li>
                }
            </ul>
        </body>
    </html>
};