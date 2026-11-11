#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

// 스페이스 싹 죽여야됨.
int match_space(FILE *f)
{
	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while ((c = fgetc(f)))
	{
		if (!isspace(c))
			break;
	}
	ungetc(c, f);
	return (1);
}

// 서식지정자가 등장하기 전까지는 문자열 매칭을 체크하기위함
int match_char(FILE *f, char c)
{
	int fc = fgetc(f);
	if (fc == EOF)
		return EOF;
	ungetc(fc, f);

	fc = fgetc(f);
	if (fc != c)
		return (0);
	return (1);
}

int scan_char(FILE *f, va_list ap)
{
	int fc = fgetc(f);
	if (fc == EOF)
		return EOF;
	ungetc(fc, f);

	fc = fgetc(f);
	char	*c = va_arg(ap, char *);
	*c = fc;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int fc = fgetc(f);
	if (fc == EOF)
		return EOF;
	ungetc(fc, f);

	int	*i = va_arg(ap, int *);

	int	res = 0;
	int	cnt = 0;
	while (isdigit(fc = fgetc(f)) && fc != EOF)
	{
		res = res * 10 + (fc - '0');
		cnt++;
	}
	if (fc != EOF)
		ungetc(fc, f);
	if (cnt == 0)
		return (0);
	*i = res;
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
	int i;
	int fc = fgetc(f);
	if (fc == EOF)
		return EOF;
	ungetc(fc, f);

	char	*str = va_arg(ap, char *);
	fc = fgetc(f);
	for (i = 0; !isspace(fc); i++)
	{
		if (fc == EOF)
			break;
		str[i] = fc;
		fc = fgetc(f);
	}
	str[i] = 0;
	if (fc == EOF && i == 0)
		return (EOF);
	ungetc(fc, f);
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
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}

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