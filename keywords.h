#include "tokens.h"
#define NUM_KEYWORDS 9

char *keywords[9] = { "if", "else", "while", "for", "print", "int", "program", "exit", "read"};
int keywordCodes[9] = { LEX_IF,LEX_ELSE,LEX_WHILE,LEX_FOR,LEX_PRINT,LEX_INT,LEX_PROGRAM,LEX_EXIT,LEX_READ};
