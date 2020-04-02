#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "part1.h"
#include "HashMap.h"
#include "part3.h"
#include "genericTuple.h"
//#include "LinkedList.h"
//#include "genericTuple.h"

//Course-Student-Grade
typedef struct CSG *CSG;

CSG CSG_new(char *course, char *studentID, char *grade) {
  CSG csg = (CSG) malloc(sizeof(struct CSG));
  //csg->course = (char*) malloc(5*sizeof(char));
  csg->studentID = studentID;
  csg->course = course;
  csg->grade = grade;

  // strcpy(csg->course, course);
  // strcpy(csg->studentID, studentID);
  // //csg->grade = (char*) malloc(2*sizeof(char));
  // strcpy(csg->grade, grade);

  csg->next = NULL;
  csg->prev = NULL;

  return csg;
}

//Print function for CSG struct
void print_CSG(CSG csg){
  while(csg != NULL) {
    printf("<%s, %s, %s>\n", csg->course, csg->studentID, csg->grade);
    csg = csg->next;
  }
}

//Student-Name-Address-Phone
typedef struct SNAP *SNAP;

SNAP SNAP_new(char *studentID, char *name, char *address, char *phone) {
  SNAP snap = (SNAP) malloc(sizeof(struct SNAP));
  snap->studentID = studentID;
  snap->name = name;
  snap->address = address;
  snap->phone = phone;
  snap->next = NULL;
  snap->prev = NULL;

  return snap;
}

void print_SNAP(SNAP t){
  while(t != NULL) {
    printf("<%s, %s, %s, %s>\n", t->studentID, t->name, t->address, t->phone);
    t = t->next;
  }
}

//Course-prereq
typedef struct CP *CP;

CP CP_new(char *course, char *prereq) {
  CP cp = (CP) malloc(sizeof(struct CP));
  cp->course = course;
  cp->prereq = prereq;
  cp->next = NULL;
  cp->prev = NULL;

  return cp;
}

void print_CP(CP t){
  while(t != NULL) {
    printf("<%s, %s>\n", t->course, t->prereq);
    t = t->next;
  }
}

//Course-Day-Hour
typedef struct CDH *CDH;

CDH CDH_new(char *course, char* day, char* hour) {
  CDH cdh = (CDH) malloc(sizeof(struct CDH));
  cdh->course = course;
  cdh->day = day;
  cdh->hour = hour;
  cdh->next = NULL;
  cdh->prev = NULL;

  return cdh;
}

void print_CDH(CDH t){
  while(t != NULL) {
    printf("<%s, %s, %s>\n", t->course, t->day, t->hour);
    t = t->next;
  }
}

//Course-Room
typedef struct CR *CR;

CR CR_new(char *course, char *room) {
  CR cr = (CR) malloc(sizeof(struct CR));
  cr->course = course;
  cr->room = room;
  cr->next = NULL;
  cr->prev = NULL;

  return cr;
}

void print_CR(CR t){
  while(t != NULL) {
    printf("<%s, %s>\n", t->course, t->room);
    t = t->next;
  }
}

//part b

//INSERTION METHODS
void insert_CSG(char *course, char *studentID, char *grade, Hashmap map) {
  //Create a tuple for the entered information
  CSG csg = CSG_new(course, studentID, grade);
  //printf("%s\n", csg->course);
  char keystring[10];
  strcpy(keystring, course);
  strcat(keystring, studentID);

  //array indexx in the hashmap
  int index = hashFunction(keystring, map);

  /*check if the bucket at the index if empty
  if it is, put tuple in the bucket
  if not, add it to the end of the linked list at the bucket
  */
  Bucket b = map->table[index];
  if(b->content == NULL) {  //empty bucket
    b->content = csg;
    // LinkedList list = LinkedList_new();
    // LinkedList_add_at_end(list, csg);
  } else { //not empty
    CSG current = b->content;
    while(current->next != NULL) {
      current = current->next;
    }
    csg->prev = current;
    current->next = csg;
    // LinkedList list = map->table[index];
    // CSG tail = list->last->data;
    // tail->next = csg;
    // LinkedList_add_at_end(list, csg);
  }
  map->tupleNumber = map->tupleNumber + 1;
}

