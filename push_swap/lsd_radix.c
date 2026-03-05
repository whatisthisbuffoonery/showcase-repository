/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsd_radix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:22:29 by dthoo             #+#    #+#             */
/*   Updated: 2026/01/17 12:22:32 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

int	find_max(t_stack *a)
{
	t_iter	iter;

	iter.i = 0;
	iter.max = 0;
	iter.min = 0;
	while (iter.i <= a->top)
	{
		if (iter.max < a->arr[iter.i])
			iter.max = a->arr[iter.i];
		iter.i ++;
	}
	iter.i = 0;
	while (iter.i <= a->top)
	{
		if (iter.max == a->arr[iter.i])
			iter.max --;
		iter.i ++;
	}
	return (iter.max);
}

int	find_min(t_stack *b)
{
	int	i;
	int	min;
	int	top;

	i = 0;
	min = 0;
	top = b->top;
	while (i <= top)
	{
		if (b->arr[i] == min)
			min ++;
		i ++;
	}
	return (min - 1);
}

int	min_rotate(t_stack *a, t_stack *b, int bit)
{
	int	ret;

	if (b->top < 0 || find_min(b) < 0)
		return (0);
	ret = 0;
	while (b->arr[0] != 0 && (a->arr[a->top] & bit && a->arr))
	{
		ret ++;
		ps_rotate(a, b, A | B);
	}
	while (b->arr[0] != 0)
		ps_rotate(a, b, B);
	return (ret);
}

void	push_back_v2(t_stack *a, t_stack *b, int bit)
{
	int	i;
	int	push;
	int	min;

	min = find_min(b) - 1;
	i = b->top;
	push = 0;
	while (i >= 0)
	{
		if (b->arr[i] & bit && b->arr[i] > min)
			push ++;
		i --;
	}
	while (push)
	{
		if (b->arr[b->top] & bit && b->arr[b->top] > min)
		{
			push --;
			ps_push(a, b, A);
		}
		else
			ps_rotate(a, b, B);
	}
}

void	lsd_radix(t_stack *a, t_stack *b, int bit_max)
{
	int	bit;
	int	i;
	int	max;

	bit = 1;
	while (bit <= bit_max && !sorted(a, b))
	{
		i = a->top - min_rotate(a, b, bit);
		max = find_max(a);
		while (i >= 0)
		{
			if (!(a->arr[a->top] & bit) && a->arr[a->top] <= max)
				ps_push(a, b, B);
			else
				ps_rotate(a, b, A);
			i --;
		}
		bit *= 2;
		if (b->top >= 0 && bit <= bit_max)
			push_back_v2(a, b, bit);
	}
	while (b->arr[0] != 0)
		ps_rotate(a, b, B);
	while (b->top >= 0)
		ps_push(a, b, A);
}
