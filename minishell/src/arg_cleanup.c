/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:47:27 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:47:36 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	free_arg(t_arg *arg)
{
	if (!arg)
		return ;
	free(arg->str);
	free(arg->mask);
	free(arg);
}

t_arg	*free_arg_list(t_arg *head)
{
	t_arg	*next;

	while (head)
	{
		next = head->next;
		free_arg(head);
		head = next;
	}
	return (NULL);
}
