/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:27:37 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/11 17:27:39 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	prec_help(char *ret, t_queue *q, int n, int index)
{
	int	i;

	if (n || !q->flags || !q->flags->precision_set)
		return (0);
	i = q->flags->width;
	q->flags->precision -= 2 * (q->flags->hex > 0);
	q->flags->precision -= (q->flags->plus_space > 0);
	if (!q->flags->precision)
	{
		ret[index] = ' ';
		if (q->flags->plus_space)
			ret[0] = q->flags->plus_space;
		i += (!i && q->flags->plus_space);
		ret[i] = '\0';
		return (1);
	}
	return (0);
}

int	uint_init(int *i, unsigned long *t)
{
	*i = 1;
	*t = 1;
	return (16);
}

int	uint_help(char *ret, int flag, t_queue *q, int *i)
{
	int		k;
	char	arg;

	if (!ret)
		return (1);
	arg = q->arg;
	if (flag)
	{
		k = 0;
		while (ret[k] == ' ' && k < *i)
			k ++;
		ret[k] = '0';
		ret[k + 1] = 'x';
		if (arg == 'X')
			ret[k + 1] = 'X';
		*i += flag;
	}
	return (0);
}

int	int_help(char *ret, int flag, t_queue *q, int *index)
{
	int	i;
	int	c;
	int	has_sign;

	if (!ret)
		return (1);
	i = 0;
	has_sign = (q->flags && q->flags->plus_space > 0);
	if (flag || has_sign)
	{
		while (i < *index && ret[i] == ' ')
			i ++;
	}
	if (flag)
		ret[i] = '-';
	else if (has_sign)
	{
		c = q->flags->plus_space;
		ret[i] = c;
	}
	if (flag || has_sign)
		*index += 1;
	return (0);
}

int	str_min(char **s, int size, t_queue *q)
{
	if (!*s)
	{
		size = 6;
		*s = "(null)";
		if (q->arg == 'p')
		{
			*s = "(nil)";
			size = 5;
			if (q->flags)
				q->flags->precision_set = 0;
		}
		if (q->flags && q->flags->precision_set && q->flags->precision < size)
			size = 0;
	}
	if (!q->flags)
		return (size);
	if (!q->flags->precision_set || q->flags->precision > size)
		q->flags->precision = size;
	if (size <= q->flags->precision)
		return (size);
	return (q->flags->precision);
}
