all:
	gcc -g -o token tok.c makeFSM.c tokens.c actions.c states.c parse.c hash.c main.c
