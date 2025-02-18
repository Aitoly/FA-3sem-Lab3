//
//������� � �  M80-211�-18
//

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include"ctype.h"

#include<stdarg.h>

//#define DEBUG 1

#include"Calculator/Calculator.h"

int main(int arg_c, char** arg_v)
{
	FILE* in;
	FILE* log;
	log = fopen("log.txt", "w");

	char in_string[BUFSIZ] = "2+2*3";
	char out_string[BUFSIZ];
	char error[BUFSIZ]; *error = '\0';
	int line = 1;

	printf("arg_c: %d\n", arg_c);
	for (int i = 1; i < arg_c; i++)
	{
		printf("arg_v[%d]: %s\n", i, arg_v[i]);
	}
	printf("====================\n");
	for (int i = 1; i < arg_c; i++)
	{
		in = fopen(arg_v[i], "r");
		if (!in)
		{
			if (log)
			{
				fprintf(log, "I can`t open file \"%s\"!\n", arg_v[i]);
			}
			continue;
		}

		while (!feof(in))
		{
			fgets(in_string, BUFSIZ, in);


			int result = Calculator(in_string, out_string, error);

			if (*error == '\0')
			{
				printf("%s = %d\n", out_string, result);
			}
			else
			{
				fprintf(log, "File[%s]Line[%d]::Error! %s\n", arg_v[i], line, error);
			}

			*in_string = '\0';
			*out_string = '\0';
			*error = '\0';
			line++;
		}
		fclose(in);
		line = 1;
	}

	if (log)
	{
		fclose(log);
	}

	system("pause");
	return 0;
}