#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<ctype.h>
#include<math.h>
#include<time.h>

typedef struct
{
	int id;
	char name[BUFSIZ], surname[BUFSIZ], group[BUFSIZ];
} Student;

void Init_Student(Student* Student, int id, char* name, char* surname, char* group)
{
	if (!Student)
	{
		return;
	}
	Student->id = id;
	strcpy(Student->name, name);
	strcpy(Student->surname, surname);
	strcpy(Student->group, group);
}

void Print_Student(Student* Student)
{
	if (!Student)
	{
		return;
	}
	printf("[id::%d] %s %s %s\n", Student->id, Student->name, Student->surname, Student->group);
}

Student* Find_With_Id(Student** Students, int count_of_Students, int id)
{
	if (!Students)
	{
		return NULL;
	}
	for (int i = 0; i < count_of_Students; i++)
	{
		if ((*(Students + i))->id == id)
		{
			return *(Students + i);
		}
	}
	return NULL;
}

Student* Find_With_Name(Student** Students, int count_of_Students, const char* name)
{
	if (!Students)
	{
		return NULL;
	}
	for (int i = 0; i < count_of_Students; i++)
	{
		if (!strcmp((*(Students + i))->name, name))
		{
			return *(Students + i);
		}
	}
	return NULL;
}

Student* Find_With_Surname(Student** Students, int count_of_Students, const char* surname)
{
	if (!Students)
	{
		return NULL;
	}
	for (int i = 0; i < count_of_Students; i++)
	{
		if (!strcmp((*(Students + i))->surname, surname))
		{
			return *(Students + i);
		}
	}
	return NULL;
}

void Print_Students_Of_Group(Student** Students, int count_of_Students, const char* group)
{
	if (!Students)
	{
		return;
	}
	for (int i = 0; i < count_of_Students; i++)
	{
		if (!strcmp((*(Students + i))->group, group))
		{
			Print_Student(*(Students + i));
		}
	}
}

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


	FILE* in;
	in = fopen(arg_v[1], "r");
	if (!in)
	{
		printf("I can`t open in.txt\n");
		system("pause");
		exit(-1);
	}

	int id;
	unsigned int count_of_Students = 0;
	char name[BUFSIZ], surname[BUFSIZ], group[BUFSIZ];
	Student** Students = NULL;

	while (!feof(in))
	{
		if (fscanf(in, "%d %s %s %s\n", &id, &name, &surname, &group) != 4)
		{
			break;
		}

		count_of_Students++;
		Students = (Student**)realloc(Students, count_of_Students * sizeof(Student*));
		*(Students + count_of_Students - 1) = (Student*)malloc(sizeof(Student));
		Init_Student(*(Students + count_of_Students - 1), id, name, surname, group);
	}

	for (int i = 0; i < count_of_Students; i++)
	{
		Print_Student(*(Students + i));
	}

	printf("============\n");
	printf("Search id=2:\n");
	Print_Student(Find_With_Id(Students, count_of_Students, 2));

	printf("============\n");
	printf("Search Jack:\n");
	Print_Student(Find_With_Name(Students, count_of_Students, "Jack"));

	printf("============\n");
	printf("Search Jobs:\n");
	Print_Student(Find_With_Surname(Students, count_of_Students, "Jobs"));

	printf("============\n");
	printf("Search M8O-211B:\n");
	Print_Students_Of_Group(Students, count_of_Students, "M8O-211B");

	for (int i = 0; i < count_of_Students; i++)
	{
		free(*(Students + i));
	}
	free(Students);

	fclose(in);
	return 0;
}