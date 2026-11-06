#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define	SIZE 4096L


//문장 만들기: read, realloc, EOF에 맞춰 널종단 처리, length 처리
int	make_str(char *res, size_t *real_size)
{
	ssize_t	curr_size;

	curr_size = read(0, res + (*real_size), SIZE);
	if (curr_size == -1)
	{
		perror("Error");
		return (-1);
	}
	if (curr_size == 0)
		return (0);
	*real_size += curr_size;
	return (1);
}

int	sub_filter(char *res, char *arg, size_t a_len, size_t start)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (res[start + i] && i < a_len)
	{
		if (res[start + i] != arg[i])
			break;
		i++;
	}
	if (i == a_len)
	{
		j = 0;
		while (j < a_len)
		{
			res[start + j] = '*';
			j++;
		}
		return (1);
	}
	return (-1);
}

//필터처리 로직
int	filter_logic(char *res, char *arg, size_t a_len)
{
	size_t	i;

	i = 0;
	while (res[i])
	{
		if (res[i] == arg[0])
			sub_filter(res, arg, a_len, i);
		i++;
	}
	if (res[i] != 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*res;
	size_t	real_size;
	int		status;
	size_t	alen;

//초기화: 거대한 문자열. 기본 사이즈 일단 4096으로 둘거고 한번에 read 할때마다 계속 4096으로 받을 것이다.
	if (argc != 2 || argv[1][0] == 0)
		return (1);
	real_size = 0;
	res = calloc(SIZE, sizeof(char));
	if (!res)
	{
		perror("Error");
		return (1);
	}
	while ((status = make_str(res, &real_size)) == 1)
	{
		res = realloc(res, real_size + SIZE + 1);
		if (!res)
		{
			perror("Error");
			return (1);
		}
	}
	if (status == -1)
	{
		free(res);
		return (1);
	}
	res[real_size] = 0;
	alen = strlen(argv[1]);
	status = filter_logic(res, argv[1], alen);
	if (status != -1)
	{
		write(1, res, real_size);
		free(res);
		return (0);
	}
	free(res);
	return (1);
}