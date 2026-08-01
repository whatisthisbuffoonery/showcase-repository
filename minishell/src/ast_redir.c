/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:08 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:08 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

t_node	*parse_one_redir(t_tok **tok, int *stop)
{
	t_node	*r;

	r = node_new(N_REDIR, stop);
	if (!r)
		return (NULL);
	r->redir_op = subtok(tok, single_tok);
	if (!*tok || !isarg((*tok)->type))
	{
		ft_putstr_fd("syntax error: redirect followed by ", 2);
		if (!*tok)
			ft_putstr_fd("EOF", 2);
		else
			ft_putstr_fd((*tok)->str, 2);
		ft_putstr_fd("\n", 2);
		*stop = 1;
	}
	else
		r->redir_target = subtok(tok, single_tok);
	return (r);
}

t_node	*parse_redir_group(t_tok **tok, int *stop)
{
	t_node	*head;
	t_node	*tail;
	t_node	*r;

	head = NULL;
	tail = NULL;
	while (*tok && !*stop && isredir((*tok)->type))
	{
		r = parse_one_redir(tok, stop);
		if (!head)
			head = r;
		if (tail)
			tail->redir_next = r;
		tail = r;
	}
	return (head);
}

void	redir_append(t_node *dst, t_node *src)
{
	t_node	*iter;

	iter = dst->redir_next;
	while (iter && iter->redir_next)
		iter = iter->redir_next;
	if (!iter)
		dst->redir_next = src;
	else
		iter->redir_next = src;
}
