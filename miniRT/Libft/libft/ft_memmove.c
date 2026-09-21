/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:43:29 by achew             #+#    #+#             */
/*   Updated: 2025/12/01 12:43:02 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ch;
	const unsigned char	*src_ch;

	dest_ch = (unsigned char *)dest;
	src_ch = (const unsigned char *)src;
	if (n == 0 || dest_ch == src_ch)
		return (dest);
	if (dest_ch < src_ch)
	{
		while (n--)
			*dest_ch++ = *src_ch++;
	}
	else
	{
		dest_ch += n;
		src_ch += n;
		while (n--)
			*--dest_ch = *--src_ch;
	}
	return (dest);
}
