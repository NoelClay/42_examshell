/*
 * EXERCISE: BROKEN_GNL (Get Next Line)
 *
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
 */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int i = 0;

	if (!s)
		return NULL;
	while (s[i])
	{
		if (s[i] == c)
			return s + i;
		i++;
	}
	return NULL;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest || !src || n < 1)
		return dest;
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return dest;
}

size_t	ft_strlen(char *s)
{
	size_t res = 0;

	if (!s)
		return (0);
	while (s[res])
		res++;
	return res;
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	ft_memmove(tmp, *s1, size1);
	ft_memmove(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return 1;
}

int	str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

//dest < src : 그냥 정방향으로 값할당을 하면 올바르게 src가 지워지면서 dest에는 src의 뒷부분이 올바르게 할당된다

//dest > src : 이렇게될때 만약겹치게되면, 예를들어 d[0] = s[0] 했는데 d[1] = s[1] 해보려하니 s[1]이 d[0]인 상황이 발생하여 s[1]이 오염되어 버렸다. 왜? src가 dest보다 왼쪽에 있다보니 그런 것. 그러면 역방향으로 할당해줘야함.  d[n - 1] 부터 할당을 해주면 문제 없음.  
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;

	if (!dest || !src || n < 1)
		return dest;
	s1 = (char *)dest;
	s2 = (char *)src;
	i = 0;
	if (dest < src)
	{
		while(i < n)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	else
	{
		while(i < n)
		{
			s1[n - i - 1] = s2[n - i - 1];
			i++;
		}
	}
	return dest;
}

//8. char *get_next_line(int fd);

//위 도구들을 활용하여 구현해야될 실제 함수인데. main은 아니다. 우리는 함수만 설계한다.

//무조건 전역버퍼 있어야됨.
//전역 버퍼가 비어있다면 아니면으로 분기

//-> 전역 버퍼가 있다.
//거기서 \n을 찾아봐. 
//	-> \n이 없어? -> ret에 전역 버퍼 전체를 붙이고 전역버퍼가 비어있다로 진입
//	-> \n이 있어? -> ret에 그 위치까지 포함해서 붙이고 나머지 정리하고 함수 끝

//-> 전역 버퍼가 비어있다.
//일단 버퍼에 read를 수행.
//거기서 \n을 찾아봐. 
//	-> \n이 없어? -> ret에 전역 버퍼 전체를 붙이고 다시 read
//	-> \n이 있어? -> ret에 그 위치까지 포함해서 붙이고 나머지 정리하고 함수 끝

char	*final_check(char *s)
{
	if (s && s[0])
		return s;
	else
		return (free(s), NULL);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char		*res;
	char		*tmp;
	ssize_t		read_size;

	res = NULL;
	tmp = NULL;
	if (ft_strlen(b) != 0)
	{
		if ((tmp = ft_strchr(b, '\n')))
		{
			if(str_append_mem(&res, b, tmp - b + 1) == 0)
				return NULL;
			else
			{
				ft_memmove(b, tmp + 1, ft_strlen(tmp) - 1);
				b[ft_strlen(tmp) - 1] = 0;
				return (final_check(res));
			}
		}
		else
		{
			if(str_append_str(&res, b) == 0)
				return NULL;
			else
				b[0] = 0;
		}
	}
//-> 전역 버퍼가 비어있다.
//일단 버퍼에 read를 수행.
//거기서 \n을 찾아봐. 
//	-> \n이 없어? -> ret에 전역 버퍼 전체를 붙이고 다시 read
//	-> \n이 있어? -> ret에 그 위치까지 포함해서 붙이고 나머지 정리하고 함수 끝
	while ((read_size = read(fd, b, BUFFER_SIZE)) != 0)
	{
		if (read_size == -1)
			continue;
		b[read_size] = 0;
		if ((tmp = ft_strchr(b, '\n')))
		{
			if(str_append_mem(&res, b, tmp - b + 1))
			{
				ft_memmove(b, tmp + 1, ft_strlen(tmp) - 1);
				b[ft_strlen(tmp) - 1] = 0;
				return (final_check(res));
			}
			else
			{
				if (res)
					free(res);
				return NULL;
			}
		}
		else
		{
			if(str_append_str(&res, b))
				b[0] = 0;
			else
			{
				if (res)
					free(res);
				return NULL;
			}
		}
	}
	if(str_append_str(&res, b))
		return (final_check(res));
	else
	{
		if (res)
			free(res);
		return NULL;
	}
}
