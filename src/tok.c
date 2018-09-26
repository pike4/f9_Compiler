#include <stdio.h>
#include "tok.h"
#include "states.h"

struct state states[4][127];

int getToken() 
{
	int ch;
	char* pch;
	int curState = 0;
	struct state* fsmptr;	

	while(1)
	{
		ch = getchar();
		fsmptr = &states[curState][ch];

		curState = fsmptr->nextState;
		
		
		switch(fsmptr->action)
		{
			case FSM_ACT_SKIP:
				break;
			case FSM_ACT_RETURN:
				return fsmptr->value;
		}

	}	
		
}

int main()
{
	for(int j = 0; j < 4; j++)
	{
		for(int i = 0; i < 127; i++)
		{
			states[j][i].nextState = 0;
			states[j][i].action = FSM_ACT_RETURN;
			states[j][i].value= i;
		}
	}

	while(1) {
		char a = getToken();
		printf("token: %c\n", a);
	}
}
