/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_func.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:11 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/16 22:32:25 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clear_q(t_pf_q **q)
{
	t_pf_q	*f;
	t_pf_q	*tmp;

	f = NULL;
	if (q && *q)
		f = *q;
	while (f)
	{
		tmp = f->next;
		if (f->str)
			free(f->str);
		if (f->flags)
			free (f->flags);
		free(f);
		f = tmp;
	}
	if (q)
		*q = NULL;
}

t_pf_q	*q_new(void)
{
	t_pf_q	*tmp;

	tmp = malloc(sizeof(t_pf_q));
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
	tmp->str = NULL;
	tmp->flags = NULL;
	tmp->arg = '\0';
	tmp->type = nil;
	return (tmp);
}

int	enq(t_pf_q **q, t_pf_q *new)
{
	t_pf_q	*f;

	if (!q)
		return (1);
	if (!new)
	{
		clear_q(q);
		return (1);
	}
	if (!*q)
	{
		*q = new;
		return (0);
	}
	f = *q;
	while (f->next)
		f = f->next;
	f->next = new;
	return (0);
}
