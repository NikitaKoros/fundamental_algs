#ifndef HASH_TABLE
#define HASH_TABLE

#include "util_task1.h"
#define INITIAL_TABLE_SIZE 50

typedef struct Macro Macro;

struct Macro {
    char* name;
    char* value;
    unsigned long cached_hash;
    Macro* nextMacro;
};

typedef struct {
    Macro** table;
    size_t size;
} HashTable;

HashTable* CreateHashTable(size_t);
Error FillTable(HashTable**, FILE*);
Error InsertMacro(HashTable*, const char*, const char*);

void PrintTable(const HashTable*);

Error ProcessFile(FILE*, char*, HashTable*);
char* ProcessLine(char*, HashTable*);
char* FindMacro(char*, HashTable*);

unsigned long HashFunction(const char*);

bool NeedRebalance(HashTable*);
Error ResizeHashTable(HashTable**);
void DestroyTable(HashTable*);

Error SubstituteReplacement(char **, size_t *, size_t *, const char *);
Error SubstituteOriginal(char **, size_t *, size_t *, const char *, size_t);

#endif