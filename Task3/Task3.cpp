#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<ctype.h>
#include<math.h>
#include<time.h>

typedef struct
{
	int id, cash;
	char* name;
	char* surname;
} Employee;

void Init_Employee(Employee* employee, int id, char* name, char* surname, int cash)
{
	if (!employee)
	{
		return;
	}
	employee->name = (char*)malloc(strlen(name) + 1);
	employee->surname = (char*)malloc(strlen(surname) + 1);
	employee->id = id;
	strcpy(employee->name, name);
	strcpy(employee->surname, surname);
	employee->cash = cash;
}

void Print_Employee(Employee* employee)
{
	if (!employee)
	{
		return;
	}
	printf("%d %s %s %d\n", employee->id, employee->name, employee->surname, employee->cash);
}

void Print_Employee(FILE* f, Employee* employee)
{
	if (!employee || !f)
	{
		return;
	}
	fprintf(f, "%d %s %s %d\n", employee->id, employee->name, employee->surname, employee->cash);
}

void Delete_Employee(Employee* employee)
{
	if (!employee)
	{
		return;
	}
	if (employee->name)
	{
		free(employee->name);
	}
	if (employee->surname)
	{
		free(employee->surname);
	}
	free(employee);
}

int compare(const void* employee1, const void* employee2)   // функция сравнения элементов массива
{
	if (!employee1 || !employee2)
	{
		return 0;
	}
	return (*(Employee**)employee1)->cash - (*(Employee**)employee2)->cash;


	// если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
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
	FILE* out;
	in = fopen(arg_v[1], "r");
	if (!in)
	{
		printf("I can`t open in.txt\n");
		system("pause");
		exit(-1);
	}
	out = fopen("out.txt", "w");
	if (!out)
	{
		fclose(in);
		printf("I can`t open out.txt\n");
		system("pause");
		exit(-1);
	}

	int id, cash;
	unsigned int count_of_employees = 0;
	char name[BUFSIZ], surname[BUFSIZ];
	Employee** employees = NULL;

	while (!feof(in))
	{
		fscanf(in, "%d %s %s %d\n", &id, &name, &surname, &cash);

		count_of_employees++;
		employees = (Employee**)realloc(employees, count_of_employees * sizeof(Employee*));
		*(employees + count_of_employees - 1) = (Employee*)malloc(sizeof(Employee));
		Init_Employee(*(employees + count_of_employees - 1), id, name, surname, cash);
	}



	qsort(employees, count_of_employees, sizeof(Employee*), compare);


	for (int i = 0; i < count_of_employees; i++)
	{
		Print_Employee(out, *(employees + i));
	}

	for (int i = 0; i < count_of_employees; i++)
	{
		Delete_Employee(*(employees + i));
	}
	free(employees);

	fclose(in);
	fclose(out);

	return 0;
}