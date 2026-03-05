/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:59:40 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/20 00:01:11 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	cmp;

	i = 0;
	cmp = c;
	while (s[i] && s[i] != cmp)
		i ++;
	if (s[i] == cmp)
		return ((char *) &s[i]);
	return (NULL);
}
