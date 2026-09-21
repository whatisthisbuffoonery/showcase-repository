/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:17:05 by achew             #+#    #+#             */
/*   Updated: 2025/11/30 15:36:10 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	temp;
	char	*big_start;

	if (ft_strlen(little) < 1)
		return ((char *)big);
	i = 0;
	while ((i + ft_strlen(little) <= len) && (big[i]))
	{
		big_start = (char *)&big[i];
		temp = i;
		j = 0;
		while (big[i] && little[j] && big[i] == little[j])
		{
			j++;
			i++;
		}
		if (!little[j])
			return (big_start);
		i = temp + 1;
	}
	return (NULL);
}
