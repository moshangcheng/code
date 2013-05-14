//所有DOM节点都可以使用的版本
function prev( elem ) {
    do {
        elem = elem.previousSibling;
    } while ( elem && elem.nodeType != 1 );
    return elem;
}

//HTMLElement可以使用的版本
HTMLElement.prototype.prev = function() {
	var elem = this;
    do {
        elem = elem.previousSibling;
    }
    while (elem && elem.nodeType != 1);
    return elem;
};

//所有DOM节点都可以使用的版本
function next( elem ) {
    do {
        elem = elem.nextSibling;
    } while ( elem && elem.nodeType != 1 );
    return elem;
}

//HTMLElement可以使用的版本
HTMLElement.prototype.next = function() {
	var elem = this;
    do {
        elem = elem.nextSibling;
    }
    while (elem && elem.nodeType != 1);
    return elem;
};


//所有DOM节点都可以使用的版本
function first( elem ) {
    elem = elem.firstChild;
    return elem && elem.nodeType != 1 ?
        nextSibling( elem ) : elem;
}

//HTMLElement可以使用的版本，基于next()函数
//注意HTMLElement只是所有DOM元素的原型，不是文本节点等其他节点的原型
HTMLElement.prototype.first = function() {
	var elem = this;
    elem = elem.firstChild;
    return elem && elem.nodeType != 1 ? next(elem) : elem;
};


//所有DOM节点都可以使用的版本
function last( elem ) {
    elem = elem.lastChild;
    return elem && elem.nodeType != 1 ?
        prevSibling( elem ) : elem;
}

//HTMLElement可以使用的版本，基于prev函数
HTMLElement.prototype.last = function() {
	var elem = this;
    elem = elem.lastChild;
    return elem && elem.nodeType != 1 ? prev(elem) : elem;
};


//所有DOM节点都可以使用的版本
function parent( elem, num ) {
    num = num || 1;
    for ( var i = 0; i < num; i++ )
        if ( elem != null ) elem = elem.parentNode;
    return elem;
}

//HTMLElement可以使用的版本
HTMLElement.prototype.parent = function(num) {
	var elem = this;
    num = num || 1;
    for (var i = 0; i < num; i++) 
        if (elem != null) 
            elem = elem.parentNode;
    return elem;
};

//另外一种的next()的实现方法
function nextByTagName(elem){
     do {
        elem = elem.nextSibling;
    }
    while (elem && !elem.tagName);
    return elem;
}




//使用firebug进行调试时，如果在<head>标签中引入js代码，会导致<head>和<body>标签中
//多出一个<div id = "_firebugConsole">的标签
//在<body>标签中引入js代码不会有问题
window.onload = function(){
    var domBody = document.body;
    var domElement = domBody.first().next().next().first().next().prev().parent(2);
    alert(domElement.tagName);
};
