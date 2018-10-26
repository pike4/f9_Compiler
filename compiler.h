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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void makeFSM();

#endif
