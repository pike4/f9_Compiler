/**********************************
*************Parse.c***************
***********************************/

#include "compiler.h"
int tmpArgs = 0;
int scopeCount = 0;
int curScope = 0;
int indentation;

void indent()
{
	for( int i = 0; i < indentation; i++)
	{
		fprintf(outFile,"\t");
	}
}

void errMsg(const char* msg)
{
	printf("Error at line %d, col %d: %s\n", line, col, msg);
	exit(-1);
}

void parseErr(int tokType)
{
	printf("Error, expected, %s, got %s\n", tokens_names[tokType], tokens_names[curTok.tok_type]);
	if(curType == LEX_UNUSED)
		printf("\tstr: %s\n", curTok.tok_str);
	errMsg("");
}

void parseFail(const char* err)
{
	errMsg(err);
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
	fprintf(outFile,"#include <stdio.h>\n#include <stdlib.h>\n#include<string.h>\n\n");
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
	while(curType == LEX_STRUCT || curType == LEX_FUNC)
	{
		if(curType == LEX_STRUCT)
			parseStruct();
		else parseFuncDecl();
	}
}

void parseFuncDecl()
{
	parseEat(LEX_FUNC);
	
	// Set up a new function declaration to be stored later
	struct funcDef* newFunc = malloc(sizeof(struct funcDef));
	int tempArgs[MAX_ARGS];
	int argC = 0;
	char tempName[200];

	strcpy(tempName, curTok.tok_str);
	
	parseAssert(LEX_IDENT);
	fprintf(outFile,"int %s (", curTok.tok_str);
	getToken();
	parseEat(LEX_LPAREN);
	
	curScope = ++scopeCount;
	while(curType != LEX_RPAREN)
	{
		int type;
		if(curType == LEX_INT
			|| curType == LEX_CHARDEC
			|| curType == LEX_STRDEC)
		{
			type = tokToType(curType);
			printTypeByID(type);
			getToken();
			tempArgs[argC++] = type;
		}

		else if(curType == LEX_STRUCT)
		{
			getToken();
			fprintf(outFile,"struct ");
			parseAssert(LEX_IDENT);
			fprintf(outFile,"%s ", curTok.tok_str);
			type = getStruct(curTok.tok_str)->type;
			getToken();
			tempArgs[argC++] = type;
		}

		else
		{
			parseFail("Expected a type specifier");
		}

		parseAssert(LEX_IDENT);
		addVar(curTok.tok_str, type);
		fprintf(outFile," %s", curTok.tok_str);
		getToken();
		
		if(curType == LEX_COMMA)
		{ 
			fprintf(outFile,", ");
			getToken();
		}
		else if(curType != LEX_RPAREN) 
		{
			parseFail("Expected a comma");
		}
	}
	getToken();
	
	// Build and store the new function declaration in the symbol table
	newFunc->argTypes = malloc(sizeof(int) * argC);
	newFunc->argC = argC;

	for(int i = 0; i < argC; i++)
	{
		newFunc->argTypes[i] = tempArgs[i];
	}

	// Parse the function body
	addFunc(tempName, newFunc);
	parseEat(LEX_LBRACK);
	fprintf(outFile,")\n{\n");
	indentation++;
	parseDecls();
	parseStmts();
	parseEat(LEX_RBRACK);
	indentation--;
	fprintf(outFile,"\n}\n\n");

}

