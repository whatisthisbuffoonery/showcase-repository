/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:22:48 by dthoo             #+#    #+#             */
/*   Updated: 2026/01/17 12:22:49 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

//top == 2
//mov == 1
//lim == top + 1 = 3
//i == 1
//tmp == arr[1 - 1 = 0]

void	ps_write(char *a)
{
	int			i;
	static int	flag;

	if (!flag)
	{
		flag = 1;
		if (a[0] == 'c')
			flag = -1;
		return ;
	}
	if (flag < 0)
		return ;
	i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
}

static void	rotate_help(t_stack *s, int mov)
{
	int	tmp;
	int	lim;
	int	i;

	if (s->top < 1)
		return ;
	i = s->top - 1;
	lim = -1;
	if (mov > 0)
	{
		lim = s->top + 1;
		i = 1;
	}
	tmp = s->arr[i - mov];
	while (i != lim)
	{
		s->arr[i - mov] = s->arr[i];
		i += mov;
	}
	s->arr[i - mov] = tmp;
}

void	ps_rotate(t_stack *a, t_stack *b, int flag)
{
	int	mov;

	mov = -1;
	if (flag & R)
	{
		mov = 1;
		ps_write("r");
	}
	if (flag & A && flag & B)
		ps_write("rr\n");
	else if (flag & A)
		ps_write("ra\n");
	else if (flag & B)
		ps_write("rb\n");
	if (flag & A && a->top > 0)
		rotate_help(a, mov);
	if (flag & B && b->top > 0)
		rotate_help(b, mov);
}

void	ps_push(t_stack *a, t_stack *b, int flag)
{
	if (flag & A)
		ps_write("pa\n");
	else if (flag & B)
		ps_write("pb\n");
	if (flag & A && b->top >= 0)
	{
		a->top += 1;
		a->arr[a->top] = b->arr[b->top];
		b->top -= 1;
	}
	else if (flag & B && a->top >= 0)
	{
		b->top += 1;
		b->arr[b->top] = a->arr[a->top];
		a->top -= 1;
	}
}

void	ps_swap(t_stack *a, t_stack *b, int flag)
{
	int	tmp;
	int	top;

	if ((flag & A) && (flag & B))
		ps_write("ss\n");
	else if (flag & A)
		ps_write("sa\n");
	else if (flag & B)
		ps_write("sb\n");
	if (flag & A && a->top > 0)
	{
		top = a->top;
		tmp = a->arr[top];
		a->arr[top] = a->arr[top - 1];
		a->arr[top - 1] = tmp;
	}
	if (flag & B && b->top > 0)
	{
		top = b->top;
		tmp = b->arr[top];
		b->arr[top] = b->arr[top - 1];
		b->arr[top - 1] = tmp;
	}
}
