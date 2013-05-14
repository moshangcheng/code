(: XQuery main module :)

<html>
    <body>
        <h1>Bookstore</h1>
        <ul>
            {
                for $x in doc("resources/books.xml")/bookstore/book
                order by $x/title
                return
                <li class="{data($x/@category)}">{data($x/title)}</li>
            }
        </ul>
    </body>
</html> 