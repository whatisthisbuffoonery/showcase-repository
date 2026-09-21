/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:22:51 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 17:22:02 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//#include <unistd.h>
//#include <stdio.h>

int	ft_putnbr(long long nb_ll, int write_nbr, t_arg *arg)
{
	char		c;
	int			i;
	int			sign;

	i = 0;
	sign = 0;
	if (nb_ll < 0)
	{
		if (write_nbr)
			write(1, "-", 1);
		nb_ll *= -1;
		i++;
		sign = 1;
	}
	if (arg)
		i += add_zero(arg, write_nbr, sign);
	if (arg && nb_ll == 0 && arg->precision == 0)
		return (i);
	if (nb_ll >= 10)
		i += ft_putnbr(nb_ll / 10, write_nbr, NULL);
	c = nb_ll % 10 + '0';
	if (write_nbr)
		write(1, &c, 1);
	return (i + 1);
}

//int	main(void)
//{
//	printf(" %d ", ft_putnbr(10));
//	write(1, "\n", 1);
//	printf(" %d ", ft_putnbr(42));
//	write(1, "\n", 1);
//	printf(" %d ", ft_putnbr(-42));
//	write(1, "\n", 1);
//	printf(" %d ", ft_putnbr('a'));
//	write(1, "\n", 1);
//	printf(" %d ", ft_putnbr(-2147483648));
//	write(1, "\n", 1);
//	printf(" %d ", ft_putnbr(0));
//	write(1, "\n", 1);
//	printf(" %d ", ft_putnbr(2147483647));
//}
