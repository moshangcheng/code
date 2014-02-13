## HTML async and defer
- If async is present: The script is executed asynchronously with the rest of the page (the script will be executed while the page continues the parsing)
-If async is not present and defer is present: The script is executed when the page has finished parsing (before DOMContentLoaded event is fired) 
- If neither async or defer is present: The script is fetched and executed immediately, before the browser continues parsing the page
- ref
	- [w3schools: defer](http://www.w3schools.com/tags/att_script_defer.asp)
	- [w3schools: async](http://www.w3schools.com/tags/att_script_async.asp)
