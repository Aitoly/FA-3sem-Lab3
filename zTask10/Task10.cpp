#pragma warning(disable:4996)

#include<stdio.h>
#include<iostream>
#include<ctype.h>
#include<math.h>
#include<time.h>

#include"MyString.h"
#include"SimpleBitCalculator.h"

#define DATA_SIZE 26

int XOR(unsigned int a)
{
	int c = 0, i = 1;
	while (a > 0)
	{
		if (a & 1)
		{
			i *= 2;
		}
		else
		{
			c += i;
			i *= 2;
		}
		a = a >> 1;
	}
	return c;


}

int char_to_int(char c)
{
	if (isalpha(c))
	{
		c = toupper(c) - 'A' + 10;
	}
	else if (isdigit(c))
	{
		return c - '0';
	}
	else
	{
		return -1;
	}
}

int string_to_int(char* old_str, int old_base)
{
	if (old_str == NULL)
	{
		return 0;
	}
	int old_num = 0;
	for (int i = 0; i < strlen(old_str); i++)
	{
		old_num += char_to_int(old_str[strlen(old_str) - i - 1]) * pow(old_base, i);
	}
	return old_num;
}

void int_to_string(int old_int, String* output)
{
	del(output);
	create(output);
	while (old_int)
	{
		add_in_home(output, '0' + (old_int % 10));
		old_int /= 10;
	}
}

void CCx_to_CCy(char* old_str, int old_base, int new_base, String* output) {

	del(output);
	create(output);
	if (old_base < 2 || old_base > 36) {
		printf("old_base must be 2..36");
		return;
	}
	if (new_base < 2 || new_base > 36) {
		printf("new_base must be 2..36");
		return;
	}

	int old_num = string_to_int(old_str, old_base);
	if (old_num < 0)
	{
		printf("input number must be >= 0");
		return;
	}
	if (old_num == 0)
	{
		add_in_home(output, '0');
		return;
	}

	int t = 0;

	while (old_num) {
		t = old_num % new_base;
		add_in_home(output, t > 9 ? 'A' + t - 10 : '0' + t);
		old_num /= new_base;
	}
}

int Get_Info(FILE* in, char* line)
{
	if (!in)
	{
		return 0;
	}



	char c;
	int mode = 0;

	//0 - нет
	//-5 - однострочный коментарий
	//>0 - просто коментарий

	while (!feof(in))
	{
		c = fgetc(in);
		c = toupper(c);

		if (mode == 0)
		{
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
			else if (c == '%')
			{
				mode = -1;
			}
			else if (c == '{')
			{
				mode++;
			}
			else if (c == '}')
			{
				mode--;
				if (mode < 0)
				{
					*line = '\0';
					return 0;
				}
			}
			else
			{
				*line++ = c;
			}
		}
		else if (mode == -1)
		{
			if (c == '\n')
			{
				mode = 0;
			}
		}
		else if (mode > 0)
		{
			if (c == '}')
			{
				mode--;
				if (mode < 0)
				{
					*line = '\0';
					return 0;
				}
			}
			else if (c == '{')
			{
				mode++;
			}
		}
	}

	if (!mode)
	{
		return 1;
	}
	else
	{
		*line = '\0';
		return 0;
	}

}

void WriteDATA(int* DATA, int* INIT)
{
	printf("DATA:\n");
	for (int i = 0; i < DATA_SIZE; i++)
	{
		if (INIT[i] != 0)
		{
			printf("%c:%d ", 'A' + i, DATA[i]);
		}
	}
	printf("\nINIT:\n");
	for (int i = 0; i < DATA_SIZE; i++)
	{
		if (INIT[i] != 0)
		{
			printf("%c:%d ", 'A' + i, INIT[i]);
		}
	}
	printf("\n");
}

