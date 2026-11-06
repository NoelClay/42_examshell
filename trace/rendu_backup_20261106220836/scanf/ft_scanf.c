#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	i = 0;
	int c;

	c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (isspace(c = fgetc(f)))
		i++;
	ungetc(c, f);
	return (1);
}

int match_char(FILE *f, char c)
{
	int	fc;

	fc = fgetc(f);
	if (fc == EOF)
		return EOF;
	if (fc == c)
		return (1);
	ungetc(fc, f);
	return (0);
}

int scan_char(FILE *f, va_list ap)
{
	char	*res = va_arg(ap, char *);
	char	c;
	c = fgetc(f);
	if (c == EOF)
		return EOF;
	*res = c;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int	*res = va_arg(ap, int *);
	int	c = fgetc(f);
	int	sign = 1;

	if (c == '+')
		c = fgetc(f);
	else if (c == '-')
	{
		sign = -1;
		c = fgetc(f);
	}
	if (c == EOF)
		return EOF;
	if (!isdigit(c))
	{
		ungetc(c, f);
		return (0);
	}
	*res = 0;
	while (isdigit(c))
	{
		*res = *res * 10 + (c - '0');
		c = fgetc(f);
	}
	ungetc(c, f);
	*res *= sign;
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char	*res = va_arg(ap, char *);
	char	c;
	int		i;

	i = 0;
	c = fgetc(f);
	if (c == EOF)
		return EOF;
	while (c != EOF && !isspace(c))
	{
		res[i] = c;
		i++;
		c = fgetc(f);
	}
	res[i] = 0;
	ungetc(c, f);
	return (1);
}

int match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
	case 'c':
		return scan_char(f, ap);
	case 'd':
		match_space(f);
		return scan_int(f, ap);
	case 's':
		match_space(f);
		return scan_string(f, ap);
	case EOF:
		return -1;
	default:
		return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	// 반환값용
	int nconv = 0;

	// EOF 확인용. 정상이라면 원상복구하고 본래 로직으로
	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	//문자열 끝까지 돌기
	while (*format)
	{
		//% 도달
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		//공백인가?
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		//그것도 아니라면 이게 일단 디폴트이다. %도 아니고 공백도 아니면 무조건 match_char이다. 
		else if (match_char(f, *format) != 1)
			break;
		// 여기서 ++는 왜 하지? matchspace 거나 matchchar를 하고나서 다음으로 가기 위해 ++ 하는거구나
		format++;
	}

	//문자열 다 돌았는데 혹시라도 아니 break를 탈출해서 확인해봤더니 fileerror에 기록된게 있는지를 확인하는건가? fileeroor가 나는 케이스가 있나? break로 탈출하는 상황이 오더라도 file error가 없었더마녀 nconv를 정상 반환하는게 맞는 상황인가?
	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}