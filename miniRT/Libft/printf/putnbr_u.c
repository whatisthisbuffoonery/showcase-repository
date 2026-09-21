/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:22:51 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 03:33:49 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putnbr_u(unsigned int nb, int write_nbr, t_arg *arg)
{
	char	c;
	int		i;

	i = 0;
	if (arg)
		i += add_zero(arg, write_nbr, 0);
	if (arg && nb == 0 && arg->precision == 0)
		return (i);
	if (nb >= 10)
		i += putnbr_u(nb / 10, write_nbr, NULL);
	c = nb % 10 + '0';
	if (write_nbr)
		write(1, &c, 1);
	i++;
	return (i);
}
