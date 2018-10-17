all:
	gcc -o token tok.c makeFSM.c tokens.c actions.c states.c parse.c main.c
