/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:34 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:34 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//empty src is easy to remove at this stage, but it would be wrong
void	append_new_wrapper(t_arg **head, t_arg **tail, t_arg *src, int assign)
{
	int	i;

	if (assign)
	{
		append_new_field(head, tail, src);
		return ;
	}
	i = 0;
	while (!src->next && src->str[i])
	{
		if (!ft_isspace(src->str[i]) || !src->mask[i])
			break ;
		i ++;
	}
	append_new_field(head, tail, src);
	while (*tail && (*tail)->next)
		*tail = (*tail)->next;
}

int	manage_fields(t_arg **fields, t_arg *arg, t_arg *head, int assign)
{
	if (assign)
	{
		*fields = arg;
		(*fields)->next = NULL;
	}
	else
		*fields = field_split(arg);
	if (*fields != arg)
		free_arg(arg);
	if (!*fields)
	{
		free_arg_list(head);
		return (1);
	}
	return (0);
}

//this will be passed as a handler to expand_all
//split_expand always overwrites arg
//expand_globs always invalidates src
int	collect_argv(t_arg **dst, t_tok *src)
{
	t_arg	*arg;
	t_arg	*fields;
	t_arg	*tail;
	t_arg	*head;

	tail = NULL;
	head = NULL;
	while (src)
	{
		if (split_expand(&arg, src))
			return (1);
		if (manage_fields(&fields, arg, head, src->assignment))
			return (1);
		append_new_wrapper(&head, &tail, fields, src->assignment);
		src = src->next;
	}
	*dst = expand_globs(head);
	return (!*dst);
}

//expand_globs checks fro null src
int	collect_redir(t_arg **dst, t_tok *src)
{
	t_arg	*arg;
	t_arg	*fields;

	if (split_expand(&arg, src))
		return (1);
	fields = field_split(arg);
	if (fields != arg)
		free_arg(arg);
	*dst = expand_globs(fields);
	return (!*dst);
}
