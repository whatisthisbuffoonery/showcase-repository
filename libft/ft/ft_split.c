/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:27:59 by dthoo             #+#    #+#             */
/*   Updated: 2026/02/19 17:28:03 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	malloc_wrap(char ***ret, int *count, int *i_ptr)
{
	int	i;

	i = 0;
	*ret = malloc((*count + 1) * sizeof(char *));
	if (!*ret)
		return (1);
	while (i < *count)
		(*ret)[i++] = NULL;
	(*ret)[*count] = NULL;
	*i_ptr = 0;
	*count = 0;
	return (0);
}

char	**split_cleanup(char **ret)
{
	int	i;

	i = 0;
	while (ret && ret[i])
		free(ret[i++]);
	free(ret);
	return (NULL);
}

/*
static void	probe(char *a, int n)
{
	ft_putstr(a);
	ft_putstr(" :");
	ft_putnbr(n);
	write(1, "\n", 1);
}
*/

static int	make_string(char **dst, char const *s, int *i, int c)
{
	int	start;

	*i += (s[*i] == c);
	start = *i;
	while (s[*i] && s[*i] != c)
		*i += 1;
	*dst = ft_substr(s, start, *i - start);
	if (!*dst)
		return (1);
	*i -= 1;
	return (0);
}

int	delimiter_cond(char const *s, char c, int i)
{
	return ((s[i] == c && s[i + 1] && s[i + 1] != c) || (!i && s[i] != c));
}

//paco notes:
//when s is a delimiter-only string, empty string, or NULL,
//a malloc-ed string array with just the terminating null string is returned

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s && s[i])
	{
		if (delimiter_cond(s, c, i))
			k ++;
		i ++;
	}
	if (malloc_wrap(&ret, &k, &i))
		return (NULL);
	while (s && s[i])
	{
		if (delimiter_cond(s, c, i) && make_string(&ret[k++], s, &i, c))
			return (split_cleanup(ret));
		i ++;
	}
	return (ret);
}
