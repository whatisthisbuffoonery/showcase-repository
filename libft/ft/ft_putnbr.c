/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:17:35 by dthoo             #+#    #+#             */
/*   Updated: 2026/01/22 17:17:36 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int src)
{
	unsigned int	n;
	unsigned int	t;
	char			a;

	n = src;
	t = 1;
	if (src < 0)
	{
		write(1, "-", 1);
		n = 0 - ((unsigned int) src);
	}
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + '0';
		write(1, &a, 1);
		t /= 10;
	}
}
