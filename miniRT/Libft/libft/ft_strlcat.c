/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:33:02 by achew             #+#    #+#             */
/*   Updated: 2025/12/03 23:07:01 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	n;
	size_t	oridst_len;

	dst_len = ft_strlen(dst);
	oridst_len = dst_len;
	src_len = ft_strlen(src);
	if (size > oridst_len)
	{
		n = 0;
		while ((size > oridst_len + n + 1) && src[n] != '\0')
			dst[dst_len++] = src[n++];
		dst[dst_len] = '\0';
	}
	else
		oridst_len = size;
	return (oridst_len + src_len);
}
