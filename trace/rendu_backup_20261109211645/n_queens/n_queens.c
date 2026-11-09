#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	abs(int a)
{
	long	b;

	b = (long)a;
	if (b < 0)
		return (-b);
	return (b);
}

int	is_correct(int *arr, int col, int row)
{
	int k;

	for (int i = 0; i < col; i++)
	{
		if (arr[i] == -1)
			return 0;
		if (arr[i] == row)
			return 0;
		k = abs(col - i);
		if (abs(row - arr[i]) == k)
			return 0;
	}
	return 1;
}

void	recurs(int *arr, int col, int size)
{
	if (col == size)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == size - 1)
				fprintf(stdout, "%d\n", arr[i]);
			else
				fprintf(stdout, "%d ", arr[i]);
		}
	}
	else
	{
		for (int row = 0; row < size; row++)
		{
			if (is_correct(arr, col, row))
			{
				arr[col] = row;
				recurs(arr, col + 1, size);
				arr[col] = -1;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	int	arr_size = atoi(argv[1]);

	if (arr_size == 0)
		return (1);
	int	*arr = malloc(sizeof(int) * arr_size);
	if (!arr)
		return (1);

	for(int i = 0; i < arr_size; i++)
		arr[i] = -1;

	//for(int col = 0; col < arr_size; col++)
	//{
	recurs(arr, 0, arr_size);
	//}
	free(arr);
	return(0);
}