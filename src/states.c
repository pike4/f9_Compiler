#include "states.h"

char* states_names[25] = 
{
	"STATE_INIT",
	"STATE_SLASH",
	"STATE_SLASH_SLASH",
	"STATE_SLASH_STAR",
	"STATE_SLASH_STAR_STAR",
	"STATE_IDENT",
	"STATE_NUM",
	"STATE_ZERO",
	"STATE_ZERO_X",
	"STATE_HEX",
	"STATE_LT",
	"STATE_GT",
	"STATE_EQ",
	"STATE_PLUS",
	"STATE_MIN",
	"STATE_MUL",
	"STATE_NOT",
	"STATE_AND",
	"STATE_OR",
	"STATE_QUOTE",
	"STATE_ESCAPE",
	"STATE_CHAR",
	"STATE_CHAR_END",
	"STATE_CHAR_ESC",
	"NUM_STATES"
};
