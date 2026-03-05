/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:22:42 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/05 18:14:44 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

static void	window_shopping(t_psnode *curr, t_psnode *a, t_psnode *b)
{
	t_psnode	*iter;

	while (a && b)
	{
		if (a->num < b->num)
		{
			curr->next = a;
			a = a->next;
		}
		else
		{
			curr->next = b;
			b = b->next;
		}
		curr = curr->next;
	}
	iter = b;
	if (!b)
		iter = a;
	while (iter)
	{
		curr->next = iter;
		curr = curr->next;
		iter = iter->next;
	}
}

static void	merge_split(t_psnode **head, t_psnode **a, t_psnode **b)
{
	t_psnode	*i;
	t_psnode	*k;

	i = *head;
	k = NULL;
	*a = i;
	if (i)
		k = i->next;
	while (k && k->next)
	{
		i = i->next;
		k = k->next->next;
	}
	if (i)
		*b = i->next;
	if (*b)
		i->next = NULL;
}

static void	merge_sort(t_psnode **head)
{
	t_psnode	*a;
	t_psnode	*b;

	a = NULL;
	b = NULL;
	merge_split(head, &a, &b);
	if (a && a->next)
		merge_sort(&a);
	if (b && b->next)
		merge_sort(&b);
	if (b && a->num > b->num)
	{
		*head = b;
		b = b->next;
	}
	else
	{
		*head = a;
		a = a->next;
	}
	window_shopping(*head, a, b);
}

static void	place_help(t_stack *a, t_psnode *sort, t_psnode *send)
{
	int			i;
	t_psnode	*curr;

	i = 0;
	curr = sort;
	while (curr)
	{
		curr->mark->num = i;
		curr = curr->next;
		i ++;
	}
	curr = send;
	i = 0;
	while (curr)
	{
		a->arr[i] = curr->num;
		curr = curr->next;
		i ++;
	}
	free(send);
}

int	ps_placement(t_stack *a)
{
	int			i;
	int			size;
	t_psnode	*sort;
	t_psnode	*send;

	i = 0;
	size = a->top + 1;
	send = malloc((2 * size) * sizeof(t_psnode));
	if (!send)
		return (1);
	sort = &send[size];
	while (i < size)
	{
		sort[i].next = &sort[i + 1];
		send[i].next = &send[i + 1];
		sort[i].num = a->arr[i];
		sort[i].mark = &send[i];
		i ++;
	}
	sort[size - 1].next = NULL;
	send[size - 1].next = NULL;
	merge_sort(&sort);
	place_help(a, sort, send);
	return (0);
}
