#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_powerset
{
	int	*candi;
	int	candi_idx;
	int	argc;
	char	**argv;
	int	arg_idx;
	int	prefix;
}t_powerset;


void	recurs(t_powerset *t)
{
	int	target = atoi(t->argv[1]);

	if (t->prefix == target)
	{
		int	i = 0;
		while (i < t->argc && t->candi[i] != -1)
		{
			if ( t->candi[i + 1] == -1)
				fprintf(stdout, "%s\n", t->argv[ t->candi[i]]);
			else
				fprintf(stdout, "%s ", t->argv[ t->candi[i]]);
			i++;
		}
	}
	for (int i = t->arg_idx; i < t->argc; i++)
	{
		int k;
		k = atoi(t->argv[i]);
		t->prefix += k;
		t->arg_idx = i + 1;
		t->candi_idx++;
		t->candi[t->candi_idx] = i;
		recurs(t);
		t->prefix -= k;
		t->arg_idx = i - 1;
		t->candi[t->candi_idx] = -1;
		t->candi_idx--;
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
	tt->prefix = 0;
	tt->arg_idx = 2;
	tt->argc = argc;
	tt->argv = argv;
	tt->candi = candikeys;
	tt->prefix = 0;
	recurs(tt);

}