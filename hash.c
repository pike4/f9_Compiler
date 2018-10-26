#include "compiler.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

int getSize(int type)
{
	switch(type)
	{
		case TYPE_INT:
			return sizeof(int);
		case TYPE_CHAR:
			return sizeof(char);
		case TYPE_STR:
			return sizeof(char*);
		default:
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
/*

void addVar(char* key, int val)
{
	struct varDef* newVar = malloc(sizeof(varDef));
	newVar->type = val;
	newVar->size = getSize(val);

	hashInsert(vars, key, newVar);
}

int getVar(char* key)
{
	struct varDef* ret = (struct VarDef*) hashGet(vars, key);
	
	if(ret != 0)
		return ret->val;
	return 0;
}

void addStruct(char* key, struct structDef* def)
{
	hashInsert(structs, key, (void*) def);
}

struct structDef* getStruct(char* key)
{
	return hashGet(structs, key);
}
*/
