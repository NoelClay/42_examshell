//1. 초기 에러 탈출: 그냥 1리턴으로 끝나는 간단한 조건문

//2. res free 처리를 해줘야되는 상황에서 복잡해지니, free error return 이라는 헬퍼 함수 : helper_error

//3. 표준 입력이 EOF가 뜰때까지 일단 문자열을 온전히 받아내기 : read_full

//4. 인자로 받은 문자열 주소로부터 filter의 길이만큼 matching이 온전히 되는지 검사: match_filter

//5. filter 처리기. 특히 4번을 활용하여 전체를 치환시켜주는 녀석: filter_exec

//6. 실행기 : main
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFF_SIZE 4096

int	helper_free(char *res, int is_sys, char *comment)
{
	int	i;

	if (res != NULL)
		free(res);
	if (is_sys)
	{
		perror("Error: ");
		return (1);
	}
	else
	{
		i = strlen(comment);
		write(2, comment, i);
		return (1);
	}
}

char	*read_full()
{
	ssize_t	rlen;
	size_t	i;
	char	*res;
	char	*tmp;

	res = calloc(BUFF_SIZE + 1, sizeof(char));
	if (res == NULL)
		return (helper_free(res, 1, NULL), NULL);
	i = 0;
	while ((rlen = read(0, res + i, BUFF_SIZE)) != 0)
	{
		if (rlen == -1)
			return (helper_free(res, 1, NULL), NULL);
		i += rlen;
		tmp = realloc(res, i + BUFF_SIZE + 1);
		if (tmp == NULL)
			return (helper_free(res, 1, NULL), NULL);
		res = tmp;
	}
	res[i + 1] = 0;
	return (res);
}

int	match_filter(char *s1, char *s2, size_t s2len)
{
	size_t	s1len;
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	s1len = strlen(s1);
	s2len = strlen(s2);
	if (s1len <= s2len)
		return (-1);
	i = 0;
	while (s1[i] == s2[i])
		i++;
	if (i == s2len)
		return (1);
	return (-1);
}

int	mask_filter(char *s1, char mask, size_t n)
{
	size_t	s1len;
	size_t	i;

	if (!s1)
		return (-1);
	s1len = strlen(s1);
	if (s1len <= n)
		return (-1);
	i = 0;
	while (i < n)
	{
		s1[i] = mask;
		i++;
	}
	return (1);
}

int filter_exec(char *dest, char *target, size_t s2len)
{
	size_t	i;
	int		status;

	if (!dest || !target)
		return (-1);
	i = 0;
	while (dest[i])
	{
		if (dest[i] == target[0])
		{
			status = match_filter(dest + i, target, s2len);
			if (status != -1)
				mask_filter(dest + i, '*', s2len);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	*res;
	int		status;

	if (argc != 2 || argv[1][0] == 0)
		return (1);
	res = read_full();
	if (res == NULL)
		return (1);
	status = filter_exec(res, argv[1], strlen(argv[1]));
	if (status == -1)
		return (helper_free(res, 1, NULL), 1);
	write(1, res, strlen(res));
	free(res);
	return (0);
}