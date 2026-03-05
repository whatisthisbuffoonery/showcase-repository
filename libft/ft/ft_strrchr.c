/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:06:04 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/20 00:04:41 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	cmp;

	i = 0;
	cmp = c;
	while (s[i])
		i ++;
	while (i && s[i] != cmp)
		i --;
	if (s[i] == cmp)
		return ((char *) &s[i]);
	return (NULL);
}
