/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:33:37 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 23:06:16 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		t;
	long	num;
	char	a;

	num = n;
	if (fd < 0)
		return ;
	if (num < 0)
	{
		write(fd, "-", 1);
		num = 0 - num;
	}
	t = 1;
	while (num / t > 9)
		t *= 10;
	while (t)
	{
		a = ((num / t) % 10) + 48;
		write(fd, &a, 1);
		t /= 10;
	}
}
