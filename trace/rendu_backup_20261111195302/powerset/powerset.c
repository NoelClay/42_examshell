#include <stdlib.h>
#include <stdio.h>

void	solve(int *src, int *buf, int src_idx, int buf_idx, int size, int target, int prefix)
{
	if (prefix == target)
	{
		for (int i = 0; i < buf_idx; i++)
		{
			if ((i + 1) == buf_idx)
				printf("%d\n", buf[i]);
			else
				printf("%d ", buf[i]);
		}

	}
	for (int i = src_idx; i < size; i++)
	{
		buf[buf_idx] = src[i];
		solve(src, buf, i + 1, buf_idx + 1, size, target, prefix + src[i]);
		buf[buf_idx] = 0;
	}
	return ;
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return 1;

	int	*arr = malloc(sizeof(int) * (argc - 2));

	if (!arr)
		return 1;

	int	arr_size = argc - 2;
	for (int i = 0; i < arr_size; i++)
		arr[i] = atoi(argv[i + 2]);

	int	target = atoi(argv[1]);

	int	*buf = calloc(sizeof(int), arr_size);
	if (!buf)
	{
		free(arr);
		return 1;
	}
	if (target == 0)
		printf("\n");
	solve(arr, buf, 0, 0, arr_size, target, 0);
	free(arr);
	free(buf);
	return (0);
}