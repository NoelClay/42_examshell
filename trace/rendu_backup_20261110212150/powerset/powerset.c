#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_powerset
{
	int	*candi;
	int	argc;
	char	**argv;
}t_powerset;


void	recurs(t_powerset *t, int arg_idx, int candi_idx, int prefix)
{
	int	target = atoi(t->argv[1]);

	if (prefix == target)
	{
		int	i = 0;
		while (i < candi_idx)
		{
			if (i == candi_idx - 1)
				fprintf(stdout, "%s\n", t->argv[t->candi[i]]);
			else
				fprintf(stdout, "%s ", t->argv[ t->candi[i]]);
			i++;
		}
		if (i == 0 && target == 0)
			fprintf(stdout, "\n");
	}
	for (int i = arg_idx; i < t->argc; i++)
	{
		int k;
		k = atoi(t->argv[i]);
		t->candi[candi_idx] = i;
		recurs(t, i + 1, candi_idx + 1, prefix + k);
		t->candi[candi_idx] = -1;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (1);
	
	int	*candikeys;

	candikeys = malloc(sizeof(int) * (argc));
	if (!candikeys)
		return (1);

	for (int i = 0; i < argc; i++)
		candikeys[i] = -1;
	
	t_powerset	*tt;
	tt = malloc(sizeof(t_powerset));
	if (!tt)
	{
		free(candikeys);
		return (1);
	}
	tt->argc = argc;
	tt->argv = argv;
	tt->candi = candikeys;
	recurs(tt, 2, 0, 0);
	free(candikeys);
	free(tt);
}