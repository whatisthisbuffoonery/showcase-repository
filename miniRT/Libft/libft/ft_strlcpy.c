/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:59:00 by achew             #+#    #+#             */
/*   Updated: 2025/11/29 22:59:24 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		i;
	int		m;
	size_t	src_len;

	i = 0;
	m = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (src[m] != '\0' && size-- > 1)
		dst[i++] = src[m++];
	dst[i] = '\0';
	return (src_len);
}
