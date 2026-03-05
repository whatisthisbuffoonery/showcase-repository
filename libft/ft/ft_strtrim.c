/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:09:14 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/20 21:47:25 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_substr_help(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ret;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i ++;
	if (start > i)
		len = 0;
	if (start + len >= i)
		len = i - start;
	ret = malloc ((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[i + start];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		k;
	char	table[256];

	i = 0;
	k = 0;
	while (i < 256)
		table[i++] = 0;
	i = 0;
	while (set[i])
		table[(unsigned char) set[i++]] = 1;
	i = 0;
	while (table[(unsigned char) s1[i]])
		i ++;
	while (s1[k])
		k ++;
	k --;
	while (k && table[(unsigned char) s1[k]])
		k --;
	return (ft_substr_help(s1, i, ((k - i) * (s1[i] > 0)) + 1));
}
