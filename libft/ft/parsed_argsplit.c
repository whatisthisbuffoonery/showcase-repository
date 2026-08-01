/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_argsplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:32:01 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/25 15:32:03 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	unclosed_check(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			c = s[i++];
			while (s[i] && s[i] != c)
				i ++;
			if (!s[i])
				return (1);
		}
		i ++;
	}
	return (0);
}

//will land on ending sep, or past ending quote
//dst calc only considers skipping first quote
int	pmake_string(char *s, char *ht, char **dst)
{
	int	i;
	int	c;
	int	flag;

	c = ft_isquote(s[0]);
	flag = (c > 0);
	i = flag;
	while (s[i])
	{
		if ((!flag && ht[(unsigned char) s[i]]) || s[i] == c)
			break ;
		i ++;
	}
	if (dst)
		*dst = ft_substr(s, flag, i - flag);
	return (i + flag);
}

char	**parsed_help(char **dst, char *s, char *ht)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (!ht[(unsigned char) s[i]] || ft_isquote(s[i]))
		{
			i += pmake_string(&s[i], ht, &dst[k]);
			if (!dst[k])
				return (split_cleanup(dst));
			k ++;
		}
		else
			i ++;
	}
	return (dst);
}

//"tr a ' a '"
char	**parsed_argsplit(char *s)
{
	int		i;
	int		k;
	char	ht[256];
	char	**ret;

	if (unclosed_check(s))
		return (NULL);
	ht_init(ht, " \t\n\'\"");
	i = 0;
	k = 0;
	while (s[i])
	{
		if (!ht[(unsigned char) s[i]] || ft_isquote(s[i]))
		{
			k ++;
			i += pmake_string(&s[i], ht, NULL);
		}
		else
			i ++;
	}
	if (!k || !malloc_cond((void **) &ret, (k + 1) * sizeof(char *)))
		return (NULL);
	return (parsed_help(ret, s, ht));
}
