#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "part1.h"
#include "HashMap.h"
#include "part3.h"
#include "part1num4.h"



//Example for CSG Database
Hashmap readCSG () {
  //Create a new hashmap
  Hashmap csgMap = Hashmap_new("CSG");
  FILE* readFile = fopen( "./FILES/readCSG.data", "r");
  //Create an array of 256 elements, this is where the data will be stored
  char data [256];
  //Atoi converts to int, fgets = reads from the line and stores it to the string 'data', with max character of 256, and from 'read file'
  int file = atoi(fgets(data, 256, readFile));

  int i = 0;
  //While there exists input in the file
  while(i < file){
    //Reads each of the inputs
    char* course = malloc(6*sizeof(char));
    fscanf(readFile, "%s", course);

    char* studentID = malloc(6*sizeof(char));
    fscanf(readFile, "%s", studentID);

    char* grade = malloc(3*sizeof(char));
    fscanf(readFile, "%s", grade);

    insert_CSG(course, studentID, grade, csgMap);

    i++;
  }
  //Close File
  fclose(readFile);
  //Return Hashmap
  return csgMap;
}

//Example for CSG Database
Hashmap readSNAP () {
  //Create a new hashmap
  Hashmap snapMap = Hashmap_new("SNAP");
  FILE* readFile = fopen( "./FILES/readSNAP.data", "r");
  //Create an array of 256 elements, this is where the data will be stored
  char data [256];
  //Atoi converts to int, fgets = reads from the line and stores it to the string 'data', with max character of 256, and from 'read file'
  int file = atoi(fgets(data, 256, readFile));

  int i = 0;
  //While there exists input in the file
  while(i < file){
    //Reads each of the inputs
    char* studentID = malloc(6*sizeof(char));
    fscanf(readFile, "%s", studentID);

    char* name = malloc(256*sizeof(char));
    fscanf(readFile, "%256[0-9a-zA-z. ], ", name);

    char* address = malloc(64*sizeof(char));
    fscanf(readFile, "%256[0-9a-zA-z. ], ", address);

    char* phone = malloc(20*sizeof(char));
    fscanf(readFile, "%s", phone);

    insert_SNAP(studentID, name, address, phone, snapMap);

    i++;
  }
  //Close File
  fclose(readFile);
  //Return Hashmap
  return snapMap;
}

//Example for CSG Database
Hashmap readCP () {
  //Create a new hashmap
  Hashmap cpMap = Hashmap_new("CP");
  FILE* readFile = fopen( "./FILES/readCP.data", "r");
  //Create an array of 256 elements, this is where the data will be stored
  char data [256];
  //Atoi converts to int, fgets = reads from the line and stores it to the string 'data', with max character of 256, and from 'read file'
  int file = atoi(fgets(data, 256, readFile));

  int i = 0;
  //While there exists input in the file
  while(i < file){
    //Reads each of the inputs
    char* course = malloc(10*sizeof(char));
    fscanf(readFile, "%s", course);

    char* prereq = malloc(10*sizeof(char));
    fscanf(readFile, "%s", prereq);


    insert_CP(course, prereq, cpMap);

    i++;
  }
  //Close File
  fclose(readFile);
  //Return Hashmap
  return cpMap;
}
//Example for CDH Database
Hashmap readCDH () {
  //Create a new hashmap
  Hashmap cdhMap = Hashmap_new("CDH");
  FILE* readFile = fopen( "./FILES/readCDH.data", "r");
  //Create an array of 256 elements, this is where the data will be stored
  char data [256];
  //Atoi converts to int, fgets = reads from the line and stores it to the string 'data', with max character of 256, and from 'read file'
  int file = atoi(fgets(data, 256, readFile));

  int i = 0;
  //While there exists input in the file
  while(i < file){
    //Reads each of the inputs
    char* course = malloc(6*sizeof(char));
    fscanf(readFile, "%s", course);

    char* day = malloc(6*sizeof(char));
    fscanf(readFile, "%s", day);

    char* hour = malloc(3*sizeof(char));
    fscanf(readFile, "%s", hour);

    insert_CDH(course, day, hour, cdhMap);

    i++;
  }
  //Close File
  fclose(readFile);
  //Return Hashmap
  return cdhMap;
}
//Example for CSG Database
Hashmap readCR () {
  //Create a new hashmap
  Hashmap crMap = Hashmap_new("CR");
  FILE* readFile = fopen( "./FILES/readCR.data", "r");
  //Create an array of 256 elements, this is where the data will be stored
  char data [256];
  //Atoi converts to int, fgets = reads from the line and stores it to the string 'data', with max character of 256, and from 'read file'
  int file = atoi(fgets(data, 256, readFile));

  int i = 0;
  //While there exists input in the file
  while(i < file){
    //Reads each of the inputs
    char* course = malloc(6*sizeof(char));
    fscanf(readFile, "%s", course);

    char* room = malloc(3*sizeof(char));
    fscanf(readFile, "%256[0-9a-zA-z. ]", room);

    insert_CR(course, room, crMap);

    i++;
  }
  //Close File
  fclose(readFile);
  //Return Hashmap
  return crMap;
}