void parsePgm()
{
	parseEat(LEX_PROGRAM);

	parseEat(LEX_LBRACK);
	curScope = 0;
	fprintf(outFile,"int main() {\n\n");
	indentation = 1;
	parseDecls();

	parseStmts();
	fprintf(outFile,"\treturn 0;\n}\n");
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
			fprintf(outFile,"int ");
			type = TYPE_INT;
			rOpt1 = rOpt2 = LEX_NUM;
			break;
		case LEX_CHARDEC:
			indent();
			fprintf(outFile,"char ");
			type = TYPE_CHAR;
			rOpt1 = LEX_CHAR;
			rOpt2 = LEX_NUM;
			break;
		case LEX_STRDEC:
			indent();
			fprintf(outFile,"char ");
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
	
	if(curType == LEX_STRDEC) {
		getToken();
		parseAssert(LEX_IDENT);
		fprintf(outFile,"%s[%d]", curTok.tok_str, MAX_TOK);
	}
	else {
		getToken();
		parseAssert(LEX_IDENT);
		fprintf(outFile,"%s = 0", curTok.tok_str);
	}

	addVar(curTok.tok_str, type);

	getToken();

	// Get any subsequent declarations deliminated by commas
	while(curTok.tok_type == LEX_COMMA)
	{
		getToken();

		parseAssert(LEX_IDENT);
		if(type != TYPE_STR)
			fprintf(outFile,", %s = 0 ", curTok.tok_str);
		else
			fprintf(outFile,", %s[%d]", curTok.tok_str, MAX_TOK);
		addVar(curTok.tok_str, type);
		getToken();
	}

	fprintf(outFile,";\n");
	parseEat(LEX_SEMICOLON);
}

void parseStruct()
{
	char structName[100];
	parseEat(LEX_STRUCT);
	fprintf(outFile,"struct %s {\n", curTok.tok_str);
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
				fprintf(outFile,"\tint ");
				type = TYPE_INT;
				break;
			case LEX_CHARDEC:
				indent();
				fprintf(outFile,"\tchar ");
				type = TYPE_CHAR;
				break;
			case LEX_STRDEC:
				indent();
				fprintf(outFile,"\tchar ");
				type = TYPE_STR;
				break;
			case LEX_STRUCT:
				indent();
				getToken();
				temp = getStruct(curTok.tok_str);
				fprintf(outFile,"\tstruct %s ", curTok.tok_str);
				if(temp == 0)
				{
					parseFail("Undefined variable in struct body\n");
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
		fprintf(outFile, "%s", curTok.tok_str);
		if(type == TYPE_STR)
			fprintf(outFile, "[%d]", MAX_TOK);
		//printf("add member %s to struct %s. Type %s\n", 
			//curTok.tok_str, structName, tokens_names[curType]);
		getToken();

		// Add the rest of the identifiers in the line as members
		while(curTok.tok_type == LEX_COMMA)
		{
			getToken();
			fprintf(outFile, ", %s ", curTok.tok_str);
			parseAssert(LEX_IDENT);
			addMember(newDef, curTok.tok_str, type);
			//printf("add member to struct %s: %s. Type %s\n", 
			//	structName, curTok.tok_str, tokens_names[curType]);
			getToken();
		}
		fprintf(outFile, ";\n");
		parseEat(LEX_SEMICOLON);
	}
	fprintf(outFile, "};\n\n");
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
		fprintf(stderr, "Undefined structure: %s\n", curTok.tok_str);
		exit(-1);
	}
	indent();
	fprintf(outFile, "struct %s ", curTok.tok_str);
	getToken();
	fprintf(outFile, "%s;\n", curTok.tok_str);
	
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
			|| curType == LEX_EXIT
			|| curType == LEX_CALL
			|| curType == LEX_COPY
			|| curType == LEX_RETURN)
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

	else if(curType == LEX_PRINT)
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

	else if(curType == LEX_CALL)
	{
		indent();
		parseCall();
		parseEat(LEX_SEMICOLON);
		fprintf(outFile, ";\n");
	}

	else if(curType == LEX_COPY)
	{
		parseCopy();
	}
	
	else if(curType == LEX_RETURN)
	{
		if(curScope == 0)
		{
			parseFail("Unexpected return statement in main function");
		}
		parseReturn();
	}
}

void parseWhile()
{
	parseEat(LEX_WHILE);
	parseEat(LEX_LPAREN);
	indent();
	fprintf(outFile, "while(");
	indentation++;
	
	parseExpr();

	fprintf(outFile, ") {\n");
	parseEat(LEX_RPAREN);
	parseEat(LEX_LBRACK);
		
	parseStmts();
	
	parseEat(LEX_RBRACK);
	fprintf(outFile, "\n");
	indentation--;
	indent();
	fprintf(outFile, "}\n");
}

