/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:26:27 by achew             #+#    #+#             */
/*   Updated: 2025/11/27 21:06:07 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		*c_s;
	size_t		n;

	n = ft_strlen(s);
	c_s = (char *)s;
	if ((char)c == '\0')
		return (&c_s[n]);
	while (n-- > 0)
	{
		if (c_s[n] == (char)c)
			return ((char *)&c_s[n]);
	}
	return (NULL);
}
