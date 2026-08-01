/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:09:14 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/11 11:29:32 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_ind(const char *nptr, int *index)
{
	int	i;
	int	a;
	int	flag;

	i = 0;
	a = 0;
	flag = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i ++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			flag = -1;
		i ++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		a *= 10;
		a += nptr[i] - '0';
		i ++;
	}
	*index += i;
	return (a * flag);
}
