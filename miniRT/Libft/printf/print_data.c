/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:28:36 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 16:21:50 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pad(t_arg arg)
{
	int	dif;
	int	temp;

	dif = arg.min_width - arg.zero_padded_width;
	if (dif <= 0)
		return (0);
	temp = dif;
	while (dif--)
		write(1, " ", 1);
	return (temp);
}

int	print_data(t_arg *arg)
{
	int	len;

	len = 0;
	if ((arg->min_width >= 0) && !(arg->flags & left_justify)
		&& !(arg->flags & zero_padding))
		len += pad(*arg);
	if (arg->type == string)
		len += ft_putstr(arg->data.s, 1, arg);
	else if (arg->type == pointer)
		len += putptr(arg->data.p, 1, arg);
	else if (arg->type == decimal || arg->type == integer)
		len += ft_putnbr(arg->data.d, 1, arg);
	else if (arg->type == unsigned_decimal)
		len += putnbr_u(arg->data.u, 1, arg);
	else if (arg->type == hexadecimal_lower)
		len += puthex_u(arg->data.u, 'l', 1, arg);
	else if (arg->type == hexadecimal_upper)
		len += puthex_u(arg->data.u, 'u', 1, arg);
	else
		len += ft_putchar(arg->data.d, 1);
	if ((arg->min_width >= 0) && (arg->flags & left_justify))
		len += pad(*arg);
	return (len);
}
