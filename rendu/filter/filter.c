/*

입력: 표준 입력으로 문자열을 받고, 인자로는 필터문자열을 받는다.

출력: 표준 출력으로 필터링된 문자열을 출력한다.

제약조건:
Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
realloc, free, printf, fprintf, stdout, stderr, perror

Eorror 출력을 시스템에러가 날때 perror를 할용해서 잘 하고 return 1 해줘야함.

유추

데이터의 크기 같은건 별로 중요하지 않다. 그냥 입력 출력 문제

모듈
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#ifndef BSIZE
#define BSIZE 4096
#endif


int main (int argc, char **argv)
{
	if (argc != 2)
		return (1);
	
	char	*buf = calloc(sizeof(char), BSIZE);
	char	*str = NULL;

	if (!buf)
	{
		perror("Error");
		return (1);
	}
	size_t	slen = 0;
	ssize_t	readlen = 0;
	while ((readlen = read(0, buf, 4096)) != 0)
	{
		
		if (!str)
		{
			slen += (readlen);
			str = calloc(sizeof(char), slen + 1);
			if (!str)
			{
				free(buf);
				perror("Error");
				return (1);
			}
			memmove(str, buf, slen);
			str[slen] = 0;
		}
		else
		{
			str = realloc(str, sizeof(char) * (slen + readlen + 1));
			if (!str)
			{
				free(buf);
				free(str);
				perror("Error");
				return (1);
			}
			memmove(str + slen, buf, readlen);
			str[slen + readlen] = 0;
			slen += readlen;
		}
	}
	for (size_t i=0; i < slen; i++)
	{
		if (str[i] == argv[1][0])
		{
			int flag = 1;
			for (int j = 0; argv[1][j] ; j++)
			{
				if (str[i + j] != argv[1][j])
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				for (int j = 0; argv[1][j] ; j++)
				{
					str[i + j] = '*';
				}
			}
		}
	}
	printf("%s", str);
}