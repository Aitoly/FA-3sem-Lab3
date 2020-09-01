#ifndef LAB3_STUDENTS2_H
#define LAB3_STUDENTS2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _students2 Student2;

struct _students2
{
    char* name;
    char* surname;
    char* patronymic;
    char* group;
    int firstExam;
    int secondExam;
    int thirdExam;
    int fourthExam;
    int fifthExam;
};


int readNextStudents2(FILE*, Student2*);


void printMiddle(Student2**, double*, double, int);


void killMassOfStud2(Student2**, int);

#endif //LAB3_STUDENTS2_H