/*************************
*********hash.c***********
*************************/


#include "hash.h"
#include "tokens.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define MAX_SYMBOL 1000

char nameBuff[MAX_SYMBOL];

void hashInit()
{
	for(int i = 0; i < HASH_MAX; i++)
	{
		vars[i] = 0;
		structs[i] = 0;
	}
}

int hash(char* key)
{
	int ind = 0, ret = 0;

	while(key[ind] != 0)
	{
		ret += ind * key[ind++];
		ret = ret % 2069;
	}

	return abs(ret % 100);
}

int tokToType(int tok)
{
	switch(tok)
	{
		case LEX_INT: return TYPE_INT;
		case LEX_CHARDEC: return TYPE_CHAR;
		case LEX_STRDEC: return TYPE_STR;
		default: return TYPE_UNDEF;
	}
}

int getSize(int type)
{
	struct structDef* temp = structsByType[type];
	switch(type)
	{
		case TYPE_INT:
			return sizeof(int);
		case TYPE_CHAR:
			return sizeof(char);
		case TYPE_STR:
			return sizeof(char*);
		default:
			if(temp != 0)
				return temp->size;
			return 0;
	}
}

void hashInsert(struct listEnt** table, char* key, void* val)
{
	int h = hash(key);

	struct listEnt* cur = table[h];
	struct listEnt* newEnt = malloc(sizeof(struct listEnt));

	newEnt->next = 0;
	newEnt->val = val;
	newEnt->key = strdup(key);

	if(table[h] == 0)
	{
		table[h] = newEnt;
		return;
	}

	while(1)
	{
		// Key is present
		if(!strcmp(newEnt->key, cur->key))
		{
			printf("duplicate string!\n");
			free(newEnt);
			return;
		}

		// Current entry is end of list
		else if(cur->next == 0)
		{
			cur->next = newEnt;
			return;
		}

		// Go to next entry
		else
		{
			cur = cur->next;
		}
	}
}

// Get the value of the given key
void* hashGet(struct listEnt** table, char* key)
{
	int h = hash(key);
	struct listEnt* cur = table[h];

	while(cur != 0)
	{
		if(!strcmp(key, cur->key))
		{
			return cur->val;
		}
		else cur = cur->next;
	}

	return 0;
}


void addVar(char* key, int val)
{
	struct varDef* newVar = malloc(sizeof(struct varDef));
	newVar->type = val;
	newVar->size = getSize(val);

	sprintf(nameBuff, "%s:%d", key, curScope);

	hashInsert(vars, nameBuff, newVar);
}

int getVar(char* key)
{
	sprintf(nameBuff, "%s:%d", key, curScope);
	struct varDef* ret = ((struct VarDef*) hashGet(vars, nameBuff));
	
	if(ret != 0)
		return ret->type;
	return 0;
}

void addFunc(char* key, struct funcDef* def)
{
	hashInsert(&funcs[0], key, (void*) def);
}

struct funcDef* getFunc(char* key)
{
	return hashGet(funcs, key);
}

void addStruct(char* key, struct structDef* def)
{
	hashInsert(&structs[0], key, (void*) def);
}

struct structDef* getStruct(char* key)
{
	return hashGet(structs, key);
}

void addMember(struct structDef* s, char* name, int type)
{
	struct member* cur = s->members;

	if(cur == 0)
	{
		cur = malloc(sizeof(struct member));
		cur->name = strdup(name);
		cur->def.type = type;
		cur->def.size = getSize(type);
		s->members = cur;
		s->size += getSize(type);
		return;
	}

	while(1)
	{
		if(cur->next == 0)
		{
			cur->next = malloc(sizeof(struct member));
			cur->next->name = strdup(name);
			cur->next->def.type = type;
			cur->next->def.size = getSize(type);
			s->size += getSize(type);
			return;
		}
		
		else cur = cur->next;
	}
}

int getStructMember(int structType, char* name)
{
	struct structDef* s = structsByType[structType];
	struct member* cur = s->members;

	while(cur != 0)
	{
		if(!strcmp(name, cur->name))
		{
			return cur->def.type;
		}
		cur = cur->next;
	}
	return 0;
}

void printTypeByID(int type)
{
	switch(type)
	{
		case TYPE_UNDEF:
			printf("undefined");
			break;
		case TYPE_INT:
			printf("int");
			break;
		case TYPE_STR:
			printf("char*");
			break;
		case TYPE_CHAR:
			printf("char");
			break;
		default:
			printf("struct");
	}
}

struct listEnt* vars[HASH_MAX];
struct listEnt* structs[HASH_MAX];
struct listEnt* funcs[HASH_MAX];

struct structDef* structsByType[HASH_MAX];
int globalType = TYPE_CHAR + 1;
