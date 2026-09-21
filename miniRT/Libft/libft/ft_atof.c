#include "libft.h"

double ft_atof(char *nptr)
{
	int		i;
	int		sign;
	double	whole;
	double	fractional;
	double	scale;

	i = 0;
	sign = 1;
	whole = 0;
	fractional = 0;
	scale = 1;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		whole = whole * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == '.')
	{
		i++;
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			scale /= 10;
			fractional += (nptr[i] - '0') * scale;
			i++;
		}
	}
	return (sign * (whole + fractional));
}

//#include <stdio.h>
//#include <math.h>
//#include <float.h>
//#include <string.h>
//
//int main(void)
//{
//	double d1 = ft_atof("  a123");
//	printf("%f\n", d1);
//	double d2 = ft_atof("  123");
//	printf("%f\n", d2);
//	double d3 = ft_atof("  123.12345");
//	printf("%f\n", d3);
//	double d4 = ft_atof("  -123.12345");
//	printf("%f\n", d4);
//	double d5 = ft_atof("  123.12.345");
//	printf("%f\n", d5);
//	double d6 = ft_atof("  123.12345a");
//	printf("%f\n", d6);
//
//	double d7 = ft_atof("  -123456789.123456789");
//	printf("%f\n", d7);
//	printf("%d\n", isinf(d7));
//
//	double d8 = ft_atof("  2147483647");
//	printf("%f\n", d8);
//	printf("%d\n", isinf(d8));
//
//	double d9 = ft_atof("  2147483648");
//	printf("%f\n", d9);
//	printf("%d\n", isinf(d9));
//
//	char buffer[310] = {0};
//	snprintf(buffer, sizeof(buffer), "%f", DBL_MAX);
//	double d10 = ft_atof(buffer);
//	printf("%f\n", d10);
//	printf("%d\n", isinf(d10));
//
//	char buffer2[311] = {0};
//	snprintf(buffer2, sizeof(buffer), "%f", DBL_MAX);
//	snprintf(buffer2 + strlen(buffer2), sizeof(buffer2) - strlen(buffer2), "1");
//	double d11 = ft_atof(buffer2);
//	printf("%f\n", d11);
//	printf("%d\n", isinf(d11));
//	return (0);
//}
