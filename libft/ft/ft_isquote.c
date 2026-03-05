#include "libft.h"

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return (0);
}
