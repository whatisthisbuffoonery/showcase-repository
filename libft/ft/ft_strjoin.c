/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:08:38 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/20 00:01:59 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	char	*ret;

	a = 0;
	b = 0;
	while (s1[a])
		a ++;
	while (s2[b])
		b ++;
	ret = malloc((a + b + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	a = -1;
	while (s1[++a])
		ret[a] = s1[a];
	b = -1;
	while (s2[++b])
		ret[a + b] = s2[b];
	ret[a + b] = '\0';
	return (ret);
}