void EnterTheNumber(char* ptr, char* line, int* DATA, int* INIT)
{
	int index_in = *ptr - 'A'; ptr++;
	if (*ptr != ',')
	{
		printf("It is an error in line \"%s\" (can`t find ',')\n", line, strlen(line));
		system("pause");
		exit(-1);
	}
	ptr++;
	int base = 0;
	while (*ptr != ')')
	{
		if (isdigit(*ptr))
		{
			base *= 10;
			base += *ptr - '0';
		}
		else
		{
			printf("It is an error in line \"%s\" (len = %d)\n", line, strlen(line));
			system("pause");
			exit(-1);
		}
		ptr++;
	}
	ptr++;
	if (*ptr != ';')
	{
		printf("It is an error in line \"%s\" (can`t find ';')\n", line, strlen(line));
		system("pause");
		exit(-1);
	}

	if (base < 2 || base > 36) {
		printf("It is an error in line \"%s\" (invalid base)\n", line, strlen(line));
		system("pause");
		exit(-1);
	}

	//printf("It a line to read in index %d in base %d\"%s\"\n", index_in, base, line);

	////////////////

	printf("Enter the number %c in base %d: ", 'A' + index_in, base);
	char in[BUFSIZ];
	if (scanf("%s", in) != 0)
	{
		for (int i = 0; i < strlen(in); i++)
		{
			if (!isdigit(in[i]))
			{
				printf("Invalid input (not digit)\n");
				system("pause");
				exit(-1);
			}
			else
			{
				if (char_to_int(in[i]) >= base)
				{
					printf("Invalid input (not in base)\n");
					system("pause");
					exit(-1);
				}
			}
		}

		String string;
		create(&string);

		CCx_to_CCy(in, base, 10, &string);
		int integer_in = string_to_int(string.data, base);

		del(&string);

		DATA[index_in] = integer_in;
		INIT[index_in] = 1;
	}
	else
	{
		printf("Invalid input\n");
		system("pause");
		exit(-1);
	}
}

void PrintTheNumber(char* ptr, char* line, int* DATA, int* INIT)
{
	int index_out = *ptr - 'A'; ptr++;
	if (*ptr != ',')
	{
		printf("It is an error in line \"%s\" (can`t find ',')\n", line, strlen(line));
		system("pause");
		exit(-1);
	}
	ptr++;
	int base = 0;
	while (*ptr != ')')
	{
		if (isdigit(*ptr))
		{
			base *= 10;
			base += *ptr - '0';
		}
		else
		{
			printf("It is an error in line \"%s\" (len = %d)\n", line, strlen(line));
			system("pause");
			exit(-1);
		}
		ptr++;
	}
	ptr++;
	if (*ptr != ';')
	{
		printf("It is an error in line \"%s\" (can`t find ';')\n", line, strlen(line));
		system("pause");
		exit(-1);
	}

	if (base < 2 || base > 36) {
		printf("It is an error in line \"%s\" (invalid base)\n", line, strlen(line));
		system("pause");
		exit(-1);
	}

	////////////////

	if (INIT[index_out])
	{
		//printf("Number %c in base %d: %d\n", 'A' + index_out, base, DATA[index_out]);
		String string_10, string;

		create(&string_10);
		int_to_string(DATA[index_out], &string_10);

		create(&string);
		CCx_to_CCy(string_10.data, 10, base, &string);

		printf("Number %c in base %d: %s\n", 'A' + index_out, base, string.data);

		del(&string);
		del(&string_10);
	}
	else
	{
		printf("It is an error in line \"%s\" (%c not init)\n", line, 'A' + index_out);
		system("pause");
		exit(-1);
	}

}

void CopyBtoA(char* ptr, char* line, int* DATA, int* INIT)
{
	int index_in, index_out;
	ptr = line;
	index_in = *ptr - 'A';
	ptr += 3;
	index_out = *ptr - 'A';
	//printf("COPY FROM %d TO %d\n", index_out, index_in);

	if (INIT[index_out])
	{
		DATA[index_in] = DATA[index_out];
		INIT[index_in] = 1;
	}
	else
	{
		printf("It is an error in line \"%s\" (%c not init)\n", line, 'A' + index_out);
		system("pause");
		exit(-1);
	}
}

void CopyNotBtoA(char* ptr, char* line, int* DATA, int* INIT)
{
	int index_in, index_out;
	ptr = line;
	index_in = *ptr - 'A';
	ptr += 3;
	index_out = *ptr - 'A';
	//printf("COPY FROM %d TO %d\n", index_out, index_in);

	if (INIT[index_out])
	{
		DATA[index_in] = XOR(DATA[index_out]);
		INIT[index_in] = 1;
	}
	else
	{
		printf("It is an error in line \"%s\" (%c not init)\n", line, 'A' + index_out);
		system("pause");
		exit(-1);
	}
}

