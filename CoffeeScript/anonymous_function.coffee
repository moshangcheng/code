# anonymous function
(-> console.log "I'm anonymous function")()

# anonymous function
do () -> console.log "I'm anonymous function2"


obj =
	"str": "abc"

(->
	console.log "hello"
	console.log "my value is #{@str}"
).call obj
