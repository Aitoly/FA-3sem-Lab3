#pragma warning(disable:4996)

#include<stdio.h>
#include<iostream>
#include<ctype.h>
#include<math.h>
#include<time.h>

#include"MyString.h"

int DATA[2][3];
int boat_location;
int boat_thing;

void Draw(int index)
{
	_sleep(500);
	system("cls");

	char who = ' ';
	switch (boat_thing)
	{
	case 0: who = 'G'; break;
	case 1: who = 'W'; break;
	case 2: who = 'C'; break;
	}

	if (DATA[0][0]) { printf("G"); }
	if (DATA[0][1]) { printf("W"); }
	if (DATA[0][2]) { printf("C"); }
	printf("|");
	if (boat_location)
	{
		for (int i = 4; i >= 0; i--)
		{
			if (i == index)
			{
				printf("%c", who);
			}
			else
			{
				printf(" ");
			}
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == index)
			{
				printf("%c", who);
			}
			else
			{
				printf(" ");
			}
		}
	}
	printf("|");
	if (DATA[1][0]) { printf("G"); }
	if (DATA[1][1]) { printf("W"); }
	if (DATA[1][2]) { printf("C"); }
	printf("\n");
	_sleep(500);
}

int Check()
{
	if (boat_location)
	{
		if (DATA[0][0] && DATA[0][1]) return 0;
		if (DATA[0][0] && DATA[0][2]) return 2;
	}
	else
	{
		if (DATA[1][0] && DATA[1][1]) return 0;
		if (DATA[1][0] && DATA[1][2]) return 2;
	}
	return 1;
}

int Take(char* ptr, char* line)
{
	String string;
	create(&string);

	while (*ptr != '/0' && *ptr != '>')
	{
		if (isalpha(*ptr))
		{
			add(&string, *ptr);
		}
		ptr++;
	}
	if (*ptr++ != '>' || *ptr != ';')
	{
		return -1;
	}
	int id;

	if (!strcmp(string.data, "GOAT"))
	{
		id = 0;
	}
	else if (!strcmp(string.data, "WOLF"))
	{
		id = 1;
	}

	else if (!strcmp(string.data, "CABBAGE"))
	{
		id = 2;
	}
	else
	{
		del(&string);
		return -1;
	}

	//printf("take %s\n", string.data);
	del(&string);


	if (DATA[boat_location][id] && boat_thing == -1)
	{
		DATA[boat_location][id] = 0;
		boat_thing = id;
	}
	else
	{
		return -2;
	}
	Draw(0);
	return 0;
}

int Move()
{
	//printf("move\n");
	for (int i = 1; i < 4; i++)
	{
		Draw(i);
	}

	if (boat_location)
	{
		boat_location = 0;
	}
	else
	{
		boat_location = 1;
	}
	return Check();
}

int Put()
{
	//printf("put\n");

	if (boat_thing != -1 && !DATA[boat_location][boat_thing])
	{
		DATA[boat_location][boat_thing] = 1;
		boat_thing = -1;
	}
	else
	{
		return -2;
	}
	Draw(4);
	return 0;
}



int Get_Info(FILE* in, char* line)
{
	if (!in)
	{
		return 0;
	}

	char c;

	while (!feof(in))
	{
		c = fgetc(in);
		c = toupper(c);

		if (isspace(c) || c == '\n' || c == EOF)
		{
			continue;
		}

		if (c == ';')
		{
			*line++ = c;
			*line = '\0';
			return 1;
		}
		else
		{
			*line++ = c;
		}

	}
}

int main()
{
	FILE* in;
	in = fopen("in.txt", "r");
	if (!in)
	{
		printf("I can`t open input file");
		system("pause");
		exit(-1);
	}

	////////////////////////////////////////////////////
	////////////////////////////////////////////////////

	char line[BUFSIZ];
	char* ptr;

	DATA[0][0] = 1; DATA[0][1] = 1; DATA[0][2] = 1;
	DATA[1][0] = 0; DATA[1][1] = 0; DATA[1][2] = 0;
	boat_location = 0;
	boat_thing = -1;

	while (!feof(in))
	{
		line[0] = 0;
		if (!Get_Info(in, line))
		{
			printf("It is an error in line \"%s\" (len = %d)\n", line, strlen(line));
			fclose(in);
			system("pause");
			exit(-1);
		}
		/////////////////////////////////////////////
		if (strlen(line) == 0)
		{
			continue;
		}

		if (strlen(line) < 4 || strlen(line) > 14)
		{
			printf("It is an error in line \"%s\" (len = %d)\n", line, strlen(line));
			system("pause");
			exit(-1);
		}
		/////////////////////////////////////////// TAKE<GOAT>;
		ptr = line;
		if (*ptr++ == 'T' && *ptr++ == 'A' && *ptr++ == 'K' && *ptr++ == 'E' && *ptr++ == '<')
		{
			int err = Take(ptr, line);
			if (err == -1)
			{
				printf("ERROR! Invalid TAKE command: \"%s\"\n", line);
				fclose(in);
				system("pause");
				exit(-1);
			}
			if (err == -2)
			{
				printf("ERROR! You try to take absent thing or boat is full\"%s\"\n", line);
				fclose(in);
				system("pause");
				exit(-1);
			}
			continue;
		}
		/////////////////////////////////////////// MOVE;
		ptr = line;
		if (*ptr++ == 'M' && *ptr++ == 'O' && *ptr++ == 'V' && *ptr++ == 'E' && *ptr++ == ';')
		{
			int error = Move();
			switch (error)
			{
			case 0:
				printf("ERROR! Goat was damaged!\n"); fclose(in);
				system("pause");
				exit(-1);
				break;
			case 2:
				printf("ERROR! Cabbage was damaged!\n"); fclose(in);
				system("pause");
				exit(-1);
				break;
			}
			continue;
		}
		/////////////////////////////////////////// PUT;
		ptr = line;
		if (*ptr++ == 'P' && *ptr++ == 'U' && *ptr++ == 'T' && *ptr++ == ';')
		{
			int err = Put();
			if (err == -2)
			{
				printf("ERROR! You try to put absent thing or boat is empty\"%s\"\n", line);
				fclose(in);
				system("pause");
				exit(-1);
			}
			continue;
		}
		///////////////////////////////////////////
		printf("It is an error in line \"%s\" (len = %d)\n", line, strlen(line));
		fclose(in);
		system("pause");
		exit(-1);
	}

	fclose(in);
	remove("time.txt");

	return 0;
}