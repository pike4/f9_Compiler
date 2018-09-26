#define MAX_TOK 50

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
