speed = 0
speed ?= 15

footprints = yeti ? "bear"
console.log footprints

a =
	b:
		c: 1

console.log a.b?.c
console.log a.d?.c
