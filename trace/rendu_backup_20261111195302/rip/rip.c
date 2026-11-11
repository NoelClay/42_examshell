#include <stdio.h>

void	solve(char *buf, int open, int close, int size, int rem, int idx)
{
	if (idx == size && open == 0 && close == 0 && rem == 0)
	{
		puts(buf);
		return ;
	}
	
	if (buf[idx] == '(')
	{
		solve(buf, open, close, size, rem + 1, idx + 1);
		if (open > 0)
		{
			buf[idx] = ' ';
			solve(buf, open -1, close, size, rem, idx + 1);
			buf[idx] = '(';
		}
	}
	else if (buf[idx] == ')')
	{
		if (rem > 0)
			solve(buf, open, close, size, rem - 1, idx + 1); 
		if (close > 0)
		{
			buf[idx] = ' ';
			solve(buf, open, close - 1, size, rem, idx + 1);
			buf[idx] = ')';
		}
	}
}

int		main(int argc, char **argv)
{
	int	open_cnt = 0;
	int	close_cnt = 0;
	int	cnt = 0;
	char	*buf;

	if (argc != 2)
		return 1;
	
	for (int i = 0; argv[1][i]; i++)
	{
		if(argv[1][i] == '(')
			open_cnt++;
		else if(argv[1][i] == ')')
		{
			if (open_cnt > 0)
				open_cnt--;
			else
				close_cnt++;
		}
		cnt++;
	}
	buf = argv[1];
	solve(buf, open_cnt, close_cnt, cnt, 0, 0);
}