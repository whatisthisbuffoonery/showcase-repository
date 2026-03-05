/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:22:53 by dthoo             #+#    #+#             */
/*   Updated: 2026/01/17 12:22:55 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

void	table_init(unsigned char table[3][256])
{
	int	i;

	i = 0;
	while (i < 256)
	{
		table[0][i] = 0;
		table[1][i] = 0;
		table[2][i] = 0;
		i ++;
	}
	table[0]['r'] = 1;
	table[1]['r'] = 1;
	table[2]['r'] = 1;
	table[0]['p'] = 1;
	table[0]['s'] = 1;
	table[1]['s'] = 1;
	table[1]['a'] = 1;
	table[2]['a'] = 1;
	table[1]['b'] = 1;
	table[2]['b'] = 1;
	table[2]['\n'] = 1;
}

int	ps_alien(unsigned char *in, unsigned char table[3][256])
{
	int	len;

	len = ft_strlen((char *) in);
	if (len < 3 || len > 4 || in[len - 1] != '\n')
		return (1);
	if (!table[0][in[0]] || !table[1][in[1]] || !table[2][in[2]])
		return (1);
	if (len == 4 && (in[0] != 'r' || in[1] != 'r' || in[2] == '\n'))
		return (1);
	if (len == 3 && (in[1] != 'a' && in[1] != 'b' && in[0] != in[1]))
		return (1);
	return (0);
}

void	ps_exec(t_stack *a, t_stack *b, unsigned char *in, int flag)
{
	if (in[0] == in[1] && (in[2] == 'r' || in[2] == '\n'))
		flag |= A | B;
	else if (in[1] == 'a' || in[2] == 'a')
		flag |= A;
	else if (in[1] == 'b' || in[2] == 'b')
		flag |= B;
	if (in[0] == 'r' && in[1] == 'r' && in[2] != '\n')
		flag |= R;
	if (in[0] == 'p')
		ps_push(a, b, flag);
	else if (in[0] == 's')
		ps_swap(a, b, flag);
	else if (in[0] == 'r')
		ps_rotate(a, b, flag);
}
