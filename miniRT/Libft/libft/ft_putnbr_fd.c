/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:22:51 by achew             #+#    #+#             */
/*   Updated: 2025/11/21 21:05:59 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb_long;
	char	c;

	nb_long = n;
	if (nb_long < 0)
	{
		write(fd, "-", 1);
		nb_long *= -1;
	}
	if (nb_long >= 10)
		ft_putnbr_fd(nb_long / 10, fd);
	c = nb_long % 10 + '0';
	write(fd, &c, 1);
}