void parseIf()
{
	// Parse condition
	parseEat(LEX_IF);
	parseEat(LEX_LPAREN);
	indent();
	fprintf(outFile, "if( ");
	parseExpr();
	parseEat(LEX_RPAREN);
	fprintf(outFile, ") {\n");
	indentation++;

	// Parse If Body
	parseEat(LEX_LBRACK);
	parseStmts();
	parseEat(LEX_RBRACK);
	indentation--;
	fprintf(outFile, "\n");
	indent();
	fprintf(outFile, "}\n");

	// Optional else statement
	if(curType == LEX_ELSE)
	{
		getToken();
		parseEat(LEX_LBRACK);
		indent();
		fprintf(outFile, "else {\n");
		indentation++;
		parseStmts();
		parseEat(LEX_RBRACK);
		fprintf(outFile, "\n");
		indentation--;
		indent();
		fprintf(outFile, "}\n");
	}
}

void parseAssn()
{
	int type = getVar(curTok.tok_str);
	if(type == 0)
	{
		fprintf(stderr, "Error: Variable %s undeclared\n", curTok.tok_str);
		exit(-1);
	}

	indent();
	fprintf(outFile, "%s ", curTok.tok_str);
	getToken();

	while(curType == LEX_DOT)
	{
		fprintf(outFile, ".");
		if(type == 0) {
			parseFail("Struct has no such member\n");
		}
		
		getToken();
		parseAssert(LEX_IDENT);
		fprintf(outFile, "%s", curTok.tok_str);
		type = getStructMember(type , curTok.tok_str);
		getToken();
	}	

	switch(curType)
	{
		case LEX_ASSIGN:
		case LEX_PLEQ:	
		case LEX_MINEQ:
		case LEX_MULEQ:
		case LEX_DIVEQ:
			fprintf(outFile, " %s ", curTok.tok_str);
			getToken();
			break;
		default:
			fprintf(outFile, "%s\n", curTok.tok_str);
			errMsg("Expected assignment statement");
	}


	if(type == TYPE_INT)
	{
		parseExpr();
	}
	
	else if(type == TYPE_CHAR)
	{
		if(curType == LEX_IDENT)
		{
			if(getVar(curTok.tok_str) != TYPE_CHAR)
			{
				parseFail("Assignment to char from incompatible type");
			}
		}
		else {
			parseAssert(LEX_CHAR);
		}
	
		fprintf(outFile, " %s ", curTok.tok_str);

		getToken();
	}

	else if(type == TYPE_STR)
	{
		parseFail("Strings are non-assignable. Use copy() to change string values");
	}

	fprintf(outFile, ";\n");
	parseEat(LEX_SEMICOLON);
}

void parseCall()
{
	parseEat(LEX_CALL);
	parseEat(LEX_COLON);
	parseEat(LEX_COLON);

	parseAssert(LEX_IDENT);

	struct funcDef* curFunc = getFunc(curTok.tok_str);

	if(curFunc == 0)
	{
		fprintf(stderr, "Undefined function\n");
		exit(-1);
	}
	
	fprintf(outFile, "%s(", curTok.tok_str);
	getToken();
	parseEat(LEX_LPAREN);
	int index = 0;
	
	while(curType != LEX_RPAREN)
	{
		int curVarType = getVar(curTok.tok_str);

		if(curType == LEX_STRING || 
			(curType == LEX_IDENT && curVarType == TYPE_STR))
		{
			if(curFunc->argTypes[index] != TYPE_STR) 
				parseFail("unexpected string in function call");
			fprintf(outFile, "%s", curTok.tok_str);
			getToken();
		}
		else if(curType == LEX_CHAR ||
			(curType == LEX_IDENT &&  curVarType == TYPE_CHAR))
		{
			if(curFunc->argTypes[index] != TYPE_CHAR)
			{
				parseFail(" unexpected char in function call");
			}

			fprintf(outFile, "%s", curTok.tok_str);
			getToken();
		}

		else if(curType == LEX_IDENT && curVarType != TYPE_INT)
		{
			if(curVarType != curFunc->argTypes[index])
			{
				fprintf(stderr, "Current function does not call for struct of type %s\n", curTok.tok_str);
				exit(-1);
			}
			fprintf(outFile, "%s", curTok.tok_str);
			getToken();
		}

		else
		{
			if(curFunc->argTypes[index] != TYPE_INT)
				parseFail("unexpected int in fuction call");
			parseExpr();
		}

		if(curType == LEX_COMMA)
		{
			fprintf(outFile, ", ");
			getToken();
		}
		else if(curType != LEX_RPAREN)
		{
			fprintf(stderr, "expectd a comma\n");
			exit(-1);
		}
		index++;
	}

	parseEat(LEX_RPAREN);
	fprintf(outFile, ")");
}

