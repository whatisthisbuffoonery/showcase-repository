#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (ft_strlen(src) < n)
		n = ft_strlen(src);
	ret = malloc(n + 1);
	if (!ret)
		return (NULL);
	while (i < n)
	{
		ret[i] = src[i];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}
