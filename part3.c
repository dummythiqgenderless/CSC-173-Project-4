#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "HashMap.h"
#include "part1.h"
#include "part3.h"

//8.12 Example =  Extract all CS101 Classes using the selection operator
//SELECTION

//Selection Operator Example
Hashmap selectionCSG(Hashmap csgMap, char *c){
  //Hashmap to add the new set of tuples too
  Hashmap selection = Hashmap_new("CSG");
  //Condition C to test if the scheme contains such or not
  char* condition = c;
  //Iterate through the tuples
  for(int i = 0; i < csgMap -> size; i++){
    //While CSG is not NULL
    if(csgMap->table[i]->content != NULL) {
      CSG csg = csgMap ->table[i]->content;
      while(csg != NULL) {
        //If the courses match, then add it to the hashmap
        if(strcmp(csg->course, condition) == 0){
        //Save each element's course, student ID, and grade
        char* course = csg->course;
        char* studentID = csg->studentID;
        char* grade = csg->grade;
        //Insert it into the hashmap
        insert_CSG(course, studentID, grade, selection);
        }
        csg = csg->next;
      }
    }
  }

  return selection;
}

//8.13 Example = See only the student ID for the students who are taking CS101
//PROJECTION

//Create a struct called student ID that is an linked list
StudentID ID_new(char *id) {
  StudentID stuID = (StudentID) malloc(sizeof(struct StudentID));
  stuID->id = id;

  stuID-> next = NULL;

  return stuID;
}

void print_IDs(StudentID t) {
  while(t != NULL) {
    printf("<%s>\n", t->id);
    t = t->next;
  }
}

//Projection Function
StudentID projectionCSG_ID(Hashmap csgMap){
  StudentID current;
  StudentID proj = NULL;
  //Condition C to test if the scheme contains such or not
  //char* condition = c;
  //Iterate through the tuples
  for(int i = 0; i < csgMap -> size; i++){
    //While CSG is not NULL
    if(csgMap->table[i]->content != NULL) {
      CSG csg = csgMap ->table[i]->content;
      while(csg != NULL) {
        //printf("%s\n", csg->studentID);
        //If the courses match, then add it to the studentID struct
        //if(strcmp(csg->course, condition) == 0){
        //Save the student id
        char* studentID = csg->studentID;
        //Create a new student ID
        if(proj == NULL) {
          proj = ID_new(studentID);
          current = proj;
        }
        else {
          int duplicate = 0;
          StudentID test = proj;
          while(test->next != NULL) {
            if(strcmp(test->id, studentID) == 0) {
              //printf("no %s\n", csg->studentID);
              duplicate = 1;
            }
            test = test->next;
          }
          if(strcmp(test->id, studentID) == 0) {
            //printf("no %s\n", csg->studentID);
            duplicate = 1;
          }

          if(duplicate == 0) {
            current->next = ID_new(studentID);
            current = current->next;
          }
        }
      //  }
        csg = csg->next;
      }
    }
  }

  return proj;
}

//8.14- what times each room is occupied by some course with the relations CR and CDH
//JOIN

//Initializer for struct
CRDH CRDH_new (char* course, char* room, char* day, char* hour){
  //Allocate space
  CRDH crdh = (CRDH) malloc(sizeof(struct CRDH));

  crdh -> course = course;
  crdh -> room = room;
  crdh -> day = day;
  crdh -> hour = hour;

  crdh -> next = NULL;
  crdh->prev = NULL;

  return crdh;
}

void print_CRDH(CRDH t) {
  while(t != NULL) {
    printf("<%s, %s, %s, %s>\n", t->course, t->room, t->day, t->hour);
    t = t->next;
  }
}

void insert_CRDH(char *course, char *room, char *day, char *hour, Hashmap map) {
  CRDH crdh = CRDH_new(course, room, day, hour);
  char keystring[5];
  strcpy(keystring, course);

  int index = hashFunction(keystring, map);

  if(map->table[index]->content == NULL) {  //empty bucket
    map->table[index]->content = crdh;
  } else { //not empty
    CRDH current = map->table[index]->content;
    while(current->next != NULL) {
      current = current->next;
    }
    crdh->prev = current;
    current->next = crdh;
  }
}


//Join function for the CR and CDH relation
Hashmap joinCRDH (Hashmap crMap, Hashmap cdhMap){
  //Create a Hashmap
  Hashmap crdhHashmap = Hashmap_new("CRDH");

  for(int i = 0; i < crMap -> size; i++){
    //While CR is not NULL
    if(crMap->table[i]->content != NULL) {
      CR cr = crMap ->table[i]->content;
      while(cr != NULL){
        for (int i = 0; i < cdhMap -> size; i++){
          //While CDH is not NULL
          if(cdhMap->table[i]->content != NULL) {
            CDH cdh = cdhMap ->table[i]->content;
            while(cdh != NULL){
              //If the courses match
              if(strcmp(cr -> course, cdh -> course) == 0){
                //Save each element's course, student ID, and grade
                char* course = cr->course;
                char* room = cr -> room;
                char* day = cdh -> day;
                char* hour = cdh-> hour;

                insert_CRDH(course, room, day, hour, crdhHashmap);
              }
              cdh = cdh->next;
            }
          }
        }
        cr = cr->next;
      }
    }
  }
  return crdhHashmap;
}

//#8.15- Only see the Day and Hour of the CRDH relation

//Struct for the day and the hour
dayHour dayHour_new(char *day, char *hour) {
  dayHour dh = (dayHour) malloc(sizeof(struct dayHour));
  dh -> day = day;
  dh -> hour = hour;

  dh -> next = NULL;

  return dh;
}


//All operators
dayHour allOperators(Hashmap crdhMap, char* condition){
  //Create a hashmap
  //Hashmap alloptHashmap = Hashmap_new("All Operators");
  //Return list of day hour
  dayHour returnList = NULL;
  dayHour current;
  //iterate through the hashmap
  for(int i = 0; i < crdhMap -> size; i++){
    //While not null
    if(crdhMap->table[i]->content != NULL) {
      CRDH crdh = crdhMap ->table[i]->content;
      while(crdh != NULL){
        if(strcmp(crdh-> room, condition) == 0){
          char* day = crdh -> day;
          char* hour = crdh -> hour;
          //Moves to the next node
          if(returnList == NULL){
              returnList = dayHour_new(day, hour);
              current = returnList;
          } else {
            current -> next = dayHour_new(day, hour);
            current = current -> next;
          }

          }
          crdh = crdh -> next;
        }
      }
    }
    return returnList;
  }

//Print function
void print_dayHour(dayHour t) {
  while(t != NULL) {
    printf("<%s, %s>\n", t->day, t->hour);
    t = t->next;
  }
}