void insert_SNAP(char *studentID, char *name, char *address, char *phone, Hashmap map) {
  SNAP snap = SNAP_new(studentID, name, address, phone);
  int index = hashFunction(studentID, map);

  if(map->table[index]->content == NULL) {  //empty bucket
    map->table[index]->content = snap;
  } else { //not empty
    SNAP current = map->table[index]->content;
    while(current->next != NULL) {
      current = current->next;
    }
    snap->prev = current;
    current->next = snap;
  }
  map->tupleNumber = map->tupleNumber + 1;
}

void insert_CP(char *course, char *prereq, Hashmap map) {
  CP cp = CP_new(course, prereq);
  char keystring[10];
  strcpy(keystring, course);
  strcat(keystring, prereq);

  int index = hashFunction(keystring, map);

  if(map->table[index]->content == NULL) {  //empty bucket
    map->table[index]->content = cp;
  } else { //not empty
    CP current = map->table[index]->content;
    while(current->next != NULL) {
      current = current->next;
    }
    cp->prev = current;
    current->next = cp;
  }
  map->tupleNumber = map->tupleNumber + 1;
  //printf("%d\n", map->tupleNumber);
}

void insert_CDH(char *course, char *day, char *hour, Hashmap map) {
  CDH cdh = CDH_new(course, day, hour);
  char keystring[5];
  strcpy(keystring, course);

  int index = hashFunction(keystring, map);

  if(map->table[index]->content == NULL) {  //empty bucket
    map->table[index]->content = cdh;
  } else { //not empty
    CDH current = map->table[index]->content;
    while(current->next != NULL) {
      current = current->next;
    }
    cdh->prev = current;
    current->next = cdh;
  }

  map->tupleNumber = map->tupleNumber + 1;
}

void insert_CR(char *course, char *room, Hashmap map) {
  CR cr = CR_new(course, room);
  int index = hashFunction(course, map);

  if(map->table[index]->content == NULL) {  //empty bucket
    map->table[index]->content = cr;
  } else { //not empty
    CR current = map->table[index]->content;
    while(current->next != NULL) {
      current = current->next;
    }
    cr->prev = current;
    current->next = cr;
  }
  map->tupleNumber = map->tupleNumber + 1;
}

//make insert methods for the rest of the relations

