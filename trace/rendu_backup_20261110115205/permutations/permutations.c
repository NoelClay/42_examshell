#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

size_t	sstrlen(char *s)
{
	size_t	res;

	res = 0;
	while (s[res])
		res++;
	return (res);
}

void	swap(char *str, int i, int j)
{
	char	tmp;

	tmp = str[i];
	str[i] = str[j];
	str[j] = tmp;
}

void	recur_perm(char *origin, int *used, char *target, int slen, int pos)
{

	if (pos == slen)
		puts(target);
	else
	{
		for (int i = 0; i < slen; i++)
		{
			if (used[i] == 0)
			{
				target[pos] = origin[i];
				used[i] = 1;
				recur_perm(origin, used, target, slen, pos + 1);
				used[i] = 0;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	int	table[26] = { 0 };
	int	arg_size = 0;
	char	origin[27] = { 0 };
	int	cnt = 0;
	int	*used;
	char	target[27] = { 0 };

	if (argc != 2)
		return 1;
	arg_size = sstrlen(argv[1]);
	for (int i = 0; i < arg_size; i++)
		table[argv[1][i] - 'a']++;
	for (int i = 0; i < 26; i++)
	{
		if (table[i] > 0)
		{
			origin[cnt] = 'a' + i;
			//target[cnt] = 'a' + i;
			cnt++;
		}
	}
	used = calloc(cnt, sizeof(int));
	if (!used)
		return (1);
	recur_perm(origin, used, target, cnt, 0);
	free(used);
	return (0);
}
