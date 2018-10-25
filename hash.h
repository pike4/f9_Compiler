#ifndef HASH
#define HASH

#define TYPE_UNDEF	0
#define TYPE_INT	1
#define TYPE_STR	2

#define HASH_MAX 100

struct listEnt
{
	struct listEnt* next;
	int val;
	char* key;
};

struct listEnt* table[HASH_MAX];

void hashInsert(char* key, int val);
int hashGet(char* key);

int hash(char* key);

void hashInit();





#endif
