/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msd_radix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:22:45 by dthoo             #+#    #+#             */
/*   Updated: 2026/01/17 12:22:47 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

static int	loop_help(t_stack *a, t_stack *b, int bit, int flag)
{
	int	i;
	int	chunk;

	i = a->top;
	chunk = 0;
	while (i >= 0 && a->top > 2)
	{
		chunk = 0;
		if (!(a->arr[a->top] & bit))
		{
			ps_push(a, b, B);
			if (flag && b->top > 0 && !(b->arr[b->top] & (bit / 2)))
				ps_rotate(a, b, B);
			else if (!flag && b->top > 0 && (b->arr[b->top] & (bit / 2)))
			{
				chunk ++;
				ps_rotate(a, b, B);
			}
		}
		else
			ps_rotate(a, b, A);
		i --;
	}
	return (chunk);
}

void	msd_radix(t_stack *a, t_stack *b, int bit, int runs)
{
	int	flag;
	int	chunk;

	flag = 1;
	while (runs && a->top > 2)
	{
		chunk = loop_help(a, b, bit, flag);
		runs --;
		bit /= 2;
		flag = 0;
		while (chunk)
		{
			chunk --;
			ps_rotate(a, b, B | R);
		}
	}
}
