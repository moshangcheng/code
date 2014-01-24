if(typeof console == 'undefined') {
    console = {};
    console.log = print;
}

var s=2;  
function test(){  
    console.log(s);//undefined  
    s=1;  
    console.log(a);//undefined  
    if(s===3){  
        var a=2;  
    }  
    console.log(a);//undefined  
}  
test();  
console.log(s)
