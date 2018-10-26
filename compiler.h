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


void makeFSM();

extern int col, line;

#endif
