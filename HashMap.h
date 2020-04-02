#ifndef _HashMap_h
#define _HashMap_h

#include <stdbool.h>
#define SIZE 97

typedef struct Hashmap *Hashmap;
typedef struct Database *Database;
typedef struct Bucket *Bucket;

struct Bucket {
  void* content;
};

//Structure for the hashmap
struct Hashmap {
  char *schema;
  int size;
  int tupleNumber;
  //array of linked lists
  Bucket table[SIZE];
};

// a database has a hashmap for data and a hashmap(?) for secondary indexing
struct Database {
  char *schema;
  Hashmap data;
  Hashmap indexing; //for secondary indexing (HASHMAP VS BST??)
};


extern int hashFunction(char *key, Hashmap map);
extern Hashmap Hashmap_new();
extern Database Database_new(char *schema, Hashmap data);
//extern void printHashmap(Hashmap hashmap);

#endif
