#ifndef _part2_h
#define _part2_h
#include <stdbool.h>
#include "HashMap.h"

extern char* getGrade(Hashmap snap, Hashmap csg, char* name, char* courseName);
extern char* getRoom(Hashmap snap, Hashmap csg, Hashmap cdh, Hashmap cr, char* studentName, char* time, char* day);


#endif
