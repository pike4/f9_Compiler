all:
	gcc -g -o token tok.c makeFSM.c tokens.c actions.c states.c parse.c keywords.c hash.c main.c
