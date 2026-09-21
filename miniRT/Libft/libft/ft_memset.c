/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:28:25 by achew             #+#    #+#             */
/*   Updated: 2025/11/27 16:05:05 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	chara;
	unsigned char	*buf;

	chara = (unsigned char)c;
	buf = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		buf[i] = chara;
		i++;
	}
	return (b);
}
