/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:09:35 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 21:37:25 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	int		move;
	int		size;
	char	*d;
	char	*s;

	i = 0;
	size = n;
	move = 1;
	d = (char *) dest;
	s = (char *) src;
	if (!dest && !src)
		return (NULL);
	if (d > s)
	{
		move = -1;
		i = size - 1;
		size = -1;
	}
	while (i != size)
	{
		d[i] = s[i];
		i += move;
	}
	return (dest);
}
