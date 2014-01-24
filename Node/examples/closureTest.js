function GetFunc() {
    var i = 3;
    return function() {
        console.log(i);
    }
}

var fn = GetFunc();
fn()
