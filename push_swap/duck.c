/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duck.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:20:26 by dthoo             #+#    #+#             */
/*   Updated: 2026/01/18 02:29:06 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

int	ps_num(int n, char *op)
{
	if (op[0] == 'a')
	{
		if (n < 0)
			return (0 - n);
		return (n);
	}
	if (op[0] == 'h')
	{
		if (n < 1)
			return (0);
		return (n / 2);
	}
	if (op[0] == 'c')
	{
		if (n < 1)
			return (0);
		return (n + 1);
	}
	return (0);
}

//max == int max //target
//min == int max //backup
//top of smallest bigger //if not, top of min

int	find_a(t_stack *a, int src, t_iter num)
{
	while (num.i <= a->top)
	{
		num.curr = a->arr[a->top - num.i];
		if (num.curr < num.min)
		{
			num.min = num.curr;
			num.min_cost = num.i;
		}
		if (num.curr < num.max && num.curr >= src)
		{
			num.target = 1;
			num.max = num.curr;
			num.max_cost = num.i;
		}
		if (num.curr == src)
			break ;
		num.i ++;
	}
	if (!num.target)
		return (num.min_cost);
	return (num.max_cost);
}

//max == 0 //backup
//min == 0 //target
//top of biggest smaller //if not, top of max

int	find_b(t_stack *b, int src, t_iter num)
{
	while (num.i <= b->top)
	{
		num.curr = b->arr[b->top - num.i];
		if (num.curr > num.max)
		{
			num.max = num.curr;
			num.max_cost = num.i;
		}
		if (num.curr > num.min && num.curr <= src)
		{
			num.target = 1;
			num.min = num.curr;
			num.min_cost = num.i;
		}
		if (num.curr == src)
			break ;
		num.i ++;
	}
	if (!num.target)
		return (num.max_cost);
	return (num.min_cost);
}

void	ps_finish(t_stack *a, t_stack *b)
{
	int	top;
	int	flag;
	int	i;
	int	*arr;

	arr = a->arr;
	top = a->top;
	i = 0;
	while (arr[i] != 0 && i <= top)
		i ++;
	if (i > top)
		return ;
	flag = A;
	if (i <= top / 2)
		flag |= R;
	while (arr[top] != 0)
		ps_rotate(a, b, flag);
}
