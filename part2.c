#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "HashMap.h"
#include "part1.h"

//Grade for x student in x course
char* getGrade (Hashmap snapMap, Hashmap csgMap, char* name, char* courseName){

  char* returnGrade = NULL;

  //Iterates through the ID-Name-Address-Phone
  for(int i = 0; i < snapMap->size; i++){
    if(snapMap->table[i]->content != NULL) {
      SNAP snap = snapMap->table[i]->content;
      while(snap != NULL) {
        // printf("name: %s\n", snap->name);
        // int compare = strcmp(snap->name, name);
        // printf("same: %d\n", compare);

        //if names match
        if(strcmp(snap->name, name) == 0){
          //printf("student!\n");
          //Retrieve ID number
          char* id = snap->studentID;
          //if s has Course component “CS101” and StudentId component id then
          for(int i = 0; i < csgMap->size; i++){
            if(csgMap->table[i]->content != NULL) {
              CSG csg = csgMap->table[i]->content;
              while(csg != NULL) {
                // printf("course: %s\n", csg->course);
                // printf("ID: %s", csg->studentID);
                // printf(" matchID: %s\n", id);
                //
                // int compare1 = strcmp(csg->course, courseName);
                // printf("sameCourse: %d\n", compare1);
                // int compare2 = strcmp(csg->studentID, id);
                // printf("sameID: %d\n", compare2);

                if(strcmp(csg->course, courseName) == 0 && strcmp(csg->studentID, id) == 0){
                  // printf("graded!\n");
                  returnGrade = csg->grade;
                  break;
                  // printf("Student's Grade%s\n", csg-> table[i] -> content -> grade);
                }
                csg = csg->next;
              }

            }
          }
        }
        snap = snap->next;
      }

    }
  }
  return returnGrade;
}


//Where is StudentName at Time on Day?
char* getRoom(Hashmap snapMap, Hashmap csgMap, Hashmap cdhMap, Hashmap crMap, char* name, char* hour, char* day){

  char* returnRoom = NULL;

  //First find the student's ID through their name
  for(int i = 0; i < snapMap->size; i++){
    //If the names match
    if(snapMap->table[i]->content != NULL) {
      SNAP snap = snapMap->table[i]->content;
      while(snap != NULL) {
        // printf("student: %s\n", snap->name);
        // printf("inputname: %s\n", name);
        // int compare = strcmp(snap->name, name);
        // printf("same: %d\n", compare);

        if(strcmp(snap->name, name) == 0){
          //Retreve id number
          char* id = snap->studentID;
          //Find all students with the same student id 'id'
          for(int i = 0; i < csgMap-> size; i++){
            //If the ID matches
            if(csgMap->table[i]->content != NULL) {
              CSG csg = csgMap->table[i]->content;
              while(csg != NULL) {
                // printf("ID: %s\n", csg->studentID);
                // int compare1 = strcmp(csg->studentID, id);
                // printf("same: %d\n", compare1);

                if(strcmp(csg->studentID, id) == 0){
                  //Retrieve the courses for that student ID
                  char* course = csg->course;
                  //Iterates through the courses for the specific time and day
                  for(int i = 0; i < cdhMap->size; i++){
                    if(cdhMap->table[i]->content != NULL) {
                      CDH cdh = cdhMap->table[i]->content;
                      //iterate through linked list within the bucket
                      while(cdh != NULL) {
                        // printf("course: %s\n", cdh->course);
                        // int compare2 = strcmp(cdh->course, course);
                        // printf("same: %d\n", compare2);
                        //
                        // printf("hour: %s\n", cdh->hour);
                        // int compare3 = strcmp(cdh->hour, hour);
                        // printf("same: %d\n", compare3);
                        // printf("day: %s\n", cdh->day);
                        // int compare4 = strcmp(cdh->day, day);
                        // printf("same: %d\n", compare4);

                        if(strcmp(cdh->course, course) == 0){


                          //Retrieves the location of the student if the time and date correspond
                          for(int i = 0; i< crMap -> size; i++){
                            if(crMap->table[i]->content != NULL) {
                              CR cr = crMap->table[i]->content;
                              while(cr != NULL) {
                                if(strcmp(cr->course, course) == 0 && strcmp(cdh->hour, hour) == 0 && strcmp(cdh->day, day) == 0){
                                  returnRoom = cr->room;
                                  break;
                                }
                                cr = cr->next;

                              }

                            }
                          }
                        }
                        cdh = cdh->next;
                      }

                    }
                  }
                }
                csg = csg->next;
              }

            }
          }
        }
        snap = snap->next;
      }

    }
  }
  return returnRoom;
}
