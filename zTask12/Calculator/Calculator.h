#include"Calculator/MyString.h"
#include"Calculator/stack.h"

void ERROR(stack* stack, String* string)
{
	Destroy_stack(stack);
	Destroy_String(string);
}

int PRIOR(char a)
{
	switch (a)
	{
	case '^':
		return 4;

	case '*':
	case '/':
		return 3;

	case '-':
	case '+':
		return 2;

	case '(':
		return 1;
	case '{':
		return 1;
	case '[':
		return 1;
	}
}

int Simple_Calculator(int left, char operation, int right, char* error = NULL)
{
#ifdef DEBUG
	printf("%d %c %d\n", left, operation, right);
#endif
	if (operation == '+')
		return left + right;
	if (operation == '-')
		return left - right;
	if (operation == '*')
		return left * right;
	if (operation == '/')
	{
		if (right == 0)
		{
			if (error)
			{
				strcpy(error, "Divizion by zero!");
				return 0;
			}
			else
			{
				printf("Error! Divizion by zero!\n");
				return 0;
			}
		}
		return left / right;
	}
	if (operation == '^')
	{
		int temp = left;
		for (int i = right; i > 1; i--)
		{
			left *= temp;
		}
		return left;
	}
}

bool open_bracket(char c)
{
	return c == '(' || c == '[' || c == '{';
}

bool close_bracket(char c)
{
	return c == ')' || c == ']' || c == '}';
}

