/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:22:50 by dthoo             #+#    #+#             */
/*   Updated: 2026/01/18 01:26:07 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

static t_cost	cost_overhead(t_stack *a, t_stack *b, t_cost rr)
{
	t_cost	ret;
	t_cost	rrr;

	rrr.a = rr.a - ps_num(a->top, "correct");
	rrr.b = rr.b - ps_num(b->top, "correct");
	rrr.total = 0 - rrr.a;
	if (rrr.b < rrr.a)
		rrr.total = 0 - rrr.b;
	ret.a = rr.a;
	if (rr.a > ps_num(a->top, "half"))
		ret.a = rrr.a;
	ret.b = rr.b;
	if (rr.b > ps_num(b->top, "half"))
		ret.b = rrr.b;
	ret.total = ps_num(ret.a, "abs") + ps_num(ret.b, "abs");
	if (ret.total > rr.total)
		ret = rr;
	if (ret.total > rrr.total)
		ret = rrr;
	ret.total += 1;
	return (ret);
}

static t_cost	find_cost(t_stack *a, t_stack *b, int src)
{
	t_cost	cost;
	t_iter	iter;

	iter.i = 0;
	iter.min = INT_MAX;
	iter.max = INT_MAX;
	iter.target = 0;
	if (a->top < 1)
		cost.a = 0;
	else
		cost.a = find_a(a, src, iter);
	iter.i = 0;
	iter.min = -1;
	iter.max = -1;
	iter.target = 0;
	if (b->top < 1)
		cost.b = 0;
	else
		cost.b = find_b(b, src, iter);
	cost.total = cost.a;
	if (cost.b > cost.a)
		cost.total = cost.b;
	return (cost_overhead(a, b, cost));
}

static void	ps_rotate_overhead(t_stack *a, t_stack *b, t_cost cost, int mov)
{
	while (cost.a > 0 && cost.b > 0)
	{
		cost.a --;
		cost.b --;
		ps_rotate(a, b, A | B);
	}
	while (cost.a < 0 && cost.b < 0)
	{
		cost.a ++;
		cost.b ++;
		ps_rotate(a, b, A | B | R);
	}
	mov = (cost.a > 0) - (cost.a < 0);
	while (cost.a != 0)
	{
		ps_rotate(a, b, A | (R * (mov < 0)));
		cost.a -= mov;
	}
	mov = (cost.b > 0) - (cost.b < 0);
	while (cost.b != 0)
	{
		ps_rotate(a, b, B | (R * (mov < 0)));
		cost.b -= mov;
	}
}

static void	heuristics(t_stack *a, t_stack *b, t_stack *src)
{
	int		i;
	int		src_num;
	t_cost	tmp;
	t_cost	cost;

	i = 0;
	cost.total = INT_MAX;
	while (i <= src->top)
	{
		src_num = src->arr[src->top - i];
		tmp = find_cost(a, b, src_num);
		if (tmp.total < cost.total)
			cost = tmp;
		src_num = src->arr[i];
		tmp = find_cost(a, b, src_num);
		if (tmp.total < cost.total)
			cost = tmp;
		if (cost.total < i + 1)
			break ;
		i ++;
	}
	if (i)
		ps_rotate_overhead(a, b, cost, 0);
}

void	ps_turk(t_stack *a, t_stack *b)
{
	t_stack	*src;

	src = a;
	while (a->top > 4)
		ps_push(a, b, B);
	if (!sorted(a, 0))
		sort_small(a, b);
	src = b;
	while (b->top >= 0)
	{
		heuristics(a, b, src);
		ps_push(a, b, A);
	}
	ps_finish(a, b);
}
