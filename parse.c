#include "compiler.h"

int indentation;

void indent()
{
	for( int i = 0; i < indentation; i++)
	{
		printf("\t");
	}
}

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
	indentation = 0;
	printf("#include <stdio.h>\n#include <stdlib.h>\n\n");
	getToken();

	parsePreDecls();
	parsePgm();

	getToken();

	if(curTok.tok_type != LEX_EOF)
	{
		parseErr(LEX_EOF);
	}
}

void parsePreDecls()
{
	while(curType == LEX_STRUCT)
	{
		parseStruct();
	}
}

void parsePgm()
{
	parseEat(LEX_PROGRAM);

	parseEat(LEX_LBRACK);
	printf("int main() {\n\n");
	indentation = 1;
	parseDecls();

	parseStmts();
	printf("\treturn 0;\n}\n");
}

void parseDecls()
{
	while(curTok.tok_type == LEX_INT
		|| curType == LEX_CHARDEC
		|| curType == LEX_STRDEC
		|| curType == LEX_STRUCT)
	{
		if(curType == LEX_IDENT && getStruct(curTok.tok_str) == 0)
			break;

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
			indent();
			printf("int ");
			type = TYPE_INT;
			rOpt1 = rOpt2 = LEX_NUM;
			break;
		case LEX_CHARDEC:
			indent();
			printf("char ");
			type = TYPE_CHAR;
			rOpt1 = LEX_CHAR;
			rOpt2 = LEX_NUM;
			break;
		case LEX_STRDEC:
			indent();
			printf("char* ");
			type = TYPE_STR;
			rOpt1 = rOpt2 = LEX_STRING;
			break;
		case LEX_STRUCT:
			parseStructInit();
			return;
		default:
			errMsg
			("missing type specifier - int assumed. Note: f9 does not support default-int\n");
	}

	parseEat(curType);
	parseAssert(LEX_IDENT);
	printf("%s = 0", curTok.tok_str);

	addVar(curTok.tok_str, type);

	getToken();

	// Get any subsequent declarations deliminated by commas
	while(curTok.tok_type == LEX_COMMA)
	{
		getToken();

		parseAssert(LEX_IDENT);
		printf(", %s = 0 ", curTok.tok_str);
		addVar(curTok.tok_str, type);
		getToken();
	}

	printf(";\n");
	parseEat(LEX_SEMICOLON);
}

void parseStruct()
{
	char structName[100];
	parseEat(LEX_STRUCT);
	printf("struct %s {\n", curTok.tok_str);
	indentation++;

	// Get the struct name from the next token
	parseAssert(LEX_IDENT);
	strcpy(structName, curTok.tok_str);

	getToken();

	if(getStruct(structName) != 0)
	{
		errMsg("struct already defined");
	}

	struct structDef* newDef = malloc(sizeof(struct structDef));
	newDef->size = 0;
	newDef->type = globalType;
	structsByType[globalType++] = newDef;
	
	// Parse the struct body
	parseEat(LEX_LBRACK);

	int type;
	struct structDef* temp;

	while( curType == LEX_INT
		|| curType == LEX_CHARDEC
		|| curType == LEX_STRDEC
		|| curType == LEX_STRUCT)
	{
		switch(curType)
		{
			case LEX_INT:
				indent();
				printf("\tint ");
				type = TYPE_INT;
				break;
			case LEX_CHARDEC:
				indent();
				printf("\tchar ");
				type = TYPE_CHAR;
				break;
			case LEX_STRDEC:
				indent();
				printf("\tchar* ");
				type = TYPE_STR;
				break;
			case LEX_STRUCT:
				indent();
				getToken();
				temp = getStruct(curTok.tok_str);
				printf("\tstruct %s ", curTok.tok_str);
				if(temp == 0)
				{
					printf("Error: undefined variable %s in struct body\n", curTok.tok_str);
					exit(-1);
				}
				type = temp->type;
				break;
				
			default:
				errMsg
				("missing type specifier - int assumed. Note: f9 does not support default-int\n");
		}

		// Add the first identifier in the line to the struct
		getToken();
		parseAssert(LEX_IDENT);
		addMember(newDef, curTok.tok_str, type);
		printf("%s", curTok.tok_str);
		//printf("add member %s to struct %s. Type %s\n", 
			//curTok.tok_str, structName, tokens_names[curType]);
		getToken();

		// Add the rest of the identifiers in the line as members
		while(curTok.tok_type == LEX_COMMA)
		{
			getToken();
			printf(", %s ", curTok.tok_str);
			parseAssert(LEX_IDENT);
			addMember(newDef, curTok.tok_str, type);
			//printf("add member to struct %s: %s. Type %s\n", 
			//	structName, curTok.tok_str, tokens_names[curType]);
			getToken();
		}
		printf(";\n");
		parseEat(LEX_SEMICOLON);
	}
	printf("};\n\n");
	indentation--;
	parseEat(LEX_RBRACK);
	parseEat(LEX_SEMICOLON);

	//printf("struct %s size: %d\n", structName, newDef->size);

	// Register the new struct and store the definition
	addStruct(structName, newDef);
}

