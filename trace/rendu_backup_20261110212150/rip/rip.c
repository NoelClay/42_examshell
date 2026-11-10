#include <stdio.h>

void	recurs(int d_open, int d_close, int unclosed, char *argv1, int pos)
{
	char	c = 0;

	if (argv1[pos] == 0 && d_open == 0 && d_close == 0 && unclosed == 0)
	{
		puts(argv1);
		return ;
	}
	c = argv1[pos];
	if (c == '(')
	{
		recurs(d_open, d_close, unclosed + 1, argv1, pos + 1);
		if (d_open > 0)
		{
			argv1[pos] = ' ';
			recurs(d_open - 1, d_close, unclosed, argv1, pos + 1);
			argv1[pos] = '(';
		}
	}
	else if (c == ')')
	{
		if (unclosed > 0)
			recurs(d_open, d_close, unclosed - 1, argv1, pos + 1);
		argv1[pos] = ' ';
		recurs(d_open, d_close - 1, unclosed, argv1, pos + 1);
		argv1[pos] = ')';
	}

}

int main(int argc, char **argv)
{
	int	i = 0;
	int	delete_open_paren = 0;
	int	delete_close_paren = 0;
	char	c = 0;

	if (argc != 2)
		return (1);
	while (argv[1][i])
	{
		c = argv[1][i];
		if (c == '(')
		{
			delete_open_paren++;
		}
		else if (c == ')')
		{
			if (delete_open_paren > 0)
				delete_open_paren--;
			else
				delete_close_paren++;
		}
		i++;
	}
	recurs(delete_open_paren, delete_close_paren, 0, argv[1], 0);

}