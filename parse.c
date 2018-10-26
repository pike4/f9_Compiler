#include "compiler.h"

void parseErr(int tokType)
{
	printf("Error, expected, %s, got %s\n", tokens_names[tokType], tokens_names[curTok.tok_type]);
	if(curType == LEX_UNUSED)
		printf("\tstr: %s\n", curTok.tok_str);
	exit(-1);
}

void errMsg(char* msg)
{
	printf("Error at line %d, col %d: %s\n", line, col, msg);
	exit(-1);
}

void parseAssert(int tokType)
{
	if(curTok.tok_type != tokType)
	{
		parseErr(tokType);
	}
}

void parseEat(int tokType)
{
	parseAssert(tokType);
	getToken();
}

void parseAll()
{
	printf("parsepgm\n");
	getToken();
	parsePgm();

	getToken();

	if(curTok.tok_type != LEX_EOF)
	{
		parseErr(LEX_EOF);
	}
	printf("done\n");
}

void parsePgm()
{
	parseEat(LEX_PROGRAM);

	parseEat(LEX_LBRACK);
	parseDecls();

	parseStmts();
}

void parseDecls()
{
	while(curTok.tok_type == LEX_INT
		|| curType == LEX_CHARDEC
		|| curType == LEX_STRDEC
		|| curType == LEX_STRUCT)
	{
		parseDecl();
	}
}

// Parse one line of variable declarations
void parseDecl()
{
	// Determine the variable type the current line
	
	int type, rOpt1, rOpt2;
	switch(curType)
	{
		case LEX_INT:
			type = TYPE_INT;
			rOpt1 = rOpt2 = LEX_NUM;
			break;
		case LEX_CHARDEC:
			type = TYPE_CHAR;
			rOpt1 = LEX_CHAR;
			rOpt2 = LEX_NUM;
			break;
		case LEX_STRDEC:
			type = TYPE_STR;
			rOpt1 = rOpt2 = LEX_STRING;
			break;
		case LEX_STRUCT:
			parseStruct();
			return;
		default:
			errMsg
			("missing type specifier - int assumed. Note: f9++ does not support default-int\n");
	}

	parseEat(curType);
	parseAssert(LEX_IDENT);
	hashInsert(curTok.tok_str, type);

	getToken();

	// Get any subsequent declarations deliminated by commas
	while(curTok.tok_type == LEX_COMMA)
	{
		printf("comma decls\n");
		getToken();

		parseAssert(LEX_IDENT);
		hashInsert(curTok.tok_str, type);
		getToken();
	}

	parseEat(LEX_SEMICOLON);
}

void parseStruct()
{
	char structName[100];
	parseEat(LEX_STRUCT);

	// Get the struct name from the next token
	parseAssert(LEX_IDENT);
	strcpy(curTok.tok_str, structName);
	getToken();
	
	// Parse the struct body
	parseEat(LEX_LBRACK);

	while( curType == LEX_INT
		|| curType == LEX_CHARDEC
		|| curType == LEX_STRDEC )
	{
		switch(curType)
		{
			
		}
	}

	parseEat(LEX_RBRACK);
	parseEat(LEX_SEMICOLON);
	
	
}

void parseStmts()
{
	printf("parseStmts\n");

	printf("stmts starting with: %s\n", curTok.tok_str); 

	while(curType == LEX_IF 
			|| curType == LEX_WHILE
			|| curType == LEX_IDENT 
			|| curType == LEX_PRINT
			|| curType == LEX_EXIT)
	{
		parseStmt();
	}
}

void parseStmt()
{
	if(curType == LEX_IF)
	{
		printf("parse if\n");
		parseIf();
	}

	else if(curType == LEX_WHILE)
	{
		printf("parse while\n");
		parseWhile();
	}

	else if(curType == LEX_IDENT)
	{
		printf("parse ident\n");
		parseAssn();
	}

	else if(curType == LEX_PRINT
		|| curType == LEX_EXIT)
	{
		printf("parse call\n");
		parseCall();
	}
}

void parseWhile()
{
	printf("parseWhile\n");
	parseEat(LEX_WHILE);
	parseEat(LEX_LPAREN);
	
	parseExpr();

	parseEat(LEX_RPAREN);
	parseEat(LEX_LBRACK);
		
	parseStmts();
	
	parseEat(LEX_RBRACK);
	printf("whileDone\n");
}

