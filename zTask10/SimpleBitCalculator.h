int Implication(int a, int b)
{
	int c = 0, i = 1;
	while (a || b)
	{
		if ((a & 1) && !(b & 1))
		{
			i *= 2;
		}
		else
		{
			c += i;
			i *= 2;
		}
		a = a >> 1;
		b = b >> 1;
	}
	return c;
}

int UnImplication(int a, int b)
{
	int c = 0, i = 1;
	while (a || b)
	{
		if (!(a & 1) && (b & 1))
		{
			i *= 2;
		}
		else
		{
			c += i;
			i *= 2;
		}
		a = a >> 1;
		b = b >> 1;
	}
	return c;
}

int CoImplication(int a, int b)
{
	int c = 0, i = 1;
	while (a || b)
	{
		if ((a & 1) && !(b & 1))
		{
			c += i;
			i *= 2;
		}
		else
		{
			i *= 2;
		}
		a = a >> 1;
		b = b >> 1;
	}
	return c;
}

int Equivalent(int a, int b)
{
	int c = 0, i = 1;
	while (a || b)
	{
		if ((a & 1) == (b & 1))
		{
			c += i;
			i *= 2;
		}
		else
		{
			i *= 2;
		}
		a = a >> 1;
		b = b >> 1;
	}
	return c;
}

int PlusMod2(int a, int b)
{
	int c = 0, i = 1;
	while (a || b)
	{
		if ((!(a & 1) && (b & 1)) || ((a & 1) && !(b & 1)))
		{
			c += i;
			i *= 2;
		}
		else
		{
			i *= 2;
		}
		a = a >> 1;
		b = b >> 1;
	}
	return c;
}

int ShefferStroke(int a, int b)
{
	int c = 0, i = 1;
	while (a || b)
	{
		if ((a & 1) && (b & 1))
		{
			i *= 2;
		}
		else
		{
			c += i;
			i *= 2;
		}
		a = a >> 1;
		b = b >> 1;
	}
	return c;
}

int PierArrow(int a, int b)
{
	int c = 0, i = 1;
	while (a || b)
	{
		if (!(a & 1) && !(b & 1))
		{
			c += i;
			i *= 2;
		}
		else
		{
			i *= 2;
		}
		a = a >> 1;
		b = b >> 1;
	}
	return c;
}

int SimpleCalculator_1(int a, char op, int b, int* error)
{
	switch (op)
	{
	case '+': return a | b;
	case '&': return a & b;
	case '~':  return Equivalent(a, b);
	case '?': return ShefferStroke(a, b);
	case '!': return PierArrow(a, b);
	}
	*error = 1;
	return 0;
}


int SimpleCalculator_2(int a, char* op, int b, int* error)
{
	if (!strcmp(op, "->"))
	{
		return Implication(a, b);
	}
	if (!strcmp(op, "<-"))
	{
		return UnImplication(a, b);
	}
	if (!strcmp(op, "<>"))
	{
		return PlusMod2(a, b);
	}
	if (!strcmp(op, "+>"))
	{
		return CoImplication(a, b);
	}
	*error = 1;
	return 0;
}