void parseStructInit()
{
	parseEat(LEX_STRUCT);
	parseAssert(LEX_IDENT);

	char buffer[1000];

	struct structDef* prototype = getStruct(curTok.tok_str);
	if(prototype == 0)
	{
		printf("Undefined structure: %s\n", curTok.tok_str);
		exit(-1);
	}
	indent();
	printf("struct %s ", curTok.tok_str);
	getToken();
	printf("%s;\n", curTok.tok_str);
	
	addVar(curTok.tok_str, prototype->type);
	getToken();
	parseEat(LEX_SEMICOLON);
}

void parseStmts()
{
	while(curType == LEX_IF 
			|| curType == LEX_WHILE
			|| curType == LEX_IDENT 
			|| curType == LEX_PRINT
			|| curType == LEX_READ
			|| curType == LEX_EXIT)
	{
		parseStmt();
	}
}

void parseStmt()
{
	if(curType == LEX_IF)
	{
		parseIf();
	}

	else if(curType == LEX_WHILE)
	{
		parseWhile();
	}

	else if(curType == LEX_IDENT)
	{
		parseAssn();
	}

	else if(curType == LEX_PRINT
		|| curType == LEX_EXIT
		|| curType == LEX_READ)
	{
		parseCall();
	}
}

void parseWhile()
{
	parseEat(LEX_WHILE);
	parseEat(LEX_LPAREN);
	indent();
	printf("while(");
	indentation++;
	
	parseExpr();

	printf(") {\n");
	parseEat(LEX_RPAREN);
	parseEat(LEX_LBRACK);
		
	parseStmts();
	
	parseEat(LEX_RBRACK);
	printf("\n");
	indentation--;
	indent();
	printf("}\n");
}

void parseIf()
{
	// Parse condition
	parseEat(LEX_IF);
	parseEat(LEX_LPAREN);
	indent();
	printf("if( ");
	parseExpr();
	parseEat(LEX_RPAREN);
	printf(") {\n");
	indentation++;

	// Parse If Body
	parseEat(LEX_LBRACK);
	parseStmts();
	parseEat(LEX_RBRACK);
	indentation--;
	printf("\n");
	indent();
	printf("}\n");

	// Optional else statement
	if(curType == LEX_ELSE)
	{
		getToken();
		parseEat(LEX_LBRACK);
		indent();
		printf("else {\n");
		indentation++;
		parseStmts();
		parseEat(LEX_RBRACK);
		printf("\n");
		indentation--;
		indent();
		printf("}\n");
	}
}

void parseAssn()
{
	int type = getVar(curTok.tok_str);
	if(type == 0)
	{
		printf("Error: Variable %s undeclared\n", curTok.tok_str);
		exit(-1);
	}

	indent();
	printf("%s ", curTok.tok_str);

	getToken();
	switch(curType)
	{
		case LEX_ASSIGN:
		case LEX_PLEQ:	
		case LEX_MINEQ:
		case LEX_MULEQ:
		case LEX_DIVEQ:
			printf(" %s ", curTok.tok_str);
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
		printf(" %s ", curTok.tok_str);
		parseEat(LEX_CHAR);
	}

	else if(type == TYPE_STR)
	{
		printf(" %s ", curTok.tok_str);
		parseEat(LEX_STRING);
	}

	printf(";\n");
	parseEat(LEX_SEMICOLON);
}

void parseCall()
{
	if(curType == LEX_PRINT)
	{
		parsePrint();
	}

	else if(curType == LEX_EXIT)
	{
		parseExit();
	}

	else if(curType == LEX_READ)
	{
		parseRead();
	}

}

