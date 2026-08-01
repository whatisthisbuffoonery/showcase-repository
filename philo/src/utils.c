/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:43:50 by dthoo             #+#    #+#             */
/*   Updated: 2026/07/28 18:43:50 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

int	ft_atoi(char *s)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (s && s[i])
	{
		a *= 10;
		a += s[i] - '0';
		i ++;
	}
	return (a);
}

void	*ft_memset(void *dst, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *) dst;
	while (i < n)
		ptr[i++] = c;
	return (dst);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dsize)
{
	static _Thread_local size_t	i;
	static _Thread_local size_t	min;
	static _Thread_local size_t	ret;

	ret = 0;
	while (src[ret])
		ret ++;
	if (dsize < 1)
		return (ret);
	min = dsize - 1;
	i = 0;
	while (i < min && i < ret)
	{
		dest[i] = src[i];
		i ++;
	}
	if (dsize > 0)
		dest[i] = '\0';
	return (ret);
}

void	*malloc_cond(void **dst, size_t size)
{
	char	*ret;
	size_t	i;

	ret = NULL;
	if (size)
		ret = malloc(size);
	if (dst)
		*dst = ret;
	i = 0;
	while (ret && i < size)
		ret[i++] = 0;
	return (ret);
}

int	bufnum(char *dst, int src, int size)
{
	static _Thread_local int	i;
	static _Thread_local int	t;

	i = 0;
	t = 1;
	while (src / t > 9)
		t *= 10;
	while (t && i + 1 < size)
	{
		dst[i] = ((src / t) % 10) + '0';
		i ++;
		t /= 10;
	}
	dst[i] = '\0';
	return (i);
}
