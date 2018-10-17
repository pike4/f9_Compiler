#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int col, line;
extern char nextChar;

char *keywords[9] = { "if", "else", "while", "for", "print", "int", "program", "exit", "read"};
int keywordCodes[9] = { LEX_IF,LEX_ELSE,LEX_WHILE,LEX_FOR,LEX_PRINT,LEX_INT,LEX_PROGRAM,LEX_EXIT,LEX_READ};

struct tok curTok;
int curType;

int main()
{
	makeFSM();

	printf("FSM Initialized\n");

	nextChar = getchar();

	printf("parseing\n");
	getToken();
	parseExpr();
	parseAll();
	
/*	while(1) 
	{
		struct tok a = getToken();
		printf("token: %s, string value: %s", tokens_names[a.tok_type], &a.tok_str[0]);
		printf("\n");
		printf("at line: %d, col %d\n\n", line, col);
		if(a.tok_type == LEX_NUM)
		{
			printf(" int value: %d", a.tok_val);
		}
		
		if(nextChar == EOF) {
			break;
		}
		if(a.tok_type == LEX_EOF) {
			break;
		}
	}*/
}
