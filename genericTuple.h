#ifndef _GenericTuple_h
#define _GenericTuple_h

#include <stdbool.h>
#include "HashMap.h"

typedef struct Tuple *Tuple;
typedef struct Data *Data;

struct Data {
  char *data;
};

//Generic Tuple
struct Tuple{
  //Contains a number of attributes
  int numAttributes;
  //Data size for the tuple
  Data * tupleData;

  //Tuples have a key
  char * tupleKey;

  //For the linked list
  Tuple next;
  Tuple prev;
};

extern Tuple newTuple (int numberOfAttributes, Data * data, char * key);
extern Data newData(char *d);
extern void insertTuple(int attributes, Data * data, char * key, Hashmap map);
extern void deleteTuple(int num, Data *attributes, Hashmap map);
extern Tuple lookupTuple(int num, Data *attributes, Hashmap map);
extern void print_Tuple(Tuple t);


#endif