void delete_CSG(char *course, char *studentID, char *grade, Hashmap map) {
  //if primary indexing case -- shorter runtime (usually constant)
  if(grade[0] == '*' && course[0] != '*' && studentID[0] != '*') {
    char keystring[10];
    strcpy(keystring, course);
    strcat(keystring, studentID);
    int index = hashFunction(keystring, map);

    if(map->table[index]->content == NULL) {
      return;
    }
    CSG csg = map->table[index]->content; // first node in bucket
    while(csg != NULL) {//iterate through linkedlist
      // check if the articular tuple is one of the specified ones for deletion
      if((strcmp(csg->course, course) == 0 || course[0] == '*') //strcmp checks if strings are equal
      && (strcmp(csg->studentID, studentID) == 0 || studentID[0] == '*')
      && (strcmp(csg->grade, grade) == 0 || grade[0] == '*')){
        //printf("delete!");
        /*different cases for deletion of specified csg*/
        //the first csg in the linkedlist (the csg is the only thing in the bucket)
        if(csg->prev == NULL && csg->next == NULL){
          map->table[index]->content = NULL;
          //csg -> prev = csg;
          csg = csg->next;
        }
        //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
        else if(csg->prev == NULL && csg->next != NULL){
          map->table[index]->content = csg->next;
          csg->next->prev = NULL;
          csg = csg->next;
        }
        //Reached the last csg in the linkedlist
        else if(csg->prev != NULL && csg->next == NULL){
          csg->prev->next = NULL;
          csg = csg->next;
        }
        //csg is in the middle of the linked list
        else {
          csg->next->prev = csg->prev;
          csg->prev->next = csg->next;
          csg = csg->next;
        }
      }
      else {
        csg = csg->next;
      }
    }

    //index
  }
  // else search through table to delete (longer runtime)
  else {
  for(int i = 0; i < map->size; i++){
    if(map->table[i]->content != NULL){
      CSG csg = map->table[i]->content; // first node in bucket
      while(csg != NULL) {
        // check if the articular tuple is one of the specified ones for deletion
        if((strcmp(csg->course, course) == 0 || course[0] == '*') //strcmp checks if strings are equal
        && (strcmp(csg->studentID, studentID) == 0 || studentID[0] == '*')
        && (strcmp(csg->grade, grade) == 0 || grade[0] == '*')){
          //printf("delete!");
          /*different cases for deletion of specified csg*/
          //the first csg in the linkedlist (the csg is the only thing in the bucket)
          if(csg->prev == NULL && csg->next == NULL){
            map->table[i]->content = NULL;
            //csg -> prev = csg;
            csg = csg->next;
          }
          //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
          else if(csg->prev == NULL && csg->next != NULL){
            map->table[i]->content = csg->next;
            csg->next->prev = NULL;
            csg = csg->next;
          }
          //Reached the last csg in the linkedlist
          else if(csg->prev != NULL && csg->next == NULL){
            csg->prev->next = NULL;
            csg = csg->next;
          }
          //csg is in the middle of the linked list
          else {
            csg->next->prev = csg->prev;
            csg->prev->next = csg->next;
            csg = csg->next;
          }
        }
        else {
          csg = csg->next;
        }
      }
    }
  }
  }
}

void delete_SNAP(char *studentID, char *name, char *address, char *phone, Hashmap map) {
  //if primary indexing case -- shorter runtime (usually constant)
  if(studentID[0] != '*' && name[0] == '*' && address[0] == '*' && phone[0] == '*') {
    int index = hashFunction(studentID, map);

    if(map->table[index]->content == NULL) {
      printf("no");
      return;
    }
    SNAP snap = map->table[index]->content; // first node in bucket
    while(snap != NULL) {
      // check if the articular tuple is one of the specified ones for deletion
      if((strcmp(snap->name, name) == 0 || name[0] == '*') //strcmp checks if strings are equal
      && (strcmp(snap->studentID, studentID) == 0 || studentID[0] == '*')
      && (strcmp(snap->address, address) == 0 || address[0] == '*')
      && (strcmp(snap->phone, phone) == 0 || phone[0] == '*')){
        //printf("delete!");
        /*different cases for deletion of specified csg*/
        //the first csg in the linkedlist (the csg is the only thing in the bucket)
        if(snap->prev == NULL && snap->next == NULL){
          map->table[index]->content = NULL;
          //csg -> prev = csg;
          snap = snap->next;
        }
        //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
        else if(snap->prev == NULL && snap->next != NULL){
          map->table[index]->content = snap->next;
          snap->next->prev = NULL;
          snap = snap->next;
        }
        //Reached the last csg in the linkedlist
        else if(snap->prev != NULL && snap->next == NULL){
          snap->prev->next = NULL;
          snap = snap->next;
        }
        //csg is in the middle of the linked list
        else {
          snap->next->prev = snap->prev;
          snap->prev->next = snap->next;
          snap = snap->next;
        }
      }
      else {
        snap = snap->next;
      }
    }

  }
  else {
  for(int i = 0; i < map->size; i++){
    if(map->table[i]->content != NULL){
      SNAP snap = map->table[i]->content; // first node in bucket
      while(snap != NULL) {
        // check if the articular tuple is one of the specified ones for deletion
        if((strcmp(snap->name, name) == 0 || name[0] == '*') //strcmp checks if strings are equal
        && (strcmp(snap->studentID, studentID) == 0 || studentID[0] == '*')
        && (strcmp(snap->address, address) == 0 || address[0] == '*')
        && (strcmp(snap->phone, phone) == 0 || phone[0] == '*')){
          //printf("delete!");
          /*different cases for deletion of specified csg*/
          //the first csg in the linkedlist (the csg is the only thing in the bucket)
          if(snap->prev == NULL && snap->next == NULL){
            map->table[i]->content = NULL;
            //csg -> prev = csg;
            snap = snap->next;
          }
          //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
          else if(snap->prev == NULL && snap->next != NULL){
            map->table[i]->content = snap->next;
            snap->next->prev = NULL;
            snap = snap->next;
          }
          //Reached the last csg in the linkedlist
          else if(snap->prev != NULL && snap->next == NULL){
            snap->prev->next = NULL;
            snap = snap->next;
          }
          //csg is in the middle of the linked list
          else {
            snap->next->prev = snap->prev;
            snap->prev->next = snap->next;
            snap = snap->next;
          }
        }
        else {
          snap = snap->next;
        }
      }
    }
  }
}
}