void parseReturn()
{
	parseEat(LEX_RETURN);
	indent();
	fprintf(outFile, "return ");
	parseExpr();
	parseEat(LEX_SEMICOLON);
	fprintf(outFile, ";\n");
}

void parseVar(int* type, char* nameBuff)
{
	int buffInd = 0;
	parseAssert(LEX_IDENT);
	strcpy(nameBuff, curTok.tok_str);
	buffInd += strlen(curTok.tok_str);

	*type = getVar(curTok.tok_str);
	if(*type == 0)
	{
		parseFail("unknown member");
	}
	
	getToken();

	while(curType == LEX_DOT)
	{
		nameBuff[buffInd++] = '.';
		getToken();
		parseAssert(LEX_IDENT);
		strcpy(nameBuff + buffInd, curTok.tok_str);
		*type = getStructMember(*type, curTok.tok_str);
		if(*type == 0)
		{
			parseFail("Unknown member");
		}

		buffInd += strlen(curTok.tok_str);
		getToken();
	}
}

void parseCopy()
{
	char buff[MAX_TOK];
	int type;

	parseEat(LEX_COPY);
	parseEat(LEX_LPAREN);
	indent();
	fprintf(outFile, "strcpy(");
	parseAssert(LEX_IDENT);

	parseVar(&type, &buff[0]);

	if(type != TYPE_STR)
	{
		parseFail("Only strings can be copied");
	}

	fprintf(outFile, "%s, ", buff);

	parseEat(LEX_COMMA);
	if(curType == LEX_STRING)
	{
		fprintf(outFile, "%s", curTok.tok_str);
		getToken();
	}
	
	else
	{
		parseAssert(LEX_IDENT);
		parseVar(&type, &buff[0]);
		if(type != TYPE_STR)
		{
			parseFail("Only strings can be copied");
		}
		fprintf(outFile, "%s", buff);
	}

	fprintf(outFile, ");\n");

	parseEat(LEX_RPAREN);
}

