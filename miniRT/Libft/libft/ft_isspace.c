#include "libft.h"

int ft_isspace(int c)
{
    if (c == ' ' || c == '\n' || c == '\t' || 
        c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}