void delete_CP(char *course, char *prereq, Hashmap map) {
  //if primary indexing case -- shorter runtime (usually constant)
  if(course[0] != '*' && prereq[0] != '*') {
    char keystring[10];
    strcpy(keystring, course);
    strcat(keystring, prereq);
    int index = hashFunction(keystring, map);

    if(map->table[index]->content != NULL){
      CP cp = map->table[index]->content; // first node in bucket
      while(cp != NULL) {
        // check if the articular tuple is one of the specified ones for deletion
        if((strcmp(cp->course, course) == 0 || course[0] == '*') //strcmp checks if strings are equal
        && (strcmp(cp->prereq, prereq) == 0 || prereq[0] == '*')){
          //printf("delete!");
          /*different cases for deletion of specified csg*/
          //the first csg in the linkedlist (the csg is the only thing in the bucket)
          if(cp->prev == NULL && cp->next == NULL){
            map->table[index]->content = NULL;
            //csg -> prev = csg;
            cp = cp->next;
          }
          //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
          else if(cp->prev == NULL && cp->next != NULL){
            map->table[index]->content = cp->next;
            cp->next->prev = NULL;
            cp = cp->next;
          }
          //Reached the last csg in the linkedlist
          else if(cp->prev != NULL && cp->next == NULL){
            cp->prev->next = NULL;
            cp = cp->next;
          }
          //csg is in the middle of the linked list
          else {
            cp->next->prev = cp->prev;
            cp->prev->next = cp->next;
            cp = cp->next;
          }
        }
        else {
          cp = cp->next;
        }
      }
    }
  }
  else {
  for(int i = 0; i < map->size; i++){
    if(map->table[i]->content != NULL){
      CP cp = map->table[i]->content; // first node in bucket
      while(cp != NULL) {
        // check if the articular tuple is one of the specified ones for deletion
        if((strcmp(cp->course, course) == 0 || course[0] == '*') //strcmp checks if strings are equal
        && (strcmp(cp->prereq, prereq) == 0 || prereq[0] == '*')){
          //printf("delete!");
          /*different cases for deletion of specified csg*/
          //the first csg in the linkedlist (the csg is the only thing in the bucket)
          if(cp->prev == NULL && cp->next == NULL){
            map->table[i]->content = NULL;
            //csg -> prev = csg;
            cp = cp->next;
          }
          //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
          else if(cp->prev == NULL && cp->next != NULL){
            map->table[i]->content = cp->next;
            cp->next->prev = NULL;
            cp = cp->next;
          }
          //Reached the last csg in the linkedlist
          else if(cp->prev != NULL && cp->next == NULL){
            cp->prev->next = NULL;
            cp = cp->next;
          }
          //csg is in the middle of the linked list
          else {
            cp->next->prev = cp->prev;
            cp->prev->next = cp->next;
            cp = cp->next;
          }
        }
        else {
          cp = cp->next;
        }
      }
    }
  }
}
}