void SimpleCalculator_1_use(char* ptr, char* line, int* DATA, int* INIT)
{
	int index_in, index_left, index_right;
	char op;
	ptr = line;
	index_in = *ptr - 'A';
	ptr += 3;
	index_left = *ptr - 'A';
	ptr++;
	op = *ptr;
	ptr++;
	index_right = *ptr - 'A';

	//printf("WRITE TO %d:::%d %c %d\n", index_in, index_left, op, index_right);

	if (INIT[index_left] && INIT[index_right])
	{
		int err = 0;
		DATA[index_in] = SimpleCalculator_1(DATA[index_left], op, DATA[index_right], &err);
		if (err)
		{
			printf("It is an error in line \"%s\" (invalid operation)\n", line);
			system("pause");
			exit(-1);
		}
		INIT[index_in] = 1;
	}
	else
	{
		printf("It is an error in line \"%s\" (not init variable)\n", line);
		system("pause");
		exit(-1);
	}
}

void SimpleCalculator_2_use(char* ptr, char* line, int* DATA, int* INIT)
{
	int index_in, index_left, index_right;
	char op[3];
	ptr = line;
	index_in = *ptr - 'A';
	ptr += 3;
	index_left = *ptr - 'A';
	ptr++;
	op[0] = *ptr;
	ptr++;
	op[1] = *ptr;
	op[2] = '\0';
	ptr++;
	index_right = *ptr - 'A';

	//printf("WRITE TO %d:::%d %s %d\n", index_in, index_left, op, index_right);

	if (INIT[index_left] && INIT[index_right])
	{
		int err = 0;
		DATA[index_in] = SimpleCalculator_2(DATA[index_left], op, DATA[index_right], &err);
		if (err)
		{
			printf("It is an error in line \"%s\" (invalid operation)\n", line);
			system("pause");
			exit(-1);
		}
		INIT[index_in] = 1;
	}
	else
	{
		printf("It is an error in line \"%s\" (not init variable)\n", line);
		system("pause");
		exit(-1);
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

	int DATA[DATA_SIZE] = { 0 };
	int INIT[DATA_SIZE] = { 0 };

	char line[BUFSIZ];
	char* ptr;

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
		if (strlen(line) == 0)
		{
			continue;
		}

		if (strlen(line) < 5 || strlen(line) > 12)
		{
			printf("It is an error in line \"%s\" (len = %d)\n", line, strlen(line));
			fclose(in);
			system("pause");
			exit(-1);
		}
		/////////////////////////////////////////// read(A, 10);
		ptr = line;
		if (*ptr++ == 'R' && *ptr++ == 'E' && *ptr++ == 'A' && *ptr++ == 'D' && *ptr++ == '(')
		{
			EnterTheNumber(ptr, line, DATA, INIT);
			continue;
		}
		/////////////////////////////////////////// write(A, 2);
		ptr = line;
		if (*ptr++ == 'W' && *ptr++ == 'R' && *ptr++ == 'I' && *ptr++ == 'T' && *ptr++ == 'E' && *ptr++ == '(')
		{
			PrintTheNumber(ptr, line, DATA, INIT);
			continue;
		}
		/////////////////////////////////////////// A:=B;
		ptr = line;
		if (isalpha(*ptr++) && *ptr++ == ':' && *ptr++ == '=' && isalpha(*ptr++) && *ptr++ == ';')
		{
			CopyBtoA(ptr, line, DATA, INIT);
			continue;
		}
		/////////////////////////////////////////// A:=B++C;
		ptr = line;
		if (isalpha(*ptr++) && *ptr++ == ':' && *ptr++ == '=' && isalpha(*ptr++) && !isalnum(*ptr++) && !isalnum(*ptr++) && isalpha(*ptr++) && *ptr++ == ';')
		{
			SimpleCalculator_2_use(ptr, line, DATA, INIT);
			continue;
		}
		/////////////////////////////////////////// A:=B+C;
		ptr = line;
		if (isalpha(*ptr++) && *ptr++ == ':' && *ptr++ == '=' && isalpha(*ptr++) && !isalnum(*ptr++) && isalpha(*ptr++) && *ptr++ == ';')
		{
			SimpleCalculator_1_use(ptr, line, DATA, INIT);
			continue;
		}
		/////////////////////////////////////////// A:=\B;
		ptr = line;
		if (isalpha(*ptr++) && *ptr++ == ':' && *ptr++ == '=' && *ptr++ == '\\' && isalpha(*ptr++) && *ptr++ == ';')
		{
			CopyNotBtoA(ptr, line, DATA, INIT);
			continue;
		}
		///////////////////////////////////////////
		printf("It is an error in line \"%s\" (len = %d)\n", line, strlen(line));
		fclose(in);
		system("pause");
		exit(-1);
	}

	WriteDATA(DATA, INIT);

	fclose(in);
	remove("time.txt");

	return 0;
}
