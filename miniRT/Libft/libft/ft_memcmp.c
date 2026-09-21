/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:26:05 by achew             #+#    #+#             */
/*   Updated: 2025/11/29 23:08:04 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*b1;
	const unsigned char	*b2;

	b1 = (const unsigned char *)s1;
	b2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while ((i < n) && (b1[i] == b2[i]))
	{
		i++;
	}
	if (i == n)
		return (0);
	return (b1[i] - b2[i]);
}
