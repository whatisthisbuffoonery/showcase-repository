/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:05:28 by achew             #+#    #+#             */
/*   Updated: 2025/11/29 22:58:19 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	size_t				j;
	unsigned char		*dest_ch;
	const unsigned char	*src_ch;

	i = 0;
	j = 0;
	dest_ch = (unsigned char *)dest;
	src_ch = (const unsigned char *)src;
	while (i < n)
	{
		dest_ch[j++] = src_ch[i++];
	}
	return (dest);
}
