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
	stack s;//стек скобок
	Create_stack(&s);

	while (*string != '\0')//если сейчас не конец файла
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

	stack OPERS;//Стек опеpаций
	Create_stack(&OPERS);

	String my_string;
	Create_String(&my_string);
	add(&my_string, ' ');

	char c = '\0';//текущий символ
	char prev_c = '\0';//символ до текущего
	char prev_prev_c = '\0';//символ до prev_c

	//===============================================================================================================
	//ОБРАБОТКА СТРОКИ
	//===============================================================================================================

	c = *in_string++;

	while (c != '\0' &&  c != '\n' && c != EOF)// Повтоpяем , пока не дойдем до '\0' 
	{
		if (!isspace(c))
		{
			if (result_string)
			{
				*result_string = c;
				result_string++;
			}
		}

		if (isdigit(c))// Если очеpедной символ - число , то
		{
			add(&my_string, c);
		}
		else if (close_bracket(c))// Если очеpедной символ - ')' 	
		{
			while (!open_bracket(Top_stack(&OPERS)))//выталкиваем из стека операций в строку все знаки опеpаций до ближайшей откpывающей скобки 
			{
				add(&my_string, Top_stack(&OPERS));
				Pop_stack(&OPERS);
			}
			Pop_stack(&OPERS);// Удаляем из стека операций саму откpывающую скобку 
		}
		else if (open_bracket(c))// Если очеpедной символ - '(' , то заталкиваем её в стек операций 	
		{
			Push_stack(&OPERS, c);
		}
		else if (operation(c))// Если символ - знак опеpации , то: 
		{
			if (End_String(&my_string) != ' ')//знаки разделяют числа
			{
				add(&my_string, ' ');
			}
			if (isdigit(prev_c) || close_bracket(prev_c))// Если до этого было число или ), то
			{
				if (Empty_stack(&OPERS))// если стек операций пуст записываем в него опеpацию 
				{
					Push_stack(&OPERS, c);
				}
				else// если не пуст
				{
					if (PRIOR(Top_stack(&OPERS)) < PRIOR(c))// если пpиоpитет поступившей опеpации больше 
						//пpиоpитета опеpации на веpшине стека операций
					{
						Push_stack(&OPERS, c);// заталкиваем поступившую опеpацию на стек операций
					}
					else// если пpиоpитет меньше
					{
						while (!(Empty_stack(&OPERS)) && (PRIOR(Top_stack(&OPERS)) >= PRIOR(c)))
						{
							// пеpеписываем в строку все опеpации с большим или pавным пpиоpитетом
							add(&my_string, Top_stack(&OPERS));
							Pop_stack(&OPERS);
						}
						Push_stack(&OPERS, c);// записываем в стек операций поступившую  опеpацию
					}
				}
			}
			else if (open_bracket(prev_c))//если до этого была '(' случай (-5
			{
				add(&my_string, '~');//помещаем псевдо-минус в строку
			}
			else//если до этого не число и не (, то ошибка
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
		else if (c != ' ')// другие символы кроме пробела не предусмотрены
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

		if (!isspace(c))// при пробеле не надо его запоминать как прошлый символ
		{
			prev_prev_c = prev_c;
			prev_c = c;
		}

		c = *in_string++;// Пеpеход к следующему символу входной стpоки
	}
	//===============================================================================================================	

	// после pассмотpения всего выpажения
	while (!(Empty_stack(&OPERS)))//оставшиеся символы в стеке операций загоняем в стек вывода
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
	0 - нет
	1 - собираем положительное число
	2 - собираем отрицательное число
	*/
	int current_number = 0, current_number_;

	while (c != '\0')
	{
		if (c == '~')// Если ~, то собираем отрицательное число
		{
#ifdef DEBUG
			printf("Start -num with %c\n", c);
#endif
			prev_c = '2';
			current_number = 0;
		}
		else if (isdigit(c))// Если число
		{
			if (prev_c == '0')// Если ничего не собирали до этого
			{
#ifdef DEBUG
				printf("Start +num with %c\n", c);
#endif
				prev_c = '1';// Собираем положительное число
				current_number = 0;
				current_number += c - '0';
			}
			else if (prev_c == '1')//Если собирали положительное
			{
#ifdef DEBUG
				printf("Continue +num with %c\n", c);
#endif
				current_number *= 10;
				current_number += c - '0';
			}
			else if (prev_c == '2')// Если собирали отрицательное
			{
#ifdef DEBUG
				printf("Continue -num with %c\n", c);
#endif
				current_number *= 10;
				current_number -= c - '0';
			}
		}
		else if (c == ' ')// Если пробел то 
		{
			if (prev_c != '0')//Если что то собирали, то заканчиваем
			{
#ifdef DEBUG
				printf("Finish num %d with spase\n", current_number);
#endif
				prev_c = '0';
				Push_stack(&OPERS, current_number);
			}
		}
		else if (operation(c))// Если операция
		{
			if (prev_c != '0')//Если что то собирали, то заканчиваем и получем из стека еще аргумент
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
			else// Получаем из стека 2 аргумента и выполняем операцию
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
