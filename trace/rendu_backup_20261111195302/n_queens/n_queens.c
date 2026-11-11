#include <stdlib.h>
#include <stdio.h>

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return a;
}

int	is_correct(int *arr, int col, int row)
{
	for (int i = 0; i < col; i++)
	{
		if (arr[i] == row)
			return 0;
		int	dx = col - i;
		int	dy = ft_abs(row - arr[i]);
		if (dx == dy)
			return 0;
	}
	return 1;
}

void	solve(int *arr, int col, int size)
{
	if (col == size)
	{
		for (int i = 0; i < size; i++)
		{
			if ((i + 1) == size)
				fprintf(stdout,"%d\n", arr[i]);
			else
				fprintf(stdout, "%d ", arr[i]);
		}
		return ;
	}
	for (int row = 0; row < size; row++)
	{
		if (is_correct(arr, col, row))
		{
			arr[col] = row;
			solve(arr, col + 1, size);
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	int	size = atoi(argv[1]);

	int	*arr = malloc(sizeof(int) * size);
	if (!arr)
		return 1;
	//for (int i = 0; i < size; i++)
	//	arr[i] = -1;
	solve(arr, 0, size);
	free(arr);
}