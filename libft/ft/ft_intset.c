#include "libft.h"

void	ft_intset(int *dst, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
		dst[i++] = c;
}
