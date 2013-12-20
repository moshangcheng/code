# Assignment:
number  = 3
opposite = true

# Conditions:
number = -42 if opposite

# Functions:
square = (x) -> x * x

# Arrays:
list = [1, 2, 3, 4, 5]

# Objects:
math =
	root:	Math.sqrt
	square:	square
	cube:	(x) -> x * square x

# Splats
race = (winder, runners...) ->
	print winder, runners

# Existence
alert "I knew it!" if elvis?

# Array comprehensions:
cubes = (math.cube num for num in list)

console.log "the length of ", cubes, " is ", cubes.length
