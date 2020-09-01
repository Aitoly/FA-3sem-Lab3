#pragma warning(disable:4996)

#include<stdio.h>
#include<iostream>
#include<ctype.h>
#include<math.h>
#include<time.h>

typedef struct
{
	char* data;
	int size;
}String;

void Create_String(String* s, const char* in)
{
	s->data = (char*)malloc(strlen(in) + 1);
	s->size = strlen(in);
	strcpy(s->data, in);
}

void Delete_String(String* s)
{
	if (s->data)
	{
		free(s->data);
	}
}

void Print_String(String* s)
{
	printf("%s\n", s->data);
}

int Compare_String(String* s1, String* s2)
{
	int i;
	if (s1->size > s2->size)
	{
		return 1;
	}
	else if (s1->size < s2->size)
	{
		return -1;
	}

	for (i = 0; i < s1->size; i++)
	{
		if (s1->data[i] < s2->data[i])
		{
			return -1;
		}
		else if (s1->data[i] > s2->data[i])
		{
			return 1;
		}
	}
	return 0;
}

void Concatenation_String(String* s1, String* s2)
{
	s1->data = (char*)realloc(s1->data, strlen(s1->data) + strlen(s2->data) + 1);
	int i;
	char* ptr = s1->data + strlen(s1->data);

	for (i = 0; i < strlen(s2->data); i++)
	{
		*ptr++ = s2->data[i];
	}
	*ptr = '\0';
}

void Duplication_String(String* s1, String* s2)
{
	free(s1->data);
	s1->data = (char*)malloc(strlen(s2->data) + 1);
	s1->size = strlen(s2->data);
	strcpy(s1->data, s2->data);
}

int main()
{
	String s1, s2, s3;
	Create_String(&s1, "stop");
	Create_String(&s2, "define");
	Create_String(&s3, "");

	Print_String(&s1);
	Print_String(&s2);

	Duplication_String(&s3, &s1);
	Print_String(&s3);

	printf("%d\n", Compare_String(&s3, &s1));
	printf("%d\n", Compare_String(&s3, &s2));

	Concatenation_String(&s1, &s2);
	Print_String(&s1);

	Delete_String(&s1);
	Delete_String(&s2);
	Delete_String(&s3);

	return 0;
}