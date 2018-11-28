#include "tokens.h"
#include "actions.h"
#include "states.h"
#include "tok.h"
void makeFSM()
{
	 int i;

	//STATE_INIT
	for( i = 0; i < 256; i++)
	{
		states[STATE_INIT][i].nextState = STATE_INIT;
		states[STATE_INIT][i].action = FSM_ACT_ERR;
		states[STATE_INIT][i].value = LEX_UNUSED;
	}

	states[STATE_INIT]['\n'].nextState = STATE_INIT;
	states[STATE_INIT]['\n'].action = FSM_ACT_SKIP;
	states[STATE_INIT]['\n'].value = LEX_UNUSED;

	states[STATE_INIT][BLANK].nextState = STATE_INIT;
	states[STATE_INIT][BLANK].action = FSM_ACT_SKIP;
	states[STATE_INIT][BLANK].value = LEX_UNUSED;

	states[STATE_INIT]['\t'].nextState = STATE_INIT;
	states[STATE_INIT]['\t'].action = FSM_ACT_SKIP;
	states[STATE_INIT]['\t'].value = LEX_UNUSED;

	states[STATE_INIT]['/'].nextState = STATE_SLASH;
	states[STATE_INIT]['/'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['/'].value = LEX_UNUSED;

	states[STATE_INIT]['('].nextState = STATE_INIT;
	states[STATE_INIT]['('].action = FSM_ACT_SRET;
	states[STATE_INIT]['('].value = LEX_LPAREN;

	states[STATE_INIT][')'].nextState = STATE_INIT;
	states[STATE_INIT][')'].action = FSM_ACT_SRET;
	states[STATE_INIT][')'].value = LEX_RPAREN;

	states[STATE_INIT]['{'].nextState = STATE_INIT;
	states[STATE_INIT]['{'].action = FSM_ACT_SRET;
	states[STATE_INIT]['{'].value = LEX_LBRACK;

	states[STATE_INIT]['}'].nextState = STATE_INIT;
	states[STATE_INIT]['}'].action = FSM_ACT_SRET;
	states[STATE_INIT]['}'].value = LEX_RBRACK;

	states[STATE_INIT][';'].nextState = STATE_INIT;
	states[STATE_INIT][';'].action = FSM_ACT_SRET;
	states[STATE_INIT][';'].value = LEX_SEMICOLON;

	states[STATE_INIT][','].nextState = STATE_INIT;
	states[STATE_INIT][','].action = FSM_ACT_SRET;
	states[STATE_INIT][','].value = LEX_COMMA;

	states[STATE_INIT]['.'].nextState = STATE_INIT;
	states[STATE_INIT]['.'].action = FSM_ACT_SRET;
	states[STATE_INIT]['.'].value = LEX_DOT;

	states[STATE_INIT][':'].nextState = STATE_INIT;
	states[STATE_INIT][':'].action = FSM_ACT_SRET;
	states[STATE_INIT][':'].value = LEX_COLON;

	states[STATE_INIT]['>'].nextState = STATE_GT;
	states[STATE_INIT]['>'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['>'].value = LEX_UNUSED;

	states[STATE_INIT]['<'].nextState = STATE_LT;
	states[STATE_INIT]['<'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['<'].value = LEX_UNUSED;

	states[STATE_INIT]['='].nextState = STATE_EQ;
	states[STATE_INIT]['='].action = FSM_ACT_SAVE;
	states[STATE_INIT]['='].value = LEX_UNUSED;

	states[STATE_INIT]['-'].nextState = STATE_MIN;
	states[STATE_INIT]['-'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['-'].value = LEX_UNUSED;

	states[STATE_INIT]['+'].nextState = STATE_PLUS;
	states[STATE_INIT]['+'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['+'].value = LEX_UNUSED;

	states[STATE_INIT]['*'].nextState = STATE_MUL;
	states[STATE_INIT]['*'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['*'].value = LEX_UNUSED;

	states[STATE_INIT]['|'].nextState = STATE_OR;
	states[STATE_INIT]['|'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['|'].value = LEX_UNUSED;

	states[STATE_INIT]['&'].nextState = STATE_AND;
	states[STATE_INIT]['&'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['&'].value = LEX_UNUSED;

	states[STATE_INIT]['!'].nextState = STATE_NOT;
	states[STATE_INIT]['!'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['!'].value = LEX_UNUSED;

	states[STATE_INIT][MEOF].nextState = STATE_INIT;
	states[STATE_INIT][MEOF].action = FSM_ACT_SRET;
	states[STATE_INIT][MEOF].value = LEX_EOF;

	for( i = 'a'; i <= 'z'; i++)
	{
		states[STATE_INIT][i].nextState = STATE_IDENT;
		states[STATE_INIT][i].action = FSM_ACT_SAVE;
		states[STATE_INIT][i].value = LEX_UNUSED;
	}

	for( i = 'A'; i <= 'Z'; i++)
	{
		states[STATE_INIT][i].nextState = STATE_IDENT;
		states[STATE_INIT][i].action = FSM_ACT_SAVE;
		states[STATE_INIT][i].value = LEX_UNUSED;
	}

	states[STATE_INIT]['_'].nextState = STATE_IDENT;
	states[STATE_INIT]['_'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['_'].value = LEX_UNUSED;

	states[STATE_INIT]['0'].nextState = STATE_ZERO;
	states[STATE_INIT]['0'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['0'].value = LEX_UNUSED;

	for( i = '1'; i <= '9'; i++)
	{
		states[STATE_INIT][i].nextState = STATE_NUM;
		states[STATE_INIT][i].action = FSM_ACT_SAVE;
		states[STATE_INIT][i].value = LEX_UNUSED;
	}

	states[STATE_INIT]['"'].nextState = STATE_QUOTE;
	states[STATE_INIT]['"'].action = FSM_ACT_SAVE;
	states[STATE_INIT]['"'].value = LEX_UNUSED;

	states[STATE_INIT]['\''].nextState = STATE_CHAR;
	states[STATE_INIT]['\''].action = FSM_ACT_SAVE;
	states[STATE_INIT]['\''].value = LEX_UNUSED;


	//STATE_SLASH
	for( i = 0; i < 256; i++)
	{
		states[STATE_SLASH][i].nextState = STATE_INIT;
		states[STATE_SLASH][i].action = FSM_ACT_RET;
		states[STATE_SLASH][i].value = LEX_DIV;
	}

	states[STATE_SLASH]['='].nextState = STATE_INIT;
	states[STATE_SLASH]['='].action = FSM_ACT_ARET;
	states[STATE_SLASH]['='].value = LEX_DIVEQ;

	states[STATE_SLASH]['/'].nextState = STATE_SLASH_SLASH;
	states[STATE_SLASH]['/'].action = FSM_ACT_SKIP;
	states[STATE_SLASH]['/'].value = LEX_UNUSED;

	states[STATE_SLASH]['*'].nextState = STATE_SLASH_STAR;
	states[STATE_SLASH]['*'].action = FSM_ACT_SKIP;
	states[STATE_SLASH]['*'].value = LEX_UNUSED;


	//STATE_SLASH_SLASH
	for( i = 0; i < 256; i++)
	{
		states[STATE_SLASH_SLASH][i].nextState = STATE_SLASH_SLASH;
		states[STATE_SLASH_SLASH][i].action = FSM_ACT_SKIP;
		states[STATE_SLASH_SLASH][i].value = LEX_UNUSED;
	}

	states[STATE_SLASH_SLASH]['\n'].nextState = STATE_INIT;
	states[STATE_SLASH_SLASH]['\n'].action = FSM_ACT_SKIP;
	states[STATE_SLASH_SLASH]['\n'].value = LEX_UNUSED;


	//STATE_SLASH_STAR
	for( i = 0; i < 256; i++)
	{
		states[STATE_SLASH_STAR][i].nextState = STATE_SLASH_STAR;
		states[STATE_SLASH_STAR][i].action = FSM_ACT_SKIP;
		states[STATE_SLASH_STAR][i].value = LEX_UNUSED;
	}

	states[STATE_SLASH_STAR]['*'].nextState = STATE_SLASH_STAR_STAR;
	states[STATE_SLASH_STAR]['*'].action = FSM_ACT_SKIP;
	states[STATE_SLASH_STAR]['*'].value = LEX_UNUSED;


	//STATE_SLASH_STAR_STAR
	for( i = 0; i < 256; i++)
	{
		states[STATE_SLASH_STAR_STAR][i].nextState = STATE_SLASH_STAR;
		states[STATE_SLASH_STAR_STAR][i].action = FSM_ACT_SKIP;
		states[STATE_SLASH_STAR_STAR][i].value = LEX_UNUSED;
	}

	states[STATE_SLASH_STAR_STAR]['/'].nextState = STATE_INIT;
	states[STATE_SLASH_STAR_STAR]['/'].action = FSM_ACT_SKIP;
	states[STATE_SLASH_STAR_STAR]['/'].value = LEX_UNUSED;


	//STATE_LT
	for( i = 0; i < 256; i++)
	{
		states[STATE_LT][i].nextState = STATE_INIT;
		states[STATE_LT][i].action = FSM_ACT_RET;
		states[STATE_LT][i].value = LEX_LT;
	}

	states[STATE_LT]['='].nextState = STATE_INIT;
	states[STATE_LT]['='].action = FSM_ACT_ARET;
	states[STATE_LT]['='].value = LEX_LEQ;


	//STATE_GT
	for( i = 0; i < 256; i++)
	{
		states[STATE_GT][i].nextState = STATE_INIT;
		states[STATE_GT][i].action = FSM_ACT_RET;
		states[STATE_GT][i].value = LEX_GT;
	}

	states[STATE_GT]['='].nextState = STATE_INIT;
	states[STATE_GT]['='].action = FSM_ACT_ARET;
	states[STATE_GT]['='].value = LEX_GEQ;


	//STATE_EQ
	for( i = 0; i < 256; i++)
	{
		states[STATE_EQ][i].nextState = STATE_INIT;
		states[STATE_EQ][i].action = FSM_ACT_RET;
		states[STATE_EQ][i].value = LEX_ASSIGN;
	}

	states[STATE_EQ]['='].nextState = STATE_INIT;
	states[STATE_EQ]['='].action = FSM_ACT_ARET;
	states[STATE_EQ]['='].value = LEX_EQ;


	//STATE_PLUS
	for( i = 0; i < 256; i++)
	{
		states[STATE_PLUS][i].nextState = STATE_INIT;
		states[STATE_PLUS][i].action = FSM_ACT_RET;
		states[STATE_PLUS][i].value = LEX_PLUS;
	}

	states[STATE_PLUS]['='].nextState = STATE_INIT;
	states[STATE_PLUS]['='].action = FSM_ACT_ARET;
	states[STATE_PLUS]['='].value = LEX_PLEQ;


	//STATE_MIN
	for( i = 0; i < 256; i++)
	{
		states[STATE_MIN][i].nextState = STATE_INIT;
		states[STATE_MIN][i].action = FSM_ACT_RET;
		states[STATE_MIN][i].value = LEX_MIN;
	}

	states[STATE_MIN]['='].nextState = STATE_INIT;
	states[STATE_MIN]['='].action = FSM_ACT_ARET;
	states[STATE_MIN]['='].value = LEX_MINEQ;

	for( i = '0'; i <= '9'; i++)
	{
		states[STATE_MIN][i].nextState = STATE_NUM;
		states[STATE_MIN][i].action = FSM_ACT_APPEND;
		states[STATE_MIN][i].value = LEX_UNUSED;
	}


	//STATE_MUL
	for( i = 0; i < 256; i++)
	{
		states[STATE_MUL][i].nextState = STATE_INIT;
		states[STATE_MUL][i].action = FSM_ACT_RET;
		states[STATE_MUL][i].value = LEX_MUL;
	}

	states[STATE_MUL]['='].nextState = STATE_INIT;
	states[STATE_MUL]['='].action = FSM_ACT_ARET;
	states[STATE_MUL]['='].value = LEX_MULEQ;


	//STATE_AND
	for( i = 0; i < 256; i++)
	{
		states[STATE_AND][i].nextState = STATE_INIT;
		states[STATE_AND][i].action = FSM_ACT_ERR;
		states[STATE_AND][i].value = LEX_UNUSED;
	}

	states[STATE_AND]['&'].nextState = STATE_INIT;
	states[STATE_AND]['&'].action = FSM_ACT_ARET;
	states[STATE_AND]['&'].value = LEX_AND;


	//STATE_OR
	for( i = 0; i < 256; i++)
	{
		states[STATE_OR][i].nextState = STATE_INIT;
		states[STATE_OR][i].action = FSM_ACT_ERR;
		states[STATE_OR][i].value = LEX_UNUSED;
	}

	states[STATE_OR]['|'].nextState = STATE_INIT;
	states[STATE_OR]['|'].action = FSM_ACT_ARET;
	states[STATE_OR]['|'].value = LEX_OR;


	//STATE_NOT
	for( i = 0; i < 256; i++)
	{
		states[STATE_NOT][i].nextState = STATE_INIT;
		states[STATE_NOT][i].action = FSM_ACT_ERR;
		states[STATE_NOT][i].value = LEX_UNUSED;
	}

	states[STATE_NOT]['='].nextState = STATE_INIT;
	states[STATE_NOT]['='].action = FSM_ACT_ARET;
	states[STATE_NOT]['='].value = LEX_NEQ;


	//STATE_IDENT
	for( i = 0; i < 256; i++)
	{
		states[STATE_IDENT][i].nextState = STATE_INIT;
		states[STATE_IDENT][i].action = FSM_ACT_RET;
		states[STATE_IDENT][i].value = LEX_IDENT;
	}

	for( i = 'a'; i <= 'z'; i++)
	{
		states[STATE_IDENT][i].nextState = STATE_IDENT;
		states[STATE_IDENT][i].action = FSM_ACT_APPEND;
		states[STATE_IDENT][i].value = LEX_UNUSED;
	}

	for( i = 'A'; i <= 'Z'; i++)
	{
		states[STATE_IDENT][i].nextState = STATE_IDENT;
		states[STATE_IDENT][i].action = FSM_ACT_APPEND;
		states[STATE_IDENT][i].value = LEX_UNUSED;
	}

	for( i = '0'; i <= '9'; i++)
	{
		states[STATE_IDENT][i].nextState = STATE_IDENT;
		states[STATE_IDENT][i].action = FSM_ACT_APPEND;
		states[STATE_IDENT][i].value = LEX_UNUSED;
	}

	states[STATE_IDENT]['_'].nextState = STATE_IDENT;
	states[STATE_IDENT]['_'].action = FSM_ACT_APPEND;
	states[STATE_IDENT]['_'].value = LEX_UNUSED;


	//STATE_NUM
	for( i = 0; i < 256; i++)
	{
		states[STATE_NUM][i].nextState = STATE_INIT;
		states[STATE_NUM][i].action = FSM_ACT_RET;
		states[STATE_NUM][i].value = LEX_NUM;
	}

	for( i = '0'; i <= '9'; i++)
	{
		states[STATE_NUM][i].nextState = STATE_NUM;
		states[STATE_NUM][i].action = FSM_ACT_APPEND;
		states[STATE_NUM][i].value = LEX_UNUSED;
	}


	//STATE_ZERO
	for( i = 0; i < 256; i++)
	{
		states[STATE_ZERO][i].nextState = STATE_INIT;
		states[STATE_ZERO][i].action = FSM_ACT_RET;
		states[STATE_ZERO][i].value = LEX_NUM;
	}

	for( i = '0'; i <= '9'; i++)
	{
		states[STATE_ZERO][i].nextState = STATE_NUM;
		states[STATE_ZERO][i].action = FSM_ACT_APPEND;
		states[STATE_ZERO][i].value = LEX_UNUSED;
	}

	states[STATE_ZERO]['x'].nextState = STATE_ZERO_X;
	states[STATE_ZERO]['x'].action = FSM_ACT_APPEND;
	states[STATE_ZERO]['x'].value = LEX_UNUSED;


	//STATE_ZERO_X
	for( i = 0; i < 256; i++)
	{
		states[STATE_ZERO_X][i].nextState = STATE_INIT;
		states[STATE_ZERO_X][i].action = FSM_ACT_ERR;
		states[STATE_ZERO_X][i].value = LEX_UNUSED;
	}

	for( i = '0'; i <= '9'; i++)
	{
		states[STATE_ZERO_X][i].nextState = STATE_HEX;
		states[STATE_ZERO_X][i].action = FSM_ACT_APPEND;
		states[STATE_ZERO_X][i].value = LEX_UNUSED;
	}


	//STATE_HEX
	for( i = 0; i < 256; i++)
	{
		states[STATE_HEX][i].nextState = STATE_INIT;
		states[STATE_HEX][i].action = FSM_ACT_RET;
		states[STATE_HEX][i].value = LEX_NUM;
	}

	for( i = '0'; i <= '9'; i++)
	{
		states[STATE_HEX][i].nextState = STATE_HEX;
		states[STATE_HEX][i].action = FSM_ACT_APPEND;
		states[STATE_HEX][i].value = LEX_UNUSED;
	}

	for( i = 'A'; i <= 'Z'; i++)
	{
		states[STATE_HEX][i].nextState = STATE_HEX;
		states[STATE_HEX][i].action = FSM_ACT_APPEND;
		states[STATE_HEX][i].value = LEX_UNUSED;
	}


	//STATE_QUOTE
	for( i = 0; i < 256; i++)
	{
		states[STATE_QUOTE][i].nextState = STATE_QUOTE;
		states[STATE_QUOTE][i].action = FSM_ACT_APPEND;
		states[STATE_QUOTE][i].value = LEX_UNUSED;
	}

	states[STATE_QUOTE]['\\'].nextState = STATE_ESCAPE;
	states[STATE_QUOTE]['\\'].action = FSM_ACT_APPEND;
	states[STATE_QUOTE]['\\'].value = LEX_UNUSED;

	states[STATE_QUOTE]['"'].nextState = STATE_INIT;
	states[STATE_QUOTE]['"'].action = FSM_ACT_ARET;
	states[STATE_QUOTE]['"'].value = LEX_STRING;


	//STATE_ESCAPE
	for( i = 0; i < 256; i++)
	{
		states[STATE_ESCAPE][i].nextState = STATE_QUOTE;
		states[STATE_ESCAPE][i].action = FSM_ACT_APPEND;
		states[STATE_ESCAPE][i].value = LEX_UNUSED;
	}


	//STATE_CHAR
	for( i = 0; i < 256; i++)
	{
		states[STATE_CHAR][i].nextState = STATE_CHAR_END;
		states[STATE_CHAR][i].action = FSM_ACT_APPEND;
		states[STATE_CHAR][i].value = LEX_UNUSED;
	}

	states[STATE_CHAR]['\\'].nextState = STATE_CHAR_ESC;
	states[STATE_CHAR]['\\'].action = FSM_ACT_APPEND;
	states[STATE_CHAR]['\\'].value = LEX_UNUSED;


	//STATE_CHAR_END
	for( i = 0; i < 256; i++)
	{
		states[STATE_CHAR_END][i].nextState = STATE_INIT;
		states[STATE_CHAR_END][i].action = FSM_ACT_ERR;
		states[STATE_CHAR_END][i].value = LEX_UNUSED;
	}

	states[STATE_CHAR_END]['\''].nextState = STATE_INIT;
	states[STATE_CHAR_END]['\''].action = FSM_ACT_ARET;
	states[STATE_CHAR_END]['\''].value = LEX_CHAR;


	//STATE_CHAR_ESC
	for( i = 0; i < 256; i++)
	{
		states[STATE_CHAR_ESC][i].nextState = STATE_CHAR_END;
		states[STATE_CHAR_ESC][i].action = FSM_ACT_APPEND;
		states[STATE_CHAR_ESC][i].value = LEX_UNUSED;
	}

}
