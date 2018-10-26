#ifndef HASH
#define HASH

#define TYPE_UNDEF	0
#define TYPE_INT	1
#define TYPE_STR	2
#define TYPE_CHAR	3

#define HASH_MAX 100

struct varDef
{
	int type;
	int size;
};

struct listEnt
{
	struct listEnt* next;
	void* val;
	char* key;
};

struct member
{
	char* name;
	struct varDef def;
};

struct structDef
{
	struct varDef* listEnt;
	int size;
};

extern void* vars[HASH_MAX];
extern void* structs[HASH_MAX];

void hashInsert(struct listEnt** table, char* key, int val);
void* hashGet(struct listEnt** table, char* key);

void addVar(char* key, int val);
int getVar(char* key);

void addStruct(char* key, struct structDef def)
struct structDef* getStruct(char* key); 

int hash(char* key);

void hashInit();


#endif