void parseIf()
{
	// Parse condition
	parseEat(LEX_IF);
	parseEat(LEX_LPAREN);
	parseExpr();
	parseEat(LEX_RPAREN);

	// Parse If Body
	parseEat(LEX_LBRACK);
	parseStmts();
	parseEat(LEX_RBRACK);

	// Optional else statement
	if(curType == LEX_ELSE)
	{
		getToken();
		parseEat(LEX_LBRACK);
		parseStmts();
		parseEat(LEX_RBRACK);
	}
}

void parseAssn()
{
	int type = hashGet(curTok.tok_str);
	if(type == 0)
	{
		printf("Error: Variable %s undeclared\n", curTok.tok_str);
		exit(-1);
	}

	getToken();
	switch(curType)
	{
		case LEX_ASSIGN:
		case LEX_PLEQ:	
		case LEX_MINEQ:
		case LEX_MULEQ:
		case LEX_DIVEQ:
			getToken();
			break;
		default:
			printf("%s\n", curTok.tok_str);
			errMsg("Expected assignment statement");
	}

	if(curType == LEX_READ)	
	{
		getToken();
	}

	else if(type == TYPE_INT)
	{
		parseExpr();
	}
	
	else if(type == TYPE_CHAR)
	{
		parseEat(LEX_CHAR);
	}

	else if(type == TYPE_STR)
	{
		parseEat(LEX_STRING);
	}

	parseEat(LEX_SEMICOLON);
}

void parseCall()
{
	if(curType == LEX_PRINT)
	{
		printf("parsePrint\n");
		getToken();
		parseEat(LEX_LPAREN);
		
		int argC = 0;
		while(1)
		{
			argC++;
			if(curType == LEX_STRING)
			{
				getToken();
			}

			else if(curType == LEX_IDENT
				|| curType == LEX_NUM
				|| curType == LEX_LPAREN)
			{
				parseExpr();
			}

			else
			{
				errMsg("Invalid function argument");
			}
	
			if(curType == LEX_COMMA)
			{
				getToken();
			}

			else break;
		}

		if(argC == 0)
		{
			errMsg("print() must have at least one argument");
		}

		parseEat(LEX_RPAREN);
	}

	else if(curType == LEX_EXIT)
	{
		getToken();
		parseEat(LEX_LPAREN);
		parseExpr();
		parseEat(LEX_RPAREN);
	}
	parseEat(LEX_SEMICOLON);
}

void parseExpr()
{
	parseComp();
	if(curTok.tok_type == LEX_AND
		|| curTok.tok_type == LEX_OR)
	{
		printf("%s", curTok.tok_str);
		getToken();
		parseComp();
	}
}

void parseComp()
{
	parseAddn();
	if(curTok.tok_type == LEX_LT
		|| curTok.tok_type == LEX_GT
		|| curTok.tok_type == LEX_GEQ
		|| curTok.tok_type == LEX_LEQ
		|| curTok.tok_type == LEX_EQ)
	{
		printf("%s", curTok.tok_str);
		getToken();
		parseAddn();
	}
}

void parseAddn()
{
	parseMuln();
	if(curTok.tok_type == LEX_PLUS
		|| curTok.tok_type == LEX_MIN)
	{
		printf("%s", curTok.tok_str);
		getToken();
		parseMuln();
	}
}

void parseMuln()
{
	parseTerm();
	if(curTok.tok_type == LEX_MUL
		|| curTok.tok_type == LEX_DIV)	
	{
		printf("%s", curTok.tok_str);
		getToken();
		parseTerm();
	}
}

void parseTerm()
{
	if( curType == LEX_IDENT )
	{
		if(hashGet(curTok.tok_str) == 0) {
			printf("Error: undeclared variable %s\n", curTok.tok_str);
			exit(-1);
		}
		printf("%s", curTok.tok_str);
		getToken();
		return;
	}

	else if( curType == LEX_NUM )
	{
		printf("%s", curTok.tok_str);
		getToken();
		return;
	}

	else
	{
		parseEat(LEX_LPAREN);
		parseExpr();
		parseEat(LEX_RPAREN);
	}
}
