/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_zero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:02:36 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 20:28:04 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	sign_force(t_arg *arg, int write_zero, int *added)
{
	if ((arg->type == decimal || arg->type == integer)
		&& (arg->flags & forced_sign) && arg->data.d >= 0)
	{
		if (write_zero)
			write(1, "+", 1);
		added[1] += 1;
	}
	else if ((arg->type == decimal || arg->type == integer)
		&& (arg->flags & forced_space) && arg->data.d >= 0)
	{
		if (write_zero)
			write(1, " ", 1);
		added[1] += 1;
	}
	return (added[1]);
}

static int	change_form(t_arg *arg, int write_zero, int *added)
{
	if ((arg->type == hexadecimal_lower)
		&& (arg->flags & form_change) && (arg->data.u != 0))
	{
		if (write_zero)
			write(1, "0x", 2);
		added[2] += 2;
	}
	else if ((arg->type == hexadecimal_upper)
		&& (arg->flags & form_change) && (arg->data.u != 0))
	{
		if (write_zero)
			write(1, "0X", 2);
		added[2] += 2;
	}
	return (added[2]);
}

static int	pad_zero(t_arg *arg, int write_zero, int sign, int *added)
{
	int	dif;
	int	dif2;

	if (arg->precision >= 0 && (arg->precision + sign > arg->data_width))
	{
		dif = arg->precision + sign - arg->data_width;
		while (dif-- > 0)
		{
			if (write_zero)
				write(1, "0", 1);
			added[0]++;
		}
	}
	else if (arg->min_width >= 0 && (arg->flags & zero_padding)
		&& (arg->min_width > arg->data_width + added[1] + added[2]))
	{
		dif2 = arg->min_width - arg->data_width - added[1] - added[2];
		while (dif2-- > 0)
		{
			if (write_zero)
				write(1, "0", 1);
			added[0]++;
		}
	}
	return (added[0]);
}

int	add_zero(t_arg *arg, int write_zero, int sign)
{
	int	*added;
	int	len_added;

	added = ft_calloc(3, sizeof(int));
	if (!added)
		return (0);
	added[1] = sign_force(arg, write_zero, added);
	added[2] = change_form(arg, write_zero, added);
	added[0] = pad_zero(arg, write_zero, sign, added);
	added[0] += added[1] + added[2];
	len_added = added[0];
	free(added);
	return (len_added);
}