void delete_CDH(char *course, char *day, char *hour, Hashmap map) {
  if(course[0] != '*' && day[0] == '*' && hour[0] == '*') {
    int index = hashFunction(course, map);
    if(map->table[index]->content != NULL){
      CDH cdh = map->table[index]->content; // first node in bucket
      while(cdh != NULL) {
        // check if the articular tuple is one of the specified ones for deletion
        if((strcmp(cdh->course, course) == 0 || course[0] == '*') //strcmp checks if strings are equal
        && (strcmp(cdh->day, day) == 0 || day[0] == '*')
        && (strcmp(cdh->hour, hour) == 0 || hour[0] == '*')){
          //printf("delete!");
          /*different cases for deletion of specified csg*/
          //the first csg in the linkedlist (the csg is the only thing in the bucket)
          if(cdh->prev == NULL && cdh->next == NULL){
            map->table[index]->content = NULL;
            //csg -> prev = csg;
            cdh = cdh->next;
          }
          //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
          else if(cdh->prev == NULL && cdh->next != NULL){
            map->table[index]->content = cdh->next;
            cdh->next->prev = NULL;
            cdh = cdh->next;
          }
          //Reached the last csg in the linkedlist
          else if(cdh->prev != NULL && cdh->next == NULL){
            cdh->prev->next = NULL;
            cdh = cdh->next;
          }
          //csg is in the middle of the linked list
          else {
            cdh->next->prev = cdh->prev;
            cdh->prev->next = cdh->next;
            cdh = cdh->next;
          }
        }
        else {
          cdh = cdh->next;
        }
      }
    }
  } else {
  for(int i = 0; i < map->size; i++){
    if(map->table[i]->content != NULL){
      CDH cdh = map->table[i]->content; // first node in bucket
      while(cdh != NULL) {
        // check if the articular tuple is one of the specified ones for deletion
        if((strcmp(cdh->course, course) == 0 || course[0] == '*') //strcmp checks if strings are equal
        && (strcmp(cdh->day, day) == 0 || day[0] == '*')
        && (strcmp(cdh->hour, hour) == 0 || hour[0] == '*')){
          //printf("delete!");
          /*different cases for deletion of specified csg*/
          //the first csg in the linkedlist (the csg is the only thing in the bucket)
          if(cdh->prev == NULL && cdh->next == NULL){
            map->table[i]->content = NULL;
            //csg -> prev = csg;
            cdh = cdh->next;
          }
          //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
          else if(cdh->prev == NULL && cdh->next != NULL){
            map->table[i]->content = cdh->next;
            cdh->next->prev = NULL;
            cdh = cdh->next;
          }
          //Reached the last csg in the linkedlist
          else if(cdh->prev != NULL && cdh->next == NULL){
            cdh->prev->next = NULL;
            cdh = cdh->next;
          }
          //csg is in the middle of the linked list
          else {
            cdh->next->prev = cdh->prev;
            cdh->prev->next = cdh->next;
            cdh = cdh->next;
          }
        }
        else {
          cdh = cdh->next;
        }
      }
    }
  }
 }
}

