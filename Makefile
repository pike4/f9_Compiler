all:
	gcc -g -o token src/states.c src/tokens.c src/keywords.c src/actions.c src/makeFSM.c src/tok.c src/hash.c src/parse.c src/main.c
