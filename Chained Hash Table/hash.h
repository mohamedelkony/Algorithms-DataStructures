#ifndef hash_h
#define hash_h

typedef struct _item item;
typedef struct _table table;

static unsigned hash(table*, char*);
static unsigned xorHash(table*, char*);
static unsigned hash2(table*, int);

table* createTable(int);
char* getName(table*, int);
void add(table*, int, char*);
void printT(table*);
int contains(table*, char*);
void erase(table*, char*);

#endif