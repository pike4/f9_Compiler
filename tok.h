#define MAX_TOK 50
#define MEOF 256

#define BLANK ' '
#include "states.h"

struct tok
{
	int tok_type;
	char tok_str[MAX_TOK];
	int tok_val;
};

// 
struct state
{
	int nextState;
	int action;
	int value;
};

// The table defining the FSM
struct state states[NUM_STATES][257];
