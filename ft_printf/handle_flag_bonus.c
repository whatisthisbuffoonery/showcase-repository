/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flag_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:27:52 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/11 17:27:55 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	muh_max(int a, int b, int c)
{
	if (a < b)
		a = b;
	if (a < c)
		a = c;
	return (a);
}

static char	*handle_flag_init(size_t size, t_queue *q, int *len)
{
	char	a;
	char	*ret;

	a = q->arg;
	*len = size;
	if (q->flags)
	{
		if (a != 'x' && a != 'X')
			q->flags->hex = 0;
		if (a != 'd' && a != 'i')
			q->flags->plus_space = 0;
		if ((a == 'c' || a == 's' || a == 'p') && q->flags->minus_zero == '0')
			q->flags->minus_zero = 0;
		if (a == 'c' || a == 'p')
			q->flags->precision = 0;
		q->flags->precision += 2 * (q->flags->hex > 0);
		q->flags->precision += (q->flags->plus_space > 0);
		*len = muh_max(size, q->flags->precision, q->flags->width);
	}
	ret = malloc((*len + 1) * sizeof(char));
	if (ret)
		ret[*len] = '\0';
	return (ret);
}

int	set_index(int size, int prec, int width, char flag)
{
	int	i;

	if (flag == '-')
		i = prec - size;
	else
		i = muh_max(width, prec, 0) - size;
	if (i < 0)
		i = 0;
	return (i);
}

char	*handle_flag(size_t size, t_queue *q, int *index)
{
	char	*ret;
	int		len;
	int		width;
	int		prec;
	int		start;

	ret = handle_flag_init(size, q, &len);
	if (!ret || !q->flags)
		return ((*index = 0), ret);
	width = q->flags->width;
	prec = q->flags->precision;
	ft_memset(ret, '0', len);
	*index = set_index(size, prec, width, q->flags->minus_zero);
	if (width > muh_max(size, prec, 0) && q->flags->minus_zero != '0')
	{
		start = 0;
		if (q->flags->minus_zero == '-')
			start = muh_max(size, prec, 0);
		width -= muh_max(size, prec, 0) * !start;
		while (start < width)
			ret[start++] = ' ';
	}
	return (ret);
}

int	valid_cond_printf(const char *format, char *type, char *flag, int *index)
{
	int	i;

	i = *index;
	while (flag[(unsigned char) format[i]])
		i ++;
	while (format[i] >= '0' && format[i] <= '9')
		i ++;
	if (format[i] == '.')
	{
		i ++;
		while (format[i] >= '0' && format[i] <= '9')
			i ++;
	}
	*index = i;
	return (type[(unsigned char) format[i]]);
}
