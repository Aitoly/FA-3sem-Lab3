#pragma warning(disable:4996)

#include "Student.h"

int readNextStudents2(FILE* fin, Student2* stud)
{
    char buff[BUFSIZ];

    if (feof(fin))
    {
        return -1;
    }

    // Фамилия
    fscanf(fin, "%s", buff);
    stud->surname = (char*)malloc(strlen(buff) + 1);
    strcpy(stud->surname, buff);

    if (feof(fin))
    {
        return -1;
    }

    // Имя
    fscanf(fin, "%s", buff);
    stud->name = (char*)malloc(strlen(buff) + 1);
    strcpy(stud->name, buff);

    if (feof(fin))
    {
        return -1;
    }

    // Отчество
    fscanf(fin, "%s", buff);
    stud->patronymic = (char*)malloc(strlen(buff) + 1);
    strcpy(stud->patronymic, buff);

    if (feof(fin))
    {
        return -1;
    }

    // Группа
    fscanf(fin, "%s", buff);
    stud->group = (char*)malloc(strlen(buff) + 1);
    strcpy(stud->group, buff);

    if (feof(fin))
    {
        return -1;
    }

    fscanf(fin, "%d", &stud->firstExam);
    if (feof(fin))
    {
        return -1;
    }
    fscanf(fin, "%d", &stud->secondExam);
    if (feof(fin))
    {
        return -1;
    }
    fscanf(fin, "%d", &stud->thirdExam);
    if (feof(fin))
    {
        return -1;
    }
    fscanf(fin, "%d", &stud->fourthExam);
    if (feof(fin))
    {
        return -1;
    }
    fscanf(fin, "%d", &stud->fifthExam);

    return 0;
}


void printMiddle(Student2** massOfStudents, double* massOfMiddle, double middle, int numberOfStudents)
{
    for (int i = 0; i < numberOfStudents; ++i)
    {
        if (middle < massOfMiddle[i])
        {
            printf("%s %s %s %s %.2f\n", massOfStudents[i]->surname,
                massOfStudents[i]->name,
                massOfStudents[i]->patronymic,
                massOfStudents[i]->group,
                massOfMiddle[i]);
        }
    }
}


void killMassOfStud2(Student2** massOfStud, int numberOfStudents)
{
    if (massOfStud == NULL)
    {
        return;
    }

    for (int i = 0; i < numberOfStudents; ++i)
    {

        free(massOfStud[i]);
    }

    free(massOfStud);
}