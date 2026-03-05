/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:25:08 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/20 00:02:26 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
{
	size_t	i;
	size_t	k;
	size_t	ret;

	i = 0;
	k = 0;
	ret = 0;
	while (src[ret])
		ret ++;
	while (dest[i] && i < dsize)
		i ++;
	if (i >= dsize)
		return (dsize + ret);
	dsize -= i;
	while (k + 1 < dsize && k < ret)
	{
		dest[i + k] = src[k];
		k ++;
	}
	dest[i + k] = '\0';
	return (ret + i);
}
