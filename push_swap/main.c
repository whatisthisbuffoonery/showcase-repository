/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:22:37 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/11 19:26:13 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

int	sorted(t_stack *a, t_stack *b)
{
	int	top;
	int	i;

	if (b && b->top != -1)
		return (0);
	top = a->top;
	i = 0;
	while (i < top)
	{
		if (a->arr[i] < a->arr[i + 1])
			return (0);
		i ++;
	}
	return (1);
}

static void	ps_clear(t_stack *a, t_stack *b)
{
	if (a)
		free(a->arr);
	if (b)
		free(b->arr);
	free(a);
	free(b);
}

//5 items capped at 12 moves

void	sort_small(t_stack *a, t_stack *b)
{
	int	min;

	min = 0;
	if (a->top == 1 && a->arr[1] > a->arr[0])
		ps_swap(a, b, A);
	if (a->top < 2)
		return ;
	while (a->top > 2)
		ps_push(a, b, B);
	if (a->arr[1] < a->arr[0])
		min = 1;
	if (a->arr[2] < a->arr[min])
		min = 2;
	if (min == 2)
		ps_rotate(a, b, A);
	else if (min == 1)
		ps_rotate(a, b, A | R);
	if (a->arr[2] > a->arr[1])
	{
		if (b->top > 0 && b->arr[b->top] < b->arr[b->top - 1])
			ps_swap(a, b, A | B);
		else
			ps_swap(a, b, A);
	}
}

void	ps_sort(t_stack *a, t_stack *b, int max)
{
	int		bit_max;

	if (sorted(a, b))
		return ;
	bit_max = 1;
	while (bit_max * 2 <= max)
		bit_max *= 2;
	if (max + 1 >= 5000)
	{
		lsd_radix(a, b, bit_max);
		return ;
	}
	if (max + 1 >= 50)
		msd_radix(a, b, bit_max, 3);
	ps_turk(a, b);
}

int	main(int c, char **v)
{
	t_stack		*a;
	t_stack		*b;

	a = NULL;
	b = NULL;
	if (c < 2)
		return (0);
	ps_write("push_swap");
	if (!init(c - 1, &v[1], &a, &b) && !ps_placement(a))
		ps_sort(a, b, a->top);
	else
		write(2, "Error\n", 6);
	ps_clear(a, b);
}
