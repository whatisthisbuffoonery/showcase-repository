/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:51:16 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 22:29:17 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	unsigned int	i;
	unsigned int	k;
	unsigned int	max;

	i = 0;
	k = 0;
	max = 0;
	while (little[max])
		max ++;
	if (max && !n)
		return (NULL);
	while (big[i + k] && k < max && i + k < n)
	{
		if (big[i + k] == little[k])
		{
			k ++;
			continue ;
		}
		k = 0;
		i ++;
	}
	if (k == max)
		return ((char *) &big[i]);
	return (NULL);
}
