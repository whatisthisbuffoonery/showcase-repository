#include "libft.h"

void	*malloc_cond(void **dst, size_t size)
{
	char	*ret;
	size_t	i;

	ret = malloc(size);
	if (dst)
		*dst = ret;
	i = 0;
	while (i < size)
		ret[i++] = 0;
	return (ret);
}