void delete_CR(char *course, char *room, Hashmap map) {
  if(course[0] != '*' && room[0] == '*') {
    int index = hashFunction(course, map);
    if(map->table[index]->content != NULL){
      CR cr = map->table[index]->content; // first node in bucket
      while(cr != NULL) {
        // check if the articular tuple is one of the specified ones for deletion
        if((strcmp(cr->course, course) == 0 || course[0] == '*') //strcmp checks if strings are equal
        && (strcmp(cr->room, room) == 0 || room[0] == '*')){
          //printf("delete!");
          /*different cases for deletion of specified csg*/
          //the first csg in the linkedlist (the csg is the only thing in the bucket)
          if(cr->prev == NULL && cr->next == NULL){
            map->table[index]->content = NULL;
            //csg -> prev = csg;
            cr = cr->next;
          }
          //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
          else if(cr->prev == NULL && cr->next != NULL){
            map->table[index]->content = cr->next;
            cr->next->prev = NULL;
            cr = cr->next;
          }
          //Reached the last csg in the linkedlist
          else if(cr->prev != NULL && cr->next == NULL){
            cr->prev->next = NULL;
            cr = cr->next;
          }
          //csg is in the middle of the linked list
          else {
            cr->next->prev = cr->prev;
            cr->prev->next = cr->next;
            cr = cr->next;
          }
        }
        else {
          cr = cr->next;
        }
      }
    }
  } else {
  for(int i = 0; i < map->size; i++){
    if(map->table[i]->content != NULL){
      CR cr = map->table[i]->content; // first node in bucket
      while(cr != NULL) {
        // check if the articular tuple is one of the specified ones for deletion
        if((strcmp(cr->course, course) == 0 || course[0] == '*') //strcmp checks if strings are equal
        && (strcmp(cr->room, room) == 0 || room[0] == '*')){
          //printf("delete!");
          /*different cases for deletion of specified csg*/
          //the first csg in the linkedlist (the csg is the only thing in the bucket)
          if(cr->prev == NULL && cr->next == NULL){
            map->table[i]->content = NULL;
            //csg -> prev = csg;
            cr = cr->next;
          }
          //If the csg has a "next" csg -- csg is first and there are multiple elements in the linkedlist
          else if(cr->prev == NULL && cr->next != NULL){
            map->table[i]->content = cr->next;
            cr->next->prev = NULL;
            cr = cr->next;
          }
          //Reached the last csg in the linkedlist
          else if(cr->prev != NULL && cr->next == NULL){
            cr->prev->next = NULL;
            cr = cr->next;
          }
          //csg is in the middle of the linked list
          else {
            cr->next->prev = cr->prev;
            cr->prev->next = cr->next;
            cr = cr->next;
          }
        }
        else {
          cr = cr->next;
        }
      }
    }
  }
}
}

CSG lookup_CSG(char *course, char *studentID, char *grade, Hashmap map) {
  CSG csg;
  CSG current;
  CSG results = NULL; //return the linkedlist of results
  for(int i = 0; i <map->size; i++) {
    csg = map->table[i]->content;
    while(csg != NULL) {
      /*if it matches the specified tuple,
      add the tuple to the end of the lined list in the bucket of the hashmap */
      if((strcmp(csg->course, course) == 0 || course[0] == '*')
      && (strcmp(csg->studentID, studentID) == 0 || studentID[0] == '*')
      && (strcmp(csg->grade, grade) == 0 || grade[0] == '*')){
        if(results == NULL){
          results = CSG_new(csg->course, csg->studentID, csg->grade);
          current = results;
        }
        else { //add to the end of the list of current results
          current->next = CSG_new(csg->course, csg->studentID, csg->grade);
          current = current->next;
        }
      }
      csg = csg->next;
    }
  }
  if(results == NULL) {
    printf("No results\n");
  }
  return results;
}

SNAP lookup_SNAP(char *studentID, char *name, char *address, char *phone, Hashmap map) {
  SNAP snap;
  SNAP current;
  SNAP results = NULL; //return the linkedlist of results
  for(int i = 0; i <map->size; i++) {
    snap = map->table[i]->content;
    while(snap != NULL) {
      /*if it matches the specified tuple,
      add the tuple to the end of the lined list in the bucket of the hashmap */
      if((strcmp(snap->name, name) == 0 || name[0] == '*') //strcmp checks if strings are equal
      && (strcmp(snap->studentID, studentID) == 0 || studentID[0] == '*')
      && (strcmp(snap->address, address) == 0 || address[0] == '*')
      && (strcmp(snap->phone, phone) == 0 || phone[0] == '*')){
        if(results == NULL){
          results = SNAP_new(snap->studentID, snap->name, snap->address, snap->phone);
          current = results;
        }
        else { //add to the end of the list of current results
          current->next = SNAP_new(snap->studentID, snap->name, snap->address, snap->phone);
          current = current->next;
        }
      }
      snap = snap->next;
    }
  }
  if(results == NULL) {
    printf("No results\n");
  }
  return results;
}

