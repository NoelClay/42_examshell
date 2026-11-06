#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int i = 0;
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
	size_t	i = 0;

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

	if (!s) return (0);
	while (s[res])
		res++;
	return res;
}


int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);

	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp )
		return 0;
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	if (s2)
		ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return 1;
}

int	str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			((char *)dest)[i] = ((char *)src)[i];
		}
	}
	return dest;
}

// 리드해서 가져와
// 그 길이만큼 버퍼에 저장되어있음. 
char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *res;
	char *tmp;
	int	blen;
	int	rlen;

	res = NULL;
	blen = ft_strlen(b);
	if (blen > 0)
	{
		tmp = ft_strchr(b, '\n');
		if (tmp == NULL) 
		{//\n 이 없었단 소리
			str_append_str(&res, b);
			b[0] = '\0';
		}
		else
		{
			str_append_mem(&res, b, tmp - b + 1);
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
			return (res);
		}
	}
	while ((rlen = read(fd, b, BUFFER_SIZE)) > 0)
	{
		b[rlen] = '\0'; // 1. 읽어온 버퍼 끝 닫기
		tmp = ft_strchr(b, '\n'); // 2. 줄바꿈 찾기
		if (tmp != NULL) // 3. 줄바꿈을 찾았다! -> 방금 쓰신 106~108줄 그대로
		{
			str_append_mem(&res, b, tmp - b + 1);
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
			return (res);
		}
		// 4. 줄바꿈이 없다! -> 방금 쓰신 103줄 그대로 (이어붙이고 다음 read로)
		str_append_str(&res, b);
		b[0] = '\0'; // <- 이 한 줄 추가
	}
	if (res && *res)
		return (res);
	free(res);
	return (NULL);
}
