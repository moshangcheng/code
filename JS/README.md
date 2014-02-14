## Model of Web Page

HTML \- content, js \- logic, css \- presentation

So there are three models

- content-driven model
	- classical web page model
	- HTML is the core
		- the only necessary resource to display a web page is HTML file
		- display of web page is driven by HTML parsing
		- the framework of page is hand-written HTML
	- usage scenario
		- simple logic
		- no complex data held by web page
- logic-driven model
	- classical C/S application model, like [ExtJS](http://www.sencha.com/products/extjs/)
	- JS is the core
		- HTML is used a container
		- use JS to generate HTML element
		- HTML can be treated as config file of web page
	- usage scenario
		- complex logic
		- web page manipulates complex data
- presentation-driven model
	- suitable for interact
	- no implementation
	- design
		- a web page is composed of many nodes
		- use qurd-tree to hold nodes 
		- use automata to maintain status( touchable, switchable) of nodes