CP lookup_CP(char *course, char *prereq, Hashmap map) {
  CP cp;
  CP current;
  CP results = NULL; //return the linkedlist of results
  for(int i = 0; i < map->size; i++) {
    cp = map->table[i]->content;
    while(cp != NULL) {
      /*if it matches the specified tuple,
      add the tuple to the end of the lined list in the bucket of the hashmap */
      if((strcmp(cp->course, course) == 0 || course[0] == '*')
      && (strcmp(cp->prereq, prereq) == 0 || prereq[0] == '*')){
        if(results == NULL){
          results = CP_new(cp->course, cp->prereq);
          current = results;
        }
        else { //add to the end of the list of current results
          current->next = CP_new(cp->course, cp->prereq);
          current = current->next;
        }
      }
      cp = cp->next;
    }
  }
  if(results == NULL) {
    printf("No results\n");
  }
  return results;
}

CDH lookup_CDH(char *course, char *day, char *hour, Hashmap map) {
  CDH cdh;
  CDH current;
  CDH results = NULL; //return the linkedlist of results
  for(int i = 0; i <map->size; i++) {
    cdh = map->table[i]->content;
    while(cdh != NULL) {
      /*if it matches the specified tuple,
      add the tuple to the end of the lined list in the bucket of the hashmap */
      if((strcmp(cdh->course, course) == 0 || course[0] == '*')
      && (strcmp(cdh->day, day) == 0 || day[0] == '*')
      && (strcmp(cdh->hour, hour) == 0 || hour[0] == '*')){
        if(results == NULL){
          results = CDH_new(cdh->course, cdh->day, cdh->hour);
          current = results;
        }
        else { //add to the end of the list of current results
          current->next = CDH_new(cdh->course, cdh->day, cdh->hour);
          current = current->next;
        }
      }
      cdh = cdh->next;
    }
  }
  if(results == NULL) {
    printf("No results\n");
  }
  return results;
}

CR lookup_CR(char *course, char *room, Hashmap map) {
  CR cr;
  CR current;
  CR results = NULL; //return the linkedlist of results
  for(int i = 0; i < map->size; i++) {
    cr = map->table[i]->content;
    while(cr != NULL) {
      /*if it matches the specified tuple,
      add the tuple to the end of the lined list in the bucket of the hashmap */
      if((strcmp(cr->course, course) == 0 || course[0] == '*')
      && (strcmp(cr->room, room) == 0 || room[0] == '*')){
        if(results == NULL){
          results = CR_new(cr->course, cr->room);
          current = results;
        }
        else { //add to the end of the list of current results
          current->next = CR_new(cr->course, cr->room);
          current = current->next;
        }
      }
      cr = cr->next;
    }
  }
  if(results == NULL) {
    printf("No results\n");
  }
  return results;
}

//Print function for hash table
void printTable(Hashmap map){
  //printf("%d", map->size);
  for(int i= 0; i < map->size; i++){
    if(map->table [i]->content == NULL) {
      //printf("no");
      continue;
    }
    if(strcmp(map->schema, "CSG") == 0) {
      //printf("yes");
      print_CSG(map->table[i]->content);
    }
    else if(strcmp(map->schema, "SNAP") == 0) {
      //printf("yes1");
      print_SNAP(map->table[i]->content);
    }
    else if(strcmp(map->schema, "CP") == 0) {
      //printf("yes2");
      print_CP(map->table[i]->content);
    }
    else if(strcmp(map->schema, "CDH") == 0) {
      //printf("yes3");
      print_CDH(map->table[i]->content);
    }
    else if(strcmp(map->schema, "CR") == 0) {
      //printf("yes4");
      print_CR(map->table[i]->content);
    }
    else if(strcmp(map->schema, "CRDH") == 0) {
      print_CRDH(map->table[i]->content);
    }
    else {
      print_Tuple(map->table[i]->content);
    }
  }

}
