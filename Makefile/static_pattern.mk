.PHONY: %.o

files = foo.elc bar.o lose.o

$(filter %.o, $(files)): %.o: 
	@echo $@ called, it depends $<
