#ifndef PARSE
#define PARSE

#define MAX_ARGS 100

void parseAll();
void parsePgm();
void parseDecls();
void parseDecl();
void parseStmts();
void parseStmt();
void parseExpr();
void parseComp();
void parseAddn();
void parseMuln();
void parseTerm();

void parseIf();
void parseWhile();
void parseCall();
void parseReturn();
void parseRead();
void parsePrint();
void parseExit();
void parseAssn();
void parseStruct();
void parseFuncDecl();
void parsePreDecls();
void parseStructInit();

void printFormatToken(int type);
#endif
