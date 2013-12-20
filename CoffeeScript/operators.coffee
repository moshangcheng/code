# true, yes, on -> true
# false, no, off -> false
# is -> ===
# isnt -> !===
# @ -> this

console.log "true" if (3 > 1) is on

str = "abc"
console.log "true" if str is "abc"

winner = yes if 92 in [47, 92, 13]
console.log winner

obj =
	"str": "abc"

(->
	console.log "hello"
	console.log "my value is #{@str}"
).call obj
