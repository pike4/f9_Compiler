#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "hash.h"

extern int col, line;
extern char nextChar;

struct tok curTok;
int curType;

int main()
{
	hashInit();
	makeFSM();
	
	printf("FSM Initialized\n");

	nextChar = getchar();

	printf("parseing\n");
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
