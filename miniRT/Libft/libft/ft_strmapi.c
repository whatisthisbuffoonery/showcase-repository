/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:53:49 by achew             #+#    #+#             */
/*   Updated: 2025/11/29 20:20:48 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s_dup;
	unsigned int	i;

	s_dup = ft_strdup(s);
	if (s_dup)
	{
		if (!f)
			return (NULL);
		i = 0;
		while (s_dup[i])
		{
			s_dup[i] = f(i, s_dup[i]);
			i++;
		}
	}
	return (s_dup);
}
