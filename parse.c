#include "compiler.h"

void parseErr(int tokType)
{
	printf("Error, expected, %s, got %s\n", tokens_names[tokType], tokens_names[curTok.tok_type]);
	if(curType == LEX_UNUSED)
		printf("\tstr: %s\n", curTok.tok_str);
	exit(-1);
}

void parseAssert(int tokType)
{
	if(curTok.tok_type != tokType)
	{
		parseErr(tokType);
	}
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
}

void parsePgm()
{
	parseAssert(LEX_PROGRAM);
	getToken();

	parseAssert(LEX_LBRACK);
	getToken();
	parseDecls();

	parseStmts();
}

void parseDecls()
{
	while(curTok.tok_type == LEX_INT)
	{
		parseDecl();
	}
}

void parseDecl()
{
	parseAssert(LEX_INT);
	printf("decl\n");
	getToken();
	parseAssert(LEX_IDENT);
	getToken();
	while(curTok.tok_type == LEX_COMMA)
	{
		printf("comma decls\n");
		getToken();
		parseAssert(LEX_IDENT);
		getToken();
	}

	parseAssert(LEX_SEMICOLON);
	getToken();
}

void parseStmts()
{
	int cur = curTok.tok_type;

	while(cur == LEX_IF 
			|| cur == LEX_WHILE
			|| cur == LEX_IDENT )
	{
		parseStmt();
	}
}

void parseStmt()
{
	
}

void parseIter()
{
	parseAssert(LEX_WHILE);
	getToken();
	parseAssert(LEX_LPAREN);
	getToken();
	
	parseStmts();

	parseAssert(LEX_RPAREN);

	parseAssert(LEX_LBRACK);
	getToken();
		
	parseStmts();
	
	parseAssert(LEX_RBRACK);
}

void parseIf()
{
	// Parse condition
	parseAssert(LEX_IF);
	getToken();
	parseAssert(LEX_LPAREN);
	getToken();
	parseExpr();
	parseAssert(LEX_RPAREN);
	getToken();

	// Parse If Body
	parseAssert(LEX_LBRACK);
	getToken();
	parseStmts();
	parseAssert(LEX_RBRACK);
	getToken();

	// Optional else statement
	if(curType == LEX_ELSE)
	{
		getToken();
		parseAssert(LEX_LBRACK);
		getToken();
		parseStmts();
		parseAssert(LEX_RBRACK);
		getToken();
	}
}

void parseAssn()
{

}

void parseCall()
{

}

void parseExpr()
{
	printf("expr in RPN:\n(");
	parseComp();
	if(curTok.tok_type == LEX_AND
		|| curTok.tok_type == LEX_OR)
	{
		printf("%s", curTok.tok_str);
		getToken();
		parseComp();
	}
	printf(")");
}

void parseComp()
{
	printf("(");
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
	printf(")");
}

void parseAddn()
{
	printf("(");
	parseMuln();
	if(curTok.tok_type == LEX_PLUS
		|| curTok.tok_type == LEX_MIN)
	{
		printf("%s", curTok.tok_str);
		getToken();
		parseMuln();
	}
	printf(")");
}

void parseMuln()
{
	printf("(");
	parseTerm();
	if(curTok.tok_type == LEX_MUL
		|| curTok.tok_type == LEX_DIV)	
	{
		printf("%s", curTok.tok_str);
		getToken();
		parseTerm();
	}
	printf(")");
}

void parseTerm()
{
	printf("(");
	if(curType == LEX_IDENT 
		|| curType == LEX_NUM
	)
	{
		printf("%s", curTok.tok_str);
		getToken();
		return;
	}

	else
	{
		parseAssert(LEX_LPAREN);
		getToken();
		parseExpr();
		parseAssert(LEX_RPAREN);
		getToken();
	}
	printf(")");
}