void parsePrint()
{
	getToken();
	parseEat(LEX_LPAREN);
	
	int argC = 0;
	while(1)
	{
		indent();
		printf("printf(");
		argC++;
		if(curType == LEX_STRING)
		{
			printf("%s);\n ", curTok.tok_str);
			getToken();
		}

		else if(curType == LEX_IDENT
			|| curType == LEX_NUM
			|| curType == LEX_LPAREN)
		{
			printf("\"%%d\", ");
			parseExpr();
			printf(");\n");
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

void parseRead()
{
	getToken();
	parseEat(LEX_LPAREN);
	indent();
	
	// Check that read() has at least one argument
	if(curTok.tok_type == LEX_RPAREN)
	{
		printf("read() must be called with at least one argument\n");
		exit(-1);
	}

	int moreVars = 1;
	int argCount = 0;
	char* argList[MAX_ARGS];

	while(moreVars > 0)
	{
		parseAssert(LEX_IDENT);
	
		// Check upper bound on input args
		if(argCount > MAX_ARGS)
		{
			printf("Too many arguments to read()\n");
			exit(-1);
		}

		// Check that the current variable exists
		if(getVar(curTok.tok_str) == 0)
		{
			printf("variable %s undeclared\n", curTok.tok_str);
			exit(-1);
		}

		// Add current var to the list of variables
		argList[argCount++] = strdup(curTok.tok_str);
		getToken();

		if(curTok.tok_type == LEX_COMMA) {
			getToken();
		}

		else {
			moreVars = 0;
		}	
	}

	parseEat(LEX_RPAREN);
	
	printf("scanf(\"");
	for(int i = 0; i < argCount; i++) {
		printFormatToken(getVar(argList[i]));
	}
	printf("\"");
	for(int i = 0; i < argCount; i++) {
		printf(",&%s", argList[i]);
	}

	printf(");");
}

void printFormatToken(int type)
{
	switch(type)
	{
		case TYPE_INT:
			printf("%%d");
			break;
		case TYPE_CHAR:
			printf("%%c");
			break;
		case TYPE_STR:
			printf("%%s");
			break;
		default:
			printf("Type cannot be printed\n");
			exit(-1);
	}
}

void parseExit()
{
	getToken();
	parseEat(LEX_LPAREN);
	indent();
	printf("exit(");
	parseExpr();
	parseEat(LEX_RPAREN);
	printf(");\n");
}

void parseExpr()
{
	parseComp();
	while(curTok.tok_type == LEX_AND
		|| curTok.tok_type == LEX_OR)
	{
		printf(" %s ", curTok.tok_str);
		getToken();
		parseComp();
	}
}

void parseComp()
{
	parseAddn();
	while(curTok.tok_type == LEX_LT
		|| curTok.tok_type == LEX_GT
		|| curTok.tok_type == LEX_GEQ
		|| curTok.tok_type == LEX_LEQ
		|| curTok.tok_type == LEX_EQ)
	{
		printf(" %s ", curTok.tok_str);
		getToken();
		parseAddn();
	}
}

void parseAddn()
{
	parseMuln();
	while(curTok.tok_type == LEX_PLUS
		|| curTok.tok_type == LEX_MIN)
	{
		printf(" %s ", curTok.tok_str);
		getToken();
		parseMuln();
	}
}

void parseMuln()
{
	parseTerm();
	while(curTok.tok_type == LEX_MUL
		|| curTok.tok_type == LEX_DIV)	
	{
		printf(" %s ", curTok.tok_str);
		getToken();
		parseTerm();
	}
}

void parseTerm()
{
	if( curType == LEX_IDENT )
	{
		int type = getVar(curTok.tok_str);
		if(type == 0) {
			printf("Error: undeclared variable %s\n", curTok.tok_str);
			exit(-1);
		}
		printf(" %s ", curTok.tok_str);

		getToken();

		while(curType == LEX_DOT)
		{
			getToken();
			if(type == 0)
			{
				printf("struct has no member \"%s\"\n", curTok.tok_str);
				exit(-1);
			}

			type = getStructMember(type, curTok.tok_str);
			printf(".%s", curTok.tok_str);

			//printf("\t.%s\n", curTok.tok_str);
			//printf("type: "); printTypeByID(type); printf("\n");
			getToken();
		}

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
		printf("(");
		parseExpr();
		parseEat(LEX_RPAREN);
		printf(")");
	}
}
