/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:34:13 by achew             #+#    #+#             */
/*   Updated: 2025/11/30 15:25:27 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char const *src)
{
	int	i;
	int	m;

	i = 0;
	m = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[m] != '\0')
	{
		dest[i] = src[m];
		m++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	get_total_len(char const *s1, char const *s2)
{
	int	total_len;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	return (total_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	total_len = get_total_len(s1, s2);
	joined = malloc(total_len * sizeof(char) + 1);
	if (joined)
	{
		joined[0] = '\0';
		ft_strcat(joined, s1);
		ft_strcat(joined, s2);
	}
	return (joined);
}
