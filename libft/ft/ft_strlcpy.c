/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:08:59 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 21:49:44 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dsize)
{
	size_t	i;
	size_t	min;
	size_t	ret;

	ret = 0;
	while (src[ret])
		ret ++;
	if (dsize < 1)
		return (ret);
	min = dsize - 1;
	i = 0;
	while (i < min && i < ret)
	{
		dest[i] = src[i];
		i ++;
	}
	if (dsize > 0)
		dest[i] = '\0';
	return (ret);
}
