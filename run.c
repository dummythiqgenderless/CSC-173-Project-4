#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "HashMap.h"
#include "part1.h"
#include "part2.h"
#include "part3.h"
#include "genericTuple.h"
#include "part1num4.h"

/* For getting input from command line (in a way to include spaces)
getlin3 function was referenced from stckoverflow:
https://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in-c */
char * getlin3() {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

int main(int argc, char const *argv[]) {
  printf("*PART 1*\n");

  /*CSG Relation*/
  printf("\nInserting tuples (from Fig 8.1) into CSG: \n");

  Hashmap mapCSG = Hashmap_new("CSG");
  insert_CSG("CS101", "12345", "A", mapCSG);
  insert_CSG("CS101", "67890", "B", mapCSG);
  insert_CSG("EE200", "12345", "C", mapCSG);
  insert_CSG("EE200", "22222", "B+", mapCSG);
  insert_CSG("CS101", "33333", "A-", mapCSG);
  insert_CSG("PH100", "67890", "C+", mapCSG);

  printf("\nTable: \n");
  printf("schema: %s\n", mapCSG->schema);
  printTable(mapCSG);

  /*SNAP*/
  Hashmap mapSNAP = Hashmap_new("SNAP");
  insert_SNAP("12345", "C. Brown", "12 Apple St.", "555-1234", mapSNAP);
  insert_SNAP("67890", "L. Van Pelt", "34 Pear Ave.", "555-5678", mapSNAP);
  insert_SNAP("22222", "P. Patty", "56 Grape Blvd.", "555-9999", mapSNAP);
  printf("\nInserting into other tables: SNAP, CP, CDH, CR...\n");
  printf("\nschema: %s\n", mapSNAP->schema);
  printTable(mapSNAP);

  /*CP*/
  Hashmap mapCP = Hashmap_new("CP");
  insert_CP("CS101", "CS100", mapCP);
  insert_CP("EE200", "EE005", mapCP);
  insert_CP("EE200", "CS100", mapCP);
  insert_CP("CS120", "CS101", mapCP);
  insert_CP("CS121", "CS120", mapCP);
  insert_CP("CS205", "CS101", mapCP);
  insert_CP("CS206", "CS121", mapCP);
  insert_CP("CS206", "CS205", mapCP);
  printf("\nschema: %s\n", mapCP->schema);
  printTable(mapCP);

  /*CDH*/
  Hashmap mapCDH = Hashmap_new("CDH");
  insert_CDH("CS101", "M", "9AM", mapCDH);
  insert_CDH("CS101", "W", "9AM", mapCDH);
  insert_CDH("CS101", "F", "9AM", mapCDH);
  insert_CDH("EE200", "Tu", "10AM", mapCDH);
  insert_CDH("EE200", "W", "1PM", mapCDH);
  insert_CDH("EE200", "Th", "10AM", mapCDH);
  printf("\nschema: %s\n", mapCDH->schema);
  printTable(mapCDH);

  /*CR*/
  Hashmap mapCR = Hashmap_new("CR");
  insert_CR("CS101", "Turing Aud.", mapCR);
  insert_CR("EE200", "25 Ohm Hall", mapCR);
  insert_CR("PH100", "Newton Lab", mapCR);
  printf("\nschema: %s\n", mapCR->schema);
  printTable(mapCR);


  printf("\nEnter a number to do the delete and lookup functions");
  printf("\n1 for CSG, 2 for SNAP, 3 for CP, 4 for CDH, 5 for CR, 0 to move on: ");
  char *choice = getlin3();
  while(choice[0] != '0') {
    if(choice[0] == '1') {
      printf("\nCSG");
      printf("\nRemoving tuples from CSG: (ex. delete(<*, 12345, *>, R) ) \n");
      printf("Enter a course argument for removal (or * to not specify): ");
      char *courseD = getlin3();
      courseD[strlen(courseD)-1] = '\0';
      printf("Enter a student ID argument for removal (or *): ");
      char *idD = getlin3();
      idD[strlen(idD)-1] = '\0';
      printf("Enter a Grade argument for removal (or *): ");
      char *gradeD = getlin3();
      gradeD[strlen(gradeD)-1] = '\0';
      delete_CSG(courseD, idD, gradeD, mapCSG);

      printf("\nNew Table: \n");
      printf("schema: %s\n", mapCSG->schema);
      printTable(mapCSG);

      printf("\nLooking up: (ex. lookup(<CS101, *, *>, R) )\n");
      printf("Enter a course argument for lookup (or * to not specify): ");
      char *courseL = getlin3();
      courseL[strlen(courseL)-1] = '\0';
      printf("Enter a student ID argument for lookup (or *): ");
      char *idL = getlin3();
      idL[strlen(idL)-1] = '\0';
      printf("Enter a Grade argument for lookup (or *): ");
      char *gradeL = getlin3();
      gradeL[strlen(gradeL)-1] = '\0';
      CSG results = lookup_CSG(courseL, idL, gradeL, mapCSG);
      printf("Results: \n");
      print_CSG(results);

      printf("\nEnter a number to do the delete and lookup functions");
      printf("\n1 for CSG, 2 for SNAP, 3 for CP, 4 for CDH, 5 for CR, 0 to move on: ");
      choice = getlin3();
    }
    else if(choice[0] == '2') {
      printf("\nSNAP");
      printf("\nRemoving: \n");
      printf("Enter a studentID argument for removal (or * to not specify): ");
      char *idD = getlin3();
      idD[strlen(idD)-1] = '\0';
      printf("Enter a name argument for removal (or *): ");
      char *nameD = getlin3();
      nameD[strlen(nameD)-1] = '\0';
      printf("Enter an address argument for removal (or *): ");
      char *addressD = getlin3();
      addressD[strlen(addressD)-1] = '\0';
      printf("Enter a phone argument for removal (or *): ");
      char *phoneD = getlin3();
      phoneD[strlen(phoneD)-1] = '\0';
      delete_SNAP(idD, nameD, addressD, phoneD, mapSNAP);

      printf("\nNew Table: \n");
      printf("schema: %s\n", mapCSG->schema);
      printTable(mapSNAP);

      printf("\nLooking up:\n");
      printf("Enter a studentID argument (or * to not specify): ");
      char *idL = getlin3();
      idL[strlen(idL)-1] = '\0';
      printf("Enter a name argument (or *): ");
      char *nameL = getlin3();
      nameL[strlen(nameL)-1] = '\0';
      printf("Enter an address argument (or *): ");
      char *addressL = getlin3();
      addressL[strlen(addressL)-1] = '\0';
      printf("Enter a phone argument (or *): ");
      char *phoneL = getlin3();
      phoneL[strlen(phoneL)-1] = '\0';
      SNAP results = lookup_SNAP(idL, nameL, addressL, phoneL, mapSNAP);
      printf("Results: \n");
      print_SNAP(results);

      printf("\nEnter a number to do the delete and lookup functions");
      printf("\n1 for CSG, 2 for SNAP, 3 for CP, 4 for CDH, 5 for CR, 0 to move on: ");
      choice = getlin3();
    }
    else if(choice[0] == '3') {
      printf("\nCP");
      printf("\nRemoving: \n");
      printf("Enter a course argument (or * to not specify): ");
      char *courseD = getlin3();
      courseD[strlen(courseD)-1] = '\0';
      printf("Enter a prereq argument (or *): ");
      char *prereqD = getlin3();
      prereqD[strlen(prereqD)-1] = '\0';
      delete_CP(courseD, prereqD, mapCP);

      printf("\nNew Table: \n");
      printf("schema: %s\n", mapCSG->schema);
      printTable(mapCP);

      printf("\nLooking up:\n");
      printf("Enter a course argument (or * to not specify): ");
      char *courseL = getlin3();
      courseL[strlen(courseL)-1] = '\0';
      printf("Enter a prereq argument (or *): ");
      char *prereqL = getlin3();
      prereqL[strlen(prereqL)-1] = '\0';
      CP results = lookup_CP(courseL, prereqL, mapCP);
      printf("Results: \n");
      print_CP(results);

      printf("\nEnter a number to do the delete and lookup functions");
      printf("\n1 for CSG, 2 for SNAP, 3 for CP, 4 for CDH, 5 for CR, 0 to move on: ");
      choice = getlin3();
    }
    else if(choice[0] == '4') {
      printf("\nCDH");
      printf("\nRemoving: \n");
      printf("Enter a course argument (or * to not specify): ");
      char *courseD = getlin3();
      courseD[strlen(courseD)-1] = '\0';
      printf("Enter a day argument (or *): ");
      char *dayD = getlin3();
      dayD[strlen(dayD)-1] = '\0';
      printf("Enter an hour argument (or *): ");
      char *hourD = getlin3();
      hourD[strlen(hourD)-1] = '\0';
      delete_CDH(courseD, dayD, hourD, mapCDH);

      printf("\nNew Table: \n");
      printf("schema: %s\n", mapCSG->schema);
      printTable(mapCDH);

      printf("\nLooking up:\n");
      printf("Enter a course argument (or * to not specify): ");
      char *courseL = getlin3();
      courseL[strlen(courseL)-1] = '\0';
      printf("Enter a day argument (or *): ");
      char *dayL = getlin3();
      dayL[strlen(dayL)-1] = '\0';
      printf("Enter an hour argument (or *): ");
      char *hourL = getlin3();
      hourL[strlen(hourL)-1] = '\0';
      CDH results = lookup_CDH(courseL, dayL, hourL, mapCDH);
      printf("Results: \n");
      print_CDH(results);

      printf("\nEnter a number to do the delete and lookup functions");
      printf("\n1 for CSG, 2 for SNAP, 3 for CP, 4 for CDH, 5 for CR, 0 to move on: ");
      choice = getlin3();
    }
    else if(choice[0] == '5') {
      printf("\nCR");
      printf("\nRemoving: \n");
      printf("Enter a course argument (or * to not specify): ");
      char *courseD = getlin3();
      courseD[strlen(courseD)-1] = '\0';
      printf("Enter a room argument (or *): ");
      char *roomD = getlin3();
      roomD[strlen(roomD)-1] = '\0';
      delete_CR(courseD, roomD, mapCR);

      printf("\nNew Table: \n");
      printf("schema: %s\n", mapCSG->schema);
      printTable(mapCR);

      printf("\nLooking up:\n");
      printf("Enter a course argument (or * to not specify): ");
      char *courseL = getlin3();
      courseL[strlen(courseL)-1] = '\0';
      printf("Enter a room argument (or *): ");
      char *roomL = getlin3();
      roomL[strlen(roomL)-1] = '\0';
      CR results = lookup_CR(courseL, roomL, mapCR);
      printf("Results: \n");
      print_CR(results);

      printf("\nEnter a number to do the delete and lookup functions");
      printf("\n1 for CSG, 2 for SNAP, 3 for CP, 4 for CDH, 5 for CR, 0 to move on: ");
      choice = getlin3();
    }
  }



  /*PART 2*/
  printf("\n\nPART 2\n");

  printf("\nQuery: Grade for x student in y course\n");
  printf("Enter a student name, or 0 to move on: ");
  char *studentName = getlin3();
  while(studentName[0] != '0') {
    //fgets(studentName, 20, stdin);
    studentName[strlen(studentName)-1] = '\0';
    printf("Enter a course: ");
    char *course = getlin3();
    course[strlen(course)-1] = '\0';
    //fgets(course, 6, stdin);
    //printf("course: %s", course);

    char *grade = getGrade(mapSNAP, mapCSG, studentName, course);
    printf("Grade: %s\n", grade);

    printf("\nEnter a student name, or 0 to move on: ");
    studentName = getlin3();
  }

  printf("\nQuery: Where is x student at y time on z day?\n");
  printf("Enter a student name, or 0 to move on: ");
  char *studentName2 = getlin3();

  while(studentName2[0] != '0') {
    //fgets(studentName2, 20, stdin);
    studentName2[strlen(studentName2)-1] = '\0';
    printf("Enter a time: ");
    char *hour = getlin3();
    //fgets(hour, 5, stdin);
    hour[strlen(hour)-1] = '\0';
    printf("Enter a day: ");
    char *day = getlin3();
    //fgets(day, 3, stdin);
    day[strlen(day)-1] = '\0';

    char *room = getRoom(mapSNAP, mapCSG, mapCDH, mapCR, studentName2, hour, day);
    printf("Room: %s\n", room);

    printf("\nEnter a student name, or 0 to move on: ");
    studentName2 = getlin3();
  }


  /*PART 3*/
  printf("\n\nPART 3\n");
  printf("\nSelection Operator on CSG: \n");
  Hashmap selection = selectionCSG(mapCSG, "CS101");
  printTable(selection);

  printf("\nProjection Operator on CSG for student ID: \n");
  StudentID ids = projectionCSG_ID(mapCSG);
  print_IDs(ids);

  printf("\nJoin CR and CDH: \n");
  Hashmap mapCRDH = joinCRDH(mapCR, mapCDH);
  printTable(mapCRDH);

  printf("\nAll Operators (8.15): \n");
  dayHour dh = allOperators(mapCRDH, "Turing Aud.");
  print_dayHour(dh);


  /*EXTRA CREDIT*/
  printf("\n\nEC: Generic Tuple Implementation\n");
  printf("\nInserting Fig. 8.1 (with names instead of studentID) into generalized Table : \n");
  Hashmap mapT = Hashmap_new("tCSG");

  Data *data = (Data*)malloc(3*sizeof(Data));
  data[0] = newData("CS101"); data[1] = newData("C. Brown"); data[2] = newData("A");
  insertTuple(3, data, "CS101C. Brown", mapT);
  Data *data1 = (Data*)malloc(3*sizeof(Data));
  data1[0] = newData("CS101"); data1[1] = newData("L. Van Pelt"); data1[2] = newData("B");
  insertTuple(3, data1, "CS101L. Van Pelt", mapT);
  Data *data2 = (Data*)malloc(3*sizeof(Data));
  data2[0] = newData("EE200"); data2[1] = newData("C. Brown"); data2[2] = newData("C");
  insertTuple(3, data2, "EE200C. Brown", mapT);
  Data *data3 = (Data*)malloc(3*sizeof(Data));
  data3[0] = newData("EE200"); data3[1] = newData("P. Patty"); data3[2] = newData("B+");
  insertTuple(3, data3, "EE200P. Patty", mapT);
  Data *data4 = (Data*)malloc(3*sizeof(Data));
  data4[0] = newData("CS101"); data4[1] = newData("G. Ferguson"); data4[2] = newData("A-");
  insertTuple(3, data4, "CS101G. Ferguson", mapT);
  Data *data5 = (Data*)malloc(3*sizeof(Data));
  data5[0] = newData("PH100"); data5[1] = newData("L. Van Pelt"); data5[2] = newData("C+");
  insertTuple(3, data5, "PH100L. Van Pelt", mapT);

  printTable(mapT);

  printf("\nRemoving tuples from CSG: (ex. delete(<PH100, *, *>, R) ) \n");

  printf("Enter a course argument for removal (or * to not specify): ");
  char *courseDT = getlin3();
  courseDT[strlen(courseDT)-1] = '\0';
  printf("Enter a name argument for removal (or *): ");
  char *idDT = getlin3();
  idDT[strlen(idDT)-1] = '\0';
  printf("Enter a grade argument for removal (or *): ");
  char *gradeDT = getlin3();
  gradeDT[strlen(gradeDT)-1] = '\0';

  Data *toDelete = (Data*)malloc(3*sizeof(Data));
  toDelete[0] = newData(courseDT); toDelete[1] = newData(idDT); toDelete[2] = newData(gradeDT);
  deleteTuple(3, toDelete, mapT);

  printf("\nNew Table: \n");
  printTable(mapT);

  printf("\nLooking up: (ex. lookup(<*, 12345, *>, R) )\n");

  printf("Enter a course argument for lookup (or * to not specify): ");
  char *courseLT = getlin3();
  courseLT[strlen(courseLT)-1] = '\0';
  printf("Enter a name argument for lookup (or *): ");
  char *idLT = getlin3();
  idLT[strlen(idLT)-1] = '\0';
  printf("Enter a grade argument for lookup (or *): ");
  char *gradeLT = getlin3();
  gradeLT[strlen(gradeLT)-1] = '\0';
  printf("Results: \n");

  Data *toLookup = (Data*)malloc(3*sizeof(Data));
  toLookup[0] = newData(courseLT); toLookup[1] = newData(idLT); toLookup[2] = newData(gradeLT);
  Tuple resultsT = lookupTuple(3, toLookup, mapT);
  print_Tuple(resultsT);


  /*IO*/
  printf("\n\nPart 1 Numver 4: Reading and Writing to Files\n");
  printf("\nRead a CSG from file readCSG.data\n");
  Hashmap testCSG = readCSG();
  printTable(testCSG);
  printf("\nRead a SNAP from file readSNAP.data\n");
  Hashmap testSNAP = readSNAP();
  printTable(testSNAP);
  printf("\nRead a CP from file readCP.data\n");
  Hashmap testCP = readCP();
  printTable(testCP);
  printf("\nRead a CR from file readCP.data\n");
  Hashmap testCR = readCR();
  printTable(testCR);
  printf("\nRead a CDH from file readCP.data\n");
  Hashmap testCDH = readCDH();
  printTable(testCDH);

  printf("\nWrite same tables back into files...");
  printf("\nWrite a CSG");
  writeCSG(testCSG);
  printf("\nWrite a SNAP");
  writeSNAP(testSNAP);
  printf("\nWrite a CP");
  writeCP(testCP);
  printf("\nWrite a CR");
  writeCR(testCR);
  printf("\nWrite a CDH\n");
  writeCDH(testCDH);

  return 0;
}
