all:
	gcc -g -o token states.c tokens.c keywords.c actions.c makeFSM.c tok.c hash.c parse.c main.c