void parsePrint()
{
	getToken();
	parseEat(LEX_LPAREN);

	char tmpName[200];
	char tmpBuff[1000];
	int buffIndex = 0;
	
	int argC = 0;
	int moreArgs = 1;
	int argStart = tmpArgs;

	if(curTok.tok_type == LEX_RPAREN)
	{
		fprintf(stderr, "print() must be called with at least one argument\n");
		exit(-1);
	}

	while(moreArgs == 1)
	{
		buffIndex = 0;
		argC++;
		if(argC > MAX_ARGS)
		{
			fprintf(stderr,"Too many arguments to print()\n");
			exit(-1);
		}
		
		sprintf(tmpName, "temp%d", tmpArgs++);

		int tempType = getVar(curTok.tok_str);
		if(curType == LEX_IDENT && getVar(curTok.tok_str) > TYPE_CHAR)
		{
			/*strcpy(&tmpBuff[0], curTok.tok_str);
			buffIndex += strlen(curTok.tok_str);
			
			getToken();
			while(curType == LEX_DOT)
			{
				if(tempType == 0)
					parseFail("No such member\n");
				getToken();
				tmpBuff[buffIndex++] = '.';
				tempType = getStructMember(tempType, curTok.tok_str);
				strcpy(&tmpBuff[buffIndex], curTok.tok_str);
				buffIndex += strlen(curTok.tok_str);
				getToken();
			}
			tmpBuff[buffIndex + 1] = 0;*/
			parseVar(&tempType, &tmpBuff[0]);
			indent();
			if(tempType == TYPE_INT)
			{
				fprintf(outFile, "int %s = %s;\n", tmpName, tmpBuff);
				addVar(tmpName, TYPE_INT);
			}
			else if(tempType == TYPE_CHAR)
			{
				fprintf(outFile, "char %s = %s;\n", tmpName, tmpBuff);
				addVar(tmpName, TYPE_CHAR);
			}
			else if(tempType == TYPE_STR)
			{
				fprintf(outFile, "char* %s = %s;\n", tmpName, tmpBuff);
				addVar(tmpName, TYPE_STR);
			}
		}

		else if(curType == LEX_IDENT
			|| curType == LEX_NUM
			|| curType == LEX_LPAREN)
		{
			indent();
		

			if(curType == LEX_IDENT)
			{
				if(tempType == TYPE_INT) {
					addVar(tmpName, TYPE_INT);
					fprintf(outFile, "int %s = ", tmpName);
					parseExpr();
				}
				else if(tempType == TYPE_STR) {
					addVar(tmpName, TYPE_STR);
					fprintf(outFile, "char* %s = %s", tmpName, curTok.tok_str);
					getToken();
				}
				else if(tempType == TYPE_CHAR) {
					addVar(tmpName, TYPE_CHAR);
					fprintf(outFile, "char %s = %s", tmpName, curTok.tok_str);
					getToken();
				}
				else {
					parseFail("Unprintable type");
				}
			}
			else {
				fprintf(outFile, "int %s = ", tmpName);
				parseExpr();
				addVar(tmpName, TYPE_INT);
			}


			fprintf(outFile, ";\n");
		}
		else if(curType == LEX_CALL)
		{
			indent();
			fprintf(outFile, "int %s = ", tmpName);
			addVar(tmpName, TYPE_INT);
			parseCall();
			fprintf(outFile, ";\n");
		}
		else if(curType == LEX_STRING)
		{
			addVar(tmpName, TYPE_STR);
			indent();
			fprintf(outFile, "char* %s = ", tmpName);
			fprintf(outFile, "%s;\n", curTok.tok_str);
			getToken();
		}
		else if(curType == LEX_CHAR)
		{
			addVar(tmpName, TYPE_CHAR);
			indent();
			fprintf(outFile, "char %s = ", tmpName);
			fprintf(outFile, "%s;\n", curTok.tok_str);
			getToken();
		}

		else {
			fprintf(outFile, "invalid parameter type\n");
			exit(-1);
		}
	
		if(curType == LEX_COMMA) {
			parseEat(LEX_COMMA);
		} else {
			moreArgs = 0;
		}
	}
	indent();
	fprintf(outFile, "printf(\"");
	for( int i = argStart; i < tmpArgs; i++)
	{
		sprintf(tmpName, "temp%d", i);
		printFormatToken(getVar(tmpName));
	}
	fprintf(outFile, "\",");

	for(int i = argStart; i < tmpArgs; i++)
	{
		sprintf(tmpName, "temp%d", i);
		fprintf(outFile, "%s", tmpName);
		if(i < tmpArgs - 1)
		{
			fprintf(outFile, ", ");
		}
	}
	fprintf(outFile, ");\n");

	parseEat(LEX_RPAREN);
	if(curTok.tok_type == LEX_SEMICOLON) {
		parseFail("print statements do not end with a semicolon!\n");
	}
}