void writeCSG(Hashmap csgMap){
  FILE* writeFile = fopen( "./FILES/writeCSG.data", "w");
  //Number of tuples (rows) present within the table
  int tupleNumber = csgMap -> tupleNumber;
  fprintf(writeFile, "%d\n", tupleNumber);
  //Iterates through the hashmap and stores the course, id, and grade
  for(int i = 0; i< csgMap-> size; i++){
    CSG csg = csgMap ->table[i]->content;
      while(csg != NULL) {
        char* course = csg -> course;
        char* studentID = csg -> studentID;
        char* grade = csg -> grade;
        //Prints out the course, id, and grade,
        fprintf(writeFile, "%s %s %s\n", course, studentID, grade);
        //Goes to the next node
        csg = csg -> next;
      }
  }
  //Closes file
  fclose(writeFile);
}


void writeSNAP(Hashmap snapMap){
  FILE* writeFile = fopen( "./FILES/writeSNAP.data", "w");
  //Number of tuples (rows) present within the table
  int tupleNumber = snapMap -> tupleNumber;
  fprintf(writeFile, "%d\n", tupleNumber);
  //Iterates through the hashmap and stores the course, id, and grade
  for(int i = 0; i< snapMap-> size; i++){
    SNAP snap = snapMap ->table[i]->content;
      while(snap != NULL) {
        char* studentID = snap -> studentID;
        char* name = snap -> name;
        char* address = snap -> address;
        char* phone = snap -> phone;

        //Prints out the course, id, and grade,
        fprintf(writeFile, "%s %s, %s,  %s\n", studentID, name, address, phone);
        //Goes to the next node
        snap = snap -> next;
      }
  }
  //Closes file
  fclose(writeFile);
}

void writeCP(Hashmap cpMap){
  FILE* writeFile = fopen( "./FILES/writeCP.data", "w");
  //Number of tuples (rows) present within the table
  //printf("%d\n", cpMap->tupleNumber);
  int tupleNumber = cpMap -> tupleNumber;
  fprintf(writeFile, "%d\n", tupleNumber);
  //Iterates through the hashmap and stores the course, id, and grade
  for(int i = 0; i< cpMap-> size; i++){
    CP cp = cpMap ->table[i]->content;
      while(cp != NULL) {
        char* course = cp-> course;
        char* prereq = cp -> prereq;

        //Prints out the course, id, and grade,
        fprintf(writeFile, "%s %s\n", course, prereq);
        //Goes to the next node
        cp = cp -> next;
      }
  }
  //Closes file
  fclose(writeFile);
}

void writeCDH(Hashmap cdhMap){
  FILE* writeFile = fopen( "./FILES/writeCDH.data", "w");
  //Number of tuples (rows) present within the table
  int tupleNumber = cdhMap -> tupleNumber;
  fprintf(writeFile, "%d\n", tupleNumber);
  //Iterates through the hashmap and stores the course, id, and grade
  for(int i = 0; i< cdhMap-> size; i++){
    CDH cdh = cdhMap ->table[i]->content;
      while(cdh != NULL) {
        char* course = cdh-> course;
        char* day = cdh -> day;
        char* hour = cdh -> hour;

        //Prints out the course, id, and grade,
        fprintf(writeFile, "%s %s %s\n", course, day, hour);
        //Goes to the next node
        cdh = cdh -> next;
      }
  }
  //Closes file
  fclose(writeFile);
}


void writeCR(Hashmap crMap){
  FILE* writeFile = fopen( "./FILES/writeCR.data", "w");
  //Number of tuples (rows) present within the table
  int tupleNumber = crMap -> tupleNumber;
  fprintf(writeFile, "%d\n", tupleNumber);
  //Iterates through the hashmap and stores the course, id, and grade
  for(int i = 0; i< crMap-> size; i++){
    CR cr = crMap ->table[i]->content;
      while(cr != NULL) {
        char* course = cr-> course;
        char* room = cr -> room;

        //Prints out the course, id, and grade,
        fprintf(writeFile, "%s %s\n", course, room);
        //Goes to the next node
        cr = cr -> next;
      }
  }
  //Closes file
  fclose(writeFile);
}
