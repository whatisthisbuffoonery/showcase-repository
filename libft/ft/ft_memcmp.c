/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:43:38 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 22:27:49 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*a;
	unsigned char	*b;

	if (!n)
		return (0);
	i = 0;
	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	while (i < n && a[i] == b[i])
		i ++;
	if (i < n)
		return (a[i] - b[i]);
	return (0);
}
