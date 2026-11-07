#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int c;

	while ((c = fgetc(f)) != EOF)
	{
		if (!isspace(c))
		{
			ungetc(c, f);
			break;
		}
	}
	return (0);
}

int match_char(FILE *f, char c)
{
	int fc = fgetc(f);

	if (fc == EOF)
		return (0);
	if (fc == c)
		return (1);
	ungetc(fc, f);
	return (0);
}

int scan_char(FILE *f, va_list ap)
{
	char *pc = va_arg(ap, char *);
	int fc = fgetc(f);

	if (fc == EOF)
		return (0);
	*pc = (char)fc;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int *pi = va_arg(ap, int *);
	int fc;
	int sign = 1;
	int cnt = 0;

	fc = fgetc(f);
	if (fc == EOF)
		return (0);
	if (fc == '+')
		sign = 1;
	else if (fc == '-')
		sign = -1;
	else
		ungetc(fc, f);
	*pi = 0;
	while ((fc = fgetc(f)) != EOF && isdigit(fc))
	{
		*pi = (*pi) * 10 + (fc - '0');
		cnt++;
	}
	if (fc != EOF)
		ungetc(fc, f);
	if (cnt == 0)
		return (0);
	*pi *= sign;
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char *pc = va_arg(ap, char *);
	size_t i = 0;
	int fc;

	while ((fc = fgetc(f)) != EOF && !isspace(fc))
	{
		pc[i] = (char)fc;
		i++;
	}
	if (fc != EOF)
		ungetc(fc, f);
	if (i == 0)
		return (0);
	pc[i] = '\0';
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
	default:
		return (0);
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return (EOF);
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
		return (EOF);
	return (nconv);
}

int ft_scanf(const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);

	return (ret);
}
