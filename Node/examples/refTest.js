var ref = require('ref')

// so we can all agree that a buffer with the int value written
// to it could be represented as an "int *"
var buf = new Buffer(4)
buf.writeInt32LE(12345, 0)

// first, what is the memory address of the buffer?
console.log(buf.address())  // ? 140362165284824

// using `ref`, you can set the "type", and gain magic abilities!
buf.type = ref.types.int

// now we can dereference to get the "meaningful" value
console.log(buf.deref())  // ? 12345


// you can also get references to the original buffer if you need it.
// this buffer could be thought of as an "int **"
var one = buf.ref()

// and you can dereference all the way back down to an int
console.log(one.deref().deref())  // ? 12345
