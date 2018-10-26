#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"

char nextChar;

struct tok curTok;
int col = 0, line = 0;

// Get the next character and update the line numbers
void getch()
{
	nextChar = getchar();
	col++;
	if(nextChar == '\n')
	{
		line++;
		col = 0;
	}
}

// True if the given token is a hex number
int isHexNum(struct tok num)
{
	if(num.tok_type == LEX_NUM &&
		num.tok_str[1] == 'x')
	{
		return 1;
	}
	else return 0;
}

// Convert the given token to its integer value
int toDec(struct tok num)
{
	int ret = 0;
	if(isHexNum(num))
	{
		int len = strlen(num.tok_str);
		for(int i = 2; i < len; i++)
		{
			char cur = num.tok_str[i];
			int nib;
			
			if(cur >= '0' && cur <= '9')
			{
				nib = cur - '0';
			}
			else if(cur >= 'A' && cur <= 'F')
			{
				nib = cur - 'A' + 10;
			}

			ret = (ret << 4) | nib;
		}
		return ret;
	}

	else
	{
		return atoi(&num.tok_str[0]);
	}
}

int lookupKeyword(char* str)
{
	for(int i = 0; i < NUM_KEYWORDS; i++)
	{
		if(!strcmp(str, keywords[i]))
		{
			return keywordCodes[i];
		}
	}

	return LEX_IDENT;
}

struct tok getToken() 
{
	int ch;
	char* pch;
	int curState = 0;
	int tokLen = 0;
	struct state* fsmptr;
	
	while(1)
	{
		ch = nextChar;
		if(ch == EOF) {
			ch = MEOF;
		}
		//printf("curchar='%c'\n", ch);
		fsmptr = &states[curState][ch];

		curState = fsmptr->nextState;
		struct tok ret;	

		char* str = &ret.tok_str[0];

		switch(fsmptr->action)
		{
			case FSM_ACT_SKIP:
				//printf("skip\n");
				getch();
				break;
			case FSM_ACT_RET:
				ret.tok_str[tokLen] = '\0';
				if(fsmptr->value == LEX_IDENT)
					ret.tok_type = lookupKeyword(&ret.tok_str[0]);
				else ret.tok_type = fsmptr->value;

				if ( ret.tok_type == LEX_NUM )
				{
					ret.tok_val = toDec(ret);
				}
				curTok = ret;
				curType = ret.tok_type;
				return ret;
			case FSM_ACT_SAVE:
				getch();
				ret.tok_str[0] = ch;
				tokLen = 1;
				break;

			case FSM_ACT_APPEND:
				getch();
				if(tokLen > MAX_TOK) {
					printf("Identifier too long\n");
					break;
				}
				else ret.tok_str[tokLen++] = ch;
				break;

			case FSM_ACT_SRET:
				ret.tok_type = fsmptr->value;
				*str++ = ch;
				getch();
				ret.tok_str[0] = ch;
				ret.tok_str[1] = '\0';
				curTok = ret;
				curType = ret.tok_type;
				return ret;

			case FSM_ACT_ARET:
				ret.tok_type = fsmptr->value;
				if(tokLen > MAX_TOK) {
					printf("Identifier too long\n");
				}	
				getch();

				ret.tok_str[tokLen++] = ch;
				ret.tok_str[tokLen++] = '\0';
				curTok = ret;
				curType = ret.tok_type;
				return ret;

			case FSM_ACT_ERR:
				printf("Undefined token\n");
				getch();
				break;

			default:
				printf("that shouldn't happen\n");
				break;
		}
	}	
}
