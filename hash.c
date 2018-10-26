#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void hashInit()
{
	for(int i = 0; i < HASH_MAX; i++)
	{
		table[i] = 0;
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

void hashInsert(char* key, int val)
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

int hashGet(char* key)
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

	return TYPE_UNDEF;
}
