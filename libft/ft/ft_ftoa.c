#include "libft.h"

unsigned int	find_part(float src)
{
	unsigned int	n;
	int				i;

	i = 0;
	n = src * 1000000.0f;
	while (n % 10 == 0 && i++ < 6)
		n /= 10;
	return (n);
}

int	count_num(unsigned int src, char *dst)
{
	int				i;
	char			a;
	unsigned int	t;

	t = 1;
	i = 0;
	while (src / t > 9)
		t *= 10;
	while (t)
	{
		a = ((src / t) % 10) + '0';
		if (dst)
			dst[i] = a;
		i ++;
		t /= 10;
	}
	return (i);
}

//always print at least one digit for both whole and part
char	*ft_ftoa(float src)
{
	unsigned int	whole;
	unsigned int	part;
	char			*ret;
	int				i;

	i = (src < 0);
	if (i)
		src = 0.0f - src;
	whole = (unsigned int) src;
	part = find_part(src - (float) whole);
	ret = malloc(count_num(whole, NULL) + count_num(part, NULL) + i + 2);
	if (!ret)
		return (NULL);
	if (i)
		ret[0] = '-';
	i += count_num(whole, &ret[i]);
	ret[i++] = '.';
	i += count_num(part, &ret[i]);
	ret[i] = '\0';
	return (ret);
}
