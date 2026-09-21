/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:41:25 by achew             #+#    #+#             */
/*   Updated: 2025/11/29 22:39:21 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	start_ori;
	size_t	i;
	char	*array;

	if (!s)
		return (NULL);
	size = 0;
	start_ori = start;
	while (start < ft_strlen(s) && (size < len))
	{
		size++;
		start++;
	}
	array = (char *)malloc((size + 1) * sizeof(char));
	if (array)
	{
		i = 0;
		while (i < size)
		{
			array[i++] = s[start_ori++];
		}
		array[i] = '\0';
	}
	return (array);
}
