/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:09:35 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 01:03:54 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	size_max;
	char	*ret;

	if (!nmemb || !size)
	{
		ret = malloc(0);
		return (ret);
	}
	i = 0;
	size_max = -1;
	i = size_max / size;
	if (nmemb > i)
		return (NULL);
	size *= nmemb;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
		ret[i++] = '\0';
	return ((void *) ret);
}
