/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_cond.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:54:15 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/05 19:55:18 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*malloc_cond(void **dst, size_t size)
{
	char	*ret;
	size_t	i;

	ret = NULL;
	if (size)
		ret = malloc(size);
	if (dst)
		*dst = ret;
	i = 0;
	while (ret && i < size)
		ret[i++] = 0;
	return (ret);
}
