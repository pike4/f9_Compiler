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
	struct member* next;
};

struct structDef
{
	struct member* members;
	int size;
	int type;
};

extern struct listEnt* vars[HASH_MAX];
extern struct listEnt* structs[HASH_MAX];
extern struct structDef* structsByType[HASH_MAX];

extern int globalType;

void hashInsert(struct listEnt** table, char* key, void* val);
void* hashGet(struct listEnt** table, char* key);

void addVar(char* key, int val);
int getVar(char* key);

void addStruct(char* key, struct structDef* def);
struct structDef* getStruct(char* key); 

int getStructMember(int structType, char* name);

void addMember(struct structDef* s, char* name, int type);

int hash(char* key);

void hashInit();

void printTypeByID(int type);

#endif