bool operation(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

char open_bracket_for_close(char c)
{
	switch (c)
	{
	case')': return'('; break;
	case'}': return'{'; break;
	case']': return'['; break;
	case'>': return'<'; break;
	}
	return' ';
}

bool nesting_of_brackets_in_string(char* string)
{
	stack s;//���� ������
	Create_stack(&s);

	while (*string != '\0')//���� ������ �� ����� �����
	{
		//----------------------------
		if (open_bracket(*string))
		{
			Push_stack(&s, *string);
		}
		else if (close_bracket(*string))
		{
			if (Top_stack(&s) == open_bracket_for_close(*string))
			{
				Pop_stack(&s);
			}
			else
			{
				//printf("Nesting of brackets is not observed.\n");
				Destroy_stack(&s);
				return false;
			}
		}
		string++;
	}

	if (Empty_stack(&s))
	{
		//printf("Nesting of brackets is observed.\n");
		Destroy_stack(&s);
		return true;
	}
	else
	{
		//printf("Nesting of brackets is not observed.\n");
		Destroy_stack(&s);
		return false;
	}
}



int Calculator(char* in_string, char* result_string, char* error = NULL)
{
	if (error)
	{
		*error = 0;
	}

	if (*in_string == '\0' ||  * in_string == '\n' || * in_string == EOF)
	{
		if (error)
		{
			strcpy(error, "Empty line!");
		}
		return 0;
	}

	if (!nesting_of_brackets_in_string(in_string))
	{
		if (error)
		{
			strcpy(error, "Nesting of brackets is not observed.");
		}
		return 0;
	}

	stack OPERS;//���� ���p����
	Create_stack(&OPERS);

	String my_string;
	Create_String(&my_string);
	add(&my_string, ' ');

	char c = '\0';//������� ������
	char prev_c = '\0';//������ �� ��������
	char prev_prev_c = '\0';//������ �� prev_c

	//===============================================================================================================
	//��������� ������
	//===============================================================================================================

	c = *in_string++;

	while (c != '\0' &&  c != '\n' && c != EOF)// �����p��� , ���� �� ������ �� '\0' 
	{
		if (!isspace(c))
		{
			if (result_string)
			{
				*result_string = c;
				result_string++;
			}
		}

		if (isdigit(c))// ���� ���p����� ������ - ����� , ��
		{
			add(&my_string, c);
		}
		else if (close_bracket(c))// ���� ���p����� ������ - ')' 	
		{
			while (!open_bracket(Top_stack(&OPERS)))//����������� �� ����� �������� � ������ ��� ����� ���p���� �� ��������� ���p������� ������ 
			{
				add(&my_string, Top_stack(&OPERS));
				Pop_stack(&OPERS);
			}
			Pop_stack(&OPERS);// ������� �� ����� �������� ���� ���p������� ������ 
		}
		else if (open_bracket(c))// ���� ���p����� ������ - '(' , �� ����������� � � ���� �������� 	
		{
			Push_stack(&OPERS, c);
		}
		else if (operation(c))// ���� ������ - ���� ���p���� , ��: 
		{
			if (End_String(&my_string) != ' ')//����� ��������� �����
			{
				add(&my_string, ' ');
			}
			if (isdigit(prev_c) || close_bracket(prev_c))// ���� �� ����� ���� ����� ��� ), ��
			{
				if (Empty_stack(&OPERS))// ���� ���� �������� ���� ���������� � ���� ���p���� 
				{
					Push_stack(&OPERS, c);
				}
				else// ���� �� ����
				{
					if (PRIOR(Top_stack(&OPERS)) < PRIOR(c))// ���� �p��p���� ����������� ���p���� ������ 
						//�p��p����� ���p���� �� ��p���� ����� ��������
					{
						Push_stack(&OPERS, c);// ����������� ����������� ���p���� �� ���� ��������
					}
					else// ���� �p��p���� ������
					{
						while (!(Empty_stack(&OPERS)) && (PRIOR(Top_stack(&OPERS)) >= PRIOR(c)))
						{
							// ��p��������� � ������ ��� ���p���� � ������� ��� p����� �p��p������
							add(&my_string, Top_stack(&OPERS));
							Pop_stack(&OPERS);
						}
						Push_stack(&OPERS, c);// ���������� � ���� �������� �����������  ���p����
					}
				}
			}
			else if (open_bracket(prev_c))//���� �� ����� ���� '(' ������ (-5
			{
				add(&my_string, '~');//�������� ������-����� � ������
			}
			else//���� �� ����� �� ����� � �� (, �� ������
			{
#ifdef DEBUG
				printf("\nError! I can not find a digit before operator %c\n", c);
#endif
				if (error)
				{
					strcpy(error, "I can not find a digit before operator!");
				}
				ERROR(&OPERS, &my_string);
				return 0;
			}

		}
		else if (c != ' ')// ������ ������� ����� ������� �� �������������
		{
#ifdef DEBUG
			printf("\nError! Not expected symbol: %c\n", c);
#endif
			if (error)
			{
				strcpy(error, "Not expected symbol!");
			}
			ERROR(&OPERS, &my_string);
			return 0;
		}

		if (!isspace(c))// ��� ������� �� ���� ��� ���������� ��� ������� ������
		{
			prev_prev_c = prev_c;
			prev_c = c;
		}

		c = *in_string++;// ��p���� � ���������� ������� ������� ��p���
	}
	//===============================================================================================================	

	// ����� p������p���� ����� ��p������
	while (!(Empty_stack(&OPERS)))//���������� ������� � ����� �������� �������� � ���� ������
	{
		add(&my_string, Top_stack(&OPERS));
		Pop_stack(&OPERS);
	}

	add(&my_string, '\0');

#ifdef DEBUG
	printf("\nmy_string: %s\n", my_string.data);
#endif

	Destroy_stack(&OPERS);
	//===============================================================================================================
	Create_stack(&OPERS);
	in_string = my_string.data;

	c = *in_string++;
	prev_c = '0';
	/*
	0 - ���
	1 - �������� ������������� �����
	2 - �������� ������������� �����
	*/
	int current_number = 0, current_number_;

	while (c != '\0')
	{
		if (c == '~')// ���� ~, �� �������� ������������� �����
		{
#ifdef DEBUG
			printf("Start -num with %c\n", c);
#endif
			prev_c = '2';
			current_number = 0;
		}
		else if (isdigit(c))// ���� �����
		{
			if (prev_c == '0')// ���� ������ �� �������� �� �����
			{
#ifdef DEBUG
				printf("Start +num with %c\n", c);
#endif
				prev_c = '1';// �������� ������������� �����
				current_number = 0;
				current_number += c - '0';
			}
			else if (prev_c == '1')//���� �������� �������������
			{
#ifdef DEBUG
				printf("Continue +num with %c\n", c);
#endif
				current_number *= 10;
				current_number += c - '0';
			}
			else if (prev_c == '2')// ���� �������� �������������
			{
#ifdef DEBUG
				printf("Continue -num with %c\n", c);
#endif
				current_number *= 10;
				current_number -= c - '0';
			}
		}
		else if (c == ' ')// ���� ������ �� 
		{
			if (prev_c != '0')//���� ��� �� ��������, �� �����������
			{
#ifdef DEBUG
				printf("Finish num %d with spase\n", current_number);
#endif
				prev_c = '0';
				Push_stack(&OPERS, current_number);
			}
		}
		else if (operation(c))// ���� ��������
		{
			if (prev_c != '0')//���� ��� �� ��������, �� ����������� � ������� �� ����� ��� ��������
			{
				prev_c = '0';
#ifdef DEBUG
				printf("Finish num %d with operation\n", current_number);
#endif
				if (!Empty_stack(&OPERS))
				{
					current_number_ = Top_stack(&OPERS);
					Pop_stack(&OPERS);
				}
				else
				{
#ifdef DEBUG
					printf("\nError! You forgot an operand\n");
#endif
					if (error)
					{
						strcpy(error, "You forgot an operand!");
					}
					ERROR(&OPERS, &my_string);
					return 0;
				}

				Push_stack(&OPERS, Simple_Calculator(current_number_, c, current_number, error));
				if (*error != '\0')
				{
					ERROR(&OPERS, &my_string);
					return 0;
				}
#ifdef DEBUG
				printf("%d in stack\n", Top_stack(&OPERS));
#endif

			}
			else// �������� �� ����� 2 ��������� � ��������� ��������
			{
				if (!Empty_stack(&OPERS))
				{
					current_number = Top_stack(&OPERS);
					Pop_stack(&OPERS);
				}
				else
				{
#ifdef DEBUG
					printf("\nError! You forgot an operand\n", c);
#endif
					if (error)
					{
						strcpy(error, "You forgot an operand!");
					}
					ERROR(&OPERS, &my_string);
					return 0;
				}

				if (!Empty_stack(&OPERS))
				{
					current_number_ = Top_stack(&OPERS);
					Pop_stack(&OPERS);
				}
				else
				{
#ifdef DEBUG
					printf("\nError! You forgot an operand\n", c);
#endif
					if (error)
					{
						strcpy(error, "You forgot an operand!");
					}
					ERROR(&OPERS, &my_string);
					return 0;
				}

				Push_stack(&OPERS, Simple_Calculator(current_number_, c, current_number, error));
				if (*error != '\0')
				{
					ERROR(&OPERS, &my_string);
					return 0;
				}
#ifdef DEBUG
				printf("%d in stack\n", Top_stack(&OPERS));
#endif
			}
		}
		c = *in_string++;
	}
	current_number = Top_stack(&OPERS);
	Pop_stack(&OPERS);

	if (!Empty_stack(&OPERS))
	{
#ifdef DEBUG
		printf("\nError! Invalid input\n");
#endif
		if (error)
		{
			strcpy(error, "Invalid input!");
		}
		ERROR(&OPERS, &my_string);
		return 0;
	}

	if (result_string)
	{
		*result_string++ = '\0';
	}
	//printf(" = %d\n", current_number);

	Destroy_stack(&OPERS);
	Destroy_String(&my_string);

	return current_number;
}
