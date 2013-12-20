eat = (e) ->
	console.log "eat ", e

menu = (e) ->
	console.log "eat ", e


eat food for food in ['toast', 'cheese', 'wine']

courses = ['greens', 'caviar', 'truffles', 'roast', 'cake']
menu i+1, dish for dish, i in courses

foods = ['broccoli', 'spinach', 'chocolate']
eat food for food in foods when food isnt 'chocolate'
