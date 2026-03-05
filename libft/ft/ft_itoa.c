/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:11:10 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/25 17:46:03 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	var_help(int *i, long *n, int *t, int *flag)
{
	*t = 1;
	*i = 0;
	*flag = 0;
	if (*n < 0)
	{
		*n = 0 - *n;
		*i = 1;
		*flag = 1;
	}
}

static void	ft_line_shave(int flag, char *ret, int *i)
{
	if (flag)
		ret[0] = '-';
	*i = flag;
}

char	*ft_itoa(int n)
{
	int		t;
	int		i;
	long	num;
	int		flag;
	char	*ret;

	num = n;
	var_help(&i, &num, &t, &flag);
	while (num / t > 9)
	{
		t *= 10;
		i ++;
	}
	ret = malloc((i + 1 + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_line_shave(flag, ret, &i);
	while (t)
	{
		ret[i++] = ((num / t) % 10) + 48;
		t /= 10;
	}
	ret[i] = '\0';
	return (ret);
}
