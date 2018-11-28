all:
	gcc -g -o f9 src/states.c src/tokens.c src/keywords.c src/actions.c src/makeFSM.c src/tok.c src/hash.c src/parse.c src/main.c

clean:
	rm ./f9; rm ./examples/*.c; rm ./examples/*.o
