/*
 * EXERCISE: BROKEN_GNL (Get Next Line)
 *
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
 */

#include "get_next_line.h"

char *ft_strchr(char *s, int c)
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

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	for (size_t i = 0; i < n; i++)
		((char *)dest)[i] = ((char *)src)[i];
	return dest;
}

size_t ft_strlen(char *s)
{
	if (s == NULL)
		return 0;
	size_t res = 0;
	while (s[res])
		res++;
	return res;
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest < src)
		return ft_memcpy(dest, src, n);
	else
	{
		for (size_t i = 1; i <= n; i++)
		{
			((char *)dest)[n - i] = ((char *)src)[n - i];
		}
		return dest;
	}
}

int str_append_mem(char **s1, char *s2, size_t size2)
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

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = NULL;
	ssize_t	readlen = 0;
	//size_t	retlen = 0;

	while ((readlen = read(fd, b, BUFFER_SIZE)) != 0)
	{
		if (readlen == -1)
		{
			if (ret != NULL)
				free(ret);
			return (NULL);
		}
		b[readlen] = 0;
		tmp = ft_strchr(b, '\n');
		if (tmp == NULL)
		{
			if (str_append_str(&ret, b) == 0)
			{
				if (ret != NULL)
					free(ret);
				return (NULL);
			}
		}
		else
		{
			if (str_append_mem(&ret, b, tmp - b + 1) == 0)
			{
				if (ret != NULL)
					free(ret);
				return (NULL);
			}
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1));
		}
	}
	return ret;
}