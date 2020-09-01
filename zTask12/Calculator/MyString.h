

typedef struct
{
	char *data;
	int size;
}String;

void Create_String(String *s)
{
	s->data = NULL;
	s->size = 0;
}

void Destroy_String(String *s)
{
	if (s->data)
	{
		free(s->data);
	}
}

void Print_String(String *s)
{
	if (s->data)
	{
		printf("%s\n", s->data);
	}
}

void add(String *s, char c)
{
	s->size++;
	s->data = (char*)realloc(s->data, s->size);
	*(s->data + s->size - 1) = c;
}

char End_String(String *s)
{
	return s->data[s->size - 1];
}