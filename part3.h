#ifndef _part3_h
#define _part3_h
#include <stdbool.h>
#include "HashMap.h"


typedef struct StudentID *StudentID;
typedef struct CRDH *CRDH;
typedef struct dayHour *dayHour;

//Struct for student ID column
struct StudentID {
  char* id;
  StudentID next;
};

//Struct for CR and CDH relations
struct CRDH {
  char* course;
  char* room;
  char* day;
  char* hour;

  CRDH next;
  CRDH prev;
};

//Struct for day hour portion of CRDH
struct dayHour {
  char* day;
  char* hour;

  dayHour next;
};



extern Hashmap selectionCSG(Hashmap csg, char *c);
extern StudentID ID_new(char *id);
extern StudentID projectionCSG_ID(Hashmap csg);
extern dayHour allOperators(Hashmap crdhMap, char* condition);
extern void print_IDs(StudentID id);
extern void print_dayHour(dayHour t);

extern CRDH CRDH_new(char *course, char *room, char *day, char *hour);
extern void insert_CRDH(char *course, char *room, char *day, char *hour, Hashmap map);
extern void print_CRDH(CRDH t);
extern Hashmap joinCRDH(Hashmap cr, Hashmap cdh);

#endif
