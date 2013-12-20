gold = silver = rest = "unknown"

awardMedals = (first, second, others...) ->
	gold = first
	silver = second
	rest = others

contenders = [
	"M P"
	"L X"
	"Y M"
	"A F"
	"S J"
	"R S"
	"G J"
	"T G"
	"A P"
	"U B"
]

awardMedals contenders...

console.log "Gold: ", gold
console.log "Silver: ", silver
console.log "The Field:", rest

