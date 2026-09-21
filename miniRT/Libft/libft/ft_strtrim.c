/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:27:25 by achew             #+#    #+#             */
/*   Updated: 2025/11/29 22:38:14 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(const char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (is_set(s1[i], set))
	{
		i++;
	}
	return (i);
}

static size_t	get_end(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (is_set(s1[i], set))
	{
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;

	start = get_start(s1, set);
	len = get_end(s1, set) - start + 1;
	return (ft_substr(s1, start, len));
}
