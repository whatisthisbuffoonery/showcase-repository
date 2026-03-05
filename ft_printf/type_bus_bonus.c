/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bus_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:39 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/11 17:28:41 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printf_atoi(const char *format, int *index)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (format[i] >= '0' && format[i] <= '9')
	{
		a *= 10;
		a += format[i] - '0';
		i ++;
	}
	*index += i;
	return (a);
}

static int	printf_len(t_flags *ret, const char *format)
{
	int	i;

	i = 0;
	if (format[i] >= '0' && format[i] <= '9')
		ret->width = printf_atoi(&format[i], &i);
	if (format[i] == '.')
	{
		ret->precision = printf_atoi(&format[++i], &i);
		ret->precision_set = 1;
		if (ret->minus_zero == '0')
			ret->minus_zero = 0;
	}
	return (i);
}

static int	bus_helper(t_queue *q, t_flags *ret, const char *format, int i)
{
	char	a;

	q->flags = ret;
	a = format[i];
	if (a == '.' || (a >= '0' && a <= '9'))
		i += printf_len(ret, &format[i]);
	q->arg = format[i];
	return (i);
}

static t_flags	*printf_new_flag_node(void)
{
	t_flags	*a;

	a = malloc(sizeof(t_flags));
	if (!a)
		return (NULL);
	a->plus_space = 0;
	a->minus_zero = 0;
	a->hex = 0;
	a->width = 0;
	a->precision = 0;
	a->precision_set = 0;
	return (a);
}

int	type_bus(t_queue *q, const char *format, char *type)
{
	t_flags	*ret;
	int		i;
	char	a;

	i = -1;
	if (!q)
		return (0);
	ret = printf_new_flag_node();
	if (!ret)
		return (0);
	while (!type[(unsigned char) format[++i]])
	{
		a = format[i];
		if (a == '.' || (a >= '1' && a <= '9'))
			break ;
		else if (a == '+' || (a == ' ' && !ret->plus_space))
			ret->plus_space = a;
		else if (a == '-' || (a == '0' && !ret->minus_zero))
			ret->minus_zero = a;
		else if (a == '#')
			ret->hex = '#';
	}
	return (bus_helper(q, ret, format, i));
}
