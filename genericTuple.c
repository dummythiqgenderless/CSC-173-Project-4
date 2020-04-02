#include <stdio.h>
#include <stdbool.h>
#include "genericTuple.h"
#include <stdlib.h>
#include <string.h>
//#include "LinkedList.h"
#include "HashMap.h"

typedef struct Tuple *Tuple;
typedef struct Data *Data;

//Initializer for tuple with data
Tuple newTuple (int numberOfAttributes, Data * data, char * key){
  //Allocate space for the tuple
  Tuple tuple = (Tuple)malloc(sizeof(struct Tuple));
  //Set the attributes to the attribute size
  tuple -> numAttributes = numberOfAttributes;
  //Sets data with data
  tuple -> tupleData = data;

  //Sets tuple key
  tuple -> tupleKey = key;

  //Set next and previous to null
  tuple -> next = NULL;
  tuple -> prev = NULL;

  //Returns tuple
  return tuple;
}

Data newData(char *d) {
  Data data = (Data)malloc(sizeof(struct Data));
  data->data = d;
  return data;
}

//Insertion Method for Generic tuple
void insertTuple(int attributes, Data * data, char * key, Hashmap map){
  //Create a tuple with the entered information
  Tuple tuple = newTuple(attributes, data, key);

  //array indexx in the hashmap
  int index = hashFunction(key, map);

  /*check if the bucket at the index if empty
  if it is, put tuple in the bucket
  if not, add it to the end of the linked list at the bucket
  */
  Bucket b = map->table[index];
  if(b->content == NULL) {  //empty bucket
    b->content = tuple;
  } else { //not empty
    Tuple current = b->content;
    while(current->next != NULL) {
      current = current->next;
    }
    tuple->prev = current;
    current->next = tuple;
  }
  map->tupleNumber = map->tupleNumber + 1;
}

int checkAttributes(Tuple t, int num, Data *attributes) {
  int count = 0;
  for(int i = 0; i < num; i++) {
    if(attributes[i]->data[0] == '*' || strcmp(t->tupleData[i]->data, attributes[i]->data) == 0) {
      count ++;
    }
  }
  if(count == num) {
    return 1;
  }
  else {
    return 0;
  }
}

void deleteTuple(int num, Data *attributes, Hashmap map) {
  for(int i = 0; i < map->size; i++) {
    Tuple t = map->table[i]->content;
    while(t != NULL) {
      if(checkAttributes(t, num, attributes)) {
        // t is the only tuple in the bucket
        if(t->prev == NULL && t->next == NULL) {
          map->table[i]->content = NULL;
          t = t->next;
        }
        // t is the first tuple in the bucket
        else if(t->prev == NULL && t->next != NULL) {
          map->table[i]->content = t->next;
          t->next->prev = NULL;
          t = t->next;
        }
        // t is the last tuple in the Bucket
        else if(t->prev != NULL && t->next == NULL) {
          t->prev->next = NULL;
          t = t->next;
        }
        // t is in the middle somewhere
        else {
          t->next->prev = t->next;
          t->prev->next = t->next;
          t = t->next;
        }
      }
      else {
        t = t->next;
      }
    }
  }
}

Tuple lookupTuple(int num, Data *attributes, Hashmap map) {
  Tuple current;
  Tuple results = NULL; //linkedlist of results
  for(int i = 0; i <map->size; i++) {
    Tuple t = map->table[i]->content;
    while(t != NULL) {
      if(checkAttributes(t, num, attributes)) {
        if(results == NULL) {
          results = newTuple(t->numAttributes, t->tupleData, t->tupleKey);
          current = results;
        }
        else {
          current->next = newTuple(t->numAttributes, t->tupleData, t->tupleKey);
          current = current->next;
        }
      }
      t = t->next;
    }
  }
  if(results == NULL) {
    printf("No results\n");
    return NULL;
  }
  else {
    return results;
  }
}

void print_Tuple(Tuple t) {
  while(t != NULL) {
    for(int i = 0; i <t->numAttributes; i++) {
      if(i == 0) {
        printf("<%s,", t->tupleData[i]->data);
      }
      else if(i == t->numAttributes - 1) {
        printf(" %s>\n", t->tupleData[i]->data);
      }
      else {
        printf(" %s,", t->tupleData[i]->data);
      }
    }
    t = t->next;
  }
}
