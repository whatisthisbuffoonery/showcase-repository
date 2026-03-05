/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:16:13 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 22:14:40 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	cmp;
	unsigned int	i;

	i = 0;
	cmp = c;
	a = (unsigned char *) s;
	while (i < n && a[i] != cmp)
		i ++;
	if (i < n && a[i] == cmp)
		return ((void *) &a[i]);
	return (NULL);
}