void parseRead()
{
	getToken();
	parseEat(LEX_LPAREN);
	indent();

	char buff[1000];
	int buffInd = 0;
	int curVarType;
	
	// Check that read() has at least one argument
	if(curTok.tok_type == LEX_RPAREN)
	{
		fprintf(stderr, "read() must be called with at least one argument\n");
		exit(-1);
	}

	int moreVars = 1;
	int argCount = 0;
	char* argList[MAX_ARGS];
	int argTypes[MAX_ARGS];

	while(moreVars > 0)
	{
		parseAssert(LEX_IDENT);
		buffInd = 0;
	
		// Check upper bound on input args
		if(argCount > MAX_ARGS)
		{
			fprintf(stderr, "Too many arguments to read()\n");
			exit(-1);
		}

		curVarType = getVar(curTok.tok_str);

		// Check that the current variable exists
		if(curVarType == 0)
		{
			parseFail("Undeclared variable\n");
			exit(-1);
		}

		strcpy(buff, curTok.tok_str);
		buffInd += strlen(curTok.tok_str);

		// Add current var to the list of variables
		getToken();

		// Continue parsing the variable if it is the member of a struct
		while(curTok.tok_type == LEX_DOT)
		{
			buff[buffInd++] = '.';
			getToken();
			parseAssert(LEX_IDENT);
			strcpy(&buff[buffInd], curTok.tok_str);
			buffInd += strlen(curTok.tok_str);
			buff[buffInd] = 0;
			curVarType = getStructMember(curVarType, curTok.tok_str);
			getToken();
		}

		argTypes[argCount] = curVarType;
		argList[argCount++] = strdup(buff);
			

		if(curTok.tok_type == LEX_COMMA) {
			getToken();
		}

		else {
			moreVars = 0;
		}
	}

	parseEat(LEX_RPAREN);
	
	// Write out the format tokens
	fprintf(outFile, "scanf(\"");
	for(int i = 0; i < argCount; i++) {
		printFormatToken(argTypes[i]);
	}
	fprintf(outFile, "\"");
	
	// Write out the variable list
	for(int i = 0; i < argCount; i++) {
		if(argTypes[i] == TYPE_STR)
			fprintf(outFile, ",%s", argList[i]);
		else
			fprintf(outFile, ",&%s", argList[i]);
		free(argList[i]);
	}

	fprintf(outFile, ");\n");

	if(curTok.tok_type == LEX_SEMICOLON) {
		parseFail("read statements do not end with a semicolon!\n");
	}
}

void printFormatToken(int type)
{
	switch(type)
	{
		case TYPE_INT:
			fprintf(outFile, "%%d");
			break;
		case TYPE_CHAR:
			fprintf(outFile," %%c");
			break;
		case TYPE_STR:
			fprintf(outFile,"%%s");
			break;
		default:
			fprintf(outFile,"Type %d cannot be printed\n", type);
			exit(-1);
	}
}

void parseExit()
{
	getToken();
	parseEat(LEX_LPAREN);
	indent();
	fprintf(outFile,"exit(");
	parseExpr();
	parseEat(LEX_RPAREN);
	fprintf(outFile,");\n");
}

void parseExpr()
{
	parseComp();
	while(curTok.tok_type == LEX_AND
		|| curTok.tok_type == LEX_OR)
	{
		fprintf(outFile," %s ", curTok.tok_str);
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
		fprintf(outFile," %s ", curTok.tok_str);
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
		fprintf(outFile," %s ", curTok.tok_str);
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
		fprintf(outFile," %s ", curTok.tok_str);
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
			parseFail("Error: undeclared variable\n");
		}
		fprintf(outFile," %s ", curTok.tok_str);

		getToken();

		while(curType == LEX_DOT)
		{
			getToken();
			if(type == 0)
			{
				parseFail("struct has no such member");
				exit(-1);
			}

			type = getStructMember(type, curTok.tok_str);
			fprintf(outFile,".%s", curTok.tok_str);

			//printf("\t.%s\n", curTok.tok_str);
			//printf("type: "); printTypeByID(type); printf("\n");
			getToken();
		}

		return;
	}

	else if( curType == LEX_NUM )
	{
		fprintf(outFile,"%s", curTok.tok_str);
		getToken();
		return;
	}

	else if(curType == LEX_CALL)
	{
		parseCall();
	}

	else
	{
		parseEat(LEX_LPAREN);
		fprintf(outFile,"(");
		parseExpr();
		parseEat(LEX_RPAREN);
		fprintf(outFile,")");
	}
}
