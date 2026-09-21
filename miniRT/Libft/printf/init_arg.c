/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:28:36 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 17:43:26 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_zero_padded_width(t_arg *arg)
{
	if (arg->type == decimal || arg->type == integer)
		arg->zero_padded_width = ft_putnbr(arg->data.d, 0, arg);
	else if (arg->type == character || arg->type == percent)
		arg->zero_padded_width = 1;
	else if (arg->type == string)
		arg->zero_padded_width = ft_putstr(arg->data.s, 0, arg);
	else if (arg->type == pointer)
		arg->zero_padded_width = putptr(arg->data.p, 0, arg);
	else if (arg->type == unsigned_decimal)
		arg->zero_padded_width = putnbr_u(arg->data.u, 0, arg);
	else if (arg->type == hexadecimal_lower || arg->type == hexadecimal_upper)
		arg->zero_padded_width = puthex_u(arg->data.u, 'l', 0, arg);
}

static void	get_data_width(t_arg *arg)
{
	if (arg->type == decimal || arg->type == integer)
		arg->data_width = ft_putnbr(arg->data.d, 0, NULL);
	else if (arg->type == character || arg->type == percent)
		arg->data_width = 1;
	else if (arg->type == string)
		arg->data_width = ft_putstr(arg->data.s, 0, NULL);
	else if (arg->type == pointer)
		arg->data_width = putptr(arg->data.p, 0, NULL);
	else if (arg->type == unsigned_decimal)
		arg->data_width = putnbr_u(arg->data.u, 0, NULL);
	else if (arg->type == hexadecimal_lower || arg->type == hexadecimal_upper)
		arg->data_width = puthex_u(arg->data.u, 'l', 0, NULL);
}

static t_arg	*get_numbers(const char *str, int *fmt_len, t_arg *arg)
{
	if (fmt_len[2])
		arg->min_width = ft_atoi(str + fmt_len[1]);
	else
		arg->min_width = -1;
	if (fmt_len[3])
	{
		if (fmt_len[3] == 1)
			arg->precision = 0;
		else
			arg->precision = ft_atoi(str + fmt_len[1] + fmt_len[2] + 1);
	}
	else
		arg->precision = -1;
	if (arg->type == percent)
	{
		arg->precision = -1;
		arg->min_width = -1;
	}
	return (arg);
}

static t_arg	*get_flags(const char *str, int *fmt_len, t_arg *arg)
{
	arg->flags = no_flags;
	while (fmt_len[1])
	{
		if (*str == '-')
			arg->flags |= left_justify;
		else if (*str == '+')
			arg->flags |= forced_sign;
		else if (*str == ' ')
			arg->flags |= forced_space;
		else if (*str == '0')
			arg->flags |= zero_padding;
		else if (*str == '#')
			arg->flags |= form_change;
		str++;
		fmt_len[1]--;
	}
	if (arg->type == percent)
		arg->flags = no_flags;
	return (arg);
}

t_arg	*init_arg(const char *str, int *fmt_len, va_list ap)
{
	t_arg	*arg;
	char	c;

	arg = malloc(sizeof(t_arg));
	c = *(str + fmt_len[0]);
	arg->type = (t_type)(c);
	if (c == '%')
		arg->data.d = '%';
	else if (c == 's')
		arg->data.s = va_arg(ap, char *);
	else if (c == 'p')
		arg->data.p = va_arg(ap, void *);
	else if (c == 'u' || c == 'x' || c == 'X')
		arg->data.u = va_arg(ap, unsigned int);
	else
		arg->data.d = (long long)va_arg(ap, int);
	arg = get_numbers(str + 1, fmt_len, arg);
	arg = get_flags(str + 1, fmt_len, arg);
	if (arg->precision >= 0 || arg->flags & left_justify
		|| arg->type == character || arg->type == string)
		arg->flags &= ~zero_padding;
	get_data_width(arg);
	get_zero_padded_width(arg);
	return (arg);
}
