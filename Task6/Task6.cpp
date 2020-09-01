#pragma warning(disable:4996)

#include "Student.h"

int main(int arg_c, char** arg_v)
{
    printf("arg_c: %d\n", arg_c);
    for (int i = 0; i < arg_c; i++)
    {
        printf("arg_v[%d]: %s\n", i, arg_v[i]);
    }

    if (arg_c <= 1)
    {
        printf("I need more arg_v\n");
        system("pause");
        exit(1);
    }


    FILE* fin;
    FILE* fout;
    fin = fopen(arg_v[1], "r");
    if (!fin)
    {
        printf("I can`t open in.txt\n");
        system("pause");
        exit(-1);
    }
    fout = fopen("out.txt", "w");
    if (!fout)
    {
        fclose(fin);
        printf("I can`t open out.txt\n");
        system("pause");
        exit(-1);
    }

    Student2** massOfStudents = NULL;
    Student2* pNewNode;
    int numberOfStudents = 0;

    double middleOfAll = 0,
        * massOfMiddle = NULL,
        currentMiddle = 0;

    while (true)
    {
        pNewNode = (Student2*)malloc(sizeof(Student2));
        if (readNextStudents2(fin, pNewNode) == -1)
        {
            free(pNewNode);
            break;
        }

        ++numberOfStudents;
        massOfStudents = (Student2**)realloc(massOfStudents, numberOfStudents * sizeof(Student2*));
        massOfStudents[numberOfStudents - 1] = pNewNode;

        currentMiddle = (pNewNode->firstExam +
            pNewNode->secondExam +
            pNewNode->thirdExam +
            pNewNode->fourthExam +
            pNewNode->fifthExam) / 5.;

        fprintf(fout, "%s %s %s %s %.2f\n", pNewNode->surname,
            pNewNode->name,
            pNewNode->patronymic,
            pNewNode->group,
            currentMiddle);

        massOfMiddle = (double*)realloc(massOfMiddle, sizeof(double) * numberOfStudents);
        massOfMiddle[numberOfStudents - 1] = currentMiddle;
    }

    for (int i = 0; i < numberOfStudents; ++i)
    {
        middleOfAll += massOfMiddle[i];
    }

    middleOfAll /= numberOfStudents;

    printMiddle(massOfStudents, massOfMiddle, middleOfAll, numberOfStudents);

    killMassOfStud2(massOfStudents, numberOfStudents);
    free(massOfMiddle);
    fclose(fin);
    fclose(fout);
}