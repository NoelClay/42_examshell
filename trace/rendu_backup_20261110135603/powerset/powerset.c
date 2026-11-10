#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	recurs(int *candikeys, int argc, char **argv, int pos, int prefix)
{
	int	target = atoi(argv[1]);

	if (prefix == target)
	{
		int	i = 0;
		while (i < argc && candikeys[i] != -1)
		{
			if (candikeys[i + 1] == -1)
				fprintf(1, "%s\n", argv[candikeys[i]]);
			else
				fprintf(1, "%s ", argv[candikeys[i]]);
			i++;
		}
		return ;
	}
	for (int i = pos; i < argc; i++)
	{
		int k;
		k = atoi(argv[i]);
		if ((prefix + k) <= target)
		{
			int	j = 0;
			while (j < argc)
			{
				if (candikeys[j] == -1)
				{
					candikeys[j] = i;
					break;
				}
				j++;
			}
			recurs
		}
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
	
	

}