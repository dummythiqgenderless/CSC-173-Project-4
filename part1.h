#ifndef _part1_h
#define _part1_h
#include <stdbool.h>
#include "HashMap.h"


typedef struct CSG *CSG;
struct CSG {
  char *course;
  char *studentID;
  char *grade;
  CSG next;
  CSG prev;
};

typedef struct SNAP *SNAP;
struct SNAP {
  char *studentID;
  char *name;
  char *address;
  char *phone;
  SNAP next;
  SNAP prev;
};

typedef struct CP *CP;
struct CP {
  char *course;
  char *prereq;
  CP next;
  CP prev;
};

typedef struct CDH *CDH;
struct CDH {
  char *course;
  char *day;
  char *hour;
  CDH next;
  CDH prev;
};

typedef struct CR *CR;
struct CR {
  char *course;
  char *room;
  CR next;
  CR prev;
};

extern void insert_CSG(char *course, char *studentID, char *grade, Hashmap map);
extern void insert_SNAP(char *studentID, char *name, char *address, char *phone, Hashmap map);
extern void insert_CP(char *course, char *prereq, Hashmap map);
extern void insert_CDH(char *course, char *day, char *hour, Hashmap map);
extern void insert_CR(char *course, char *room, Hashmap map);

extern void delete_CSG(char *course, char *studentID, char *grade, Hashmap map);
extern void delete_SNAP(char *studentID, char *name, char *address, char *phone, Hashmap map);
extern void delete_CP(char *course, char *prereq, Hashmap map);
extern void delete_CDH(char *course, char *day, char *hour, Hashmap map);
extern void delete_CR(char *course, char *room, Hashmap map);

extern CSG lookup_CSG(char *course, char *studentID, char *grade, Hashmap map);
extern SNAP lookup_SNAP(char *studentID, char *name, char *address, char *phone, Hashmap map);
extern CP lookup_CP(char *course, char *prereq, Hashmap map);
extern CDH lookup_CDH(char *course, char *day, char *hour, Hashmap map);
extern CR lookup_CR(char *course, char *room, Hashmap map);

extern void printTable(Hashmap hashmap);
extern void print_CSG(CSG csg);
extern void print_SNAP(SNAP t);
extern void print_CP(CP t);
extern void print_CDH(CDH t);
extern void print_CR(CR t);

#endif
