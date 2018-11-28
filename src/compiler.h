/* Global include file containing all common includes used throughout the compiler */

#ifndef COMPILER
#define COMPILER

#include "tokens.h"
#include "tok.h"
#include "states.h"
#include "actions.h"
#include "keywords.h"
#include "parse.h"
#include "hash.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char nextChar;
extern struct tok curTok;
extern int line, col;

void makeFSM();

#endif
