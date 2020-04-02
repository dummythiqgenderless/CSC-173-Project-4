//CSC 173 Project #4
//HashMap

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "LinkedList.h"
#include "HashMap.h"
#define SIZE 97

typedef struct Hashmap *Hashmap;
typedef struct Database *Database;
typedef struct Bucket *Bucket;


//Converts char [] to an unique integer value by converting each character to an int ascii value and adding the integer values together
int hashFunction(char *key, Hashmap map) {
  int hashcode = 0;
  //Temporary variable that has the ascii value of the character
  int asciivalue;
  for(int i = 0; i < strlen(key); i++){
    asciivalue = (int) key[i];
    hashcode += asciivalue;
  }

  //Need to ensure that that it is within the size of the hashmap
  hashcode = hashcode % map->size;

  return hashcode;
}

Bucket Bucket_new(void* content) {
  Bucket bucket = (Bucket) malloc(sizeof(Bucket));
  bucket->content = content;
  return bucket;
}

//Initialize a new hashmap
Hashmap Hashmap_new(char *schema) {
  Hashmap hashmap = (Hashmap) malloc(sizeof(struct Hashmap));
  hashmap->size = SIZE;
  hashmap->schema = schema;
  hashmap->tupleNumber = 0;
  //hashmap->table = (Bucket*)malloc(size*sizeof(Bucket));

  for(int i = 0; i < SIZE; i++ ) {
    // LinkedList *l = LinkedList_new();
    // hashmap->table[i] = &l;
    hashmap->table[i] = Bucket_new(NULL);
  }
  return hashmap;
}

//initialize a databse
Database Database_new(char *schema, Hashmap data) {
  Database database = (Database) malloc(sizeof(struct Database));
  database->data = data;
  database->indexing = Hashmap_new(schema);
  strcpy(database->schema, schema);

  return database;
}

// //Print function for hash table
// void printHashmap(Hashmap hashmap){
//   for(int i; i < SIZE; i++){
//     if(hashmap -> table [i] -> content == NULL) {
//       continue;
//     }
//     print_CSG(hashmap -> table [i] -> content);
//   }
//
// }
